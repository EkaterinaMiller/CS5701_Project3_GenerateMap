cmake_minimum_required(VERSION 3.22)
project(SFML3_App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PATH helps at runtime for DLL lookup, but find_package() needs the CMake config path.
if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "C:/SFML-3.1.0")
endif()

# 1. Tell CMake to explicitly look for static SFML libraries
#set(SFML_STATIC_LIBRARIES ON)
#Add Main to remove consol when click on executable
find_package(SFML 3 REQUIRED COMPONENTS Main Graphics Window System)

# Optional: also force static MinGW runtime if using MinGW/GCC
# if(MINGW)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
# endif()

set(SFML_APP_SOURCES
    src/main.cpp
    src/bulletList.cpp
    src/button.cpp
    src/mapDisplay.cpp
    src/display.cpp
    src/minConflict.cpp
    src/legend.cpp
)

add_executable(mapGenerator WIN32 ${SFML_APP_SOURCES})
target_include_directories(mapGenerator PRIVATE include)
#target_link_libraries(mapGenerator PRIVATE SFML::Graphics SFML::Window SFML::System)
#Remove terminal when click on executable
target_link_libraries(mapGenerator PRIVATE SFML::Main SFML::Graphics SFML::Window SFML::System)

# 2. WINDOWS ONLY: Force SFML to compile in static mode (prevents missing DLL errors)
if(WIN32)
    target_compile_definitions(mapGenerator PRIVATE include)#SFML_STATIC)
endif()

# Automatically copy the assets into the executable output directory on every build
add_custom_command(
    TARGET mapGenerator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:mapGenerator>"
    COMMENT "Copying game assets to the build output directory..."
)