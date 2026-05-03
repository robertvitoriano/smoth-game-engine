cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(SmothGameEngine)

set(PROJECT_SOURCE_FILES
  source/main.cpp
)
# Add the application
include_directories(source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add Engine Library
add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")


# Link ENGINE LIBRARY
target_link_libraries(${PROJECT_NAME}
  Engine
)
