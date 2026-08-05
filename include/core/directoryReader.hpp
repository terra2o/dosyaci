#pragma once

#include "core/fileEntry.hpp"
#include <filesystem>
#include <vector>

namespace dosyaci
{

std::vector<FileEntry> listDirectory(const std::filesystem::path& dir);

}

