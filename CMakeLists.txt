cmake_minimum_required(VERSION 3.19)
project(WEngine)

# 项目编译配置选项
include(cmake/option.cmake)

if (BUILD_MODE_PLUG)
    set(T_LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
else ()
    set(T_LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/BinTrd)
endif ()


#add_subdirectory(3part/SDL2)

#ToolLibs
#add_subdirectory(ToolLibs)

#GpuLink
#add_subdirectory(GpuLink)

#WellLight
#add_subdirectory(WellLight)

# Example

add_subdirectory(SoftRenderer)
