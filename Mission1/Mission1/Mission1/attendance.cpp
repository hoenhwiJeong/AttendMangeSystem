#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <exception>
#include "attendance.h"

using namespace std;

class InvalidDayOfWeekInputException : public std::exception {
public:
	const char* what() const noexcept override {
		return "InvalidDayOfWeekInputException Occur!";
	}
};
class PlayerData {
public:
	string names;
	int id = 0;
	bool isAttendKeyDayOfWeeks = false;
	int grade = 0;
	int points = 0;
	int attendantDayData[Max_Day_Of_Week] = { 0, };
};

void checkPlayerList(std::map<std::string, PlayerData>& playerListMap, std::string& attendanceName)
{
	static int idCount = 0;
	if (playerListMap.count(attendanceName) == 0) {

		PlayerData playerData;
		playerData.names = attendanceName;
		playerData.id = ++idCount;
		playerListMap.insert({ attendanceName, playerData });
	}
}

void inputAttendanceFileInData(std::map<std::string, PlayerData>& playerListMap, string attendanceName, string dayOfWeek) {

	checkPlayerList(playerListMap, attendanceName);
	PlayerData& playerData = playerListMap[attendanceName];

	int dayOfWeekIndex = 0;

	if (dayOfWeek == "monday") {
		dayOfWeekIndex = Monday;
	}
	else if (dayOfWeek == "tuesday") {
		dayOfWeekIndex = Tuesday;
	}
	else if (dayOfWeek == "wednesday") {
		dayOfWeekIndex = Wednesday;
	}
	else if (dayOfWeek == "thursday") {
		dayOfWeekIndex = Thursday;
	}
	else if (dayOfWeek == "friday") {
		dayOfWeekIndex = Friday;
	}
	else if (dayOfWeek == "saturday") {
		dayOfWeekIndex = Saturday;
	}
	else if (dayOfWeek == "sunday") {
		dayOfWeekIndex = Sunday;
	}
	else
		throw InvalidDayOfWeekInputException();

	playerData.attendantDayData[dayOfWeekIndex]++;
}

void readAttendanceFile(std::map<std::string, PlayerData>& playerListMap)
{
	ifstream fin{ INPUT_FIME_NAME };
	for (int i = 0; i < MAX_INPUT_FILE_LINE_NUMBER; i++) {
		string attendanceName, dayOfWeek;
		fin >> attendanceName >> dayOfWeek;
		try {
			inputAttendanceFileInData(playerListMap, attendanceName, dayOfWeek);
		}
		catch (const InvalidDayOfWeekInputException& exception) {
			std::cout << exception.what() << std::endl;
		}
	}
}

int getAdditionalPoint(PlayerData& data) {
	int addPoint = 0;
	if (data.attendantDayData[Wednesday] >= WEDNESDAY_ATTEND_DAY_FOR_POINT) {
		addPoint += ADDTIONAL_POINT_WEDNESDAY_ATTEND;
	}
	if ((data.attendantDayData[Saturday] + data.attendantDayData[Sunday]) >= WEEKEND_ATTEND_DAY_FOR_POINT) {
		addPoint += ADDTIONAL_POINT_WEEKEND_ATTEND;
	}

	return addPoint;
}

int getGradeLevel(int point) {
	if (point >= GOID_LEVEL_POINT) {
		return GoldLevel;
	}
	if (point >= SILVER_LEVEL_POINT) {
		return SilverLevel;
	}
	return NormalLevel;
}

void listReleasedPlayers(PlayerData& playerData, std::map<int, std::string>& removePlayer)
{
	if (playerData.grade == NormalLevel && playerData.isAttendKeyDayOfWeeks == false) {
		removePlayer.insert({ playerData.id, playerData.names });
	}
}

void CalculatePointsForAllPlayers(std::map<std::string, PlayerData>& playerListMap, std::map<int, std::string>& removePlayer) {
	for (auto& pair : playerListMap) {
		PlayerData& playerData = pair.second;

		for (int dayOfWeek = Monday; dayOfWeek < Max_Day_Of_Week; dayOfWeek++) {
			if (playerData.attendantDayData[dayOfWeek] > 0) {
				if (dayOfWeek == Wednesday) {
					playerData.points += (playerData.attendantDayData[dayOfWeek] * WEDNESDAY_ATTEND_POINT);
					playerData.isAttendKeyDayOfWeeks = true;
				}
				else if (dayOfWeek == Saturday || dayOfWeek == Sunday) {
					playerData.points += (playerData.attendantDayData[dayOfWeek] * WEEKEND_ATTEND_POINT);
					playerData.isAttendKeyDayOfWeeks = true;
				}
				else {
					playerData.points += (playerData.attendantDayData[dayOfWeek] * NORMALDAYA_ATTEND_POINT);
				}
			}
		}

		playerData.points += getAdditionalPoint(playerData);
		playerData.grade = getGradeLevel(playerData.points);
		listReleasedPlayers(playerData, removePlayer);
	}
}

void PrintPlayerAttendanceResults(const std::map<std::string, PlayerData>& playerListMap, const std::map<int, std::string>& removePlayer)
{
	for (const auto& pair : playerListMap) {
		const std::string& name = pair.first;
		const PlayerData& data = pair.second;

		cout << "ID : " << data.id << ", NAME : " << data.names << ", POINT : " << data.points << ", GRADE : ";
		if (data.grade == GoldLevel) {
			cout << "GOLD" << "\n";
		}
		else if (data.grade == SilverLevel) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
		}
	}

	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (const auto& pair : removePlayer) {
		cout << pair.second << endl;
	}
}

void AttendanceManagementSystem() {

	map<int, string> removePlayer;
	map<string, PlayerData> playerListMap;

	readAttendanceFile(playerListMap);
	CalculatePointsForAllPlayers(playerListMap, removePlayer);
	PrintPlayerAttendanceResults(playerListMap, removePlayer);
}

int main() {
	AttendanceManagementSystem();
}