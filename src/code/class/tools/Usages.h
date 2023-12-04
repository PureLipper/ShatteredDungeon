//
// Created by 林炜昊 on 2023/11/23.
//
#pragma once

#include <vector>
#include <easyx.h>
#include "map/Point.h"
#include "entity/Entity.h"

/*BFS广度优先搜索路径
 * 输入为起点和终点
 * 返回值为路径栈，取用时倒取为顺序，也就是说vector的第一个元素是整条路的终点，最后一个元素是下一步的位置*/
std::vector<Point> BFSRoadFinding(const Point &startP, const Point &targetP);

//绘制透明背景png，在GameWindow里的Canvas上绘制
void drawTransparentToCanvas(int x, int y, IMAGE *src);

//对e进行视野判断，如果范围内存在player就设置移动路径到player
bool LookingForTarget(Entity *e);