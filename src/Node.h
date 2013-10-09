#ifndef NODE_H
#define NODE_H
namespace eudyp {

// 
#define MIN_MIN_FREQUENCY 15.0
#define MAX_MAX_FREQUENCY 20000.0

#define MIN_MIN_AMPLITUDE 0.0
#define MAX_MAX_AMPLITUDE 0.5

class Node {
  public:
    virtual int getNumControls() = 0;
    virtual const char* getControlName(int idx) = 0;
    // virtual void tweakControl(int idx, double amount) = 0;
    virtual void setControlValue(int idx, double value) = 0;

    virtual bool acceptsInput() = 0;
    virtual int getNumFlavours() = 0;
    virtual const char* getFlavourName(int idx) = 0;
    virtual void setFlavour(int idx) = 0;

    // default ticks do absolutely nothing :-)
    virtual stk::StkFloat tick( void ) { return 0; }
    virtual stk::StkFrames& tick( stk::StkFrames& frames ) { return frames; }
};

};

#endif // NODE_H
