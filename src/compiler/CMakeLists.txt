add_library(compiler INTERFACE)
target_include_directories(compiler INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(compiler INTERFACE sv_parser core)
