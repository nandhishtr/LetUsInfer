cmake_minimum_required(VERSION 3.21)

project(LetUsInfer VERSION 0.1 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt specific -> needed for MOC, RCC to run automatically
set(CMAKE_AUTOMOC ON)

# Find Qt6 with required modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)

# Find OpenCV 
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Find ONNX Runtime
find_package(onnxruntime REQUIRED)

#Collect source files
set(SOURCES
    src/main.cpp
    src/model/inferenceengine.cpp
    src/model/modelloader.cpp
    src/model/dataloader.cpp
    src/model/preprocessor.cpp
    src/service/inferenceservice.cpp
    src/viewmodel/inferenceviewmodel.cpp
)

qt_add_executable(LetUsInfer ${SOURCES})

qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0001 NEW)

#QML Module
qt_add_qml_module(LetUsInfer
    URI LetUsInfer
    VERSION 1.0
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml/LetUsInfer
    QML_FILES
    qml/Main.qml
    qml/input/InputView.qml
    qml/inference/InferenceView.qml
    qml/output/OutputView.qml
    qml/performance/PerformanceView.qml
    SOURCES include/common/types.h
    SOURCES include/model/dataloader.h include/model/inferenceengine.h include/model/modelloader.h include/model/preprocessor.h
    SOURCES include/service/inferenceservice.h
    SOURCES include/viewmodel/inferenceviewmodel.h
)

# Include directories
target_include_directories(LetUsInfer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/model
    ${CMAKE_CURRENT_SOURCE_DIR}/include/service
    ${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/include/common
    ${VCPKG_ROOT}/installed/arm64-osx/include
)

#Link librariesß
target_link_libraries(LetUsInfer PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    onnxruntime::onnxruntime
    ${OpenCV_LIBS}
)

