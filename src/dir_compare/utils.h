#ifndef DIR_COMPARE_UTILS_H
#define DIR_COMPARE_UTILS_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_map>

#include <openssl/md5.h>
#include <openssl/evp.h>


/**
 * Creates and returns a MD5SUM of the given file's contents.
 *
 * @param[in] filePath A std::filesystem::directory_entry path to the file being hashed.
 * @return A MD5SUM of the file's contents as a hexadecimal string.
 */
std::string getFileHash(const std::string& filePath)
{
    std::ifstream file(filePath, std::ifstream::binary);

    // Make sure file exists before hashing it.
    if(!file)
    {
        std::cout << "[ERROR] No such file: " << filePath << std::endl;
        return "";
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    char buffer[1024];
    while(file.read(buffer, sizeof(buffer)))
    {
        MD5_Update(&md5Context, buffer, file.gcount());
    }
    MD5_Update(&md5Context, buffer, file.gcount());  // Make sure we don't miss data < 1024 bytes.
    file.close();

    unsigned char result[MD5_DIGEST_LENGTH];
    MD5_Final(result, &md5Context);

    std::ostringstream hexStream;
    for(unsigned char c : result)
    {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    return hexStream.str();

//    EVP_MD_CTX* context = EVP_MD_CTX_new();
//    const EVP_MD* md = EVP_md5();  // Ensure MD5SUM is used for hash.
//    unsigned char md_value[MD5_DIGEST_LENGTH];  // 16 characters is sufficient for file comparison.
//
//    EVP_DigestInit_ex2(context, md, nullptr);
//    char buffer[1024];
//    while(file.read(buffer, sizeof(buffer)))
//    {
//        EVP_DigestUpdate(context, buffer, sizeof(buffer));
//    }
//    EVP_DigestUpdate(context, buffer, sizeof(buffer));  // Make sure we don't miss data < 1024 bytes.
//    file.close();
//    EVP_DigestFinal_ex(context, md_value, nullptr);
//    EVP_MD_CTX_free(context);
//
//    std::ostringstream hexStream;
//    for(unsigned char c : md_value)
//    {
//        hexStream << std::hex << std::setw(2) << std::setfill('0') << (int) c;
//    }
//    return hexStream.str();
}

/**
 * Creates and returns a mapping of MD5SUM file hashes to lists of files found within the given directory. By default,
 * this is done recursively for all subdirectories within the selected folder.
 *
 * @param dir A std::filesystem::directory_entry path to the directory to search for files.
 * @param recursive Whether or not to delve into subdirectories during the iterative search. Defaults to true.
 * @return A std::unordered_map<std::string, std::vector<std::string>> mapping of hash values to vectors of file path
 * strings.
 */
std::unordered_map<std::string, std::vector<std::string>> findFiles(const std::filesystem::directory_entry& dir,
                                                                    bool recursive = true)
{
    std::unordered_map<std::string, std::vector<std::string>> files;

    if(!dir.exists() || !dir.is_directory())
    {
        std::cout << "[ERROR] No such directory: " << dir << std::endl;
        return files;
    }

    for(const auto& file : std::filesystem::directory_iterator(dir))
    {
        if(file.is_directory())
        {
            if(recursive)
            {
                auto subfiles = findFiles(file);
                for(const auto& [hash, filesList] : subfiles)
                {
                    files[hash].reserve(files[hash].size() + filesList.size());
                    files[hash].insert(files[hash].end(), filesList.begin(), filesList.end());
                }
            }
        }
        else
        {
            files[getFileHash(file.path())].push_back(file.path());

//            auto hash = getFileHash(file.path());
//            std::cout << "FOUND: " << file << ", " << hash << std::endl;
        }
    }

    return files;
}

#endif //DIR_COMPARE_UTILS_H
