#pragma once
#include "common.h"
#include "playerManger.h"

class WeekOfDayAdditionalPoint {
public:
    virtual int getPoint(PlayerData& data) { return 0; };
};

class WednesDayAdditionalPoint : public WeekOfDayAdditionalPoint {
public:
    int getPoint(PlayerData& data) override {
        if (data.attendantDayData[Wednesday] >= WEDNESDAY_ATTEND_DAY_FOR_POINT)
            return ADDTIONAL_POINT_WEDNESDAY_ATTEND;
        return 0;
    }
};

class WeekendDayAdditionalPoint : public WeekOfDayAdditionalPoint {
public:
    int getPoint(PlayerData& data) override {
        if ((data.attendantDayData[Saturday] + data.attendantDayData[Sunday]) >= WEEKEND_ATTEND_DAY_FOR_POINT)
            return ADDTIONAL_POINT_WEEKEND_ATTEND;
        return 0;
    }
};

WeekOfDayAdditionalPoint* weekOfDayAdditionalPointFactory(int weekOfDay);

class PlayerPointCalculator {
    PlayerDataManager* dataManger = NULL;
public:
    PlayerPointCalculator(PlayerDataManager* getDataManger) {
        dataManger = getDataManger;
    }

    int getAdditionalPoint(PlayerData& data);
    int getGradeLevel(int point);
    bool calculatePointsForAllPlayers();
};