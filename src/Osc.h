#ifndef OSC_H
#define OSC_H

#include "Stk.h"
#include "Node.h"
#include "SineWave.h"
#include "Noise.h"
#include "Blit.h"
#include "BlitSaw.h"
#include "BlitSquare.h"

namespace eudyp {

// 
#define MIN_MIN_FREQUENCY 15.0
#define MAX_MAX_FREQUENCY 20000.0

#define MIN_MIN_AMPLITUDE 0.0
#define MAX_MAX_AMPLITUDE 0.5

class Osc : public Node {
  private:
    stk::Generator* m_generator;
    volatile int m_flavour;

    Control m_frequency;
    Control m_amplitude;
    Control m_pan;
    Control m_width;
    Control m_phase;

  public:
    /*
    Osc() :
      m_generator(0),
      m_frequency(this, 0, POW2, false, MIN_MIN_FREQUENCY, MAX_MAX_FREQUENCY, 220.5),
      m_amplitude(this, 1, LINEAR, true, MIN_MIN_AMPLITUDE, MAX_MAX_AMPLITUDE, 0.25),
      m_pan(this, 2, LINEAR, false, -1.0, 1.0, 0.0),
      m_width(this, 3, LINEAR, false, -1.0, 1.0, 0.0),
      m_phase(this, 4, LINEAR, false, -1.0, 1.0, 0.0)
    {
      setFlavour(0);
    }
    */

    Osc(int flavour) :
      m_generator(0),
      m_frequency(this, 0, POW2, true, MIN_MIN_FREQUENCY, MAX_MAX_FREQUENCY, 220.5),
      m_amplitude(this, 1, LINEAR, true, MIN_MIN_AMPLITUDE, MAX_MAX_AMPLITUDE, 0.25),
      m_pan(this, 2, LINEAR, true, -1.0, 1.0, 0.0),
      m_width(this, 3, LINEAR, false, -1.0, 1.0, 0.0),
      m_phase(this, 4, LINEAR, false, -1.0, 1.0, 0.0)
    {
      setFlavour(flavour);
    }

    virtual bool acceptsInput() { return false; }

    virtual int getNumControls() { return 5; }
    virtual const char* getControlName(int idx) {
      switch (idx) {
        case 0: return "Frequency";
        case 1: return "Amplitude";
        case 2: return "Pan";
        case 3: return "Width"; // what does this do on Sin?
        case 4: return "Phase";
        default: return "Error";
      }
    }

    virtual void setControlValue(int idx, double value)
    {
      if (!m_generator) {return; }
      switch (idx) {
        case 0:
          // std::cerr << "Setting Frequence " << value << std::endl;
          m_generator->setFrequency(value);
          break;
        case 1:
          // std::cerr << "Setting Amplitude " << value << std::endl;
          m_generator->setAmplitude(value);
          break;
        case 2: break; // PAN - tbd
        case 3: break; // width - tbd
        case 4: break; // phase - tbd
      }
    }

    virtual Control& control(int idx) {
      switch (idx) {
        case 0: return m_frequency;
        case 1: return m_amplitude;
        case 2: return m_pan;
        case 3: return m_width;
        case 4: return m_phase;
        default: return m_frequency;
      }
    }

    virtual int getNumFlavours() { return 5; }
    virtual const char* getFlavourName(int idx) {
      switch (idx) {
        case 0: return "Sin";
        case 1: return "Pulse";
        case 2: return "Saw";
        case 3: return "Square";
        case 4: return "Noise";
      }
      return "Unknown";
    }
    virtual void setFlavour(int idx) {
      if (m_generator) { delete m_generator; m_generator = 0; }

      switch (idx) {
        case 0: m_generator = new stk::SineWave(); break;
        case 1: m_generator = new stk::Blit(); break; // impulse train
        case 2: m_generator = new stk::BlitSaw(); break; // blit saw
        case 3: m_generator = new stk::BlitSquare(); break;
        case 4: m_generator = new stk::Noise(); break; // bring the noise!
        default: std::cerr << "ERROR: unknown flavour: " << idx << std::endl;
      }
    }
    virtual stk::StkFloat tick( void ) {
      if (!m_generator) { return 0; }
      return m_generator->tick();
    }
    virtual stk::StkFrames& tick( stk::StkFrames& frames ) {
      if (!m_generator) { return frames; }
      m_generator->tick(frames, 0);
      frames.copyChannelWithPan(0, 1, m_pan.getValue());
      return frames;
    }
};
};
#endif // OSC_H
