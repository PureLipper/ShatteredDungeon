#include "MapGenerator.h"

MapGenerator *MapGenerator::Map_Generator = nullptr;
unsigned int MapGenerator::MAX_ROOM_LENGTH = 20;
unsigned int MapGenerator::MAX_ROOM_WIDTH = 20;
unsigned int MapGenerator::MIN_ROOM_LENGTH = 9;
unsigned int MapGenerator::MIN_ROOM_WIDTH = 9;

bool isOverlapped(room &r, const std::vector<room> &rooms, unsigned int length, unsigned int width);

bool generateRooms(std::vector<room> &rooms, unsigned int target_room_num, std::default_random_engine &e, unsigned int length,
                   unsigned int width);

void initMapByRooms(std::vector<room> &rooms, Map *map, std::default_random_engine &e);

bool isEnd(const Point &p, Map *map);
bool isEnd(int x,int y, Map *map) ;

void generateRoads(Map *map, std::default_random_engine &e);

void clearRoad(Map *map);

bool isOkDirection(unsigned int lastDirection,unsigned int direction, Map *map, Point p);

void generateDoors(std::vector<room> &rooms, Map *map, std::default_random_engine &e);

void fillDoors(std::vector<room> &rooms,Map *map);

void reloadWall(std::vector<room> &rooms,Map *map);

void MapGenerator::deleteMapGenerator() {
    delete Map_Generator;
}

MapGenerator *MapGenerator::getMapGenerator() {
    if (Map_Generator != nullptr) {
        return Map_Generator;
    } else {
        Map_Generator = new MapGenerator();
        return Map_Generator;
    }
}

Map *MapGenerator::generateMap(unsigned int s) {
    seed = s;
    Map *map = new Map(map_length, map_width);
    MapGenerator::MAX_ROOM_LENGTH = map_length / 5;
    MapGenerator::MAX_ROOM_WIDTH = map_width / 5;
    BASE_ROOM_NUM = map_length * map_width * density;
    std::default_random_engine RE;
    RE.seed(seed);
    std::vector<room> rooms;
    unsigned int target_room_num = RE() % 5 - 2 + BASE_ROOM_NUM;
    while(!generateRooms(rooms, target_room_num, RE, map_length, map_width)){
        target_room_num = RE() % 5 - 2 + BASE_ROOM_NUM;
    }//随机生成房间
    initMapByRooms(rooms, map,RE);//在地图填充房间
    generateRoads(map, RE);//随机生成路线
    generateDoors(rooms, map, RE);//根据已有路线生成门，且填充为FLOOR
    clearRoad(map);//清除多余路线
    reloadWall(rooms,map);
    fillDoors(rooms,map);
    return map;
}

void MapGenerator::setSeed(unsigned int s) {
    this->seed = s;
}

unsigned int MapGenerator::getSeed() const {
    return seed;
}

int MapGenerator::getMapLength() const {
    return map_length;
}

void MapGenerator::setMapLength(int mapLength) {
    map_length = mapLength;
}

int MapGenerator::getMapWidth() const {
    return map_width;
}

void MapGenerator::setMapWidth(int mapWidth) {
    map_width = mapWidth;
}

float MapGenerator::getDensity() const {
    return density;
}

void MapGenerator::setDensity(float density) {
    MapGenerator::density = density;
}

