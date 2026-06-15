#include "inferenceviewmodel.h"    

InferenceViewModel::InferenceViewModel(InferenceService* inferenceService, 
        QObject* parent) {
    m_inferenceService = inferenceService;
}

void InferenceViewModel::setDataPath(const QString path) {
    m_inferenceService->setDataPath(path.toStdString());
    std::cout << "setDataPath: "<< path.toStdString() << std::endl;

}
void InferenceViewModel::setModelPath(const QString path) {
    m_inferenceService->setModelPath(path.toStdString());
    std::cout << "setModelPath: " << path.toStdString() << std::endl;

}
void InferenceViewModel::setTopK(const int k){
    m_inferenceService->setTopK(k);
    std::cout << "setTopK: "<< k << std::endl;
}

void InferenceViewModel::runInference() {
    std::cout << "Running Inference" << std::endl;
    auto output = m_inferenceService->runInference();
    if (!output.has_value()) {
        std::cout << " Run Inference Failed: " << static_cast<int>(output.error()) << std::endl;
        return;
    }
    auto topKResults = output.value().inferenceOutputs;
    QVariantList outputTable;
    for (const auto& result : topKResults) {
        QVariantMap data;
        data["Rank"] = result.rank;
        data["Confidence"] = result.confidenceScore;
        data["Label"] = QString::fromStdString(result.label);
        outputTable.append(data);
    }
    setTableModel(outputTable);
}

void InferenceViewModel::setTableModel(QVariantList& tableData) {
    m_tableModel = tableData;
    emit tableModelChanged();
}

QVariantList InferenceViewModel::tableModel() const {
    return m_tableModel;
}