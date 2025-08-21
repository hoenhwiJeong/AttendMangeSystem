#include "playerManger.h"

void PlayerDataManager::setPlayerAttendatDayData(string name, int attendDayOfWeek) {
    bool isAlreadySettedPlayer = false;
    for (auto& player : playerData) {
        if (player.names == name)
        {
            player.attendantDayData[attendDayOfWeek]++;
            isAlreadySettedPlayer = true;
        }
    }

    if (isAlreadySettedPlayer == false) {
        PlayerData newPlayerData;
        newPlayerData.id = ++idCount;
        newPlayerData.names = name;
        newPlayerData.attendantDayData[attendDayOfWeek]++;
        playerData.push_back(newPlayerData);
    }
}

void PlayerDataManager::setReleasedPlayers() {
    for (auto& player : playerData) {
        if (player.grade == NormalLevel && player.isAttendKeyDayOfWeeks == false) {
            player.isReleasedPlayer = true;
        }
    }
}
void PlayerDataManager::printPlayerAttendanceResults() {
    for (auto& player : playerData) {
        cout << "ID : " << player.id << ", NAME : " << player.names << ", POINT : " << player.points << ", GRADE : ";
        if (player.grade == GoldLevel) {
            cout << "GOLD" << "\n";
        }
        else if (player.grade == SilverLevel) {
            cout << "SILVER" << "\n";
        }
        else {
            cout << "NORMAL" << "\n";
        }
    }
}

void PlayerDataManager::printRelaePlayer() {
    std::cout << "\n";
    std::cout << "Removed player\n";
    std::cout << "==============\n";

    for (auto& player : playerData) {
        if (player.isReleasedPlayer == true) {
            cout << player.names << endl;
        }
    }
}