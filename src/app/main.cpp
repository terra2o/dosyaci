#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <filesystem>
#include <iostream>

#include "core/directoryReader.hpp"
#include "core/fileEntry.hpp"
#include "core/fileEntryFormat.hpp"
#include "ui/fileListComponent.hpp"

int main(int argc, char *argv[])
{
    if (argc >= 3)
    {
        std::cerr << "There must be one argument.";
        return 1;
    }

    using namespace ftxui;

    auto fileList = Make<dosyaci::FileListComponent>(MenuOption::VerticalAnimated());

    if (argc == 1)
        fileList->setFile(std::filesystem::current_path());
    else if (argc == 2)
        fileList->setFile(argv[1]);

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(fileList);

    return 0;
}
