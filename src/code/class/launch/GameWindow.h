#pragma once

#include<easyx.h>
#include "map/Point.h"

class GameWindow {
private:
    GameWindow();
    static GameWindow* gw;
    int height = 1280;
    int width = 1960;
    float canvasAspectRatio = 2;
    float minRatio = 1;
    float maxRatio = 4;
public:
    void setCanvasFocusPoint(int x, int y);

    void focusPointLeftward(int d);
    void focusPointRightward(int d);
    void focusPointUpward(int d);
    void focusPointDownward(int d);

private:
    Point canvasFocusPoint{0,0};
    IMAGE *canvas = new IMAGE(1280,1280);
    IMAGE *focusRegionImg = new IMAGE(1280,1280);
    Point center_canvas{0,0};
    IMAGE *targetDetail = new IMAGE(640,128);
    Point center_targetDetail{1280,0};
    IMAGE *playerDetail = new IMAGE(640,128);
    Point center_playerDetail{1280,128};
    IMAGE *backpack = new IMAGE(640,640);
    Point center_backpack{1280,256};
    IMAGE *logger = new IMAGE(640,384);
    Point center_logger{1280,896};
public:
    void drawAll();

    void drawCanvas();
    void drawDetail();
    void drawTargetDetail();
    void drawBackpack();
    void drawLogger();

    void clearCanvas();
    static GameWindow* getGameWindow();

    void initWindow() const;

    int getHeight() const;

    int getWidth() const;

    float getCanvasAspectRatio() const;

    void canvasAspectRatioUp(float i);

    void canvasAspectRatioDown(float i);

    IMAGE *getCanvas() const;

    const Point &getCenterCanvas() const;

    IMAGE *getTargetDetail() const;

    const Point &getCenterTargetDetail() const;

    IMAGE *getPlayerDetail() const;

    const Point &getCenterPlayerDetail() const;

    IMAGE *getBackpack() const;

    const Point &getCenterBackpack() const;

    IMAGE *getLogger() const;

    const Point &getCenterLogger() const;

};

