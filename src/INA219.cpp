#include "Arduino.h"
#include <TwoWireDevice.h>

#include "INA219.h"
#include "INA219_regs.h"

bool INA219::begin()
{
	TwoWireDevice::begin();

	// set to defaults
	_config = 0x399F;

	return (_wire.lastError() == 0);
};

void INA219::shutdown()
{
	_config &= ~CONFIG_MODE_MASK;
	_config |= CONFIG_MODE_POWERDOWN;

	writereg16_ML(REG_CONFIG, _config);
}

void INA219::setGainDiv(GainDiv_t pga)
{
	_config &= ~CONFIG_PGA_MASK;
	_config |= pga;

	writereg16_ML(REG_CONFIG, _config);
}

void INA219::setBusVoltage(BusVoltage_t v)
{
	_config &= ~CONFIG_BRNG_MASK;
	_config |= v;

	writereg16_ML(REG_CONFIG, _config);
}

void INA219::setShuntAverage(Average_t avg)
{
	_config &= ~CONFIG_SADC_MASK;
	_config |= (avg << CONFIG_SADC);

	writereg16_ML(REG_CONFIG, _config);
};

void INA219::setBusAverage(Average_t avg)
{
	_config &= ~CONFIG_BADC_MASK;
	_config |= (avg << CONFIG_BADC);

	writereg16_ML(REG_CONFIG, _config);
};

void INA219::setOperatingMode(OperatingMode_t mode)
{
	_config &= ~CONFIG_MODE_MASK;
	_config |= mode;

	writereg16_ML(REG_CONFIG, _config);
};

int16_t INA219::getShunt()
{
	return readreg16_ML(REG_SHUNT);
}

int16_t INA219::getBus()
{
	uint16_t vbus = readreg16_ML(REG_BUS);

	// Conversion ready
	// bool cnvr = vbus & 0x02;

	// overflow
	bool ovf = vbus & 0x01;
	if(ovf)
		return -1;
	
	return (vbus >> 3) * 4 /* LSB is always 4 mV */;
}

int16_t INA219::getPower()
{
	return readreg16_ML(REG_POWER);
}

int16_t INA219::getCurrent()
{
	return readreg16_ML(REG_CURRENT);
}

void INA219::setCalibration(uint16_t cal)
{
	writereg16_ML(REG_CAL, cal);
}

int16_t INA219::getCalibration()
{
	return readreg16_ML(REG_CAL);
}
