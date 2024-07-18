#include "dir_compare/Directory.h"

#include "utils.h"

namespace dc
{

Directory::Directory(const char* dir) : m_dir(dir)
{

}

Directory::Directory(const std::string& dir) : m_dir(dir)
{

}

Directory::Directory(const std::filesystem::directory_entry& dir) : m_dir(dir)
{

}

void Directory::compare(const char* dir,
                        std::unordered_map<std::string, std::vector<std::string>>& dirAOnlyFilesMap,
                        std::unordered_map<std::string, std::vector<std::string>>& dirBOnlyFilesMap,
                        std::unordered_map<std::string, std::vector<std::string>>& commonFilesMap)
{
    Directory::compare(std::filesystem::directory_entry(dir), dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap);
}

void Directory::compare(const std::string& dir,
                        std::unordered_map<std::string, std::vector<std::string>>& dirAOnlyFilesMap,
                        std::unordered_map<std::string, std::vector<std::string>>& dirBOnlyFilesMap,
                        std::unordered_map<std::string, std::vector<std::string>>& commonFilesMap)
{
    Directory::compare(std::filesystem::directory_entry(dir), dirAOnlyFilesMap, dirBOnlyFilesMap, commonFilesMap);
}

void Directory::compare(const std::filesystem::directory_entry& dir,
                        std::unordered_map<std::string, std::vector<std::string>>& dirAOnlyFilesMap,
                        std::unordered_map<std::string, std::vector<std::string>>& dirBOnlyFilesMap,
                        std::unordered_map<std::string, std::vector<std::string>>& commonFilesMap)
{
    auto myFilesMap = findFiles(m_dir);
    auto otherDirFilesMap = findFiles(dir);

    for(const auto& [hash, filesList] : myFilesMap)
    {
        if(otherDirFilesMap.find(hash) != otherDirFilesMap.end())
        {
            commonFilesMap[hash].reserve(filesList.size() + otherDirFilesMap[hash].size());
            commonFilesMap[hash].insert(commonFilesMap[hash].end(), filesList.begin(), filesList.end());
            commonFilesMap[hash].insert(commonFilesMap[hash].end(), otherDirFilesMap[hash].begin(), otherDirFilesMap[hash].end());
        }
        else
        {
            dirAOnlyFilesMap[hash] = filesList;
        }
    }

    for(const auto& [hash, filesList] : otherDirFilesMap)
    {
        if(myFilesMap.find(hash) == myFilesMap.end())
        {
            dirBOnlyFilesMap[hash] = filesList;
        }
    }
}

}