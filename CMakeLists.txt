# Specify minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(untitled-engine VERSION 1.0)

# Set the standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add the source directory and specify source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/**.cpp)

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Find all include directories recursively
file(GLOB_RECURSE INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/*.h)

# Get list of unique directories
set(DIR_LIST "")
foreach(FILE ${INCLUDE_DIRS})
    get_filename_component(DIR ${FILE} PATH)
    list(APPEND DIR_LIST ${DIR})
endforeach()
list(REMOVE_DUPLICATES DIR_LIST)

# Add include directories to the project
foreach(DIR ${DIR_LIST})
    target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})    
endforeach()

# Specify include directories to ensure paths are relative to the project folder
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include)

# Find SDL2 and SDL_image
find_package(SDL2 REQUIRED)

# Manually specify SDL2_image include directory (Finding didn't work)
set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/Cellar/sdl2_image/2.8.2_1/include)
set(SDL2_IMAGE_LIBRARIES /opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib/libSDL2_image.dylib)

# Link SDL2 and SDL2_image to the project
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
