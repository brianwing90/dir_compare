#include <iostream>
#include <fstream>

#include "dir_compare/Directory.h"


/**
 * Creates or empties the given filePath and writes each key/value pair from the fileMap onto a line in the file with
 * space delimited file names.
 *
 * @param filePath The path to the file to create or update with the given file names.
 * @param filesMap The relative file paths organized by hash to store in the file.
 */
void writeFile(const std::string& filePath, const std::unordered_map<std::string, std::vector<std::string>>& filesMap)
{
    std::cout << "Writing " << filePath << "..." << std::endl;

    std::ofstream fileStream(filePath);
    for(const auto& [hash, filesList] : filesMap)
    {
        fileStream << hash << ": ";
        for(const auto& file : filesList)
        {
            fileStream << file << " ";
        }
        fileStream << std::endl;
    }
    fileStream.close();
}

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Usage: dir-compare dirA dirB" << std::endl;
        return -1;
    }

    std::unordered_map<std::string, std::vector<std::string>> dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap;
    auto dir = dc::Directory(argv[1]);
    dir.compare(argv[2], dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap);

    writeFile("a_only", dirAOnlyFilesMap);
    writeFile("b_only", dirBOnlyFilesMap);
    writeFile("common", commonFilesMap);

    return 0;
}
