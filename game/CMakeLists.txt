file(GLOB sources src/*.*)
include_directories(../extlibs/glfw/include 
                    ../extlibs/glew/include
                    ../extlibs/glm/include
					../extlibs/libpng/include
					../gamelib/include)

add_executable(game ${sources})

if (MSVC)
	message("Building on Windows")
	target_link_libraries(game gamelib opengl32.lib glu32.lib)

	target_link_libraries (game
    debug ${CMAKE_SOURCE_DIR}/extlibs/glfw/x64/Debug/glfw3dll.lib
    optimized ${CMAKE_SOURCE_DIR}/extlibs/glfw/x64/Release/glfw3dll.lib)

	target_link_libraries (game
    debug ${CMAKE_SOURCE_DIR}/extlibs/glew/x64/lib/Debug/x64/glew32d.lib
    optimized ${CMAKE_SOURCE_DIR}/extlibs/glew/x64/lib/Release/x64/glew32.lib)

	target_link_libraries (game ${CMAKE_SOURCE_DIR}/extlibs/libpng/x64/libpng16.lib)

	add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/extlibs/glfw/x64/$<CONFIGURATION>/glfw3.dll"
        $<TARGET_FILE_DIR:game>)

	add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/extlibs/glew/x64/bin/$<CONFIGURATION>/x64/"
        $<TARGET_FILE_DIR:game>)

	add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/extlibs/libpng/x64/libpng16.dll"
        $<TARGET_FILE_DIR:game>)

	add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:gamelib>/gamelib.dll"
        $<TARGET_FILE_DIR:game>)

	add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/extlibs/zlib/x64/zlib.dll"
        $<TARGET_FILE_DIR:game>)

	add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/extlibs/freeimage/x64/freeimage.dll"
        $<TARGET_FILE_DIR:game>)
endif()

if (UNIX) 
	message("Building on linux")
	target_link_libraries(game gamelib libGL.so libGLU.so)

	target_link_libraries (game
    ${CMAKE_SOURCE_DIR}/extlibs/glfw/linux/libglfw.so)

	target_link_libraries (game
    ${CMAKE_SOURCE_DIR}/extlibs/glew/linux/libGLEW.so)

	
endif()
