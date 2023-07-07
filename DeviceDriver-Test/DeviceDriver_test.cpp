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

class FlashFixture : public testing::Test
{
public:
	FlashMock flashMock;
};

TEST_F(FlashFixture, callFiveTimesTest) {
	EXPECT_CALL(flashMock, read)
		.Times(5);

	DeviceDriver deviceDriver(&flashMock);
	deviceDriver.read(0x5);
}

TEST_F(FlashFixture, readPassTest) {
	EXPECT_CALL(flashMock, read)
		.Times(5)
		.WillRepeatedly(Return(100));

	DeviceDriver deviceDriver(&flashMock);
	EXPECT_THAT(100, deviceDriver.read(0x5));
}

TEST_F(FlashFixture, readFailTest) {
	EXPECT_CALL(flashMock, read)
		.Times(5)
		.WillOnce(Return(1))
		.WillRepeatedly(Return(100));

	DeviceDriver deviceDriver(&flashMock);
	EXPECT_THROW(deviceDriver.read(0x5), ReadFailException);
}

TEST_F(FlashFixture, readBeforeWritingTest) {
	EXPECT_CALL(flashMock, read)
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	DeviceDriver deviceDriver(&flashMock);
	deviceDriver.write(0x5, 3);
}

TEST_F(FlashFixture, checkWriteFailTest) {
	EXPECT_CALL(flashMock, read)
		.WillRepeatedly(Return(0x12));

	DeviceDriver deviceDriver(&flashMock);
	EXPECT_THROW(deviceDriver.write(0x5, 3), WriteFailException);
}

TEST_F(FlashFixture, checkWritePassTest) {
	EXPECT_CALL(flashMock, read)
		.WillRepeatedly(Return(0xFF));

	DeviceDriver deviceDriver(&flashMock);
	EXPECT_NO_THROW(deviceDriver.write(0x5, 3), WriteFailException);
}

