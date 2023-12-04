//
// Created by 林炜昊 on 2023/11/9.
//

#include "GameCore.h"
#include "tools/Log.h"
#include "entity/enemy/Rat.h"

GameCore *GameCore::game = nullptr;

GameCore::GameCore() {
    Map::preloadRes();
    Item::preloadRes();
    player.loadImages();
    mapGenerator = MapGenerator::getMapGenerator();
    maps.push_back(*mapGenerator->generateMap());
    player.setPos(maps.at(floor_now).getUpFloorPoint());
    maps.at(floor_now).setEntity(player.getPos(),&player);
}

GameCore *GameCore::getGameCore() {
    if (game != nullptr) {
        return game;
    } else {
        game = new GameCore();
        return game;
    }
}

void GameCore::deleteGame() {
    delete game;
}

void GameCore::start() {
    BeginBatchDraw();
    player.gainVision();
    gw->setCanvasFocusPoint(player.getPos().getX()*16,player.getPos().getY()*16);
    Rat *r = new Rat();
    r->loadImages();
    r->setPos(Point(player.getPos(),0,1));
    maps.at(floor_now).setEntity(Point(player.getPos(),0,1),r);
    maps.at(floor_now).addItemTo(*new ItemStack(ClothArmor(),1),Point(player.getPos(),0,-1));
    Log::p("system","你降入了地牢的第一层");
    gw->drawAll();
//    player.watching();
//    auto *watching_anim = new std::thread([this] {
//        while (isRunning) {
//            Sleep(1000);//降低cpu占用率
//            if (player.getStatus() == WATCHING) {
//                if (time(nullptr) % 6 == 0) {
//                    putimage(player.getPos().getX() * 16, player.getPos().getY() * 16,
//                             &Map::pics[GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(
//                                     player.getPos())]);
//                    player.draw(0);
//                    FlushBatchDraw();
//                } else if (time(nullptr) % 6 == 3) {
//                    putimage(player.getPos().getX() * 16, player.getPos().getY() * 16,
//                             &Map::pics[GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(
//                                     player.getPos())]);
//                    player.draw(1);
//                    FlushBatchDraw();
//                }
//            }
//        }
//    });
//    watching_anim->detach();
    FlushBatchDraw();
    while (isRunning) {
        Sleep(1);
        if(GetAsyncKeyState(VK_LMENU)){
            followPlayer = !followPlayer;
            gw->drawCanvas();
            FlushBatchDraw();
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_DOWN)){
            followPlayer = false;
            gw->focusPointDownward(16);
            gw->drawCanvas();
            FlushBatchDraw();
            Sleep(2);
            continue;
        }
        if (GetAsyncKeyState(VK_RIGHT)){
            followPlayer = false;
            gw->focusPointRightward(16);
            gw->drawCanvas();
            FlushBatchDraw();
            Sleep(2);
            continue;
        }
        if (GetAsyncKeyState(VK_UP)){
            followPlayer = false;
            gw->focusPointUpward(16);
            gw->drawCanvas();
            FlushBatchDraw();
            Sleep(2);
            continue;
        }
        if (GetAsyncKeyState(VK_LEFT)){
            followPlayer = false;
            gw->focusPointLeftward(16);
            gw->drawCanvas();
            FlushBatchDraw();
            Sleep(2);
            continue;
        }
        if (GetAsyncKeyState(VK_ADD)){
            gw->canvasAspectRatioUp(0.1);
            gw->drawCanvas();
            FlushBatchDraw();
            Sleep(50);
            continue;
        }
        if (GetAsyncKeyState(VK_SUBTRACT)){
            gw->canvasAspectRatioDown(0.1);
            gw->drawCanvas();
            FlushBatchDraw();
            Sleep(50);
            continue;
        }
        if (GetAsyncKeyState(0x57)) {
            int interval = 50;
            Entity *entityOnIntent = maps.at(floor_now).getEntity(player.getPos(),0,-1);
            auto *e = dynamic_cast<Enemy*>(entityOnIntent);
            if(e){
                player.attack(*e);
                e->attack(player);
                Log::p("system","敌人剩余血量：" + std::to_string(e->getHealthNow()) + "您的血量：" + std::to_string(player.getHealthNow()));
                interval += 150;
            }else{
                player.upward();
            }
            maps.at(floor_now).updateEntity();
            gw->drawAll();
            FlushBatchDraw();
            Sleep(interval);
        }
        if (GetAsyncKeyState(0x53)) {
            int interval = 50;
            Entity *entityOnIntent = maps.at(floor_now).getEntity(player.getPos(),0,1);
            auto *e = dynamic_cast<Enemy*>(entityOnIntent);
            if(e){
                player.attack(*e);
                e->attack(player);
                Log::p("system","敌人剩余血量：" + std::to_string(e->getHealthNow()) + "您的血量：" + std::to_string(player.getHealthNow()));
                interval += 150;
            }else {
                player.downward();
            }
            maps.at(floor_now).updateEntity();
            gw->drawAll();
            FlushBatchDraw();
            Sleep(interval);
        }
        if (GetAsyncKeyState(0x41)) {
            int interval = 50;
            Entity *entityOnIntent = maps.at(floor_now).getEntity(player.getPos(),-1,0);
            auto *e = dynamic_cast<Enemy*>(entityOnIntent);
            if(e){
                player.attack(*e);
                e->attack(player);
                Log::p("system","敌人剩余血量：" + std::to_string(e->getHealthNow()) + "您的血量：" + std::to_string(player.getHealthNow()));
                interval += 150;
            }else {
                player.leftward();
            }
            maps.at(floor_now).updateEntity();
            gw->drawAll();
            FlushBatchDraw();
            Sleep(interval);
        }
        if (GetAsyncKeyState(0x44)) {
            int interval = 50;
            Entity *entityOnIntent = maps.at(floor_now).getEntity(player.getPos(),1,0);
            auto *e = dynamic_cast<Enemy*>(entityOnIntent);
            if(e){
                player.attack(*e);
                e->attack(player);
                Log::p("system","敌人剩余血量：" + std::to_string(e->getHealthNow()) + ",您的血量：" + std::to_string(player.getHealthNow()));
                interval += 150;
            }else {
                player.rightward();
            }
            maps.at(floor_now).updateEntity();
            gw->drawAll();
            FlushBatchDraw();
            Sleep(interval);
        }
        if (GetAsyncKeyState(VK_RETURN)) {
            if(!maps.at(floor_now).getItemStacksOn(player.getPos()).empty()){
                player.pickUp();
            }else{
                if (maps.at(floor_now).getPointValue(player.getPos()) == DOWN_FLOOR) {
                    downFloor();
                    Sleep(500);
                } else if (maps.at(floor_now).getPointValue(player.getPos()) == UP_FLOOR) {
                    if (floor_now == 0) {
                        Log::p("system", "您现在在第一层！");
                        gw->drawLogger();
                        FlushBatchDraw();
                    }else{
                        upFloor();
                    }
                    Sleep(500);
                }
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            MapGenerator::deleteMapGenerator();
            isRunning = false;
        }
    }
}

