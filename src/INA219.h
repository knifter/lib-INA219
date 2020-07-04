#ifndef __INA219_H
#define __INA219_H

#include <Arduino.h>
#include <TwoWireDevice.h>


#define INA219_ADDRESS_DEFAULT              (0x40)

class INA219: public TwoWireDevice {
    public:    
        typedef enum
        {
			GAIN_DIV1 = 0x00 << 11,
			GAIN_DIV2 = 0x01 << 11,
			GAIN_DIV4 = 0x02 << 11,
			GAIN_DIV8 = 0x03 << 11
        } GainDiv_t;

		typedef enum
		{
			BUS_16V = 0x00,
			BUS_32V = 0x01 << 13
		} BusVoltage_t;

		typedef enum
		{
			BIT9B = 0x00,	// 84 us
			BIT10B = 0x01,	// 148 us
			BIT11B = 0x02,	// 276 us
			BIT12B = 0x03,	// 532 us (POR default)
			AVG2 = 0x09,	// 1.06 ms
			AVG4 = 0x0A,	// 2.13 ms
			AVG8 = 0x0B,	// 4.26 ms
			AVG16 = 0x0C,	// 8.51 ms
			AVG32 = 0x0D,	// 17.02 ms
			AVG64 = 0x0E,	// 34.05 ms
			AVG128 = 0x0F	// 68.10 ms
		} Average_t;

		typedef enum
		{
			MODE_POWERDOWN 		= 0b0000,	// Power Down
			MODE_SHUNT_TRIG 	= 0b0001,	// Shunt voltage, triggered
			MODE_BUS_TRIG		= 0b0010,	// Bus voltage, triggered
			MODE_SHUNTBUS_TRIG	= 0b0011, 	// Shun and bus, triggered
			MODE_ADCOFF			= 0b0100,	// ADC Off
			MODE_SHUNT			= 0b0101,	// Shunt voltage, continues
			MODE_BUS			= 0b0110,	// Bus voltage, continues
			MODE_SHUNTBUS		= 0b0111,	// Shunt and bus, continues (POR default)
		} OperatingMode_t;

        INA219(TwoWire& wire, const uint8_t addr = INA219_ADDRESS_DEFAULT) : TwoWireDevice(wire, addr) {};
        INA219(const uint8_t addr = INA219_ADDRESS_DEFAULT) : TwoWireDevice(addr) {};

        bool begin();
		void shutdown();
		void setGainDiv(GainDiv_t);
		void setBusVoltage(BusVoltage_t);
		void setShuntAverage(Average_t);
		void setBusAverage(Average_t);
		void setOperatingMode(OperatingMode_t);
		int16_t getShunt();
		int16_t getBus();
		int16_t getPower();
		int16_t getCurrent();
		void setCalibration(uint16_t);
		int16_t getCalibration();

    protected:

    private:
        INA219(const INA219&);
        INA219& operator=(const INA219&);

		uint16_t _config;
};

#endif // __INA219_H
