#pragma once

#include "Map.h"
#include"Point.h"
#include"room.h"
#include<vector>
#include<random>

class MapGenerator {

private:
    static MapGenerator *Map_Generator;
    unsigned int BASE_ROOM_NUM = 25;
    unsigned int seed = 0;
    int map_length = 80;
    int map_width = 80;
    float density = 0.004;//参数控制问题

private:
    MapGenerator() {};

    ~MapGenerator() = default;

public:

    static void deleteMapGenerator();

    //获取唯一地图生成器
    static MapGenerator *getMapGenerator();

    void setSeed(unsigned int s);

    unsigned int getSeed() const;

    //生成地图，返回一个Map指针
    Map *generateMap(unsigned int s = time(nullptr));

    int getMapLength() const;

    void setMapLength(int mapLength);

    int getMapWidth() const;

    void setMapWidth(int mapWidth);

    float getDensity() const;

    void setDensity(float density);

    static unsigned int MAX_ROOM_LENGTH;
    static unsigned int MAX_ROOM_WIDTH;
    static unsigned int MIN_ROOM_LENGTH;
    static unsigned int MIN_ROOM_WIDTH;
};