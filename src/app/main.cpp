#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <filesystem>

#include "core/directoryReader.hpp"
#include "core/fileEntry.hpp"
#include "core/fileEntryFormat.hpp"
#include "ui/fileListComponent.hpp"

int main()
{
    using namespace ftxui;

    auto fileList = Make<dosyaci::FileListComponent>(MenuOption::VerticalAnimated());
    fileList->setFile(std::filesystem::current_path());

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(fileList);

    return 0;
}
