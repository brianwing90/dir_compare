add_subdirectory(dir_compare)

add_executable(dir-compare dir-compare.cpp)
target_link_libraries(dir-compare PRIVATE dir_compare)

add_custom_target(run dir-compare ../../tests/dir1 ../../tests/dir2)
