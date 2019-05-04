#ifndef __INA219_H
#define __INA219_H

#include <Arduino.h>
#include <TwoWireDevice.h>

#define INA219_ADDRESS_DEFAULT              (0x40)

class INA219: public TwoWireDevice {
    public:    
        typedef enum
        {
        } PinMode_t;

        typedef enum
        {
        } InterruptMode_t;

        INA219(TwoWire& wire, const uint8_t addr = INA219_ADDRESS_DEFAULT) : TwoWireDevice(wire, addr) {};
        INA219(const uint8_t addr = INA219_ADDRESS_DEFAULT) : TwoWireDevice(addr) {};

        bool 	begin();

    protected:

    private:
        INA219(const INA219&);
        INA219& operator=(const INA219&);
};

#endif // __INA219_H
