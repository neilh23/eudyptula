#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H
namespace eudyp {
  class KeyboardListener {
    public:
      virtual void keyDownEvent(char key) = 0;
      virtual void keyUpEvent(char key) = 0;
      virtual void mouseDownEvent(int button) = 0;
      virtual void mouseUpEvent(int button) = 0;
  };
};
#endif // KEYBOARD_LISTENER_H
