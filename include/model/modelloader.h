#pragma once

#include "types.h"
#include <expected>
#include <onnxruntime_cxx_api.h>

class ModelLoader{

public:
    std::expected<Ort::Session, ErrorCode> loadModel(std::string_view modelPath);
};
