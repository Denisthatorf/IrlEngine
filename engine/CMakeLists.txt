project(Engine LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_RELEASE")

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

add_library(Engine SHARED ${SOURCES})

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_include_directories(Engine
    PUBLIC
        ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        
)

target_link_libraries(Engine
    PUBLIC
        glm
    PRIVATE
        glfw
        Vulkan::Vulkan
)

target_compile_definitions(Engine
    PRIVATE
        -DUSE_GLFW
    PUBLIC
        )