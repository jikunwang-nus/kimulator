add_subdirectory(base)
add_subdirectory(dram)
# add_subdirectory(mem_controller)

target_sources(
  kimulator-exe
  PRIVATE 
  main.cpp
)
