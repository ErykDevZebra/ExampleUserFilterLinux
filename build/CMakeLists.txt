cmake_minimum_required(VERSION 3.16)

# Define the project name and specify the required C++ standard
project(UserFilterLibrary)

# Specify the version (optional)
set(PROJECT_VERSION 1.0)

# Set the C++ standard for the project (you can change this if needed)
set(CMAKE_CXX_STANDARD 17)

# Specify the source directory
set(AVEXECUTOR_DIR "/etc/avexecutor/")

message(STATUS "AVExecutor path: ${AVEXECUTOR_DIR}")
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64" OR CMAKE_GENERATOR_PLATFORM MATCHES "AMD64")
	message(STATUS "Building for ${CMAKE_SYSTEM_PROCESSOR} platform")
	set(AVEXECUTOR_DIR_LIB_DIR "${AVEXECUTOR_DIR}lib/x86_64-linux-gnu/")

elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i[3-6]86 " OR CMAKE_GENERATOR_PLATFORM MATCHES "x86")
	message(STATUS "Building for ${CMAKE_SYSTEM_PROCESSOR} platform")
	set(AVEXECUTOR_DIR_LIB_DIR "${AVEXECUTOR_DIR}lib/x86_64-linux-gnu//")

elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
	message(STATUS "Building for ${CMAKE_SYSTEM_PROCESSOR} platform")
	set(AVEXECUTOR_DIR_LIB_DIR "${AVEXECUTOR_DIR}lib/aarch64-linux-gnu/")
else()
	message(WARNING "Unsuported platform: ${CMAKE_SYSTEM_PROCESSOR}")
	set(AVEXECUTOR_DIR_LIB_DIR "${AVEXECUTOR_DIR}lib/x86_64-linux-gnu/")
endif()

#including avexecutor headers
set(AVEXECUTOR_DIR_LIB_INCLUDE "${AVEXECUTOR_DIR}include/")

set(HEAD_DIR "../headers")
set(SRC_DIR "../sources")

set(SRC_FILES
    ${SRC_DIR}/main.cpp
    #${SRC_DIR}/other.cpp
)

# Specify the include directories for avexecutor
include_directories(${AVEXECUTOR_DIR_LIB_INCLUDE})

# Include directories for headers
include_directories(${HEAD_DIR})

# Specify the library directories for avexecutor and other dependencies
link_directories(${AVEXECUTOR_DIR_LIB_DIR})

# Add the shared library target
add_library(user_filter_library SHARED ${SRC_FILES})

# Link the necessary libraries
target_link_libraries(user_filter_library
    AVL_Lite  # Assuming this is available in the specified library directory
    UserFilters  # Assuming this is available in the specified library directory
)

# Set the output name for the shared library
set_target_properties(user_filter_library PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# Additional flags for compiling and linking (this is added automatically by CMake when using SHARED)
set_target_properties(user_filter_library PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

# Add a custom target for cleaning up
add_custom_target(clear
    COMMENT "${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/CMakeFiles"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/CMakeCache.txt"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/cmake_install.cmake"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/Makefile"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/*.so"
    COMMENT "Removing CMake-generated files and the executable"
)