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
			BIT9B = 0x00,
			BIT10B = 0x01,
			BIT11B = 0x02,
			BIT12B = 0x03,
			AVG2 = 0x09,
			AVG4 = 0x0A,
			AVG8 = 0x0B,
			AVG16 = 0x0C,
			AVG32 = 0x0D,
			AVG64 = 0x0E,
			AVG128 = 0x0F
		} Average_t;

        INA219(TwoWire& wire, const uint8_t addr = INA219_ADDRESS_DEFAULT) : TwoWireDevice(wire, addr) {};
        INA219(const uint8_t addr = INA219_ADDRESS_DEFAULT) : TwoWireDevice(addr) {};

        bool begin();
		void shutdown();
		void setGainDiv(GainDiv_t);
		void setBusVoltage(BusVoltage_t);
		void setShuntAverage(Average_t);
		void setBusAverage(Average_t);
		int16_t getShunt();
		int16_t getBus();
		int16_t getPower();
		int16_t getCurrent();
		int16_t getCalibration();

    protected:

    private:
        INA219(const INA219&);
        INA219& operator=(const INA219&);

		uint16_t _config;
};

#endif // __INA219_H
