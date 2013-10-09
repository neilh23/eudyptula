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

#include <boost/thread.hpp>

using namespace stk;

#define MAX_FREQ 15000.0
#define MIN_FREQ 22.0

float s_freq1 = 22;
float s_freq2 = 22;
float s_amp1 = 0.5;
float s_amp2 = 0.5;

int s_selected = 1;

class MainWidget : public Fl_Widget {
protected:
  int m_x;
  int m_y;
  float m_freq;
  float m_amp;
  Fl_Color m_black;
  Fl_Color m_white;

  void draw() {
     char thetext[256];

     const char* selected = ((s_selected == 1) ? "A" : "S");

     sprintf(thetext, "%s W: %d, H: %d X: %d, Y: %d. Freq: %.2f, Amp: %.2f", selected, w(), h(), m_x, m_y, m_freq, m_amp);
     // printf("In draw: %s\n", thetext);

     fl_color(m_white);
     fl_rectf(0, 0, w(), h());
     fl_color(m_black);
     fl_point(m_x, m_y);

     fl_font(FL_HELVETICA_BOLD, 15);
     fl_draw(thetext, x(), 40);
  }

public:
  MainWidget(int X,int Y,int W,int H,const char* L=0) : Fl_Widget(X,Y,W,H,L) {
    m_x = 0;
    m_y = 0;
    m_freq = MIN_FREQ;

    m_black = fl_rgb_color(0, 0, 0);
    m_white = fl_rgb_color(255, 255, 255);
    // callback(&event_callback, (void*)this);
    when(FL_WHEN_NOT_CHANGED|when());
    // end();
  }
  ~MainWidget() { }

  int handle(int e);

};

MainWidget *widget;

// Handle drawing all cells in table

// Callback whenever someone clicks on different parts of the table
int MainWidget::handle(int e) {
  int ret = 0;
  if (e == FL_ENTER || e == FL_FOCUS) {
    ret = 1;
  } else if (e == FL_MOVE) {
    ret = 1;
     m_x = Fl::event_x() - x();
     m_y = Fl::event_y() - y();
     int width = w() - x();
     int height = h() - y();

     m_freq = ((((MAX_FREQ - MIN_FREQ)*(pow((float)m_x, 2))))/(pow((float)width,2))) + MIN_FREQ;
     m_amp = ((float)(height - m_y))/(float)(height);
     if (s_selected == 1) {
       s_freq1 = m_freq;
       s_amp1 = m_amp;
     } else {
       s_freq2 = m_freq;
       s_amp2 = m_amp;
     }
     //  printf("FL_MOVE: %d, %d\n",m_x, m_y);
    widget->redraw();
  } else if (e == FL_KEYDOWN) {
     if (Fl::event_key() == 'q') {
       exit(0);
     }
     if (Fl::event_key() == 'a') {
       s_selected = 1;
     } else if (Fl::event_key() == 's') {
       s_selected = 2;
     }
  } else {
    // printf("handle called not MOVE: %d\n", e);
  }
  return ret;
}

void audio_thread() {
  // Set the global sample rate before creating class instances.
  Stk::setSampleRate( 44100.0 );
  Stk::showWarnings( true );

  SineWave sine1;
  SineWave sine2;
  // SineWave lfo;
  RtWvOut *dac = 0;

  try {
    // Define and open the default realtime output device for one-channel playback
    dac = new RtWvOut( 2 );
  }
  catch ( StkError & ) {
    exit( 1 );
  }

  try {
    while(1) {
      sine1.setFrequency( s_freq1 );
      sine2.setFrequency( s_freq2 );

      // dac->tick( sine.tick() * lfo.tick() * 0.25  );
      dac->tick( ((sine1.tick() * s_amp1 ) + (sine2.tick() * s_amp2 )) * 0.01  );
    }
  }
  catch ( StkError & ) {
    goto cleanup;
  }

 cleanup:
  delete dac;
}

int main(int argc, char** argv) {
  Fl_Double_Window window(800,600);
  widget = new MainWidget(10, 10, 800, 600, "IA IA PINGU");
  // Show window
  window.end();
  window.show(argc, argv);
  boost::thread workerThread(audio_thread); 
  return Fl::run();
}

