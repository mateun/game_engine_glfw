include_directories(include 
					../extlibs/glm/include 
					../extlibs/glew/include 
					../extlibs/glfw/include
					../extlibs/libpng/include
					../extlibs/freeimage/include
					)
file(GLOB sources src/*.*)

add_library(gamelib SHARED ${sources})

target_link_libraries(gamelib opengl32.lib glu32.lib)

target_link_libraries (gamelib
    debug ${CMAKE_SOURCE_DIR}/extlibs/glfw/x64/Debug/glfw3dll.lib
    optimized ${CMAKE_SOURCE_DIR}/extlibs/glfw/x64/Release/glfw3dll.lib)

target_link_libraries (gamelib
    debug ${CMAKE_SOURCE_DIR}/extlibs/glew/x64/lib/Debug/x64/glew32d.lib
    optimized ${CMAKE_SOURCE_DIR}/extlibs/glew/x64/lib/Release/x64/glew32.lib)

target_link_libraries (gamelib
    ${CMAKE_SOURCE_DIR}/extlibs/libpng/x64/libpng16.lib)

target_link_libraries (gamelib
    ${CMAKE_SOURCE_DIR}/extlibs/freeimage/x64/freeimage.lib)