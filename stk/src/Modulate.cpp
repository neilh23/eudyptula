/***************************************************/
/*! \class Modulate
    \brief STK periodic/random modulator.

    This class combines random and periodic
    modulations to give a nice, natural human
    modulation function.

    by Perry R. Cook and Gary P. Scavone, 1995-2011.
*/
/***************************************************/

#include "Modulate.h"

namespace stk {

Modulate :: Modulate( void )
{
  vibrato_.setFrequency( 6.0 );
  vibratoGain_ = 0.04;

  noiseRate_ = (unsigned int) ( 330.0 * Stk::sampleRate() / 22050.0 );
  noiseCounter_ = noiseRate_;

  randomGain_ = 0.05;
  filter_.setPole( 0.999 );
  filter_.setGain( randomGain_ );

  Stk::addSampleRateAlert( this );
}

Modulate :: ~Modulate( void )
{
  Stk::removeSampleRateAlert( this );
}

void Modulate :: sampleRateChanged( StkFloat newRate, StkFloat oldRate )
{
  if ( !ignoreSampleRateChange_ )
    noiseRate_ = (unsigned int ) ( newRate * noiseRate_ / oldRate );
}

void Modulate :: setRandomGain( StkFloat gain )
{
  randomGain_ = gain;
  filter_.setGain( randomGain_ );
}

void Modulate :: setFrequency (StkFloat freq)
{
  vibrato_.setFrequency(freq);
}

void Modulate::setAmplitude( StkFloat amplitude)
{
  if (amplitude > 1.0) {
    amplitude_ = 1.0;
  } else if ( amplitude < 0.0) {
    amplitude_ = 0.0;
  } else {
    amplitude_ = amplitude;
  }
}
} // stk namespace
