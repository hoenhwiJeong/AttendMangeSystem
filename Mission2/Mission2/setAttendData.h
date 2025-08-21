#pragma once
#include "common.h"

class InvalidDayOfWeekInputException : public std::exception {
public:
	const char* what() const noexcept override {
		return "InvalidDayOfWeekInputException Occur!";
	}
};

class AttendInputData {
public:
	string name;
	int weekOfDay;
};

class ReadInputData {
public:
	vector<AttendInputData> attendData;
	int getDayOfWeekIndex(string dayOfWeek);
	bool setReadInputData(AttendInputData attendInputDate);
	bool readAttendanceFile(string inputFileName);
};