cmake_minimum_required(VERSION 3.1)
#set(CMAKE_CXX_STANDARD 20)
project(IrlEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_C_COMPILER /usr/bin/clang)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)

add_subdirectory(vendor/glm)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)

add_subdirectory(engine)
add_subdirectory(test)

# SHADER COMPILATION

#file (GLOB SHADERS shaders/*.frag shaders/*.vert)
#
#add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#        COMMAND mkdir -p ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASSETS_DIR_NAME}/shaders)
#
#foreach(shader ${SHADERS})
#    get_filename_component(SHADER_NAME ${shader} NAME)
#
#    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#            COMMAND ${Vulkan_GLSLC_EXECUTABLE} -c ${shader} -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASSETS_DIR_NAME}/shaders/${SHADER_NAME}.spv)
#endforeach()