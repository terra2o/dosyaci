#pragma once

#include "ftxui/component/event.hpp"

#include "core/action.hpp"
#include "core/mode.hpp"

#include <optional>
#include <string>

namespace dosyaci
{

using namespace ftxui;

struct DispatchResult
{
    Action action{ Action::None };
    int count{ 1 };
};

class EventHandler
{

public:
    DispatchResult Handle(Event event);

private:
    bool handleNormal(Event event, DispatchResult& result);
    bool handleCommand(Event event, DispatchResult& result); // vim-like commands

    void resetPending();
    void resetBuffer();
    std::optional<int> tryConsumeCount(Event event);

    std::string pendingSequence_;
    std::string commandBuffer_;
    int pendingCount_{ 0 };

    Mode mode_{ Mode::Normal };
};

}
