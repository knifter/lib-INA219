#include "Arduino.h"
#include <TwoWireDevice.h>

#include "INA219.h"

bool MCP23008::begin()
{
	TwoWireDevice::begin();

	return (_wire.lastError() == 0);
};

