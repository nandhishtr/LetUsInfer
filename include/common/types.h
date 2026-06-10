#ifndef LETUSINFER_TYPES_H
#define LETUSINFER_TYPES_H

#include <QString>
#include <opencv2/opencv.hpp>

enum class ErrorCode {
    MODEL_NOT_FOUND,
    IMAGE_CORRUPT,
    INFERENCE_CRASHED,
    NO_OUTPUT,
    INVALID_OUTPUT,
    NO_PERFORMANCE_DATA,
    INVALID_PERFORMANCE_DATA,
    PRE_PROCESS_FAILED,
    MEMORY_LIMIT_HIT,
    DATA_LOADER_FAIL,
    MODEL_LOADER_FAIL
};

enum class ModelType {
    CLASSIFIER,
    OBJECT_DETECTOR,
    SEGMENTATION
};

struct InferenceConfig {
    QString modelPath;
    ModelType modelType;
    bool parallelExecution;
    int topK;
    QString dataPath;
};

struct TopKResult {
    QString label;
    float confidenceScore;
    int rank;
    int classIndex;
};

enum class InferenceStatus {
    IDLE,
    PROCESSING,
    FAILURE,
    FINISH
};

struct OutputData {
    std::vector<TopKResult> inferenceOutputs;
    float inferenceTimeMs;
    float preprocessTimeMs;
    float throughputImgPerSec;
    float memoryUsageMB;
};

struct InputData {
    std::vector<cv::Mat> images;
    float sizeMB;
};

#endif // LETUSINFER_TYPES_H
