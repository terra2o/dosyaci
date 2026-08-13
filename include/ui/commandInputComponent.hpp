#pragma once

#include <ftxui/component/component.hpp>

#include "core/eventHandler.hpp"

namespace dosyaci
{
using namespace ftxui;

class CommandInputComponent : public ComponentBase
{
    EventHandler& eventHandler_;

public:
    explicit CommandInputComponent(EventHandler& eventHandler);
    std::string showCommandBuffer();
    Element Render() override;
};

}
