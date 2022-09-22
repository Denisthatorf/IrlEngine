project(Engine LANGUAGES C CXX)

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

#set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
#set_property(TARGET Engine PROPERTY C_STANDARD 17)

#$<INSTALL_INTERFACE:include>
#$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

#${Vulkan_LIBRARIES}
#${Vulkan_INCLUDE_DIRS}