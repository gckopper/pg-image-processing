#pragma once

namespace self {

class Screen {
  public:
    virtual void render() = 0;
    virtual void render_ui() = 0;
    virtual void logic() = 0;
    virtual void update_ui() = 0;
    virtual bool init(int argc, char** argv) = 0;
    virtual void quit() = 0;
};

} // namespace self