//初始化房间四壁为wall，内部为floor，初始化map周围一圈为wall
void initMapByRooms(std::vector<room> &rooms, Map *map, std::default_random_engine &e) {
    //初始化房间四壁为wall，内部为floor
    for (room &r: rooms) {
        for (unsigned int i = r.getPoints()[0].getX(); i <= r.getPoints()[2].getX(); i++) {
            map->setPointValue(i, r.getPoints()[0].getY(), WALL);
            map->setPointValue(i, r.getPoints()[2].getY(), WALL);
        }
        for (unsigned int i = r.getPoints()[0].getY(); i <= r.getPoints()[2].getY(); i++) {
            map->setPointValue(r.getPoints()[0].getX(), i, WALL);
            map->setPointValue(r.getPoints()[2].getX(), i, WALL);
        }
        for (unsigned int i = r.getPoints()[0].getX() + 1; i < r.getPoints()[2].getX(); i++) {
            for (unsigned int j = r.getPoints()[0].getY() + 1; j < r.getPoints()[2].getY(); j++) {
                map->setPointValue(i, j, FLOOR);
            }
        }
        if(r.getTag() == UP_FLOOR_ROOM){
            Point p(r.getPoints()[0].getX() + e() % r.getLength() + 1,r.getPoints()[0].getY() + e() % r.getWidth() + 1);
            map->setPointValue(p,UP_FLOOR);
            map->setUpFloorPoint(p);
        }
        if(r.getTag() == DOWN_FLOOR_ROOM){
            Point p(r.getPoints()[0].getX() + e() % r.getLength() + 1,r.getPoints()[0].getY() + e() % r.getWidth() + 1);
            map->setPointValue(p,DOWN_FLOOR);
            map->setDownFloorPoint(p);
        }
    }
    //初始化map周围一圈为wall
    for (int i = 0; i < map->getLength(); i++) {
        map->setPointValue(i, 0, WALL);
    }
    for (int i = 0; i < map->getLength(); i++) {
        map->setPointValue(i, map->getWidth() - 1, WALL);
    }
    for (int i = 0; i < map->getWidth(); i++) {
        map->setPointValue(0, i, WALL);
    }
    for (int i = 0; i < map->getWidth(); i++) {
        map->setPointValue(map->getLength() - 1, i, WALL);
    }
}

//随机生成房间，若生成的房间合理，则加入rooms容器，完美生成返回true，否则返回false
bool generateRooms(std::vector<room> &rooms, unsigned int target_room_num, std::default_random_engine &e, unsigned int length,
                   unsigned int width) {
    int ac_room_num = 0;
    int try_times = 0;
    while (ac_room_num <= target_room_num) {
        if(try_times >= 10000) {
            rooms.clear();
            return false;
        }
        auto *p1 = new Point(e() % length, e() % width);
        auto *p2 = new Point(p1->getX() + e() % (MapGenerator::MAX_ROOM_LENGTH - MapGenerator::MIN_ROOM_LENGTH + 1) +
                             MapGenerator::MIN_ROOM_LENGTH,
                             p1->getY() + e() % (MapGenerator::MAX_ROOM_WIDTH - MapGenerator::MIN_ROOM_WIDTH + 1) +
                             MapGenerator::MIN_ROOM_WIDTH);
        room &r = *new room(p1, p2);
        delete p1;
        delete p2;
        if (!isOverlapped(r, rooms, length, width)) {
            rooms.push_back(r);
            ac_room_num++;
            try_times = 0;
        }else{
            try_times++;
        }
    }
    unsigned int upFloor = e() % rooms.size();
    unsigned int downFloor = e() % rooms.size();
    while(downFloor == upFloor) downFloor = e() % rooms.size();
    rooms.at(upFloor).setTag(UP_FLOOR_ROOM);
    rooms.at(downFloor).setTag(DOWN_FLOOR_ROOM);

    std::cout << ac_room_num << std::endl;
    return true;
}

//判断目标房间r是否与已有房间rooms重叠，length和width为map的参数，避免r出界
bool isOverlapped(room &r, const std::vector<room> &rooms, unsigned int length, unsigned int width) {
    if (!(r.getPoints()[2].getX() < length && r.getPoints()[2].getY() < width)) return true;
    for (auto &room: rooms) {
        //点是否在已有房间内
        for (int i = 0; i < 4; i++) {
            if (room.getPoints()[0].getX() < r.getPoints()[i].getX() &&
                room.getPoints()[2].getX() > r.getPoints()[i].getX() &&
                room.getPoints()[0].getY() < r.getPoints()[i].getY() &&
                room.getPoints()[2].getY() > r.getPoints()[i].getY()) {
                return true;
            }
            if (room.getPoints()[i].getX() > r.getPoints()[0].getX() &&
                room.getPoints()[i].getX() < r.getPoints()[2].getX() &&
                room.getPoints()[i].getY() > r.getPoints()[0].getY() &&
                room.getPoints()[i].getY() < r.getPoints()[2].getY()) {
                return true;
            }
        }
        //是否穿过
        if (r.getPoints()[0].getX() <= room.getPoints()[0].getX() &&
            r.getPoints()[1].getX() >= room.getPoints()[1].getX() &&
            ((r.getPoints()[0].getY() >= room.getPoints()[0].getY() &&
              r.getPoints()[0].getY() <= room.getPoints()[3].getY()) ||
             (r.getPoints()[3].getY() >= room.getPoints()[0].getY() &&
              r.getPoints()[3].getY() <= room.getPoints()[3].getY())))
            return true;
        if (r.getPoints()[0].getY() <= room.getPoints()[0].getY() &&
            r.getPoints()[3].getY() >= room.getPoints()[3].getY() &&
            ((r.getPoints()[0].getX() >= room.getPoints()[0].getX() &&
              r.getPoints()[0].getX() <= room.getPoints()[1].getX()) ||
             (r.getPoints()[1].getX() >= room.getPoints()[0].getX() &&
              r.getPoints()[1].getX() <= room.getPoints()[1].getX())))
            return true;
    }
    return false;
}

