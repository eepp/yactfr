add_executable (metadata-text-tester EXCLUDE_FROM_ALL metadata-text-tester.cpp)
add_executable (metadata-stream-tester EXCLUDE_FROM_ALL metadata-stream-tester.cpp)
add_executable (iter-data-tester EXCLUDE_FROM_ALL iter-data-tester.cpp)
add_executable (trace-env-stream-tester EXCLUDE_FROM_ALL trace-env-stream-tester.cpp)
target_link_libraries (metadata-text-tester yactfr)
target_link_libraries (metadata-stream-tester yactfr)
target_link_libraries (iter-data-tester yactfr)
target_link_libraries (trace-env-stream-tester yactfr)
include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
    ${Boost_INCLUDE_DIRS}
)
add_custom_target (
    testers
    DEPENDS
        metadata-text-tester
        metadata-stream-tester
        iter-data-tester
        trace-env-stream-tester
)
