#ifndef TICK_LISTENER_H
#define TICK_LISTENER_H
namespace eudyp {
  class TickListener {
    public:
      virtual void tick() = 0;
  };
};
#endif // TICK_LISTENER_H
