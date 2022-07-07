project(test C)

file(GLOB SOURCES "src/*.c" "src/*/*.c" "src/*/*/*.c" "src/*/*/*/*.c")

add_executable(test ${SOURCES})

target_include_directories(test 
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            "../engine/src/"
            )

target_link_libraries(test
        PUBLIC
            Engine
            )

#target_include_directories(Engine
#    PUBLIC
#        $<INSTALL_INTERFACE:include>
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    PRIVATE
#        ${Vulkan_INCLUDE_DIRS}
#        
#        "src"
#)