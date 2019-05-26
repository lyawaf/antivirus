cmake_minimum_required (VERSION 3.10)
project (ccptool)
set (CMAKE_CXX_STANDART 14)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-I. -Wall -Wno-reorder")

add_custom_target(includefunctions
                  COMMAND ./includefunctions.rb)

add_library( ${PROJECT_NAME}
             functions.cpp
             functions.h
             heuristics/nikitail.cpp
             heuristics/nikitail.h
             wrapper.cpp
             wrapper.h
           )

add_dependencies(${PROJECT_NAME} includefunctions)
add_executable (main main.cpp)
target_link_libraries(main ${PROJECT_NAME} capstone)
