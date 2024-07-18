#include <catch2/catch.hpp>

#include "dir_compare/Directory.h"


TEST_CASE("TestConstruction", "Ensure all forms of construction work.")
{
    std::string dirPath = "../../tests/dir1/unique_file.txt";
    dc::Directory dir(dirPath.c_str());
    REQUIRE(&dir != nullptr);

    dir = dc::Directory(dirPath);
    REQUIRE(&dir != nullptr);

    dir = dc::Directory(std::filesystem::directory_entry(dirPath));
    REQUIRE(&dir != nullptr);
}

TEST_CASE("TestComparison", "Ensure all forms of comparison work.")
{
    std::string dirB = "../../tests/dir2";
    std::unordered_map<std::string, std::vector<std::string>> dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap;
    dc::Directory dir("../../tests/dir1");
    dir.compare(dirB.c_str(), dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap);
    REQUIRE(dirAOnlyFilesMap.size() == 2);
    REQUIRE(dirBOnlyFilesMap.size() == 1);
    REQUIRE(commonFilesMap.size() == 1);
    REQUIRE(commonFilesMap["43951c12558ec72210c2230129f4720d"].size() == 3);

    dirAOnlyFilesMap.clear();
    dirBOnlyFilesMap.clear();
    commonFilesMap.clear();

    dir.compare(dirB, dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap);
    REQUIRE(dirAOnlyFilesMap.size() == 2);
    REQUIRE(dirBOnlyFilesMap.size() == 1);
    REQUIRE(commonFilesMap.size() == 1);
    REQUIRE(commonFilesMap["43951c12558ec72210c2230129f4720d"].size() == 3);

    dirAOnlyFilesMap.clear();
    dirBOnlyFilesMap.clear();
    commonFilesMap.clear();

    dir.compare(std::filesystem::directory_entry(dirB), dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap);
    REQUIRE(dirAOnlyFilesMap.size() == 2);
    REQUIRE(dirBOnlyFilesMap.size() == 1);
    REQUIRE(commonFilesMap.size() == 1);
    REQUIRE(commonFilesMap["43951c12558ec72210c2230129f4720d"].size() == 3);
}
