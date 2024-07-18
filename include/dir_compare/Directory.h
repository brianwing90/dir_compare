#ifndef DIR_COMPARE_DIRECTORY_H
#define DIR_COMPARE_DIRECTORY_H

#include <filesystem>
#include <vector>
#include <unordered_map>


namespace dc
{

/**
 * A reference to a directory on the file system with convenience functions for comparison against other folders.
 */
class Directory
{
public:
    /**
     * Creates and returns a new Directory object.
     *
     * @param[in] dir A C-string pointer file path to the directory represented by this object.
     */
    explicit Directory(const char* dir);

    /**
     * Creates and returns a new Directory object.
     *
     * @param[in] dir A string file path to the directory represented by this object.
     */
    explicit Directory(const std::string& dir);

    /**
     * Creates and returns a new Directory object.
     *
     * @param[in] dir A std::filesystem::directory_entry path to the directory represented by this object.
     */
    explicit Directory(const std::filesystem::directory_entry& dir);

    ~Directory() = default;

    /**
     * Populates the given hash maps by iterating over this directory and the given path to find which files are
     * unique to one, the other, or both.
     *
     * @param[in] dir A C-string pointer file path to the directory which will be compared against this object.
     * @param[out] dirAOnlyFilesMap A mapping of MD5SUM hashs to lists of files that are unique to this directory.
     * @param[out] dirBOnlyFilesMap A mapping of MD5SUM hashs to lists of files that are unique to the given comparison
     * directory.
     * @param[out] commonFilesMap A mapping of MD5SUM hashs to lists of files that are found in both directories.
     */
    void compare(const char* dir,
                 std::unordered_map<std::string, std::vector<std::string>>& dirAOnlyFilesMap,
                 std::unordered_map<std::string, std::vector<std::string>>& dirBOnlyFilesMap,
                 std::unordered_map<std::string, std::vector<std::string>>& commonFilesMap);

    /**
     * Populates the given hash maps by iterating over this directory and the given path to find which files are
     * unique to one, the other, or both.
     *
     * @param[in] dir A string file path to the directory which will be compared against this object.
     * @param[out] dirAOnlyFilesMap A mapping of MD5SUM hashs to lists of files that are unique to this directory.
     * @param[out] dirBOnlyFilesMap A mapping of MD5SUM hashs to lists of files that are unique to the given comparison
     * directory.
     * @param[out] commonFilesMap A mapping of MD5SUM hashs to lists of files that are found in both directories.
     */
    void compare(const std::string& dir,
                 std::unordered_map<std::string, std::vector<std::string>>& dirAOnlyFilesMap,
                 std::unordered_map<std::string, std::vector<std::string>>& dirBOnlyFilesMap,
                 std::unordered_map<std::string, std::vector<std::string>>& commonFilesMap);

    /**
     * Populates the given hash maps by iterating over this directory and the given path to find which files are
     * unique to one, the other, or both.
     *
     * @param[in] dir A std::filesystem::directory_entry path to the directory which will be compared against this object.
     * @param[out] dirAOnlyFilesMap A mapping of MD5SUM hashs to lists of files that are unique to this directory.
     * @param[out] dirBOnlyFilesMap A mapping of MD5SUM hashs to lists of files that are unique to the given comparison
     * directory.
     * @param[out] commonFilesMap A mapping of MD5SUM hashs to lists of files that are found in both directories.
     */
    void compare(const std::filesystem::directory_entry& dir,
                 std::unordered_map<std::string, std::vector<std::string>>& dirAOnlyFilesMap,
                 std::unordered_map<std::string, std::vector<std::string>>& dirBOnlyFilesMap,
                 std::unordered_map<std::string, std::vector<std::string>>& commonFilesMap);

private:
    // A std::filesystem::directory_entry object of this directory's path.
    std::filesystem::directory_entry m_dir;
};

}

#endif //DIR_COMPARE_DIRECTORY_H
