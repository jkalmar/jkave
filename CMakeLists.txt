project(jkave)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

set (SPDLOG_INCLUDE_DIR "ext_modules/spdlog/include")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# set policy to find new OpenGL library
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)

message(STATUS "Includes:")
message(STATUS "\${OPENGL_INCLUDE_DIR}=${OPENGL_INCLUDE_DIR}")
message(STATUS "\${GLEW_INCLUDE_DIRS}=${GLEW_INCLUDE_DIRS}")
message(STATUS "\${SDL2_INCLUDE_DIR}=${SDL2_INCLUDE_DIR}")
message(STATUS "\${SDL2_IMAGE_INCLUDE_DIRS}=${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "\${SDL2TTF_INCLUDE_DIR}=${SDL2TTF_INCLUDE_DIR}")
message(STATUS "\${SPDLOG_INCLUDE_DIR}=${SPDLOG_INCLUDE_DIR}")


message(STATUS "Libraries:")
message(STATUS "\${OPENGL_LIBRARIES}=${OPENGL_LIBRARIES}")
message(STATUS "\${GLEW_LIBRARIES}=${GLEW_LIBRARIES}")
message(STATUS "\${SDL2_LIBRARIES}=${SDL2_LIBRARIES}")
message(STATUS "\${SDL2_IMAGE_LIBRARIES}=${SDL2_IMAGE_LIBRARIES}")
message(STATUS "\${SDL2TTF_LIBRARY}=${SDL2TTF_LIBRARY}")

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${SPDLOG_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

add_executable(jkave src/main.cpp
    src/Enviroment.cpp
    src/Game.cpp
    src/Utils.cpp
    src/Shader.cpp
    src/Texture.cpp
)
install(TARGETS jkave DESTINATION bin)

target_link_libraries(jkave ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} )
