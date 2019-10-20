cmake_minimum_required(VERSION 3.0)
project(MinecraftC++)


option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(MinecraftC++/Vendor/glfw)


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()


include_directories(MinecraftC++/Headers/
                    MinecraftC++/Vendor/glad/include/
                    MinecraftC++/Vendor/glfw/include/
                    MinecraftC++/Vendor/glm/
                    MinecraftC++/Vendor/stb/)

file(GLOB VENDORS_SOURCES MinecraftC++/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS MinecraftC++/Headers/*.hpp)
file(GLOB PROJECT_SOURCES MinecraftC++/Sources/main.cpp)
file(GLOB PROJECT_SHADERS MinecraftC++/Shaders/*.comp
                          MinecraftC++/Shaders/*.frag
                          MinecraftC++/Shaders/*.geom
                          MinecraftC++/Shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)
                         
file(GLOB PROJECT_TEXTURES MinecraftC++/Textures/*.png)
                         


source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES} ${PROJECT_TEXTURES})
                               
target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/MinecraftC++/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
    DEPENDS ${PROJECT_SHADERS})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/MinecraftC++/Textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures
        DEPENDS ${PROJECT_TEXTURES})

   