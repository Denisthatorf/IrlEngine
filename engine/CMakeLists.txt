project(Engine)

file(GLOB SOURCES "src/*.c" "src/*/*.c" "src/*/*/*.c" "src/*/*/*/*.c")

add_library(Engine SHARED ${SOURCES})

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_include_directories(Engine
    PUBLIC
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        "src"
)

target_link_libraries(Engine
    PUBLIC
        glm
    PRIVATE
        glfw
)

#$<INSTALL_INTERFACE:include>
#$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

#${Vulkan_LIBRARIES}
#${Vulkan_INCLUDE_DIRS}