#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/Application.cpp"
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

TEST_F(FlashFixture, ReadAndPrintPassTest)
{
	long startAddr = 0x1;
	long endAddr = 0x5;

	EXPECT_CALL(flashMock, read)
		.Times(5 * (endAddr - startAddr + 1))
		.WillRepeatedly(Return(100));

	DeviceDriver deviceDriver(&flashMock);
	Application app(&deviceDriver);
	app.ReadAndPrint(startAddr, endAddr);
}

TEST_F(FlashFixture, ReadAndPrintFailTest)
{
	long startAddr = 0x1;
	long endAddr = 0x5;

	EXPECT_CALL(flashMock, read)
		.WillOnce(Return(1))
		.WillOnce(Return(3))
		.WillRepeatedly(Return(100));

	DeviceDriver deviceDriver(&flashMock);
	Application app(&deviceDriver);
	EXPECT_THROW(app.ReadAndPrint(startAddr, endAddr), ReadFailException);
}

TEST_F(FlashFixture, WriteAllPassTest)
{
	DeviceDriver deviceDriver(&flashMock);
	Application app(&deviceDriver);

	EXPECT_CALL(flashMock, read)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMock, write)
		.Times(5);

	app.WriteAll(100);
}

TEST_F(FlashFixture, WriteAllFailTest)
{
	DeviceDriver deviceDriver(&flashMock);
	Application app(&deviceDriver);

	EXPECT_CALL(flashMock, read)
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(1));

	EXPECT_THROW(app.WriteAll(100), WriteFailException);
}

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

