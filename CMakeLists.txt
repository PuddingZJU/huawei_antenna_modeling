cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(HuaweiAntennaModeling)
if(WIN32)
	ADD_DEFINITIONS(-DNOMINMAX)
endif()	
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set Include
include_directories(include)
include_directories(./src)
include_directories(./src/Curve)
include_directories(./src/MocapIO)
include_directories(./src/NansyLib)
include_directories(./src/QuasarMath)
include_directories(./src/QuasarMath/Curve)
include_directories(./src/Skinning)
include_directories(./src/Util)
include_directories(ui)
#set source
aux_source_directory(src Main_SRC_LIST)
aux_source_directory(./src/Curve Main_SRC_LIST)
aux_source_directory(./src/MocapIO	Main_SRC_LIST)
aux_source_directory(./src/NansyLib  Main_SRC_LIST)
aux_source_directory(./src/QuasarMath  Main_SRC_LIST)
aux_source_directory(./src/QuasarMath/Curve	Main_SRC_LIST)
aux_source_directory(./src/Skinning	Main_SRC_LIST)
aux_source_directory(./src/Skinning/IO	Main_SRC_LIST)
aux_source_directory(./src/Util	Main_SRC_LIST)
aux_source_directory(ui Main_SRC_LIST)
#add thirdparty mod

#find packages
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
add_executable(AntennaBuilder ${Main_SRC_LIST} ${SandBoxGL_SRC_LIST} ${GUI_MOC} ${GUI_UI} ${GUI_QRC})
#link qt5
target_link_libraries(AntennaBuilder Qt5::Widgets Qt5::OpenGL Qt5::Core Qt5::Gui)
