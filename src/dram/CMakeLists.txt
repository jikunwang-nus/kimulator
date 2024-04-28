add_library(kimulator-dram OBJECT)

target_sources(
  kimulator-dram PRIVATE
  dram.h 
  spec.h 

  impl/DDR4.cpp
)

target_link_libraries(
  kimulator
  PRIVATE
  kimulator-dram
)