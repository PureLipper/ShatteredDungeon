#include <conio.h>
#include <map>
#include <queue>
#include "launch/GameCore.h"
#include "entity/player/Warrior.h"
#include "launch/DataCenter.h"
#include "entity/Enemy.h"
#include "tools/Log.h"
#include "tools/Usages.h"
#include "entity/enemy/Rat.h"

#pragma execution_character_set("utf-8")
using namespace std;

int main() {
    GameCore *game = GameCore::getGameCore();
    game->start();
}