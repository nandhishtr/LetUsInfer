#pragma once

#include "types.h"

class PreProcessor{

private:
    void resize(const int height, const int width, InputData& data);
    bool normalize(InputData& data, const InferenceConfig& config);
    std::vector<float> flattenData(const InputData& data);

public:
    std::vector<float> preprocess(InputData& data, const InferenceConfig& config);

};
