#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "inferenceservice.h"
#include "inferenceviewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    InferenceConfig config;
    config.normalizedMean = {0.485f, 0.456f, 0.406f};
    config.normalizedStd = {0.229f, 0.224f, 0.225f};
    std::unique_ptr<InferenceService> inferenceService = std::make_unique<InferenceService>(config);
    std::unique_ptr<InferenceViewModel> inferenceViewModel = std::make_unique<InferenceViewModel>(inferenceService.get());

    engine.rootContext()->setContextProperty("InferenceViewModel", inferenceViewModel.get());
    engine.loadFromModule("LetUsInfer", "Main");

    return app.exec();
}
