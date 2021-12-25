#ifndef ACReader_hpp
#define ACReader_hpp

#include <Arduino.h>

class ACReader {
  public:
    ACReader(uint8_t analogPort, short cycleDuration);
    void tick(unsigned long now);
    short getActValue();
    short getAverageValue();

  private:
    uint8_t m_analogPort;
    short m_cycleDuration;

    unsigned long m_nextTick;
    unsigned long m_nextCycle;

    short m_cycleMin;
    short m_cycleMax;
    short m_lastCycleVal;
    short m_averageVal;
};

#endif