#ifndef CONTROL_H
#define CONTROL_H
#include "Node.h"
#include "TickListener.h"
#include "TickController.h"
#include "RecordBuffer.h"

namespace eudyp {

enum ControlAlg { LINEAR, POW2 };
enum RecordMode { NONE, RECORD, PLAYBACK };

class Control : public TickListener {
  private:
    volatile double m_value;
    volatile double m_min_value;
    volatile double m_max_value;

    double m_min_min_value;
    double m_max_max_value;

    ControlAlg m_algorithm;
    bool m_reverse;
    RecordMode m_record_mode;

    Node* m_master;
    int m_master_idx;

    RecordBuffer m_record_buffer;
  public:

    Control(Node* master, int idx, ControlAlg algorithm, bool reverse, double min, double max, double value)
      : m_value(value),
        m_min_value(min),
        m_max_value(max),
        m_min_min_value(min),
        m_max_max_value(max),
        m_algorithm(algorithm),
        m_reverse(reverse),
        m_record_mode(NONE),
        m_master(master),
        m_master_idx(idx)
    { ; }
    double operator()() { return m_value; }

    double getValue() const { return m_value; }
    void setValue(double value) {
      if (value > m_max_value) value = m_max_value;
      else if (value < m_min_value) value = m_min_value;

      m_value = value;

      if (m_master && m_master_idx >= 0) {
        m_master->setControlValue(m_master_idx, value);
      }
    }

    void setNormalisedValue(double value) {
      if (value < 0.0) {
        value = 0.0;
      } else if (value > 1.0) {
        value = 1.0;
      }
      if (m_reverse) { value = 1.0 - value; }

      if (m_algorithm == POW2) {
        setValue(((m_max_value - m_min_value)*pow(value, 2)) + m_min_value);
      } else {
        // fallback is linear
        setValue(((m_max_value - m_min_value)*value) + m_min_value);
      }
    }

    void tweakValue(double amount) {
      setValue(m_value + ((m_max_value - m_min_value)*amount));
    }

    double getMinValue() const { return m_min_value; }
    void setMinValue(double value) {
      if (value > m_min_min_value) value = m_min_min_value;
      else if (value < m_min_min_value) value = m_min_min_value;

      m_min_value = value;
    }
    void tweakMinValue(double amount) {
      setMinValue(m_min_value + ((m_min_min_value - m_min_min_value)*amount));
    }

    double getMaxValue() const { return m_max_value; }
    void setMaxValue(double value) {
      if (value > m_max_max_value) value = m_max_max_value;
      else if (value < m_min_min_value) value = m_min_min_value;

      m_max_value = value;
    }
    void tweakMaxValue(double amount) {
      setMaxValue(m_max_value + ((m_max_max_value - m_min_min_value)*amount));
    }

    void startRecording(TickController* tick_con) {
      m_record_mode = RECORD;
      m_record_buffer.reset_buffer();
      tick_con->addTickListener(this);
    }

    void stopRecording(TickController* tick_con) {
      m_record_mode = NONE;
      tick_con->removeTickListener(this);
      tick_con->addTickListener(this);
    }

    void startPlayback(TickController* tick_con) {
      m_record_mode = PLAYBACK;
    }

    void stopPlayback(TickController* tick_con) {
      m_record_mode = NONE;
      tick_con->removeTickListener(this);
    }

    const RecordBuffer* getRecordBuffer() const { return &m_record_buffer; }
    RecordBuffer* getRecordBuffer() { return &m_record_buffer; }

    bool recording() const {
      return (m_record_mode == RECORD);
    }
    
    void tick()
    {
      //std::cerr << "Tick ..." << std::endl;
      switch(m_record_mode) {
        case RECORD:
          //std::cerr << "Recording value " << getValue();
          m_record_buffer.record_value(getValue());
          break;
        case PLAYBACK:
          setValue(m_record_buffer.get_next_value());
          //std::cerr << "Playing back value " << getValue();
          break;
        case NONE:
          break;
      }
    }
};

};
#endif // CONTROL_H
