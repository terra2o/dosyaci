#include <string>
#include <iterator>
#include <vector>

#include "ui/fileListComponent.hpp"
#include "core/fileEntryFormat.hpp"

namespace dosyaci
{

FileListComponent::FileListComponent(ftxui::MenuOption menu)
    : menu_ ( ftxui::Menu(&labels_, &selected_, menu) )
    {
        Add(menu_);
    }

const std::vector<FileEntry>& FileListComponent::getFile()
{
    return files;
}

void FileListComponent::setFile(const std::filesystem::path& dir)
{
    files = listDirectory(dir);
    labels_.clear();
    for (auto& file : files)
        labels_.push_back(dosyaci::formatEntry(file));
}

ftxui::Element FileListComponent::Render()
{
    return menu_->Render();
}

}
