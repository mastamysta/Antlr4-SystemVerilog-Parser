add_library(simulator ModuleSimulator.cpp SimulationState.cpp)
target_include_directories(simulator PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(simulator PUBLIC core)
