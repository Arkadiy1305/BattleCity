cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)

set(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDART 17)

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/Renderer/ShaderProgramm.cpp
	src/Renderer/ShaderProgramm.h
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME}
				   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res/)
