cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(qtcustomplot_online)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(Qt4 REQUIRED)
INCLUDE         (${QT_USE_FILE})
ADD_DEFINITIONS (${QT_DEFINITIONS})

find_package(QCustomPlot REQUIRED)
include_directories(${QCustomPlot_INCLUDE_DIRS})

# Add bin and build dir to include
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_SHARED_LIBRARY_SUFFIX .so)

# Widget
QT4_WRAP_CPP(qtguiapplication_moc src/qtguiapplication.h)
QT4_WRAP_UI(qtguiapplication_ui src/qtguiapplication.ui)
add_library(qtguiapplication SHARED src/qtguiapplication.cpp ${qtguiapplication_moc} ${qtguiapplication_ui})
target_link_libraries(qtguiapplication ${QT_LIBRARIES} ${QCustomPlot_LIBRARIES})

# Qcustomplot example
add_executable(main src/main.cpp)
target_link_libraries(main ${QT_LIBRARIES} qtguiapplication)

