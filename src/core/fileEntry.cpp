#include "core/fileEntry.hpp"

bool FileEntry::isDirectory() const { return type == EntryType::Directory; }
bool FileEntry::isSymlink() const { return type == EntryType::Symlink; }
std::string FileEntry::name() const { return path.filename().string(); }
