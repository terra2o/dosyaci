#include <string>
#include <iterator>
#include <vector>
#include <unistd.h>
#include <stdlib.h>

#include "ui/fileListComponent.hpp"
#include "core/directoryReader.hpp"
#include "core/fileEntryFormat.hpp"
#include "core/fileEntry.hpp"
#include "core/eventHandler.hpp"

namespace dosyaci
{

FileListComponent::FileListComponent(ftxui::MenuOption menu)
    : menu_ ( ftxui::Menu(&labels_, &selected_, menu) )
    {
        Add(menu_);
    }

const std::vector<FileEntry>& FileListComponent::getFiles()
{
    return files;
}

void FileListComponent::setDir(const std::filesystem::path& dir)
{
    currentDir_ = dir;
    files = listDirectory(dir);
    labels_.clear();
    for (auto& file : files)
        labels_.push_back(dosyaci::formatEntry(file));
}

FileEntry FileListComponent::getSelectedFileEntry()
{
    return getFiles()[selected_];
}

void FileListComponent::execute(const std::filesystem::path& path)
{
    std::string pathString{ path.generic_string() };
    std::string formattedString{ "xdg-open " + pathString };
    const char* formatted{ formattedString.c_str() };
    system(formatted);
}

ftxui::Element FileListComponent::Render()
{
    return menu_->Render()
        | ftxui::vscroll_indicator
        | ftxui::frame
        | ftxui::border;
}

bool FileListComponent::OnEvent(Event event)
{
    const DispatchResult result{ eventHandler_.Handle(event) };

    switch (result.action)
    {
        case Action::Enter:
            if (getSelectedFileEntry().isDirectory())
                setDir(getSelectedFileEntry().path);
            else
                execute(getSelectedFileEntry().path);
            return true;

        case Action::MoveRight: // same as Enter
            if (getSelectedFileEntry().isDirectory())
                setDir(getSelectedFileEntry().path);
            else
                execute(getSelectedFileEntry().path);
            return true;

        case Action::MoveLeft:
            setDir(currentDir_.parent_path());
            return true;

        case Action::MoveDown:
            for (int i = 0; i < result.count; ++i)
                menu_->OnEvent(Event::ArrowDown);
            return true;

        case Action::MoveUp:
            for (int i = 0; i < result.count; ++i)
                menu_->OnEvent(Event::ArrowUp);
            return true;

        case Action::GoToTop:
            OnEvent(Event::Home);
            return true;

        case Action::GoToBottom:
            OnEvent(Event::End);
            return true;

        case Action::None:
        default:
            break;
    }

    return menu_->OnEvent(event);
}

}
