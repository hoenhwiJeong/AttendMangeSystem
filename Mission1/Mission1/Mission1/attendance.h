#pragma once
#define MAX_INPUT_FILE_LINE_NUMBER 500
#define MAX_PLAYER_NUMBER 100
#define WEDNESDAY_ATTEND_DAY_FOR_POINT 10
#define WEEKEND_ATTEND_DAY_FOR_POINT 10
#define ADDTIONAL_POINT_WEDNESDAY_ATTEND 10
#define ADDTIONAL_POINT_WEEKEND_ATTEND 10

#define WEDNESDAY_ATTEND_POINT 3
#define WEEKEND_ATTEND_POINT 2
#define NORMALDAYA_ATTEND_POINT 1

#define GOID_LEVEL_POINT 50
#define SILVER_LEVEL_POINT 30

#define INPUT_FIME_NAME "attendance_weekday_500.txt"

enum DayOfWeek {
    Monday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
    Max_Day_Of_Week,
};

enum GradeLevel {
    NormalLevel = 0,
    SilverLevel,
    GoldLevel,
    MaxGradeLevel,
};

void PrintPlayerAttendanceResults();
#pragma once
