#include <string>

#include "core/fileEntryFormat.hpp"

namespace dosyaci
{

std::string formatEntry(const FileEntry& entry)
{
    if (entry.isDirectory())
        return "/" + entry.name();
    else if (entry.isSymlink())
        return "@" + entry.name();
    else
        return entry.name();
}

}