const std::vector<Map> &GameCore::getMaps() const {
    return maps;
}

int GameCore::getFloorNow() const {
    return floor_now;
}

void GameCore::upFloor() {
    floor_now--;
    player.setPos(maps.at(floor_now).getDownFloorPoint());
    maps.at(floor_now).setEntity(player.getPos(),&player);
    gw->setCanvasFocusPoint(player.getPos().getX()*16,player.getPos().getY()*16);
    player.gainVision();
    gw->clearCanvas();
    gw->drawCanvas();
    FlushBatchDraw();

}

void GameCore::downFloor() {
    if (maps.size() == floor_now + 1) {
        maps.push_back(*mapGenerator->generateMap());
    }
    floor_now++;
    player.setPos(maps.at(floor_now).getUpFloorPoint());
    maps.at(floor_now).setEntity(player.getPos(),&player);
    gw->setCanvasFocusPoint(player.getPos().getX()*16,player.getPos().getY()*16);
    player.gainVision();
    gw->clearCanvas();
    gw->drawCanvas();
    FlushBatchDraw();
}

GameWindow *GameCore::getGw() const {
    return gw;
}

const Point &GameCore::getOrigin() const {
    return origin;
}

void GameCore::setOrigin(int x, int y) {
    origin.setX(x);
    origin.setY(y);

}

float GameCore::getAspectRatio() const {
    return aspectRatio;
}

void GameCore::setAspectRatio(float ratio) {
    GameCore::aspectRatio = ratio;
}

bool GameCore::isFollowPlayer() const {
    return followPlayer;
}

void GameCore::setFollowPlayer(bool b) {
    GameCore::followPlayer = b;
}

Player &GameCore::getPlayer() const {
    return player;
}

double GameCore::getTurns() const {
    return turns;
}

void GameCore::turnsUp(double x) {
    turns += x;
}

