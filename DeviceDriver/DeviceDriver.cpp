#include "DeviceDriver.h"
#define EMPTY_VALUE 0xFF

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));
    int readData[4] = { 0 };
    for (int i= 0; i < 4; i++)
    {
        readData[i] = (int)(m_hardware->read(address));
        if (readData[i] != result)
        {
            throw ReadFailException();
        }        
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
	if (EMPTY_VALUE == (int)(m_hardware->read(address)))
    {
        m_hardware->write(address, (unsigned char)data);
        return;
    }
    throw WriteFailException();
}