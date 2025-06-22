project(usecases)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

include(GenerateExportHeader)
include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(${PROJECT_NAME})

generate_export_header(${PROJECT_NAME}
        BASE_NAME ${PROJECT_NAME}
        EXPORT_MACRO_NAME UC_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/uc_export.h"
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

target_sources(${PROJECT_NAME}
        PRIVATE
        FetchPostUseCase.cpp

        PUBLIC
        FILE_SET HEADERS BASE_DIRS . # include
        FILES
        FetchPostUseCase.h
)


target_link_libraries(${PROJECT_NAME}
        PUBLIC
        MVVM::interfaces
        PRIVATE
        MVVM::Model
)

add_library(MVVM::UC ALIAS ${PROJECT_NAME})