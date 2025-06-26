project(network)

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
        EXPORT_MACRO_NAME NETWORK_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/network_export.h"
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

find_package(Qt6
        REQUIRED COMPONENTS
        Network
        Core
)
find_package(cpr REQUIRED)

qt_standard_project_setup()

target_sources(${PROJECT_NAME}
        PRIVATE
        QtPostService.cpp

        CprPostService.cpp
        CprPostService.h

        PUBLIC
        FILE_SET HEADERS BASE_DIRS .
        FILES
        QtPostService.h
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Qt6::Network
        Qt6::Core
        MVVM::interfaces
        MVVM::Model # weakened layers.. down to core/model
        cpr::cpr
)


add_library(MVVM::Network ALIAS ${PROJECT_NAME})

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    get_filename_component(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}/../../../bin" ABSOLUTE)
    message(STATUS "Qt binary path: ${QT_INSTALL_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()