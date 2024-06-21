cmake_minimum_required(VERSION 3.10)
project(almaden-cac)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Lista de arquivos fonte
set(HEADERS
    src/include/cactypes.hpp
    src/include/chrome.hpp
    src/include/edge.hpp
)

# Lista de arquivos fonte
set(SOURCES
    src/chrome.cpp
    src/edge.cpp
)

# Cria a biblioteca compartilhada
add_library(almaden-cac SHARED ${SOURCES})
target_compile_definitions(almaden-cac PRIVATE ALMADEN_CAC_EXPORTS)
target_include_directories(almaden-cac INTERFACE ${CMAKE_SOURCE_DIR}/src/include)

set_target_properties(almaden-cac PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)
