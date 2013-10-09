#include "MainWidget.h"

namespace eudyp {

// Handle drawing all cells in table

// Callback whenever someone clicks on different parts of the table
int MainWidget::handle(int e) {
  int ret = 0;
  if (e == FL_ENTER || e == FL_FOCUS) {
    ret = 1;
  } else if (e == FL_MOVE || e == FL_DRAG) {
    ret = 1;
    m_x = Fl::event_x() - x();
    m_y = Fl::event_y() - y();

    int width = w() - x();
    int height = h() - y();

    if (m_x_controller) {
      m_x_controller->setNormalisedValue(((double)m_x)/(double)width);
    }
    if (m_y_controller) {
      m_y_controller->setNormalisedValue(((double)m_y)/(double)height);
    }

    this->redraw();
  } else if (e == FL_KEYDOWN) {
    if (m_keyboard_listener) {
      m_keyboard_listener->keyDownEvent(Fl::event_key());
    }
  } else if (e == FL_KEYUP) {
    if (m_keyboard_listener) {
      m_keyboard_listener->keyUpEvent(Fl::event_key());
    }
  } else if (e == FL_PUSH) {
    if (m_keyboard_listener) {
      m_keyboard_listener->mouseDownEvent(Fl::event_button());
      ret = 1;
    }
  } else if (e == FL_RELEASE) {
    if (m_keyboard_listener) {
      m_keyboard_listener->mouseUpEvent(Fl::event_button());
      ret = 1;
    }
  } else {
    // printf("handle called not MOVE: %d\n", e);
  }
  return ret;
}

void MainWidget::draw() {
   char thetext[256];

   // const char* selected = ((s_selected == 1) ? "A" : "S");

   //sprintf(thetext, "%s W: %d, H: %d X: %d, Y: %d. Freq: %.2f, Amp: %.2f", selected, w(), h(), m_x, m_y, m_freq, m_amp);
   sprintf(thetext, "W: %d, H: %d X: %d, Y: %d.", w(), h(), m_x, m_y);
   // printf("In draw: %s\n", thetext);

   fl_color(m_white);
   fl_rectf(0, 0, w(), h());
   fl_color(m_black);
   fl_point(m_x, m_y);

   fl_font(FL_HELVETICA_BOLD, 15);
   fl_draw(thetext, x(), 40);
}

};
