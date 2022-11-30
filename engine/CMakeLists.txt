project(Engine LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_RELEASE")

file(GLOB SOURCES_C "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")
file(GLOB SOURCES_CXX "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

file(GLOB HEADERS_C "src/*.h" "src/*/*.h" "src/*/*/*.h" "src/*/*/*/*.h")
#"src/*.hpp"
file(GLOB HEADERS_CXX  "src/*/*.hpp" "src/*/*/*.hpp" "src/*/*/*/*.hpp")

add_library(Engine SHARED ${SOURCES_C} ${SOURCES_CXX})

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

#find_package(GLUT REQUIRED)

find_package(GLEW REQUIRED)
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
        OpenGL::OpenGL
        GLEW::GLEW
)

target_compile_definitions(Engine
    PRIVATE
        -DUSE_GLFW
    PUBLIC
        )

target_precompile_headers(Engine
    PRIVATE
        ${HEADERS_C}
        ${HEADERS_CXX}
)