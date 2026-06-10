#pragma once

#include "inferenceservice.h"
#include <QObject>

class InferenceViewModel : public QObject {

    Q_OBJECT

public:
    explicit InferenceViewModel(InferenceService* inferenceService, QObject* parent = nullptr);

private:
    InferenceService* m_inferenceService;
};
