#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Int_Input.H>
#include <FL/fl_draw.H>

#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>
#include "Control.h"
#include "KeyboardListener.h"
#include "TickListener.h"
#include "TickController.h"

#include <boost/thread.hpp>

#define MIN_FREQ 22.0

using namespace stk;

namespace eudyp {

class MainWidget : public Fl_Widget {
protected:
  int m_x;
  int m_y;
  float m_freq;
  float m_amp;
  Fl_Color m_black;
  Fl_Color m_white;

  void draw();

  Control* m_x_controller;
  Control* m_y_controller;
  TickController* m_tick_controller;
  KeyboardListener* m_keyboard_listener;

public:
  MainWidget(TickController* tick_controller, int X,int Y,int W,int H,const char* L=0)
      : Fl_Widget(X,Y,W,H,L),
        m_tick_controller(tick_controller)
  {
    m_x = 0;
    m_y = 0;
    m_freq = MIN_FREQ;
    m_x_controller = 0;
    m_y_controller = 0;
    m_keyboard_listener = 0;

    m_black = fl_rgb_color(0, 0, 0);
    m_white = fl_rgb_color(255, 255, 255);
    // callback(&event_callback, (void*)this);
    when(FL_WHEN_NOT_CHANGED|when());
    // end();
  }
  ~MainWidget() { }

  int handle(int e);

  void attachXController(Control* controller) {
    if (m_x_controller && m_x_controller->recording()) {
      m_x_controller->stopRecording(m_tick_controller);
      m_x_controller->startPlayback(m_tick_controller);
    }
    m_x_controller = controller;
  }
  void attachYController(Control* controller) {
    if (m_y_controller && m_y_controller->recording()) {
      m_y_controller->stopRecording(m_tick_controller);
      m_y_controller->startPlayback(m_tick_controller);
    }
    m_y_controller = controller;
  }
  void attachKeyboardListener(KeyboardListener* listener) { m_keyboard_listener = listener; }
  void startRecordX() {
    if (!m_x_controller) { return; }
    m_x_controller->startRecording(m_tick_controller);
  }
  void startRecordY() {
    if (!m_y_controller) { return; }
    m_y_controller->startRecording(m_tick_controller);
  }
  void stopRecordX() {
    if (!m_x_controller) { return; }
    m_x_controller->stopRecording(m_tick_controller);
  }
  void stopRecordY() {
    if (!m_y_controller) { return; }
    m_y_controller->stopRecording(m_tick_controller);
  }
  void startPlaybackX() {
    if (!m_x_controller) { return; }
    m_x_controller->startPlayback(m_tick_controller);
  }
  void startPlaybackY() {
    if (!m_y_controller) { return; }
    m_y_controller->startPlayback(m_tick_controller);
  }

  Control* getXController() { return m_x_controller; }
  Control* getYController() { return m_y_controller; }
};

};

#endif // MAIN_WIDGET_H
