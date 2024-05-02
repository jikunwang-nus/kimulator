
# add_subdirectory(mem_controller)

add_executable(KT-exe main.cpp)
set_target_properties(
    KT-exe
  PROPERTIES 
  OUTPUT_NAME kimulator
)

add_subdirectory(base)
add_subdirectory(dram)

target_link_libraries(KT-exe PRIVATE base yaml-cpp)
