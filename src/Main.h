#ifndef MAIN_H
#define MAIN_H

#include <set>

#include <FL/Fl_Double_Window.H>
#include "MainWidget.h"
#include "KeyboardListener.h"
#include "TickListener.h"
#include "Node.h"

namespace eudyp {
  class Main : public TickController {
    private:
      Fl_Double_Window m_window;
      MainWidget m_mainWidget;
      KeyboardListener* m_keymapPtr;
      std::list<Node* > m_nodes;
      std::list<Node* > m_effects;
      std::set<TickListener* > m_tickListeners;
    public:
      Main(int argc, char** argv);
      std::set<TickListener* >::iterator first_tick_listener() { return m_tickListeners.begin(); }
      std::set<TickListener* >::iterator last_tick_listener() { return m_tickListeners.end(); }
      std::list<Node* >::iterator first_node() { return m_nodes.begin(); }
      std::list<Node* >::iterator last_node() { return m_nodes.end(); }

      std::list<Node* >::iterator first_effect() { return m_effects.begin(); }
      std::list<Node* >::iterator last_effect() { return m_effects.end(); }

      void addTickListener(TickListener* listener) {
        m_tickListeners.insert(listener);
      }
      void removeTickListener(TickListener* listener) {
        m_tickListeners.erase(listener);
      }
  };
};
#endif
