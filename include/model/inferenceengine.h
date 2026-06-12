#ifndef INFERENCEENGINE_H
#define INFERENCEENGINE_H

#include "preprocessor.h"
#include "modelloader.h"
#include "types.h"

class InferenceEngine{

    public:
        InferenceEngine(std::string_view labelPath);
        std::expected<OutputData,ErrorCode> forwardPass(std::vector<float>& data, 
                            Ort::Session& model, const InferenceConfig& config);
    private:
        std::expected<void, ErrorCode> loadLabels(std::string_view labelPath);
        std::vector<std::string> m_classLabels;
};

#endif
