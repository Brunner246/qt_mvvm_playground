project(viewmodels)

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

#if(BUILD_SHARED_LIBS)
#    target_compile_definitions(${PROJECT_NAME}
#            PRIVATE viewmodels_EXPORTS QT_SHARED
#            INTERFACE $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${PROJECT_NAME}_BUILT_AS_STATIC>
#    )
#else()
#    target_compile_definitions(${PROJECT_NAME}
#            PUBLIC ${PROJECT_NAME}_BUILT_AS_STATIC
#    )
#endif()

find_package(Qt6 COMPONENTS
        Core
        REQUIRED)

qt_standard_project_setup()

target_sources(${PROJECT_NAME}
        PRIVATE
        CustomButtonViewModel.cpp

        PUBLIC
        FILE_SET HEADERS BASE_DIRS include
        FILES
        include/CustomButtonViewModel.h
)

target_link_libraries(${PROJECT_NAME}
        Qt::Core
)

add_library(MVVM::ViewModels ALIAS ${PROJECT_NAME})

#install(
#        TARGETS ${PROJECT_NAME}
#        EXPORT ${PROJECT_NAME}-config
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MVVM
#        COMPONENT viewmodels
#)
#install(
#        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MVVM
#        COMPONENT ${PROJECT_NAME}
#)
#
#install(
#        FILES "${CMAKE_CURRENT_BINARY_DIR}/viewmodels_export.h"
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MVVM
#        COMPONENT ${PROJECT_NAME}
#)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    get_filename_component(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}/../../../bin" ABSOLUTE)
    message(STATUS "Qt binary path: ${QT_BIN_PATH}")
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