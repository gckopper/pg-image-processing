#pragma once

namespace self {

class Screen {
  public:
    virtual void render() = 0;
    virtual void logic() = 0;
    virtual bool init() = 0;
    virtual void quit() = 0;
};

} // namespace self
