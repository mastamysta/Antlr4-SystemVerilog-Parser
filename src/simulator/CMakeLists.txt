add_library(simulator INTERFACE)
target_include_directories(simulator INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(simulator INTERFACE core)
