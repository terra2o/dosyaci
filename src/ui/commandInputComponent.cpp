#include "ui/commandInputComponent.hpp"

namespace dosyaci
{

CommandInputComponent::CommandInputComponent(EventHandler& eventHandler)
    : eventHandler_( eventHandler )
    {

    }

std::string CommandInputComponent::showCommandBuffer()
{
    return eventHandler_.getCommandBuffer();
}

ftxui::Element CommandInputComponent::Render()
{
    return ftxui::text(":" + showCommandBuffer());
}

}
