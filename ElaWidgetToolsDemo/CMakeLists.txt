cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0087 NEW)
project(ElaWidgetToolsDemo VERSION 0.1 LANGUAGES CXX)

FILE(GLOB ORIGIN *.cpp *.h)
FILE(GLOB EXAMPLEPAGE ExamplePage/*.h ExamplePage/*.cpp)

source_group(ExamplePage FILES ${EXAMPLEPAGE})

set(PROJECT_SOURCES
    ${ORIGIN}
    ${EXAMPLEPAGE}
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else ()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    ExamplePage
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Ela::WidgetTools
)

if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif ()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}"
    VS_DEBUGGER_COMMAND "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/${PROJECT_NAME}.exe"
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif ()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
)

install(TARGETS ElaWidgetTools
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
)

find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_SDK_DIR}/bin")
if (WIN32)
    install(CODE "
    if(EXISTS \"${WINDEPLOYQT_EXECUTABLE}\" AND NOT EXISTS \"${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/platforms\")
        execute_process(
            COMMAND \"${CMAKE_COMMAND}\" -E env PATH=\"${QT_SDK_DIR}/bin\"
                \"${WINDEPLOYQT_EXECUTABLE}\"
                \"$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:${PROJECT_NAME}>\"
                --dir \"${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}\"
                --no-compiler-runtime
                --no-system-d3d-compiler
                --no-opengl-sw
                --verbose 1
        )
    endif()"
    )
endif ()

if (WIN32)
    if (WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            # 运行 windeployqt 部署 Qt 依赖
            COMMAND ${CMAKE_COMMAND} -E env PATH="${QT_SDK_DIR}/bin"
                ${WINDEPLOYQT_EXECUTABLE}
                "$<TARGET_FILE:${PROJECT_NAME}>"
                --no-compiler-runtime 
                --no-system-d3d-compiler
                --no-opengl-sw
            # 手动复制 ElaWidgetTools.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE_DIR:ElaWidgetTools>/$<TARGET_FILE_NAME:ElaWidgetTools>"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            COMMENT "正在将 Qt 依赖和 ElaWidgetTools.dll 部署到编译目录..."
        )
    else()
        message(WARNING "未找到 windeployqt: ${QT_SDK_DIR}/bin/windeployqt.exe")
    endif()
endif()
