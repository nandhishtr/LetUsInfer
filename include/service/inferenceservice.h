#ifndef INFERENCESERVICE_H
#define INFERENCESERVICE_H

#include <expected>
#include "dataloader.h"
#include "modelloader.h"
#include "preprocessor.h"
#include "inferenceengine.h"

class InferenceService {
    
    public:
        InferenceService(const InferenceConfig& config);
        std::expected<OutputData, ErrorCode> runInference();

    private:
        std::unique_ptr<DataLoader> m_dataLoader = nullptr;
        std::unique_ptr<PreProcessor> m_preProcessor = nullptr;
        std::unique_ptr<ModelLoader> m_modelLoader = nullptr;
        std::unique_ptr<InferenceEngine> m_inferenceEngine = nullptr;
        InferenceConfig m_currentConfig;
};

#endif
