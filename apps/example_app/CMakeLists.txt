project(app)

add_executable(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)

include(QtUtils)

message(STATUS "QtUtils.cmake loaded")

if(MSVC)
    add_compile_options(/W4 /wd4251) # /wd4251 disable warning about DLL interface
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
qt_standard_project_setup()

target_sources(${PROJECT_NAME}
        PRIVATE
        main.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src/presentation/viewmodels/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src/ui>
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
        MVVM::Network
        MVVM::interfaces
        MVVM::UC
        MVVM::Model
        MVVM::Ui
)

# add_library(MVVM::App ALIAS ${PROJECT_NAME})

setup_qt_deployment(${PROJECT_NAME})