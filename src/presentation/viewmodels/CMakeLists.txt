project(viewmodels)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

include(GenerateExportHeader)
include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(${PROJECT_NAME})

generate_export_header(${PROJECT_NAME}
        BASE_NAME ${PROJECT_NAME}
        EXPORT_MACRO_NAME VM_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/viewmodels_export.h"
        STATIC_DEFINE ${PROJECT_NAME}_BUILT_AS_STATIC
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

find_package(Qt6 COMPONENTS
        Core
        REQUIRED)

qt_standard_project_setup()

target_sources(${PROJECT_NAME}
        PRIVATE
        CustomButtonViewModel.cpp
        UserViewModel.h
        UserViewModel.cpp
        PostViewModel.cpp

        PUBLIC
        FILE_SET HEADERS BASE_DIRS include
        FILES
        include/CustomButtonViewModel.h
        include/PostViewModel.h
)

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        MVVM::UC
        MVVM::Model
)

add_library(MVVM::ViewModels ALIAS ${PROJECT_NAME})

message(STATUS "CMake prefix path: ${CMAKE_PREFIX_PATH}")

