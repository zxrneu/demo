cmake_minimum_required(VERSION 3.10)
project(demo)

# 设置Python优先查找路径
if(DEFINED ENV{CONDA_PREFIX})
    set(Python3_ROOT_DIR $ENV{CONDA_PREFIX})
    set(Python3_FIND_STRATEGY LOCATION)
endif()

# 查找Python组件
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python3_LIBRARIES: ${Python3_LIBRARIES}")
message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Python3_SITELIB: ${Python3_SITELIB}")

# 收集所有源文件
file(GLOB MATH_SOURCES "src/demo/math/*.c")
file(GLOB SORTING_SOURCES "src/demo/sorting/*.c")
file(GLOB SEARCHING_SOURCES "src/demo/searching/*.c")

set(SOURCES 
    src/demo/algoModule.c
    ${MATH_SOURCES}
    ${SORTING_SOURCES}
    ${SEARCHING_SOURCES}
)

# 添加编译定义
add_definitions(-DPY_SSIZE_T_CLEAN)

# 添加Python扩展模块
add_library(demo MODULE ${SOURCES})

# 设置模块属性
set_target_properties(demo PROPERTIES
    PREFIX ""
    SUFFIX ".so"
    C_VISIBILITY_PRESET hidden
    POSITION_INDEPENDENT_CODE ON
)

if(WIN32)
    set_target_properties(demo PROPERTIES SUFFIX ".pyd")
endif()

# 包含目录
target_include_directories(demo PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/demo/include
)

# 链接Python库
target_link_libraries(demo PRIVATE
    ${Python3_LIBRARIES}
)

# 编译选项
target_compile_options(demo PRIVATE 
    -Wall 
    -Wextra 
    -Wno-unused-parameter
    -fPIC
    $<$<CONFIG:Debug>:-g -O0 -DDEBUG>
    $<$<CONFIG:Release>:-O2>
)

# 编译定义
target_compile_definitions(demo PRIVATE 
    PY_SSIZE_T_CLEAN
    VERSION="1.0.0"
)

# 使用 setup.py 安装和卸载
add_custom_target(pip_install
    COMMAND ${Python3_EXECUTABLE} -m pip install .
    DEPENDS demo
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Installing Python package using pip"
)

add_custom_target(pip_uninstall
    COMMAND ${Python3_EXECUTABLE} -m pip uninstall -y demo
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Uninstalling Python package using pip"
)

# 添加一个清理目标（可选）
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/dist
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/demo.egg-info
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/src/demo/__pycache__
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/tests/__pycache__
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Cleaning all build files"
)

# 添加测试
enable_testing()
add_test(
    NAME python_tests
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tests/test.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# 添加卸载目标
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
    )

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    )
endif()