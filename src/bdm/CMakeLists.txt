
set (target bdm)
set (sources BdmLoader.hpp BdmLoader.cpp BdmFile.hpp BdmFile.cpp)

add_library(${target} ${sources})


