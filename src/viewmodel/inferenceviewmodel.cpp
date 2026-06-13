#include "inferenceviewmodel.h"    
    
InferenceViewModel::InferenceViewModel(InferenceService* inferenceService, 
        QObject* parent) {
    m_inferenceService = inferenceService;
}
