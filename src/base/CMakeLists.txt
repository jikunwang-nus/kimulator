add_library(base OBJECT)
set_target_properties(base PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_sources(
  base PRIVATE
  param.h utils.h exception.h 

  utils.cpp
)

target_link_libraries(
  kt_lib_shared
  PRIVATE
  base
)