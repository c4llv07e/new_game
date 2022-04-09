cmake_minimum_required(VERSION 3.10)

project(new_game)

set(EXEC_NAME "game")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(LUA REQUIRED lua5.2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

FILE(GLOB sources src/*.c)
FILE(GLOB lua_codes *.lua)

add_executable(${EXEC_NAME} ${sources})

# SDL2
target_include_directories(${EXEC_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${EXEC_NAME} PRIVATE ${SDL2_LIBRARIES})

# SDL2_ttf
target_include_directories(${EXEC_NAME} PRIVATE ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${EXEC_NAME} PRIVATE ${SDL2TTF_LIBRARIES})

# lua
target_include_directories(${EXEC_NAME} PRIVATE ${LUA_INCLUDE_DIRS})
target_link_libraries(${EXEC_NAME} PRIVATE ${LUA_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})
add_custom_command(TARGET ${EXEC_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})

foreach(lua IN LISTS lua_codes)
  get_filename_component(file_name ${lua} NAME)
  file(COPY_FILE ${lua} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/${file_name})
endforeach()
