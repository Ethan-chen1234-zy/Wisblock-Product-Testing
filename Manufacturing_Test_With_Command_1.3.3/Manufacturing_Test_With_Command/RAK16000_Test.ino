#ifdef RAK16000_MODULE
#include <Wire.h>
#include <INA219_WE.h>// Click here to get the library: http://librarymanager/All#INA219_WE   2026.1.20 v1.4.1
#define I2C_ADDRESS 0x41
INA219_WE ina219 = INA219_WE(I2C_ADDRESS);


void RAK16000_test(unsigned long timeout)
{

  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0;
  bool ina219_overflow = false;
  Wire.begin();
  if (!ina219.init()) {
    Serial.printf("-----------RAK16000 Test Failed!-----------\n");
    return ;
  }
      // /* Set ADC Mode for Bus and ShuntVoltage
      //   Mode *            * Res / Samples *       * Conversion Time
      //   BIT_MODE_9        9 Bit Resolution             84 µs
      //   BIT_MODE_10       10 Bit Resolution            148 µs
      //   BIT_MODE_11       11 Bit Resolution            276 µs
      //   BIT_MODE_12       12 Bit Resolution            532 µs  (DEFAULT)
      //   SAMPLE_MODE_2     Mean Value 2 samples         1.06 ms
      //   SAMPLE_MODE_4     Mean Value 4 samples         2.13 ms
      //   SAMPLE_MODE_8     Mean Value 8 samples         4.26 ms
      //   SAMPLE_MODE_16    Mean Value 16 samples        8.51 ms
      //   SAMPLE_MODE_32    Mean Value 32 samples        17.02 ms
      //   SAMPLE_MODE_64    Mean Value 64 samples        34.05 ms
      //   SAMPLE_MODE_128   Mean Value 128 samples       68.10 ms
      // */
      //ina219.setADCMode(SAMPLE_MODE_128); // choose mode and uncomment for change of default
  /* Set ADC Mode for Bus and ShuntVoltage                                                        2026.1.20     v1.4.1  枚举变量名称更改
    * Mode *                 * Res / Samples *       * Conversion Time *
    INA219_BIT_MODE_9        9 Bit Resolution             84 µs
    INA219_BIT_MODE_10       10 Bit Resolution            148 µs  
    INA219_BIT_MODE_11       11 Bit Resolution            276 µs
    INA219_BIT_MODE_12       12 Bit Resolution            532 µs  (DEFAULT)
    INA219_SAMPLE_MODE_2     Mean Value 2 samples         1.06 ms
    INA219_SAMPLE_MODE_4     Mean Value 4 samples         2.13 ms
    INA219_SAMPLE_MODE_8     Mean Value 8 samples         4.26 ms
    INA219_SAMPLE_MODE_16    Mean Value 16 samples        8.51 ms     
    INA219_SAMPLE_MODE_32    Mean Value 32 samples        17.02 ms
    INA219_SAMPLE_MODE_64    Mean Value 64 samples        34.05 ms
    INA219_SAMPLE_MODE_128   Mean Value 128 samples       68.10 ms
    
    If you measure both current and bus voltage (which is the default), the conversion time doubles.
  */

  ina219.setADCMode(INA219_SAMPLE_MODE_128); // choose mode and uncomment for change of default    

      // /* Set measure mode
      //   POWER_DOWN - INA219 switched off
      //   TRIGGERED  - measurement on demand
      //   ADC_OFF    - Analog/Digital Converter switched off
      //   CONTINUOUS  - Continuous measurements (DEFAULT)
      // */
      // ina219.setMeasureMode(CONTINUOUS); // choose mode and uncomment for change of default
  /* Set measure mode                                                                                 2026.1.20     v1.4.1  枚举变量名称更改
    INA219_POWER_DOWN              - INA219 switched off
    INA219_TRIGGERED               - measurement on demand, current and bus
    INA219_TRIGGERED_CURRENT_ONLY  - on demand, current only
    INA219_TRIGGERED_BUS_ONLY      - on demand, bus voltage only
    INA219_ADC_OFF                 - analog/digital converter switched off
    INA219_CONTINUOUS              - continuous measurements (DEFAULT)
    INA219_CONTINUOUS_CURRENT_ONLY - continuous, current only
    INA219_CONTINUOUS_BUS_ONLY     - continuous, bus voltage only
  */
  ina219.setMeasureMode(INA219_CONTINUOUS); // choose gain and uncomment for change of default

      // /* Set PGain
      //   Gain *  * Shunt Voltage Range *   * Max Current (if shunt is 0.1 ohms)
      //   PG_40       40 mV                    0.4 A
      //   PG_80       80 mV                    0.8 A
      //   PG_160      160 mV                   1.6 A
      //   PG_320      320 mV                   3.2 A (DEFAULT)
      // */
      // ina219.setPGain(PG_320); // choose gain and uncomment for change of default
  /* Set PGain                                                                                         2026.1.20     v1.4.1  枚举变量名称更改
     * Gain *     * Shunt Voltage Range *   * Max Current (if shunt is 0.1 ohms) *
    INA219_PG_40         40 mV                    0.4 A
    INA219_PG_80         80 mV                    0.8 A
    INA219_PG_160        160 mV                   1.6 A
    INA219_PG_320        320 mV                   3.2 A (DEFAULT)
  */
  ina219.setPGain(INA219_PG_320); // choose gain and uncomment for change of default

      // /* Set Bus Voltage Range
      //   BRNG_16   -> 16 V
      //   BRNG_32   -> 32 V (DEFAULT)
      // */
      // ina219.setBusRange(BRNG_32); // choose range and uncomment for change of default
  /* Set Bus Voltage Range                                                                                2026.1.20     v1.4.1  枚举变量名称更改
    INA219_BRNG_16   -> 16 V
    INA219_BRNG_32   -> 32 V (DEFAULT)
  */
  ina219.setBusRange(INA219_BRNG_32); // choose range and uncomment for change of default

  ina219.setShuntSizeInOhms(0.1); // we use 100ohm
  Serial.println("INA219 Current Sensor Example Sketch - Continuous");

  /* If the current values delivered by the INA219 differ by a constant factor
     from values obtained with calibrated equipment you can define a correction factor.
     Correction factor = current delivered from calibrated equipment / current delivered by INA219
  */
  ina219.setCorrectionFactor(0.99); // insert your correction factor if necessary
  shuntVoltage_mV = ina219.getShuntVoltage_mV();
  busVoltage_V = ina219.getBusVoltage_V();
  //here we use the I=U/R to calculate, here the Resistor is 100mΩ, accuracy can reach to 0.5%.
  current_mA = shuntVoltage_mV / 0.1;
  power_mW = ina219.getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV / 1000);
  ina219_overflow = ina219.getOverflow();

  Serial.print("Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV);
  Serial.print("Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("Current[mA]: "); Serial.println(current_mA);
  Serial.print("Bus Power [mW]: "); Serial.println(power_mW);
  if (!ina219_overflow) {
    Serial.println("Values OK - no overflow");
    Serial.printf("\n-----------RAK16000 Test OK!-----------\n");
  }
  else {
    Serial.println("Overflow! Choose higher PGAIN");
    Serial.printf("-----------RAK16000 Test Failed!-----------\n");
  }
  delay(500);
}
#endif
