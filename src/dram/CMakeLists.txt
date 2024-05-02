add_library(dram OBJECT)
set_target_properties(dram PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(dram PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_sources(
  dram PRIVATE
  dram.h 
  spec.h 

  impl/DDR4.cpp
)
target_link_libraries(
  kt_lib_shared
  PRIVATE 
  dram
)