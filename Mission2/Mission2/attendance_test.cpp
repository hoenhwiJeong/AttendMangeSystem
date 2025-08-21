#include "gmock/gmock.h"
#include "playerManger.h"
#include "setAttendData.h"
#include "playerCalculator.h"

using namespace testing;

class AttendanceTestFixture : public Test {
public:
	void SetUp() override {}
};

TEST_F(AttendanceTestFixture, ReadResultTest) {
	ReadInputData readInpuDate;
	readInpuDate.readAttendanceFile(INPUT_FIME_NAME);

	for (int i = 0; i < readInpuDate.attendData.size(); i++) {
		cout << readInpuDate.attendData[i].name << " " << readInpuDate.attendData[i].weekOfDay << endl;
	}
}

TEST_F(AttendanceTestFixture, ReadAllResultTest) {
	ReadInputData readInpuDate;
	PlayerDataManager playerManger;
	PlayerPointCalculator* playerPointCalculator = new PlayerPointCalculator(&playerManger);
	readInpuDate.readAttendanceFile(INPUT_FIME_NAME);

	for (int i = 0; i < readInpuDate.attendData.size(); i++) {
		playerManger.setPlayerAttendatDayData(readInpuDate.attendData[i].name, readInpuDate.attendData[i].weekOfDay);
	}
	playerPointCalculator->calculatePointsForAllPlayers();
	playerManger.printPlayerAttendanceResults();
	playerManger.setReleasedPlayers();
	playerManger.printRelaePlayer();

	vector <string> releasePlayerName;

	EXPECT_EQ(playerManger.playerData.size(), 19);
}

TEST_F(AttendanceTestFixture, ReleasePlayerTest) {
	ReadInputData readInpuDate;
	PlayerDataManager playerManger;
	PlayerPointCalculator* playerPointCalculator = new PlayerPointCalculator(&playerManger);
	vector <string> releasePlayerName;
	readInpuDate.readAttendanceFile(INPUT_FIME_NAME);

	for (int i = 0; i < readInpuDate.attendData.size(); i++) {
		playerManger.setPlayerAttendatDayData(readInpuDate.attendData[i].name, readInpuDate.attendData[i].weekOfDay);
	}

	playerPointCalculator->calculatePointsForAllPlayers();
	playerManger.setReleasedPlayers();

	for (int i = 0; i < playerManger.playerData.size(); i++) {
		if (playerManger.playerData[i].isReleasedPlayer == true)
			releasePlayerName.push_back(playerManger.playerData[i].names);
	}

	EXPECT_EQ(releasePlayerName.size(), 2);
	EXPECT_EQ(releasePlayerName[0], "Bob");
	EXPECT_EQ(releasePlayerName[1], "Zane");
}

TEST_F(AttendanceTestFixture, InvalidTest) {
	PlayerPointCalculator* playerPointCalculator = new PlayerPointCalculator(NULL);
	EXPECT_EQ(playerPointCalculator->calculatePointsForAllPlayers(), false);
}

TEST_F(AttendanceTestFixture, InvalidTest2) {
	ReadInputData readInpuDate;
	EXPECT_THROW(readInpuDate.getDayOfWeekIndex("DEAD"), InvalidDayOfWeekInputException);
}

TEST_F(AttendanceTestFixture, InvalidTest3) {
	ReadInputData readInpuDate;
	EXPECT_EQ(readInpuDate.readAttendanceFile(INPUT_FIME_NAME_INVALID), false);
}