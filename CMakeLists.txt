# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET (CMAKE_CXX_STANDARD 23)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/extern/antlr4/runtime/Cpp)

add_library(sv_lib antlr_generated/SVParser.cpp 
                      antlr_generated/SVListener.cpp 
                      antlr_generated/SVLexer.cpp 
                      antlr_generated/SVBaseListener.cpp)
target_include_directories(sv_lib PUBLIC antlr_generated)
target_link_libraries(sv_lib PUBLIC antlr4_static)

add_executable(test_antlr sim_main.cpp)
target_link_libraries(test_antlr sv_lib)