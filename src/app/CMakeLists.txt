project(app)

add_executable(${PROJECT_NAME})

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
qt_standard_project_setup()

target_sources(${PROJECT_NAME}
        PRIVATE
        main.cpp
        UserViewModel.cpp
        UserViewModel.h
        UserModel.h
        CustomButton.cpp
        CustomButton.h
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../presentation/viewmodels/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


#target_include_directories(${PROJECT_NAME}
#        PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
#        $<INSTALL_INTERFACE:include>
#        PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/src
#)

#qt_add_resources(helloworld imageresources
#        PREFIX "/images"
#        FILES logo.png splashscreen.png
#)

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        MVVM::ViewModels
)

# add_library(MVVM::App ALIAS ${PROJECT_NAME})

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    # set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    # message(STATUS "QT_INSTALL_PATH: ${QT_INSTALL_PATH}")
    # set(QT_LIB_CMAKE_PATH "C:/Qt/6.8.0/msvc2022_64/lib/cmake/Qt6")
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
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
