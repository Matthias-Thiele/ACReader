#include "ACReader.h"

ACReader::ACReader(uint8_t analogPort, short cycleDuration) {
  m_analogPort = analogPort;
  m_cycleDuration = cycleDuration;

  m_cycleMin = analogRead(m_analogPort);
  m_cycleMax = m_cycleMin;
  m_lastCycleVal = 0;

  unsigned long now = millis();
  m_nextTick = now + 1;
  m_nextCycle = now + cycleDuration;
}

void ACReader::tick(unsigned long now) {
  if (now == 0) {
    now = millis();
  }

  if (now < m_nextTick) {
    return;
  }

  short val = analogRead(m_analogPort);
  if (val < m_cycleMin) {
    m_cycleMin = val;
  }

  if (val > m_cycleMax) {
    m_cycleMax = val;
  }

  m_nextTick++;

  if (now >= m_nextCycle) {
    m_nextCycle += m_cycleDuration;
    m_lastCycleVal = m_cycleMax - m_cycleMin;
    m_averageVal = (m_averageVal + m_averageVal + m_averageVal + m_lastCycleVal) >> 2;
    m_cycleMax = val;
    m_cycleMin = val;
  }
}

short ACReader::getActValue() {
  return m_lastCycleVal;
}

short ACReader::getAverageValue() {
  return m_averageVal;
}