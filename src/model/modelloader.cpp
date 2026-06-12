#include "modelloader.h"
#include <filesystem>

std::expected<Ort::Session, ErrorCode> ModelLoader::loadModel(std::string_view modelPath){
    if (!std::filesystem::exists(modelPath)) {
        return std::unexpected(ErrorCode::MODEL_NOT_FOUND);
    }
    try{
        static auto env = Ort::Env{OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "OnnxLetUsInfer"};
        auto sessionOptions = Ort::SessionOptions{};
        return  Ort::Session{env, modelPath.data(), sessionOptions};
    } catch (Ort::Exception& e) {
        return std::unexpected(ErrorCode::MODEL_LOADER_FAIL);
    }
}
