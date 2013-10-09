#ifndef MY_KEY_MAP_H
#define MY_KEY_MAP_H

#include <map>

#include "KeyboardListener.h"
#include "MainWidget.h"
#include "Osc.h"
/*
 * Throughaway listener class for getting stuff up and working
 */
namespace eudyp {
  class MyKeyMap : public KeyboardListener
  {
    private:
      std::map<char, Osc*> m_oscillators;
      MainWidget* m_mw;
      bool m_quantise;
      long m_quantiseValue;
    public:
      MyKeyMap(const std::map<char, Osc*>& oscillators, MainWidget* mw, bool quantise)
        : m_oscillators(oscillators), m_mw(mw), m_quantiseValue(-1)
      { }

      virtual void keyDownEvent(char key) {
        // std::cerr << "keyDownEvent called" << std::endl;
        if (!m_mw) return;

        Osc* osc = m_oscillators[key];

        if (osc) {
            osc->control(1).setValue(1.0);

            m_mw->attachXController(&(osc->control(2)));
            // m_mw->attachYController(&(osc->control(1)));
            m_mw->attachYController(&(osc->control(0)));
        }
      }
      virtual void keyUpEvent(char key) {
        // do nothing!
      }

      virtual void mouseDownEvent(int button)
      {
        // std::cerr << "Mousedown: " << button << std::endl;
        if (button == 1) {
          m_mw->startRecordX();
          m_mw->startRecordY();
        }
      }

      virtual void mouseUpEvent(int button)
      {
        std::cerr << "Mouseup: " << button << std::endl;
        if (button == 1) {
          m_mw->stopRecordX();
          m_mw->stopRecordY();
          if (m_quantise) {
            Control* xc = m_mw->getXController();
            Control* yc = m_mw->getXController();
            RecordBuffer* xr = 0;
            RecordBuffer* yr = 0;
            if (xc) { xr = xc->getRecordBuffer(); }
            if (yc) { yr = yc->getRecordBuffer(); }

            if (m_quantiseValue < 0) {
              if (xr) {
                m_quantiseValue = xr->getSize();
                if (yr) {
              }
              if (yr) {
                  if (m_quantiseValue > 0) {
                    yr->quantise(m_quantiseValue); // should do nothing if they're the same anyway ...
                  } else {
                    m_quantiseValue = yr->getSize();
                  }
                }
              }
            } else {
              if (xr) { xr->quantise(m_quantiseValue); }
              if (yr) { yr->quantise(m_quantiseValue); }
            }
          }
          m_mw->startPlaybackX();
          m_mw->startPlaybackY();
        }
      }
  };
};
#endif // MY_KEY_MAP_H
