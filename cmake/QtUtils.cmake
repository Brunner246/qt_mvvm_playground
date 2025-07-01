function(setup_qt_deployment target_name)
    message(STATUS "=== setup_qt_deployment called for target: ${target_name} ===")

    set(QT_INSTALL_PATH "")
    if(DEFINED ENV{QT_ROOT})
        set(QT_INSTALL_PATH "$ENV{QT_ROOT}")
        message(STATUS "Using Qt from QT_ROOT environment: ${QT_INSTALL_PATH}")
    else()
        foreach(prefix_path ${CMAKE_PREFIX_PATH})
            if(prefix_path MATCHES "Qt6")
                get_filename_component(QT_INSTALL_PATH "${prefix_path}/../../.." ABSOLUTE)
                break()
            endif()
        endforeach()
    endif()

    if(NOT QT_INSTALL_PATH)
        message(WARNING "Qt installation path not found")
        return()
    endif()

    if(NOT TARGET ${target_name})
        message(ERROR "Target ${target_name} does not exist!")
        return()
    endif()

    if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(DEBUG_SUFFIX)
        if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
            set(DEBUG_SUFFIX "d")
        endif ()

        set(QT_BIN_PATH "${QT_INSTALL_PATH}/bin")
        message(STATUS "Qt binary path: ${QT_BIN_PATH}")

        if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${target_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${target_name}>/plugins/platforms/")
            add_custom_command(TARGET ${target_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${target_name}>/plugins/platforms/")
        endif ()

        foreach (QT_LIB Core)
            add_custom_command(TARGET ${target_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_BIN_PATH}/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${target_name}>")
        endforeach ()
    endif ()
endfunction()
