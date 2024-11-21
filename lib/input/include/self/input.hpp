#pragma once

#include <queue>

namespace self {

enum InputEvent {
    UNDO,
    QUIT,
};

struct Input {
static std::queue<InputEvent> queue;
};

} // namespace self
