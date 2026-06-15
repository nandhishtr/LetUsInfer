#include "modelloader.h"
#include <filesystem>

ModelLoader::ModelLoader(std::string_view modelPath): 
    m_modelPath{modelPath} {
}

void ModelLoader::setModelPath(std::string_view modelPath) {
    if (modelPath != m_modelPath) {
        m_modelPath = modelPath;
    }
}

std::string_view ModelLoader::getModelPath() const {
    return m_modelPath;
}

std::expected<Ort::Session, ErrorCode> ModelLoader::loadModel(){
    if (!std::filesystem::exists(m_modelPath)) {
        return std::unexpected(ErrorCode::MODEL_NOT_FOUND);
    }
    try{
        setenv("ORT_DISABLE_ORT_OPERATOR_SCHEMA", "1", 1);
        static auto env = Ort::Env{OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "OnnxLetUsInfer"};
        auto sessionOptions = Ort::SessionOptions{};
        sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_DISABLE_ALL);
        return  Ort::Session{env, m_modelPath.data(), sessionOptions};
    } catch (Ort::Exception& e) {
        std::cout << "Model Loader failed: " << e.what() << std::endl;
        return std::unexpected(ErrorCode::MODEL_LOADER_FAIL);
    }
}
