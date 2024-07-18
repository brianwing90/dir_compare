find_package(Catch2 REQUIRED)

add_executable(test_utils TestUtils.cpp)
target_link_libraries(test_utils PRIVATE
        dir_compare
        Catch2::Catch2WithMain
        )
add_test(NAME TestUtils COMMAND test_utils)

add_executable(test_directory TestDirectory.cpp)
target_link_libraries(test_directory PRIVATE
        dir_compare
        Catch2::Catch2WithMain
        )
add_test(NAME TestDirectory COMMAND test_directory)