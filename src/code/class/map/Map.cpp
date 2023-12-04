#include "Map.h"
#include "easyx.h"
#include "attr.h"
#include "tools/Usages.h"

IMAGE *Map::pics = new IMAGE[30];
IMAGE *Map::shadePics = new IMAGE[30];
void changeAlpha(IMAGE *src1, IMAGE *src2, IMAGE *target, int alpha);
Map::Map(unsigned int l, unsigned int w) {
    this->length = l;
    this->width = w;
    map = new unsigned int *[length];
    maskMap = new unsigned int *[length];
    itemOnMap = new std::vector<ItemStack> *[length];
    inSight = new unsigned int *[length];
    entityMap = new Entity **[length];
    for (int i = 0; i < length; i++) {
        map[i] = new unsigned int[width];
        maskMap[i] = new unsigned int[width];
        itemOnMap[i] = new std::vector<ItemStack>[width];
        inSight[i] = new unsigned int[width];
        entityMap[i] = new Entity*[width];
        for (int j = 0; j < width; j++) {
            map[i][j] = _NULL;
            maskMap[i][j] = UNKNOWN;
            itemOnMap[i][j] = *new std::vector<ItemStack>;
            inSight[i][j] = OUTSIGHT;
            entityMap[i][j] = nullptr;
        }
    }
}

void Map::drawMapTo(IMAGE* dst) const {
    SetWorkingImage(dst);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (maskMap[i][j] == KNOWN) {
                if (inSight[i][j] == OUTSIGHT) {
                    putimage(i * 16, j * 16, &shadePics[map[i][j]]);
                }else{
                    putimage(i * 16, j * 16, &pics[map[i][j]]);
                    std::vector<ItemStack> &is = itemOnMap[i][j];
                    if(!is.empty()){
                        drawTransparentToCanvas(i * 16,j * 16, is.back().getItem().getAvatar());
                    }
                    Entity *e = entityMap[i][j];
                    if(e){
                        e->draw(0);
                    }
                }

            }
        }
    }

    SetWorkingImage();
}

void drawEntity(IMAGE* dst){

}

void Map::setPointValue(unsigned int x, unsigned int y, unsigned int value, unsigned int dx, unsigned int dy) {
    map[x + dx][y + dy] = value;
}


unsigned int Map::getLength() const {
    return length;
}

void Map::setLength(unsigned int l) {
    Map::length = l;
}

unsigned int Map::getWidth() const {
    return width;
}

void Map::setWidth(unsigned int w) {
    Map::width = w;
}

void Map::setPointValue(const Point &p, unsigned int value, unsigned int dx, unsigned int dy) {
    map[p.getX() + dx][p.getY() + dy] = value;
}

unsigned int Map::getPointValue(const Point &p, int dx, int dy) const {
    return map[p.getX() + dx][p.getY() + dy];
}

void Map::preloadRes() {
    auto *tiles = new IMAGE;
    loadimage(tiles, _T("src\\image\\environments\\tiles_sewers.png"));
    SetWorkingImage(tiles);
    getimage(&Map::pics[FLOOR], 0, 0, 16, 16);
    getimage(&Map::pics[CLOSED_DOOR], 128, 48, 16, 16);
    getimage(&Map::pics[_NULL], 128, 16, 16, 16);
    getimage(&Map::pics[WALL], 0, 48, 16, 16);
    getimage(&Map::pics[UP_FLOOR], 0, 16, 16, 16);
    getimage(&Map::pics[DOWN_FLOOR], 16, 16, 16, 16);
    getimage(&Map::pics[GRAY],128,16,16,16);
    delete tiles;
    auto *temp = new IMAGE(pics[GRAY].getwidth(),pics[GRAY].getheight());
    for(int i = 0;i < 30;i++){
        if(pics[i].getwidth() != 0){
            changeAlpha(&pics[GRAY], &pics[i], temp,128);
            shadePics[i] = *temp;
        }
    }
    delete temp;
    SetWorkingImage();
}

