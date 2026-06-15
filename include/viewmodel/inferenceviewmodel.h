#pragma once

#include "inferenceservice.h"
#include <QObject>
#include <QVariant>

class InferenceViewModel : public QObject {

    Q_OBJECT
    Q_PROPERTY(QVariantList tableModel READ tableModel WRITE setTableModel NOTIFY tableModelChanged)

public:
    explicit InferenceViewModel(InferenceService* inferenceService, QObject* parent = nullptr);
    Q_INVOKABLE void setDataPath(const QString path);
    Q_INVOKABLE void setModelPath(const QString path);
    Q_INVOKABLE void setTopK(const int k);
    Q_INVOKABLE void runInference();
    void setTableModel(QVariantList& tableData);
    QVariantList tableModel() const;
signals:
    void tableModelChanged();

private:
    InferenceService* m_inferenceService;
    QVariantList m_tableModel{};
};
