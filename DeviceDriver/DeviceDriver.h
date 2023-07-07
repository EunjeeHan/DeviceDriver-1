#pragma once
#include "FlashMemoryDevice.h"
#include <exception>

using namespace std;

class ReadFailException : public exception
{};

class WriteFailException : public exception
{};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};