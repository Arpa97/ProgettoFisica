cmake_minimum_required(VERSION 3.5)

project(gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_compile_definitions(_USE_MATH_DEFINES)
# Inclusione delle directories principali
include_directories(
    ${PROJECT_SOURCE_DIR}/Classi/Include
    ${PROJECT_SOURCE_DIR}/Librerie/Include
    ${PROJECT_SOURCE_DIR}
)
# Compilazione classi/librerie
set(Classi Vertex CiclicVector WaveFront PriorityQueue Fire Fuel Cell Environment)
set(Librerie Rothermel Rothermel2)
add_subdirectory(${PROJECT_SOURCE_DIR}/Librerie)
link_libraries(${Librerie})
add_subdirectory(${PROJECT_SOURCE_DIR}/Classi)

add_executable(gui
main.cpp
mainwindow.cpp
mainwindow.h
mainwindow.ui
resources.qrc)

configure_file(${PROJECT_SOURCE_DIR}/File/FuelTypes.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Classi}
    ${Librerie})
