#ifndef REVERB_H
#define REVERB_H

#include "Node.h"
#include <NRev.h>

namespace eudyp {

/*
 * Native Reverb Node
 */
class Reverb : public Node
{
  private:
    // FIXME: implement a stereo reverb class in stk!!!
    stk::NRev* m_revLPtr;
    stk::NRev* m_revRPtr;
  public:
    Reverb() {
      m_revLPtr = new stk::NRev();
      m_revRPtr = new stk::NRev();
    }
    ~Reverb() {
      if (m_revLPtr) { delete m_revLPtr; m_revLPtr = 0; }
      if (m_revRPtr) { delete m_revRPtr; m_revRPtr = 0; }
    }
    int getNumControls()  { return 1; }
    const char* getControlName(int idx) {
      switch (idx) {
        case 0: return "Time (s)";
        default: return "Error";
      }
    }
    virtual void setControlValue(int idx, double value) {
      switch (idx) {
        case 0:
          if (m_revLPtr) { m_revLPtr->setT60(value); }
          if (m_revRPtr) { m_revRPtr->setT60(value); }
          break;
      }
    }

    virtual bool acceptsInput() { return true; }
    virtual int getNumFlavours() { return 1; } // FIXME: 3 flavours in stk ...
    virtual const char* getFlavourName(int idx) {
      switch (idx) {
        case 0: return "NReverb";
        default: return "Error";
      }
    }
    virtual void setFlavour(int idx) {
      // do nothing ...
    }

    virtual stk::StkFrames& tick( stk::StkFrames& frames ) {
      if (!(m_revLPtr && m_revRPtr)) { return frames; }

      stk::StkFrames rOut(frames.frames(), frames.channels());
      stk::StkFrames lOut(frames.frames(), frames.channels());

      m_revLPtr->tick(frames, lOut, 0);
      m_revRPtr->tick(frames, rOut, 1);
      lOut.applyPan(-0.8); // allow a little bleed between channels
      rOut.applyPan(0.8);

      frames = rOut;

      frames += lOut;

      return frames;
    }
};

};

#endif // REVERB_H
