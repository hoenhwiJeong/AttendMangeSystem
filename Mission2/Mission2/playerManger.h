#pragma once
#include "common.h"

class PlayerData {
public:
    string names;
    int id = 0;
    bool isAttendKeyDayOfWeeks = false;
    int grade = 0;
    int points = 0;
    int attendantDayData[Max_Day_Of_Week] = { 0, };
    bool isReleasedPlayer = false;
};

class PlayerDataManager {
private:
    int idCount = 0;
public:
    vector<PlayerData> playerData;
    void setPlayerAttendatDayData(string name, int attendDayOfWeek);
    void setReleasedPlayers();
    void printPlayerAttendanceResults();
    void printRelaePlayer();
};