const Point &Map::getUpFloorPoint() const {
    return upFloorPoint;
}

void Map::setUpFloorPoint(const Point &p) {
    Map::upFloorPoint = p;
}

const Point &Map::getDownFloorPoint() const {
    return downFloorPoint;
}

void Map::setDownFloorPoint(const Point &p) {
    Map::downFloorPoint = p;
}

unsigned int **Map::getMaskMap() const {
    return maskMap;
}

unsigned int **Map::getMap() const {
    return map;
}

void Map::addItemTo(ItemStack &itemstack, const Point &p) const {
    for(ItemStack &IS : itemOnMap[p.getX()][p.getY()]){
        if(typeid(IS.getItem()).name() == typeid(itemstack.getItem()).name()){
            IS.countUp(itemstack.getCount());
            return;
        }
    }
    itemOnMap[p.getX()][p.getY()].push_back(itemstack);
}

unsigned int Map::getPointValue(int x, int y) const {
    return map[x][y];
}

unsigned int **Map::getInSight() const {
    return inSight;
}

void Map::restoreInSight() const{
    for(unsigned int i = 0;i < length;i++){
        for(unsigned int j = 0;j < width;j++){
            inSight[i][j] = OUTSIGHT;
        }
    }
}

void Map::show() const {
    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < width; j++) {
            std::printf("%2d ", map[j][i]);
        }
        std::cout << std::endl;
    }
}

void Map::showInSight() const {
    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < width; j++) {
            std::printf("%2d ", inSight[j][i]);
        }
        std::cout << std::endl;
    }
}

void Map::showMaskMap() const {
    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < width; j++) {
            std::printf("%2d ", maskMap[j][i]);
        }
        std::cout << std::endl;
    }
}

std::vector<ItemStack> &Map::getItemStacksOn(Point p) const{
    return itemOnMap[p.getX()][p.getY()];
}

Entity * Map::getEntity(const Point &p,int dx,int dy) const {
    return entityMap[p.getX() + dx][p.getY() + dy];
}

void Map::setEntity(const Point &p, Entity *e) const {
    entityMap[p.getX()][p.getY()] = e;
}

void Map::updateEntity() {
    for(int i = 0;i < length;i++){
        for(int j = 0;j < width;j++){
            Entity *e = entityMap[i][j];
            if(e != nullptr){
                e->act();
            }
        }
    }
}

void Map::moveEntity(Entity *target, const Point &to) const {
    entityMap[target->getPos().getX()][target->getPos().getY()] = nullptr;
    entityMap[to.getX()][to.getY()] = target;
}

//0~255 255表示不透明
void changeAlpha(IMAGE *src1, IMAGE *src2, IMAGE *target, int alpha) {
    DWORD *imgp1 = GetImageBuffer(src1);
    DWORD *imgp2 = GetImageBuffer(src2);
    DWORD *t = GetImageBuffer(target);
    int w, bw, h, i, j;
    w = src1->getwidth();
    bw = target->getwidth();
    h = src1->getheight();
    if (alpha < 0)alpha = 0;
    else if(alpha>255)alpha=255;
    for (i = 0; i < h; ++i){
        for (j = 0; j < w; ++j){
            t[i * bw + j] = RGB(
                    ((int)(alpha / 255.0* GetRValue(imgp1[i * w + j]) + (1 - alpha / 255.0) * GetRValue(imgp2[i * bw + j]))),
                    ((int)(alpha / 255.0* GetGValue(imgp1[i * w + j]) + (1 - alpha / 255.0) * GetGValue(imgp2[i * bw + j]))),
                    ((int)(alpha / 255.0* GetBValue(imgp1[i * w + j]) + (1 - alpha / 255.0) * GetBValue(imgp2[i * bw + j])))
            );
        }
    }
}