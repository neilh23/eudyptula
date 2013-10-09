#ifndef RECORD_BUFFER_H
#define RECORD_BUFFER_H

#define BUFFER_SIZE 2048
#define MAX_BUFFERS 1024

namespace eudyp {

class RecordBuffer
{
  private:
    double* m_buffers[MAX_BUFFERS]; // FIXME: this should be extensible!
    long m_pos;
    long m_buffer_length;
    long m_next_extension;
  protected:
    void add_buffer() {
      if ((m_buffer_length/BUFFER_SIZE) >= MAX_BUFFERS) {
        // FIXME: extensible ...
        std::cerr << "Ran out of length for buffer!" << std::endl;
        m_buffer_length = (m_next_extension - 1);
        return;
      }
      m_buffer_length = (m_buffer_length/BUFFER_SIZE)*BUFFER_SIZE;
      // std::cerr << "Adding buffer at " << (int)(m_buffer_length/BUFFER_SIZE) << " length = " << m_buffer_length << std::endl;
      m_buffers[(m_buffer_length/BUFFER_SIZE)] = new double[BUFFER_SIZE];
      m_next_extension = ((m_buffer_length/BUFFER_SIZE) +1)*BUFFER_SIZE;
    }
  public:
    RecordBuffer() 
      : m_pos(0), m_buffer_length(-1), m_next_extension(0) 
    {
      m_buffers[0] = 0;
    }

    void quantise(long qValue) {
      std::cerr << "Called quantise with " << qValue << std::endl;
      if (m_buffer_length < 2) { return; }

      long orig = qValue;
      if (qValue <= 1) { return; }

      while (qValue < ((m_buffer_length*3)/2)) {
        qValue *= 2;
      }

      while (qValue > ((m_buffer_length*2)/3)) {
        qValue /= 2;
      }


      std::cerr << "Quantise - going from " << m_buffer_length << " to " << qValue << " using qValue " << orig << std::endl;

      if (qValue == m_buffer_length) { return; } // nothing to do ...

      if (qValue > m_buffer_length) {
        double lastValue ;
        
        if (m_buffer_length <= 0) {
          lastValue = 0.0;
        } else {
          lastValue = m_buffers[(m_buffer_length/BUFFER_SIZE)][(m_buffer_length%BUFFER_SIZE)];
        }

        while (m_buffer_length < qValue) { record_value(lastValue); } // FIXME: hackity hackity hack - 
      } else {

        while ((m_next_extension - BUFFER_SIZE) > qValue) {
          delete m_buffers[m_next_extension/BUFFER_SIZE];
          m_buffers[m_next_extension/BUFFER_SIZE] = 0;

          m_next_extension -= BUFFER_SIZE;
        }
        m_buffer_length = qValue;
      }
    }

    void reset_buffer() {
      if (m_buffer_length < 0) { return; }

      double** bf = m_buffers;

      while(*bf) {
        delete *bf;
        (*bf) = 0;
        bf++;
      }
      m_buffer_length = 0;
      m_next_extension = -1;
      m_pos = 0;
    }
    void record_value(double value) {
      if (m_pos != 0) { reset_buffer(); }

      if (++m_buffer_length >= m_next_extension) { add_buffer(); }

      m_buffers[(m_buffer_length/BUFFER_SIZE)][(m_buffer_length%BUFFER_SIZE)] = value;
    }
    double get_next_value() { 
      if (m_buffer_length <= 0) {
        return 0.0;
      }
      double rv = m_buffers[(m_pos/BUFFER_SIZE)][(m_pos%BUFFER_SIZE)];

      if (++m_pos >= m_buffer_length) {
        // std::cerr << "Back to beginning, buffer length: "  << m_buffer_length << std::endl;
        m_pos = 0;
      }

      return rv;
    }

    long getSize() const { return m_buffer_length; }
};
};

#endif
