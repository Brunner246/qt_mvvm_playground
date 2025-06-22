cmake_minimum_required(VERSION 3.31)
project(qt_mvvm)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64/lib/cmake/Qt6")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

if(MSVC)
    add_compile_options(/W4 /wd4251) # /wd4251 disable warning about DLL interface
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/release)


add_subdirectory(src/domain/model)
add_subdirectory(src/app/interfaces)
add_subdirectory(src/app/usecases)
add_subdirectory(src/presentation/viewmodels)
add_subdirectory(src/infrastructure/network)
add_subdirectory(src/ui)

add_subdirectory(apps/example_app)