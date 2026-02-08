CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(HardwareSimulator)

SET (CMAKE_CXX_STANDARD 23)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/extern/antlr4/runtime/Cpp)

add_library(sv_parser antlr_generated/SVParser.cpp 
                      antlr_generated/SVListener.cpp 
                      antlr_generated/SVLexer.cpp 
                      antlr_generated/SVBaseListener.cpp)
target_include_directories(sv_parser PUBLIC antlr_generated)
target_link_libraries(sv_parser PUBLIC antlr4_static)

add_subdirectory(src)

add_executable(sim_main sim_main.cpp)
target_link_libraries(sim_main PUBLIC compiler simulator)
