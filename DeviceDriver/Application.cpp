#include "Application.h"
#include <iostream>

#define START_ADDR 0x00l
#define END_ADDR 0x04l

Application::Application(DeviceDriver* driver) : driver(driver)
{
}
void Application::ReadAndPrint(long startAddr, long endAddr)
{
	for (long addr = startAddr; addr <= endAddr; addr++)
	{
		cout << driver->read(addr) << "\n";
	}
}

void Application::WriteAll(int value)
{
	for (long addr = START_ADDR; addr <= END_ADDR; addr++)
	{
		driver->write(addr, value);
	}
}
