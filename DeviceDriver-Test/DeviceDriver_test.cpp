#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../DeviceDriver/DeviceDriver.cpp"
using namespace testing;

class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriverReadTest, callFiveTimesTest) {
	FlashMock flashMock;

	EXPECT_CALL(flashMock, read)
		.Times(5);

	DeviceDriver deviceDriver(&flashMock);
	deviceDriver.read(0x5);
}