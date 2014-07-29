cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(HuaweiAntennaModeling)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set Include
include_directories(include)
include_directories(ui)
#set source
aux_source_directory(src Main_SRC_LIST)
aux_source_directory(ui Main_SRC_LIST)
#set Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
#set Qt5 file
file(GLOB_RECURSE GUI_H    "uis/*.h"   )
file(GLOB_RECURSE GUI_CPP  "uis/*.cpp" )
file(GLOB_RECURSE GUI_UI   "uis/*.ui"  )
file(GLOB_RECURSE GUI_QRC  "uis/*.qrc" )
qt5_wrap_ui(GUI_H ${GUI_UI})
qt5_add_resources(GUI_QRC ${GUI_QRC})
#source groups
#add executable
add_executable(AntennaBuilder ${Main_SRC_LIST} ${GUI_MOC} ${GUI_UI} ${GUI_QRC})
#link qt5
target_link_libraries(AntennaBuilder Qt5::Widgets Qt5::OpenGL Qt5::Core Qt5::Gui)
