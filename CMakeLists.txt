cmake_minimum_required(VERSION 3.30)

# Set project name and languages
project(vale C CXX)

# Set build type
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
    "Choose the type of build, options are: Debug, Release, RelWithDebInfo, MinSizeRel." FORCE)

# Specify Vale version
set(VALE_VERSION_MAJOR 0)
set(VALE_VERSION_MINOR 0)
set(VALE_VERSION_PATCH 0)
set(VALE_VERSION "${VALE_VERSION_MAJOR}.${VALE_VERSION_MINOR}.${VALE_VERSION_PATCH}")
message("Configuring Vale version ${VALE_VERSION}!")

# Set module path for custom CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Find LLVM package
find_package(llvm REQUIRED CONFIG)

# Include LLVM directories
include_directories(${LLVM_INCLUDE_DIRS})

# Include source and binary directories
include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
)

# Set source files
set(VALE_SOURCES
  "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

# Configure header file
set(CONFIGURE_OUT_FILE "${CMAKE_BINARY_DIR}/config.h")
configure_file(
  "${CMAKE_SOURCE_DIR}/src/config.h.in"
  ${CONFIGURE_OUT_FILE}
)

# Compiler and linker flags
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-unused-variable -Wno-unused-but-set-variable")
set(EXE_CFLAGS "-std=c++11 -Werror -Wall -Werror=strict-prototypes -Werror=old-style-definition -Werror=missing-prototypes")

# Ensure correct C++ standard library is used and set architecture to arm64
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11")
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Add executable target
add_executable(vale ${VALE_SOURCES})

# Set target properties
set_target_properties(vale PROPERTIES
  LINKER_LANGUAGE CXX
  COMPILE_FLAGS ${EXE_CFLAGS}
)

# Link LLVM libraries and libc++
target_link_libraries(vale LINK_PUBLIC
  ${LLVM_LIBRARIES}
  c++
)

# Installation rule
install(TARGETS vale DESTINATION bin)
