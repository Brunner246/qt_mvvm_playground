project(interfaces)
add_library(${PROJECT_NAME} INTERFACE
        include/IPostService.h)
target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../domain/model/include>
)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

target_compile_options(${PROJECT_NAME}
        INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /wd4251>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        include/INotificationService.h
)

add_library(MVVM::interfaces ALIAS ${PROJECT_NAME})

#add_library(project_warnings INTERFACE)
#
#target_compile_options(project_warnings
#        INTERFACE
#        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
#        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
#)