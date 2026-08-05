#pragma once

#include <filesystem>
#include <string>

enum class EntryType { Regular, Directory, Symlink, Other };

class FileEntry
{
public:
    std::filesystem::path path;
    EntryType type;
    uintmax_t size;
    std::filesystem::file_time_type mtime;
    std::filesystem::perms permissions;

    bool isDirectory() const;
    bool isSymlink() const;
    std::string name() const;
};
