#####################################
# WEngine 工程编译配置信息
#
# 一般由主CMakeLists.txt引用,
# 如果某个模块需要支持完全独立编译，
# 可通过include本文件获取编译配置信息
#####################################

if (W_USE_OPTION)
    return()
endif ()
set(W_USE_OPTION ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if (APPLE)
    set(CMAKE_CXX_FLAGS "-ObjC++ --std=c++17")
else ()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

if (NOT CMAKE_SIZEOF_VOID_P)
    if (CMAKE_CL_64)
        set(CMAKE_SIZEOF_VOID_P 8)
    else ()
        set(CMAKE_SIZEOF_VOID_P 4)
    endif ()
endif ()

# options
set(BUILD_MODE_PLUG ON)   ## 构造模式为Plug模式

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_DEBUG_POSTFIX "")

if (CMAKE_SYSTEM_NAME MATCHES "Windows" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(BUILD_IN_STATIC OFF)
else ()
    set(BUILD_IN_STATIC ON)
    set(PLUG_USE_RAW ON)
endif ()

if (BUILD_MODE_PLUG)
    add_definitions(-DW_USE_PLUG_DEV)

    if (PLUG_USE_RAW)
        add_definitions(-Duse_raw_shared_memory)
    endif ()
endif ()

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_C_FLAGS "-fPIC ${CMAKE_C_FLAGS}")

    if (BUILD_MODE_PLUG)
        set(PLUG_MODE_BOOST_SM ON)
        add_definitions(-Dboost_shared_memory)
    endif ()
endif ()
