#include <catch2/catch.hpp>

#include "../src/dir_compare/utils.h"


TEST_CASE("TestFileHash", "Ensure MD5SUM hashes are working as expected.")
{
    auto hash = getFileHash("../../tests/dir1/unique_file.txt");
    REQUIRE(hash == "c7c94ca9ed1d35697e6c3f9e223427ea");

    hash = getFileHash("../../tests/dir2/unique_file.txt");
    REQUIRE(hash == "d87265285fe8dbccc645209c2828a6cc");

    hash = getFileHash("../../tests/dir1/subdir1/common_file2.png");
    REQUIRE(hash == "43951c12558ec72210c2230129f4720d");
}

TEST_CASE("TestFindFiles", "Ensure the expected number of files are found.")
{
    std::filesystem::directory_entry dir("../../tests/dir1");
    auto filesMap = findFiles(dir);
    REQUIRE(filesMap.size() == 3);  // 3 unique hashed file lists.
    REQUIRE(filesMap["43951c12558ec72210c2230129f4720d"].size() == 2);  // One list with 2 files in it.

    filesMap = findFiles(dir, false);
    REQUIRE(filesMap.size() == 2);  // 2 top-level files not in the subdir1.
}
