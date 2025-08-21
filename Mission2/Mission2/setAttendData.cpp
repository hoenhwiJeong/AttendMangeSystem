#include "setAttendData.h"

int ReadInputData::getDayOfWeekIndex(string dayOfWeek) {
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

	return dayOfWeekIndex;
}

bool ReadInputData::setReadInputData(AttendInputData attendInputDate) {
	attendData.push_back(attendInputDate);
	return true;
}

bool ReadInputData::readAttendanceFile(string inputFileName)
{
	bool ret = true;
	std::ifstream fin{ inputFileName };
	AttendInputData attendData;
	string weekOfDay;
	for (int i = 0; i < MAX_INPUT_FILE_LINE_NUMBER; i++) {
		fin >> attendData.name >> weekOfDay;
		try {
			attendData.weekOfDay = getDayOfWeekIndex(weekOfDay);
			setReadInputData(attendData);
		}
		catch (const InvalidDayOfWeekInputException& exception) {
			std::cout << exception.what() << std::endl;
			ret = false;
		}
	}
	return ret;
}