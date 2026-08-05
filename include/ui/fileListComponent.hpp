#pragma once

#include <ftxui/component/component.hpp>

#include "core/directoryReader.hpp"
#include "core/fileEntry.hpp"

namespace dosyaci
{

class FileListComponent : public ftxui::ComponentBase
{
    std::vector<FileEntry> files;
    std::vector<std::string> labels_;
    ftxui::Component menu_;
    int selected_{0};


public:
    explicit FileListComponent(ftxui::MenuOption menu);

    const std::vector<FileEntry>& getFile();
    void setFile(const std::filesystem::path& dir);
    ftxui::Element Render() override;
};

}
