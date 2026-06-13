#include "inferenceservice.h"


InferenceService::InferenceService(const InferenceConfig& config) {
    m_dataLoader = std::make_unique<DataLoader>(config.dataPath);
    m_preProcessor = std::make_unique<PreProcessor>();
    m_modelLoader = std::make_unique<ModelLoader>(config.modelPath);
    m_inferenceEngine = std::make_unique<InferenceEngine>(config.labelPath);
    m_currentConfig = config;
}

std::expected<OutputData, ErrorCode> InferenceService::runInference() {
    auto inputData = m_dataLoader->loadData();
    if (!inputData.has_value()) {
        std::cout << "Data load failed: " << static_cast<int>(inputData.error()) << std::endl;
        return std::unexpected(inputData.error());
    }
    auto modelSession = m_modelLoader->loadModel();
    if (!modelSession.has_value()) {
        std::cout << "Model load failed: " << static_cast<int>(modelSession.error()) << std::endl;
        return std::unexpected(modelSession.error());
    }
    auto preProcessedData = m_preProcessor->preprocess(inputData.value(), m_currentConfig);
    auto outputData = m_inferenceEngine->forwardPass(preProcessedData, 
                                            modelSession.value(), m_currentConfig);
    if (!outputData.has_value()) {
        std::cout << "Forward pass failed: " << static_cast<int>(outputData.error()) << std::endl;
        return std::unexpected(outputData.error());
    }
    return outputData;
}