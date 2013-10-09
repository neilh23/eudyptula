#include "Audio.h"
#include "Main.h"

using namespace stk;

namespace eudyp {
  Audio::Audio(Main* main)
    : m_mainPtr(main)
  {
    initialise();
  }

  Audio::~Audio()
  {
    delete m_dac;
    m_dac = 0;
  }

  void Audio::initialise()
  {
    std::cerr << "Initialising audio" << std::endl;
    Stk::setSampleRate( 44100.0 );
    Stk::showWarnings( true );
    try {
    // Define and open the default realtime output device for one-channel playback
      m_dac = new RtWvOut( 2 );
    }
    catch ( StkError & ) {
      // FIXME: print out error!
      exit( 1 );
    }
    std::cerr << "initialised DAC" << std::endl;
  }

  void Audio::tick()
  {
    std::set<TickListener* >::iterator tick_it = m_mainPtr->first_tick_listener();
    while(tick_it != m_mainPtr->last_tick_listener()) {
      (*tick_it)->tick();
      tick_it++;
    }

    StkFrames frame(1, 2);
    static StkFrames tframe(1, 2);

    std::list<Node* >::iterator node_it = m_mainPtr->first_node();
    while(node_it != m_mainPtr->last_node()) {
      frame += (*node_it)->tick(tframe);

      node_it++;
    }

    node_it = m_mainPtr->first_effect();

    while(node_it != m_mainPtr->last_effect()) {
      frame = (*node_it)->tick(frame);
      node_it++;
    }

    frame *= 0.03; // NDH: fixme, stupid soundcard ...
    m_dac->tick( frame  );
  }

};
