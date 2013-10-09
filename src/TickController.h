#ifndef TICK_CONTROLLER_H
#define TICK_CONTROLLER_H

namespace eudyp {
class TickListener;

class TickController {
  public:
    virtual void addTickListener(TickListener* listener) = 0;
    virtual void removeTickListener(TickListener* listener) = 0;
};
};
#endif // TICK_CONTROLLER_H
