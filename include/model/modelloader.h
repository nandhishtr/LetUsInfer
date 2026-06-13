#pragma once

#include "types.h"
#include <expected>
#include <onnxruntime/onnxruntime_cxx_api.h>

class ModelLoader{
    
public:
    ModelLoader(std::string_view modelPath);
    std::expected<Ort::Session, ErrorCode> loadModel();
    void setModelPath(std::string_view modelPath);
    std::string_view getModelPath() const;
private:
    std::string m_modelPath{};
};
