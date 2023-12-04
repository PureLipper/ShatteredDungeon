#include <windef.h>
#include <winuser.h>
#include <tchar.h>
#include <easyx.h>
#include "GameCore.h"

//
// Created by 林炜昊 on 2023/11/13.
//
class DataCenter {
private:
    int startX = 1280;
    int startY = 0;
    int width = 680;
    int height = 1280;
    GameCore *game = GameCore::getGameCore();
    RECT region = {1280,0,1960,1280};
public:
    void loadPlayerDetail();
    void drawText(){
        RECT r = {1050, 0, 1280, 1280};
        drawtext(_T("Hello World"), &r,DT_LEFT);
    }
};