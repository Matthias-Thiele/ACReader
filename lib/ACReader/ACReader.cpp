#include "ACReader.h"

/**
 * @brief Construct a new ACReader::ACReader object
 * 
 * The cycleDuration should be more than one complete
 * period to be sure to have a max and a min value in
 * every cycle. 
 * 
 * @param analogPort Arduino port name of the used A/D pin.
 * @param cycleDuration cycle duration in milliseconds
 */
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

/**
 * @brief periodic call from the loop to update the values
 * 
 * This call should be done at least every millisecond, 
 * otherwise the max or min value might be overlooked.
 * 
 * If the actual millis value is available, send it as
 * parameter. Otherwise set now to zero and the actual
 * millis value will be fetched internal.
 * 
 * @param now 
 */
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

/**
 * @brief Returns the difference between max and min of the last cycle
 * 
 * @return short 
 */
short ACReader::getActValue() {
  return m_lastCycleVal;
}

/**
 * @brief Returns an averaged value of the last cycles
 * 
 * @return short 
 */
short ACReader::getAverageValue() {
  return m_averageVal;
}