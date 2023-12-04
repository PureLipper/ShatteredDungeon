#include "Usages.h"
#include <vector>
#include <queue>
#include "map/Point.h"
#include "launch/GameCore.h"

//
// Created by 林炜昊 on 2023/11/23.
//
std::vector<Point> BFSRoadFinding(const Point &startP, const Point &targetP) {
    std::vector<Point> road;
    if(GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(targetP) == WALL ||
       GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(targetP) == _NULL){
        return road;
    }
    Point dir[4] = {{0,  -1},
                    {1,  0},
                    {0,  1},
                    {-1, 0}};
    std::queue<Point> q;
    q.push(startP);
    bool flag[80][80];
    Point preP[80][80];
    for (auto &i: flag) {
        for (auto &j: i) {
            j = false;
        }
    }
    preP[startP.getX()][startP.getY()] = startP;
    bool f = true;
    while (!q.empty() && f) {
        Point t = q.front();
        q.pop();
        for (Point &p: dir) {
            if (GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(t + p) != WALL &&
                GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getPointValue(t + p) != _NULL &&
                GameCore::getGameCore()->getMaps().at(GameCore::getGameCore()->getFloorNow()).getEntity(t + p) == nullptr &&
                !flag[(t + p).getX()][(t + p).getY()]) {
                q.push(t + p);
                flag[(t + p).getX()][(t + p).getY()] = true;
                preP[(t+p).getX()][(t+p).getY()] = t;
                if(targetP == (t+p)){
                    f = false;
                }
            }
        }
    }
    if(f){
        
    }
    auto *p = &targetP;
    while(*p != startP){
        road.push_back(*p);
        p = &preP[p->getX()][p->getY()];
    }
    return road;
}

void drawTransparentToCanvas(int x, int y, IMAGE *src) {
    DWORD *src1 = GetImageBuffer(src);
    DWORD *t = GetImageBuffer(GameWindow::getGameWindow()->getCanvas());
    int w, h, dw;
    w = src->getwidth();
    dw = GameWindow::getGameWindow()->getCanvas()->getwidth();
    h = src->getheight();
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (src1[i * w + j] != RGB(0,0,0)) {
                t[y * dw + x + i * dw + j] = src1[i * w + j];
            }
        }
    }
}

bool LookingForTarget(Entity *e) {
    const Map &map = GameCore::getGameCore()->getMaps().at((GameCore::getGameCore()->getFloorNow()));
    unsigned int length = map.getLength();
    unsigned int width = map.getWidth();
    const Point& pos = e->getPos();
    int vision = e->getVision();
    Player* player;
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() + 1), p.setY(
            p.getY() + 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i++) {
            player = dynamic_cast<Player*>(map.getEntity({i, p.getY()}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i++) {
            player = dynamic_cast<Player*>(map.getEntity({p.getX(), i}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() - 1), p.setY(
            p.getY() + 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i--) {
            player = dynamic_cast<Player*>(map.getEntity({i, p.getY()}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i++) {
            player = dynamic_cast<Player*>(map.getEntity({p.getX(), i}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() + 1), p.setY(
            p.getY() - 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i++) {
            player = dynamic_cast<Player*>(map.getEntity({i, p.getY()}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i--) {
            player = dynamic_cast<Player*>(map.getEntity({p.getX(), i}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
    for (Point p(pos.getX(), pos.getY());
         p.getX() >= 0 && p.getX() < length && p.getY() >= 0 && p.getY() < width; p.setX(p.getX() - 1), p.setY(
            p.getY() - 1)) {
        for (int i = p.getX();
             ((pos.getX() - i) * (pos.getX() - i) + (pos.getY() - p.getY()) * (pos.getY() - p.getY()) <
              vision * vision) && i >= 0 && i < length && p.getY() >= 0 && p.getY() < width; i--) {
            player = dynamic_cast<Player*>(map.getEntity({i, p.getY()}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(i, p.getY()) == WALL || map.getPointValue(i, p.getY()) == CLOSED_DOOR) break;
        }
        for (int i = p.getY();
             ((pos.getY() - i) * (pos.getY() - i) + (pos.getX() - p.getX()) * (pos.getX() - p.getX()) <
              vision * vision) && p.getX() >= 0 && p.getX() < length && i >= 0 && i < width; i--) {
            player = dynamic_cast<Player*>(map.getEntity({p.getX(), i}));
            if(player){
                e->gainIntent(player->getPos());
                return true;
            }
            if (map.getPointValue(p.getX(), i) == WALL || map.getPointValue(p.getX(), i) == CLOSED_DOOR) break;
        }
        if (map.getPointValue(p) == WALL || map.getPointValue(p) == CLOSED_DOOR) break;
    }
    return false;
}


