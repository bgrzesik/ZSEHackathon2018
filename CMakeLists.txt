cmake_minimum_required(VERSION 3.10)
project(AudioNoob)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)

add_executable(AudioNoob MACOSX_BUNDLE
               main.cpp
               App.cpp App.hpp
               Handler.cpp Handler.hpp
               macos/Resources/index.html
               Hallayeah.cpp Hallayeah.hpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/cef)
message(CEF_TARGET ${CEF_TARGET})
include_directories(${PROJECT_SOURCE_DIR}/cef)
target_link_libraries(AudioNoob libcef_dll_wrapper)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/cef/Debug")

target_compile_options(AudioNoob PUBLIC "-F" "${PROJECT_SOURCE_DIR}/cef/Debug")
target_link_libraries(AudioNoob "-framework AppKit")
target_link_libraries(AudioNoob "-framework OpenGL")
target_link_libraries(AudioNoob "-framework Cocoa")
target_link_libraries(AudioNoob "-framework Foundation")
target_link_libraries(AudioNoob "-framework IOKit")
target_link_libraries(AudioNoob "-framework Security")
target_link_libraries(AudioNoob "-framework SystemConfiguration")
target_link_libraries(AudioNoob "-F ${PROJECT_SOURCE_DIR}/cef/Debug -framework 'Chromium Embedded Framework'")

set_target_properties(AudioNoob PROPERTIES INSTALL_RPATH "${PROJECT_SOURCE_DIR}/cef/Debug")
set_target_properties(AudioNoob PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
set_target_properties(AudioNoob PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/")
FIX_MACOSX_MAIN_FRAMEWORK_RPATH(AudioNoob)

#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${CMAKE_CURRENT_BINARY_DIR}/cef/tests/cefsimple/Debug/cefclient Helper.app"
#        "${CMAKE_CURRENT_BINARY_DIR}/Contents/Frameworks/cefclient Helper.app"

#        COMMAND ${CMAKE_COMMAND} -E copy
#            "${CMAKE_CURRENT_BINARY_DIR}/cef/tests/cefsimple/Debug/cefclient Helper.app/Contents/MacOS/cefclient Helper"
#            "${CMAKE_CURRENT_BINARY_DIR}/Contents/Frameworks/AudioNoob Helper.app/Contents/MacOS/AudioNoob Helper"
#        COMMAND ${CMAKE_COMMAND} -E copy
#            "${CMAKE_CURRENT_BINARY_DIR}/cef/tests/cefsimple/Debug/cefclient Helper.app/Contents/MacOS/cefclient Helper.app"
#            "${CMAKE_CURRENT_BINARY_DIR}/Contents/Frameworks/AudioNoob Helper.app/Contents/MacOS/AudioNoob Helper.app"


add_custom_command(
        TARGET AudioNoob
        POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/macos"
        "${CMAKE_CURRENT_BINARY_DIR}/AudioNoob.app/Contents/"

        VERBATIM
)


add_library(OSXHelper OSXHelper.mm OSXHelper.h)
target_link_libraries(OSXHelper "-framework AppKit")
target_link_libraries(OSXHelper "-framework OpenGL")
target_link_libraries(OSXHelper "-framework Cocoa")
target_link_libraries(OSXHelper "-framework Foundation")
target_link_libraries(OSXHelper "-framework IOKit")
target_link_libraries(OSXHelper "-framework Security")
target_link_libraries(OSXHelper "-framework SystemConfiguration")
target_link_libraries(OSXHelper "-F ${PROJECT_SOURCE_DIR}/cef/Debug -framework 'Chromium Embedded Framework'")
target_link_libraries(AudioNoob OSXHelper)
set_target_properties(OSXHelper PROPERTIES COMPILE_FLAGS "-x objective-c++")

