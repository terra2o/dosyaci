#pragma once

#include <ftxui/component/component.hpp>

#include "core/directoryReader.hpp"
#include "core/fileEntry.hpp"
#include "core/eventHandler.hpp"

namespace dosyaci
{
using namespace ftxui;

class FileListComponent : public ComponentBase
{
    std::vector<FileEntry> files;
    std::vector<std::string> labels_;
    Component menu_;
    int selected_{0};
    EventHandler eventHandler_;


public:
    explicit FileListComponent(MenuOption menu);

    const std::vector<FileEntry>& getFile();
    void setFile(const std::filesystem::path& dir);
    Element Render() override;


    bool OnEvent(Event event) override;
};

}
