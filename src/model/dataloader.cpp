#include "dataloader.h"
#include <filesystem>

namespace fs = std::filesystem;

DataLoader::DataLoader(std::string_view dataPath): 
    m_dataPath{dataPath} {
}

void DataLoader::setDataPath(std::string_view path) {
    if (path != m_dataPath) {
        m_dataPath = path;
    }
}

std::string_view DataLoader::getDataPath() const {
    return m_dataPath;
}

std::expected<InputData, ErrorCode> DataLoader::loadData() {
    InputData input;
    fs::path currentPath(m_dataPath);
    if (!fs::is_directory(currentPath)) {
        return std::unexpected(ErrorCode::DIRECTORY_NOT_FOUND);
    }
    for (auto const& img_entry : fs::directory_iterator{currentPath})
    {
        auto path = img_entry.path();
        cv::Mat imgMatrix = cv::imread(path.string());
        // imgMatrix is returned empty when the file format is not supported, 
        // no need for additional format check
        if (imgMatrix.empty()) {
            return std::unexpected(ErrorCode::IMAGE_READ_FAILED);
        }
        input.images.push_back(imgMatrix);
        input.sizeMB += (imgMatrix.total() * imgMatrix.elemSize()) / (1024 * 1024);
    }
    return input;
}
