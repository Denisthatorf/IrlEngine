project(test LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

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

#set_property(TARGET test PROPERTY CXX_STANDARD 17)
#set_property(TARGET test PROPERTY C_STANDARD 17)

#target_include_directories(Engine
#    PUBLIC
#        $<INSTALL_INTERFACE:include>
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    PRIVATE
#        ${Vulkan_INCLUDE_DIRS}
#        
#        "src"
#)