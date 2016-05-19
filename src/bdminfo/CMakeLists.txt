
set (target bdminfo)
set (sources BdmInfo.cpp)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

target_link_libraries(${target} bdm)
