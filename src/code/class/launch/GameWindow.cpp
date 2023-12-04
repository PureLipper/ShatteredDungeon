#include"GameWindow.h"
#include "GameCore.h"
GameWindow* GameWindow::gw = GameWindow::getGameWindow();
void GameWindow::initWindow() const {
    initgraph(width, height);
//    setaspectratio(1.5,1.5);
}

int GameWindow::getHeight() const {
    return height;
}

int GameWindow::getWidth() const {
    return width;
}

float GameWindow::getCanvasAspectRatio() const {
    return canvasAspectRatio;
}

IMAGE *GameWindow::getCanvas() const {
    return canvas;
}

const Point &GameWindow::getCenterCanvas() const {
    return center_canvas;
}

IMAGE *GameWindow::getTargetDetail() const {
    return targetDetail;
}

const Point &GameWindow::getCenterTargetDetail() const {
    return center_targetDetail;
}

IMAGE *GameWindow::getPlayerDetail() const {
    return playerDetail;
}

const Point &GameWindow::getCenterPlayerDetail() const {
    return center_playerDetail;
}

IMAGE *GameWindow::getBackpack() const {
    return backpack;
}

const Point &GameWindow::getCenterBackpack() const {
    return center_backpack;
}

GameWindow *GameWindow::getGameWindow() {
    if(gw == nullptr){
        gw = new GameWindow();
        return gw;
    }else{
        return gw;
    }
}

GameWindow::GameWindow() {
    initWindow();
}

IMAGE *GameWindow::getLogger() const {
    return logger;
}

const Point &GameWindow::getCenterLogger() const {
    return center_logger;
}

void GameWindow::drawAll() {
    SetWorkingImage();
    drawCanvas();
    drawDetail();
    drawTargetDetail();
    drawBackpack();
    drawLogger();
}

void GameWindow::clearCanvas(){
    SetWorkingImage(canvas);
    cleardevice();
    SetWorkingImage();
}

void GameWindow::drawCanvas() {
    GameCore *gc = GameCore::getGameCore();
    gc->getMaps().at(gc->getFloorNow()).drawMapTo(canvas);
    SetWorkingImage(canvas);
    //截取范围
    if(gc->isFollowPlayer()){
        canvasFocusPoint = Point(gc->getPlayer().getPos().getX()*16,gc->getPlayer().getPos().getY()*16);
    }
    int w = (int)((float)canvas->getwidth() / canvasAspectRatio);
    int h = w;
    int startX = canvasFocusPoint.getX() - w/2;
    int startY = canvasFocusPoint.getY() - h/2;
    getimage(focusRegionImg,startX,startY,w,h);
    SetWorkingImage();
    setaspectratio(canvasAspectRatio,canvasAspectRatio);
    putimage(0,0,focusRegionImg);
    setaspectratio(1,1);
}

void GameWindow::drawDetail() {
    SetWorkingImage();
    putimage(center_playerDetail.getX(),center_playerDetail.getY(),playerDetail);
}

void GameWindow::drawTargetDetail() {
    SetWorkingImage();
    putimage(center_targetDetail.getX(),center_targetDetail.getY(),targetDetail);
}

void GameWindow::drawBackpack() {
    SetWorkingImage();
    putimage(center_backpack.getX(),center_backpack.getY(),backpack);
}

void GameWindow::drawLogger() {
    SetWorkingImage();
    putimage(center_logger.getX(),center_logger.getY(),logger);
}

void GameWindow::canvasAspectRatioUp(float i) {
    if(canvasAspectRatio < maxRatio){
        canvasAspectRatio += i;
    }
}

void GameWindow::canvasAspectRatioDown(float i) {
    if(canvasAspectRatio > minRatio){
        canvasAspectRatio -= i;
    }
}

void GameWindow::setCanvasFocusPoint(int x, int y) {
    canvasFocusPoint.setX(x);
    canvasFocusPoint.setY(y);
}

void GameWindow::focusPointLeftward(int d) {
    canvasFocusPoint.setX(canvasFocusPoint.getX()-d);
}

void GameWindow::focusPointRightward(int d) {
    canvasFocusPoint.setX(canvasFocusPoint.getX()+d);

}

void GameWindow::focusPointUpward(int d) {
    canvasFocusPoint.setY(canvasFocusPoint.getY()-d);

}

void GameWindow::focusPointDownward(int d) {
    canvasFocusPoint.setY(canvasFocusPoint.getY()+d);

}
