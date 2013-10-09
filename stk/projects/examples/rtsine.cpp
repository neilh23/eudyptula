// rtsine.cpp STK tutorial program

#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>

using namespace stk;

int main()
{
  // Set the global sample rate before creating class instances.
  Stk::setSampleRate( 44100.0 );
  Stk::showWarnings( true );

  int nFrames = 100000;
  SineWave sine;
  SineWave lfo;
  RtWvOut *dac = 0;

  try {
    // Define and open the default realtime output device for one-channel playback
    dac = new RtWvOut( 2 );
  }
  catch ( StkError & ) {
    exit( 1 );
  }

  sine.setFrequency( 441.0 );
  lfo.setFrequency( 0.2 );

  bool high = true;
  // StkFrames frames( nFrames, 2 );
  try {
    for(int i = 0; i < nFrames; i++) {
      dac->tick( sine.tick() * lfo.tick() * 0.25  );
    }
  }
  catch ( StkError & ) {
    goto cleanup;
  }

 cleanup:
  delete dac;

  return 0;
}
