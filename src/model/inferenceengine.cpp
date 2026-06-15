#include "inferenceengine.h"       
#include <expected>
#include <filesystem>
#include <fstream>

InferenceEngine::InferenceEngine(std::string_view labelPath) {
    auto result = loadLabels(labelPath);
    if(!result) {
        std::cout << "Error: " << static_cast<int>(result.error()) << std::endl;
    }
}

std::expected<OutputData,ErrorCode> InferenceEngine::forwardPass(
        std::vector<float>& data, Ort::Session& model, const InferenceConfig& config) {

    try {
    auto memoryInfo = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtDeviceAllocator, 
                        OrtMemType::OrtMemTypeCPU);
    std::vector<int64_t> mobileNetV2Shape{1, 3, 224, 224};

    auto dataTensor = Ort::Value::CreateTensor<float>(memoryInfo, data.data(), data.size(), 
                        mobileNetV2Shape.data(), mobileNetV2Shape.size());
    auto allocator = Ort::AllocatorWithDefaultOptions{};
    auto inputNames = model.GetInputNameAllocated(0, allocator);
    const char* inputNamesPtr = inputNames.get();
    auto outputNames = model.GetOutputNameAllocated(0, allocator);
    const char* outputNamesPtr = outputNames.get();
    std::vector<Ort::Value> outputTensor = model.Run(Ort::RunOptions{nullptr}, 
                                            &inputNamesPtr, &dataTensor, 1, &outputNamesPtr, 1);
    OutputData finalOutput;
    // We only do it for one image with outputTensor[0] for v0.1
    auto outPtr = outputTensor[0].GetTensorData<float>();
    // From raw pointer, we store the index and Score in a vector to sort
    std::vector<std::pair<float, int>> outVec;
    for (int i{}; i < m_classLabels.size(); i++) {
        outVec.push_back(std::make_pair(*outPtr, i));
        outPtr++;
    }
    // We get 1000 class labels with scores. these need to be sorted to fetch topK
    std::sort(outVec.begin(), outVec.end(), 
    [] (std::pair<float, int> left, std::pair<float, int> right) {
        return left.first > right.first;
    });
    for (int i{}; i < config.topK; i++) {
        TopKResult topKResult;
        topKResult.classIndex = outVec[i].second;
        topKResult.confidenceScore = outVec[i].first;
        topKResult.label = m_classLabels[topKResult.classIndex];
        topKResult.rank = i + 1;
        finalOutput.inferenceOutputs.push_back(topKResult);
    }
    return finalOutput;
    } catch (Ort::Exception& e) {
        return std::unexpected(ErrorCode::FORWARD_PASS_FAILED);
    }
}

std::expected<void, ErrorCode> InferenceEngine::loadLabels(std::string_view labelPath) {
    if (!std::filesystem::exists(labelPath)) {
        return std::unexpected(ErrorCode::LABELS_NOT_FOUND);
    }
    std::ifstream istrm(labelPath.data(), std::ios::binary);
    if (!istrm.is_open()) {
        return std::unexpected(ErrorCode::LABELS_ACCESS_ISSUE);
    }
    else
    {
        std::string label;  
        while (getline(istrm, label)) {
            m_classLabels.push_back(label);
        }                              
    }
    return {};
}

std::vector<std::string> InferenceEngine::getClassLabels() const {
    return m_classLabels;
}
