#pragma once

#include "types.h"

class DataLoader {
    std::string m_dataPath{};
    InputData m_data;

public:
    void setDataPath(std::string_view path);
    std::string_view getDataPath();
    InputData loadData();

};
