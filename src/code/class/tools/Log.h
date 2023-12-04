//
// Created by 林炜昊 on 2023/11/16.
//

#pragma once

#include <windef.h>
#include <string>
#include <easyx.h>

class Log {
private:
    static std::string sysDiary;
    static std::string diary;

public:
    static void p(const std::string& context, const std::string& content);
    static void s(const std::string& context, const std::string& content);
};