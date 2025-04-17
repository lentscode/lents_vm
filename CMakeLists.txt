cmake_minimum_required(VERSION 3.10)

project(lents_vm)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(
  lents_vm 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/commands.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/system.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.c
)