//同名函数：某点周围若有三个及以上的wall，则返回true，否则返回false
bool isEnd(const Point &p, Map *map) {
    int count = 0;
    if (map->getMap()[p.getX()][p.getY() + 1] == WALL) count++;
    if (map->getMap()[p.getX()][p.getY() - 1] == WALL) count++;
    if (map->getMap()[p.getX() + 1][p.getY()] == WALL) count++;
    if (map->getMap()[p.getX() - 1][p.getY()] == WALL) count++;
    if (count >= 3) return true;
    else return false;
}
//同名函数：某点周围若有三个及以上的wall，则返回true，否则返回false
bool isEnd(int x,int y, Map *map) {
    int count = 0;
    if (map->getMap()[x][y + 1] == WALL) count++;
    if (map->getMap()[x][y - 1] == WALL) count++;
    if (map->getMap()[x + 1][y] == WALL) count++;
    if (map->getMap()[x - 1][y] == WALL) count++;
    if (count >= 3) return true;
    else return false;
}

//生成道路：对地图中两两间隔1的点进行遍历，随机寻找合理的方向并生成道路。
//合理性见isOkDirection()
void generateRoads(Map *map, std::default_random_engine &e) {
    for (int i = 2; i < map->getLength() - 2; i += 2) {
        for (int j = 2; j < map->getWidth() - 2; j += 2) {
            if (map->getMap()[i][j] == _NULL) {
                Point p(i, j);
                unsigned int lastDirection = 0;
                while (!isEnd(p, map)) {
                    map->setPointValue(p.getX(), p.getY(), FLOOR);
                    unsigned int direction = e() % 4;//0上1左2下3右
                    while (!isOkDirection(lastDirection, direction, map, p)) {
                        direction = e() % 4;
                    }
                    switch (direction) {
                        case 0: {
                            if (map->getMap()[p.getX()][p.getY() + 1] == _NULL)
                                map->setPointValue(p.getX(), p.getY() + 1, WALL);

                            if (map->getMap()[p.getX() + 1][p.getY()] == _NULL)
                                map->setPointValue(p.getX() + 1, p.getY(), WALL);
                            if (map->getMap()[p.getX() - 1][p.getY()] == _NULL)
                                map->setPointValue(p.getX() - 1, p.getY(), WALL);
                            if (map->getMap()[p.getX()][p.getY() - 1] != WALL)
                                p.setY(p.getY() - 1);
                            break;
                        }
                        case 1: {
                            if (map->getMap()[p.getX() + 1][p.getY()] == _NULL)
                                map->setPointValue(p.getX() + 1, p.getY(), WALL);

                            if (map->getMap()[p.getX()][p.getY() + 1] == _NULL)
                                map->setPointValue(p.getX(), p.getY() + 1, WALL);
                            if (map->getMap()[p.getX()][p.getY() - 1] == _NULL)
                                map->setPointValue(p.getX(), p.getY() - 1, WALL);
                            if (map->getMap()[p.getX() - 1][p.getY()] != WALL)
                                p.setX(p.getX() - 1);
                            break;
                        }
                        case 2: {
                            if (map->getMap()[p.getX()][p.getY() - 1] == _NULL)
                                map->setPointValue(p.getX(), p.getY() - 1, WALL);

                            if (map->getMap()[p.getX() + 1][p.getY()] == _NULL)
                                map->setPointValue(p.getX() + 1, p.getY(), WALL);
                            if (map->getMap()[p.getX() - 1][p.getY()] == _NULL)
                                map->setPointValue(p.getX() - 1, p.getY(), WALL);
                            if (map->getMap()[p.getX()][p.getY() + 1] != WALL)
                                p.setY(p.getY() + 1);
                            break;
                        }
                        case 3: {
                            if (map->getMap()[p.getX() - 1][p.getY()] == _NULL)
                                map->setPointValue(p.getX() - 1, p.getY(), WALL);

                            if (map->getMap()[p.getX()][p.getY() + 1] == _NULL)
                                map->setPointValue(p.getX(), p.getY() + 1, WALL);
                            if (map->getMap()[p.getX()][p.getY() - 1] == _NULL)
                                map->setPointValue(p.getX(), p.getY() - 1, WALL);
                            if (map->getMap()[p.getX() + 1][p.getY()] != WALL)
                                p.setX(p.getX() + 1);
                            break;
                        }
                        default:{}
                    }
                    lastDirection = direction;
                }
            }
        }
    }
}

