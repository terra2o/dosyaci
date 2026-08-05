#include "core/directoryReader.hpp"

namespace dosyaci
{

std::vector<FileEntry> listDirectory(const std::filesystem::path& dir)
{
    std::vector<FileEntry> result;

    std::error_code dirEc;
    std::filesystem::directory_iterator it(dir, dirEc);
    if (dirEc)
        return result;

    for (const auto& dirEntry : it)
    {
        FileEntry entry;
        entry.path = dirEntry.path();

        std::error_code ec;
        if (dirEntry.is_symlink(ec))
            entry.type = EntryType::Symlink;
        else if (dirEntry.is_directory(ec))
            entry.type = EntryType::Directory;
        else if (dirEntry.is_regular_file(ec))
            entry.type = EntryType::Regular;
        else
            entry.type = EntryType::Other;

        entry.size = dirEntry.is_regular_file(ec) ? dirEntry.file_size(ec) : 0;
        entry.mtime = dirEntry.last_write_time(ec);
        entry.permissions = dirEntry.status(ec).permissions();

        result.push_back(std::move(entry));
    }

    return result;
}

}
