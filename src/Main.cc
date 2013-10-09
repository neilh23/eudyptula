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

#include "Control.h"
#include "Osc.h"
#include "Reverb.h"
#include "MainWidget.h"
#include "MyKeyMap.h"
#include "Audio.h"
#include "Main.h"

using namespace stk;
using namespace eudyp;

eudyp::Main::Main(int argc, char** argv)
  : m_window(800, 600),
    m_mainWidget(this, 10, 10, 800, 600, "IA IA PINGU"),
    m_keymapPtr(0)
{
  std::map<char, Osc* > oscs;
  Osc* osc1 = new Osc(0);
  Osc* osc2 = new Osc(0);
  Osc* osc3 = new Osc(2);
  Reverb* rev = new Reverb();

  osc1->control(0).setMaxValue(880);
  osc2->control(0).setMaxValue(1760);
  osc3->control(0).setMaxValue(1760);

  osc1->control(1).setValue(0.0);
  osc2->control(1).setValue(0.0);
  osc3->control(1).setValue(0.0);

  oscs['a'] = osc1;
  oscs['b'] = osc2;
  oscs['c'] = osc3;

  m_nodes.push_back(osc1);
  m_nodes.push_back(osc2);
  m_nodes.push_back(osc3);

  m_effects.push_back(rev);

  m_window.end();
  m_window.show(argc, argv);
  m_keymapPtr = new MyKeyMap(oscs, &m_mainWidget, true);
  m_keymapPtr->keyDownEvent('a'); // hack - simulate initial attachment ...
  m_mainWidget.attachKeyboardListener(m_keymapPtr);
}

Main* s_main;

void audio_thread() {
  std::cerr << "Running audio thread" << std::endl;
  Audio audio(s_main);

  while(true) {
    audio.tick();
  }
}

int main(int argc, char** argv) {
  s_main = new Main(argc, argv);

  boost::thread workerThread(audio_thread);
  return Fl::run();
}
