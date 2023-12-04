//
// Created by 林炜昊 on 2023/11/16.
//

#include <iostream>
#include "launch/GameWindow.h"
#include "Log.h"
std::string Log::diary;
std::string Log::sysDiary;
void Log::p(const std::string& context, const std::string& content) {
    SetWorkingImage(GameWindow::getGameWindow()->getLogger());
    setaspectratio(1,1);
    cleardevice();
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 18;
    _tcscpy(f.lfFaceName, _T("黑体"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    diary = context + ":   " + content + "\n" + diary;
    drawtext(_T(diary.c_str()),new RECT{0,0,640,384},DT_WORDBREAK);
    SetWorkingImage();
}

void Log::s(const std::string &context, const std::string &content) {
    sysDiary += context + ":   " + content + "\n";
    std::cout << context + ":   " + content + "\n";
}
