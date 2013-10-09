#ifndef AUDIO_H
#define AUDIO_H

#include "RtWvOut.h"

namespace eudyp {
  class Main;

  class Audio {
    private:
      Main* m_mainPtr; 
      stk::RtWvOut* m_dac;
      void initialise();
    public:
      Audio(Main* main);
      ~Audio();
      void tick();
  };
};
#endif