//清除路径：置所有_NULL的点为WALL，统计所有端点存入endPoints，对每一个endPoint做填充。
//填充：寻找endPoint的周围唯一一个FLOOR点，将endPoint置为WALL，把endPoint指向找到的FLOOR点，循环。
void clearRoad(Map *map) {
    std::vector<Point> endPoints;
    for (int i = 1; i < map->getLength() - 1; i++) {
        for (int j = 1; j < map->getWidth() - 1; j++) {
            Point p(i, j);
            if (map->getPointValue(p) == _NULL) {
                map->setPointValue(p, WALL);
            }
        }
    }
    for (int i = 1; i < map->getLength() - 1; i++) {
        for (int j = 1; j < map->getWidth() - 1; j++) {
            Point p(i, j);
            if (map->getPointValue(p) == FLOOR && isEnd(p, map)) {
                endPoints.push_back(p);
            }
        }
    }
    for (Point &p: endPoints) {
        while (isEnd(p, map) && map->getPointValue(p) != WALL) {
            map->setPointValue(p, WALL);
            if (map->getPointValue(p, 1, 0) == FLOOR) {
                p.setX(p.getX() + 1);
                continue;
            }
            if (map->getPointValue(p, -1, 0) == FLOOR) {
                p.setX(p.getX() - 1);
                continue;
            }
            if (map->getPointValue(p, 0, 1) == FLOOR) {
                p.setY(p.getY() + 1);
                continue;
            }
            if (map->getPointValue(p, 0, -1) == FLOOR) {
                p.setY(p.getY() - 1);
                continue;
            }
        }
    }
}

//如果p点的direction方向的下一个点是合理位置则返回true
//合理性：下一个点不是墙，且下一个点两侧和前方不是路；方向和上一个方向不同
bool isOkDirection(unsigned int lastDirection, unsigned int direction, Map *map, Point p) {
    bool flag = true;
    Point *nextP;
    switch (direction) {
        case 0: {
            nextP = new Point(p.getX(), p.getY() - 1);
            if (map->getPointValue(*nextP) == WALL || map->getPointValue(*nextP, 1, 0) == FLOOR ||
                    map->getPointValue(*nextP, -1, 0) == FLOOR || map->getPointValue(*nextP, 0, -1) == FLOOR)
                flag = false;
            break;
        }
        case 1: {
            nextP = new Point(p.getX() - 1, p.getY());
            if (map->getPointValue(*nextP) == WALL || map->getPointValue(*nextP, 0, 1) == FLOOR ||
                    map->getPointValue(*nextP, -1, 0) == FLOOR || map->getPointValue(*nextP, 0, -1) == FLOOR)
                flag = false;
            break;
        }
        case 2: {
            nextP = new Point(p.getX(), p.getY() + 1);
            if (map->getPointValue(*nextP) == WALL || map->getPointValue(*nextP, 1, 0) == FLOOR ||
                    map->getPointValue(*nextP, 0, 1) == FLOOR || map->getPointValue(*nextP, -1, 0) == FLOOR)
                flag = false;
            break;
        }
        case 3: {
            nextP = new Point(p.getX() + 1, p.getY());
            if (map->getPointValue(*nextP) == WALL || map->getPointValue(*nextP, 1, 0) == FLOOR ||
                    map->getPointValue(*nextP, 0, 1) == FLOOR || map->getPointValue(*nextP, 0, -1) == FLOOR)
                flag = false;
            break;
        }
        default:{}
    }
    if (direction == (lastDirection + 2) % 4)
        flag = false;
    return flag;
}

