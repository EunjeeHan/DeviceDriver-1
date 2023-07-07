#include "Application.h"
#include <iostream>

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

}
