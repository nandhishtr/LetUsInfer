#pragma once

#include "types.h"

class PreProcessor{

private:
    bool cropToSize(const int height, const int width, InputData& data);
    bool normalize(InputData& data);
    std::vector<float> flattenData(const InputData& data);

public:
    std::vector<float> preprocess(const InputData& data);

};
