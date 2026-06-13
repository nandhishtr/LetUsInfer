#pragma once

#include "types.h"
#include <expected>

class DataLoader {

public:
    DataLoader(std::string_view dataPath);
    void setDataPath(std::string_view path);
    std::string_view getDataPath() const;
    std::expected<InputData, ErrorCode> loadData();

private:
    std::string m_dataPath{};
    InputData m_data;
};
