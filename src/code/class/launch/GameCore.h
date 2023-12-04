//
// Created by 林炜昊 on 2023/11/9.
//
#pragma once

#include <thread>
#include "GameWindow.h"
#include "entity/Player.h"
#include "map/MapGenerator.h"
#include "attr.h"
#include "entity/player/Warrior.h"
#include "entity/player/Rogue.h"

class GameCore {
private:
    std::vector<std::thread> thread_pool;
    int floor_now = 0;//越深数字越大
    GameWindow *gw = GameWindow::getGameWindow();
    Point origin{0, 0};
    GameCore();
    double turns = 0.0;
public:
    Player &getPlayer() const;

    double getTurns() const;

    void turnsUp(double x);

private:
    Player &player = *new Warrior();
    bool isRunning = true;
    MapGenerator *mapGenerator;
    std::vector<Map> maps;
    static GameCore *game;
    float aspectRatio = 1.0;
    bool followPlayer = false;

public:
    int getFloorNow() const;

    const std::vector<Map> &getMaps() const;

    static GameCore *getGameCore();

    static void deleteGame();

    void start();

    void upFloor();

    void downFloor();

    GameWindow *getGw() const;

    bool isFollowPlayer() const;

    void setFollowPlayer(bool b);

    float getAspectRatio() const;

    void setAspectRatio(float ratio);

    const Point &getOrigin() const;

    void setOrigin(int x, int y);
};