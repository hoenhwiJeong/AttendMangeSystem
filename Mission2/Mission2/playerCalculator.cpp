#include "playerCalculator.h"

WeekOfDayAdditionalPoint* weekOfDayAdditionalPointFactory(int weekOfDay) {
    if (weekOfDay == Wednesday)
        return new WednesDayAdditionalPoint;
    else if (weekOfDay == Saturday)
        return new WeekendDayAdditionalPoint;
    else
        return NULL;
};

int PlayerPointCalculator::getAdditionalPoint(PlayerData& data) {
    int addPoint = 0;

    for (int weekOfday = Monday; weekOfday <= Saturday; weekOfday++) {
        WeekOfDayAdditionalPoint* weekofDayAdditionalPoint = weekOfDayAdditionalPointFactory(weekOfday);
        if (weekofDayAdditionalPoint != NULL) {
            addPoint += weekofDayAdditionalPoint->getPoint(data);
            delete weekofDayAdditionalPoint;
        }
    }

    return addPoint;
}

int PlayerPointCalculator::getGradeLevel(int point) {
    if (point >= GOID_LEVEL_POINT) {
        return GoldLevel;
    }
    if (point >= SILVER_LEVEL_POINT) {
        return SilverLevel;
    }
    return NormalLevel;
}

bool PlayerPointCalculator::calculatePointsForAllPlayers() {
    if (dataManger == NULL) {
        return false;
    }

    for (auto& playerData : dataManger->playerData) {
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
    }

    return true;
}