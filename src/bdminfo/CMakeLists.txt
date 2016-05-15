
set (target bdminfo)
set (sources BdmInfo.cpp)

add_executable(${target} ${sources})

target_link_libraries(${target} bdm)
