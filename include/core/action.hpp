// core/action.hpp
#pragma once
namespace dosyaci {
enum class Action {
    None,
    MoveDown,         // these are handled but here anways just in case
    MoveUp,           // these are handled but here anways just in case
    MoveLeft,         // go to parent dir
    MoveRight,        // enter dir
    Enter,            // enter dir too?
    GoToTop,          // gg
    GoToBottom,       // G
    DeleteEntry,      // dd
    EnterCommandMode, // :
    Quit,             // ZZ or :q
};
}
