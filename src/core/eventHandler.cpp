#include "core/eventHandler.hpp"

#include <cctype>

namespace dosyaci
{

DispatchResult EventHandler::Handle(Event event)
{
    DispatchResult result{};

    if (event == Event::Escape)
    {
        EventHandler::resetPending();
        mode_ = Mode::Normal;
    }

    switch (mode_)
    {
        case Mode::Normal:
            handleNormal(event, result);
            break;
        case Mode::Command:
            handleCommand(event, result);
            break;
        default:
            break;
    }
    return result;
}

bool EventHandler::handleNormal(Event event, DispatchResult& result)
{
    if (tryConsumeCount(event).has_value())
        return true;

    const int count{ pendingCount_ > 0 ? pendingCount_ : 1};

    if (event.is_character())
    {
        pendingSequence_ += event.input();

        if (pendingSequence_ == "g")
            return true; // wait for second 'g'

        if (pendingSequence_ == "gg")
        {
            result.action = Action::GoToTop;
            result.count = count;
            EventHandler::resetPending();
            return true;
        }

        EventHandler::resetPending();
    }

    return false;
}

bool EventHandler::handleCommand(Event event, DispatchResult& result)
{
    if (event != Event::Return)
        commandBuffer_ += event.input();

    if (event == Event::Return)
    {
        if (commandBuffer_ == "q")
        {
            result.action = Action::Quit;
            EventHandler::resetBuffer();
            return true;
        }
    }

    return false;
}

void EventHandler::resetBuffer()
{
    commandBuffer_.clear();
}

void EventHandler::resetPending()
{
    pendingSequence_.clear();
    pendingCount_ = 0;
}

std::optional<int> EventHandler::tryConsumeCount(Event event)
{
    if (!event.is_character() || event.input().size() != 1)
        return std::nullopt;

    const char digit{ event.input()[0] };

    if (!std::isdigit(static_cast<unsigned char>(digit)))
        return std::nullopt;

    if (digit == '0' && pendingCount_ == 0)
        return std::nullopt; // bare '0' is the go-to-line-start motion, not a count digit

    pendingCount_ = pendingCount_ * 10 + (digit - '0');
    return pendingCount_;
}

}

