cmake_minimum_required(VERSION 3.1)
project("TTMunchkinTut" VERSION 1.0.0 LANGUAGES CXX)

# external dependencies
find_package(OpenCV 3 REQUIRED)

# all sources
set(sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/BadThings.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Button.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/CardTypeActions.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/common.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Extras.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/GameState.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/InputEvent.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/MunchkinCards.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ArucoGenerator.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/CameraCalibration.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/DetectionVariants.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/PostProcessFunctions.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/YOLODataGenerator.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/BadThings.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Button.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CardTypeActions.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Extras.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/MunchkinCards.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TTMunchkinTut.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ArucoGenerator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CameraCalibration.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/DetectionVariants.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/PostProcessFunctions.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/YOLODataGenerator.cpp"
)

# executable
add_executable(${CMAKE_PROJECT_NAME}
    ${sources}
)

target_compile_features(${CMAKE_PROJECT_NAME}
    PUBLIC
        cxx_std_17
)

# include directories
target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# enable openmp
find_package(OpenMP)
if(OpenMP_FOUND)
	target_link_libraries(${CMAKE_PROJECT_NAME}
		OpenMP::OpenMP_CXX
	)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${OpenCV_LIBS}
)

# fuer visual studio krams
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source})