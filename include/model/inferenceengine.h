#ifndef INFERENCEENGINE_H
#define INFERENCEENGINE_H

#include "preprocessor.h"
#include "modelloader.h"
#include "types.h"

class InferenceEngine{

    public:
        std::expected<OutputData,ErrorCode> forwardPass(const std::vector<float>& data, const Ort::Session& model);
};

#endif
