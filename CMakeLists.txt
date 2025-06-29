cmake_minimum_required(VERSION 3.28)
project(GraphGen LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)

set(SOURCES
    src/Source.cpp
    src/core/Errors.cpp
    src/core/EventHandle.cpp
    src/core/Renderer.cpp
    src/core/Utils.cpp
    src/UI/InputWidget.cpp
    src/UI/Sidebar.cpp
    src/UI/UI.cpp
    src/UI/ViewWidget.cpp
)

add_executable(GraphGen ${SOURCES})
target_compile_features(GraphGen PRIVATE cxx_std_17)
target_link_libraries(GraphGen PRIVATE SFML::Graphics)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "GraphGen")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)