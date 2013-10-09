/***************************************************/
/*! \class Noise
    \brief STK noise generator.

    Generic random number generation using the
    C rand() function.  The quality of the rand()
    function varies from one OS to another.

    by Perry R. Cook and Gary P. Scavone, 1995-2011.
*/
/***************************************************/

#include "Noise.h"
#include <time.h>

namespace stk {

Noise :: Noise( unsigned int seed )
  : amplitude_(1.0)
{
  // Seed the random number generator
  this->setSeed( seed );
}

void Noise :: setSeed( unsigned int seed )
{
  if ( seed == 0 )
    srand( (unsigned int) time( NULL ) );
  else
    srand( seed );
}

void Noise :: setFrequency( StkFloat frequency) {
  // Does nothing ...
}

void Noise :: setAmplitude( StkFloat amplitude) {
  if (amplitude > 1.0) {
    amplitude_ = 1.0;
  } else if (amplitude < 0.0) {
    amplitude_ = 0.0;
  } else {
    amplitude_ = amplitude;
  }
}
} // stk namespace


