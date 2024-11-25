cmake_minimum_required(VERSION 3.22)

project(CUSTOM_USER_FILTER)

include(CMakePrintHelpers)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the source directory
set(AVEXECUTOR_DIR "/home/mk6554/Downloads/avexecutor")
set(AVEXECUTOR_DIR_LIB_DIR "${AVEXECUTOR_DIR}/lib/x86_64-linux-gnu/")

# Define the executable name
set(OUT_LIB_FILE "UserFilter")

set(SRC_DIR "../sources")
set(HEAD_DIR "../headers")

# Collect all .cpp files in the src directory
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

# Optionally, include header files for IDEs
file(GLOB_RECURSE HEADER_FILES "${HEAD_DIR}/*.h")

# Find the AVL package
find_package(
    AVL
    # for a specific version, uncomment the line below
    #5.3
    CONFIG
    REQUIRED
)

# copy binaries to build directory
#copy_avl()

# Include directories for headers
include_directories(${HEAD_DIR})
include_directories(${AVL_INCLUDE_DIRS}) # Assuming AVL_INCLUDE_DIRS is set by find_package

#file(GLOB_RECURSE AVEXECUTOR_LIBS "${AVEXECUTOR_DIR_LIB_DIR}/*.so")

#cmake_print_variables(AVEXECUTOR_LIBS)
#target_link_libraries(${OUT_LIB_FILE} SHARED 
#/home/mk6554/Downloads/avexecutor/lib/x86_64-linux-gnu/libAVL_Lite.so
#)


# Add the shared library
add_library(${OUT_LIB_FILE} SHARED ${SRC_FILES})

# Link the AVL library
#target_link_libraries(${OUT_LIB_FILE} PRIVATE ${AVEXECUTOR_DIR_LIB_DIR})


# Install headers
install(FILES ${HEADER_FILES} DESTINATION include/${OUT_LIB_FILE})


# Add a custom target for cleaning up
add_custom_target(clear
    COMMENT "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/CMakeFiles"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/CMakeCache.txt"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/cmake_install.cmake"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/Makefile"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/${EXECUTABLE_FILE}"

    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/*.so"
    COMMENT "Removing CMake-generated files and the executable"
)