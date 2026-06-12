#include "preprocessor.h"


void PreProcessor::resize(const int height, const int width, InputData& data) {
    for (auto& img : data.images) {
        cv::resize(img, img, cv::Size(width, height));
    }
}

bool PreProcessor::normalize(InputData& data, const InferenceConfig& config) {
    if (!(config.normalizedStd[0] && config.normalizedStd[1] && config.normalizedStd[2])) {
        // invalid std config, leads to division by zero
        return false;
    }
    for (auto& img : data.images) {
        img.convertTo(img, CV_32F);
        img = img / 255.0;
        img -= cv::Scalar(config.normalizedMean[0], config.normalizedMean[1], config.normalizedMean[2]);
        img /= cv::Scalar(config.normalizedStd[0], config.normalizedStd[1], config.normalizedStd[2]); 
    }
    return true;
}

std::vector<float> PreProcessor::flattenData(const InputData& data) {
    std::vector<float> array;
    for (auto const& img : data.images) {
        array.insert(array.end(), (float*)img.data, (float*)img.data + img.total()*img.channels());
    }
    return array;
}

std::vector<float> PreProcessor::preprocess(InputData& data, const InferenceConfig& config) {
    int height = config.inputDimensions.first;
    int width = config.inputDimensions.second;
    resize(height, width, data);
    normalize(data, config);
    return flattenData(data);
}