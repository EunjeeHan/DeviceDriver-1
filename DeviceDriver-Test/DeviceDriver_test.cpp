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

class ReadFixture : public testing::Test
{
public:
	FlashMock flashMock;
};

TEST_F(ReadFixture, callFiveTimesTest) {
	EXPECT_CALL(flashMock, read)
		.Times(5);

	DeviceDriver deviceDriver(&flashMock);
	deviceDriver.read(0x5);
}

TEST_F(ReadFixture, readPassTest) {
	EXPECT_CALL(flashMock, read)
		.Times(5)
		.WillRepeatedly(Return(100));

	DeviceDriver deviceDriver(&flashMock);
	EXPECT_THAT(100, deviceDriver.read(0x5));
}

TEST_F(ReadFixture, readFailTest) {
	EXPECT_CALL(flashMock, read)
		.Times(5)
		.WillOnce(Return(1))
		.WillRepeatedly(Return(100));

	DeviceDriver deviceDriver(&flashMock);
	EXPECT_THROW(deviceDriver.read(0x5), ReadFailException);
}
