
set (target bdm)
set (sources BdmLoader.hpp BdmLoader.cpp BdmFile.hpp BdmFile.cpp)

add_library(${target} ${sources})

install (DIRECTORY . DESTINATION include/bdm FILES_MATCHING PATTERN "*.hpp")
install (
    TARGETS ${target}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