//遍历所有房间的所有边，寻找合适的门的点并记录到该room的doors容器中，并置map中该点的值为FLOOR
void generateDoors(std::vector<room> &rooms, Map *map, std::default_random_engine &e) {
    for (room &room: rooms) {
        std::vector<unsigned int> available_doors;
        if (room.getPoints()[0].getY() != 0) {
            for (unsigned int i = room.getPoints()[0].getX() + 1; i < room.getPoints()[1].getX(); i++) {
                if (map->getMap()[i][room.getPoints()[0].getY() - 1] == FLOOR) available_doors.push_back(i);
            }
            if (!available_doors.empty()) {
                Point p(available_doors.at(e() % available_doors.size()), room.getPoints()[0].getY());
                map->setPointValue(p, FLOOR);
                room.addDoor(p);
            }
        }
        available_doors.clear();
        if (room.getPoints()[0].getX() != 0) {
            for (unsigned int i = room.getPoints()[0].getY() + 1; i < room.getPoints()[3].getY(); i++) {
                if (map->getMap()[room.getPoints()[0].getX() - 1][i] == FLOOR) available_doors.push_back(i);
            }
            if (!available_doors.empty()) {
                Point p(room.getPoints()[0].getX(), available_doors.at(e() % available_doors.size()));
                map->setPointValue(p, FLOOR);
                room.addDoor(p);
            }
        }
        available_doors.clear();
        if (room.getPoints()[3].getY() != map->getWidth() - 1) {
            for (unsigned int i = room.getPoints()[3].getX() + 1; i < room.getPoints()[2].getX(); i++) {
                if (map->getMap()[i][room.getPoints()[3].getY() + 1] == FLOOR) available_doors.push_back(i);
            }
            if (!available_doors.empty()) {
                Point p(available_doors.at(e() % available_doors.size()), room.getPoints()[3].getY());
                map->setPointValue(p, FLOOR);
                room.addDoor(p);
            }
        }
        available_doors.clear();
        if (room.getPoints()[1].getX() != map->getLength() - 1) {
            for (unsigned int i = room.getPoints()[1].getY() + 1; i < room.getPoints()[2].getY(); i++) {
                if (map->getMap()[room.getPoints()[1].getX() + 1][i] == FLOOR) available_doors.push_back(i);
            }
            if (!available_doors.empty()) {
                Point p(room.getPoints()[1].getX(), available_doors.at(e() % available_doors.size()));
                map->setPointValue(p, FLOOR);
                room.addDoor(p);
            }
        }
    }
}

//遍历所有房间的所有门点，若该点周围没有_NULL，则置map中该点的值为CLOSED_DOOR
void fillDoors(std::vector<room> &rooms,Map *map){
    for(room &r : rooms){
        for(auto &p : r.getDoor()){
            if((map->getPointValue(p, 0, 1) != _NULL && map->getPointValue(p, 0, -1) != _NULL &&
                    map->getPointValue(p, 1, 0) != _NULL && map->getPointValue(p, -1, 0) != _NULL) && !isEnd(p, map)){
                map->setPointValue(p,CLOSED_DOOR);
            }
        }
    }
}

void reloadWall(std::vector<room> &rooms,Map *map){
    for(int i = 0;i < map->getLength();i++){
        for(int j = 0;j < map->getWidth();j++){
            Point p(i, j);
            if(map->getPointValue(p) == WALL){
                map->setPointValue(p,_NULL);
            }
        }
    }
    for (room &r: rooms) {
        for (unsigned int i = r.getPoints()[0].getX(); i <= r.getPoints()[2].getX(); i++) {
            map->setPointValue(i, r.getPoints()[0].getY(), WALL);
            map->setPointValue(i, r.getPoints()[2].getY(), WALL);
        }
        for (unsigned int i = r.getPoints()[0].getY(); i <= r.getPoints()[2].getY(); i++) {
            map->setPointValue(r.getPoints()[0].getX(), i, WALL);
            map->setPointValue(r.getPoints()[2].getX(), i, WALL);
        }
    }
}