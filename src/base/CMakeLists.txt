add_library(kimulator-base OBJECT)
set_target_properties(kimulator-base PROPERTIES LINKER_LANGUAGE CXX)


target_sources(
  kimulator-base PRIVATE
  param.h 
)

target_link_libraries(
  kimulator
  PRIVATE
  kimulator-base
)