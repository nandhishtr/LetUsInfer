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
    // Convert from BGR to RGB format as the model requires it
    for (auto const& img : data.images) {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    }
    resize(height, width, data);
    normalize(data, config);
    //TODO: refactor to remove redundant looping. 
    //TODO: right now handling channel split and flatten for one image
    std::vector<cv::Mat> splitDataVector;
    for (auto const& img : data.images) {
        cv::split(img, splitDataVector);
    } 
    std::vector<float> array;
    for (auto const& channel : splitDataVector) {
        array.insert(array.end(), (float*)channel.data, (float*)channel.data + channel.total()*channel.channels());
    }
    return array;
    // return flattenData(splitDataVector);
}