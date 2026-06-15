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

void InferenceService::setDataPath(const std::string_view path) {
    if (path != m_currentConfig.dataPath) {
        m_currentConfig.dataPath = path;
        m_dataLoader->setDataPath(m_currentConfig.dataPath);
    }
}
void InferenceService::setModelPath(const std::string_view path) {
    if (path != m_currentConfig.modelPath) {
        m_currentConfig.modelPath = path;
        m_modelLoader->setModelPath(m_currentConfig.modelPath);
    }
}
void InferenceService::setTopK(const int& k) {
    if (k != m_currentConfig.topK) {
        m_currentConfig.topK = k;
    }
}

std::string InferenceService::getClassLabelFromIndex(const int& index) {
    return m_inferenceEngine->getClassLabels().at(index);
}

