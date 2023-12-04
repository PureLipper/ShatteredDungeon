//
// Created by 林炜昊 on 2023/11/6.
//
#pragma once
    static const int _NULL = 0;              //空

    //地形的参数标签：
    static const int FLOOR = 28;			//普通地板
    static const int WALL = 1;				//墙
    static const int WATER = 2;				//水地
    static const int GRASS = 3;				//草
    static const int _GRASS = 4;			//踩踏过的草
    static const int CLOSED_DOOR = 5;		//关闭的门
    static const int OPENED_DOOR = 25;		//打开的门
    static const int LOCKED_DOOR = 6;		//上锁的门
    static const int _VOID = 7;				//跳进下一层
    static const int WOODEN_FLOOR = 8;		//木地板
    static const int TRAP = 9;				//陷阱
    static const int DOWN_FLOOR = 10;		//下楼
    static const int UP_FLOOR = 11;			//上楼
    static const int SCULPTURE = 12;		//雕像
    static const int INVISIBLE_DOOR = 13;	//隐形门
    static const int INVISIBLE_TRAP = 14;	//隐形陷阱
    static const int SP_GRASS = 15;			//特殊的草
    static const int TREASURE = 16;			//宝箱
    static const int GOLDEN_TREASURE = 26;	//金宝箱
    static const int ASH = 17;				//灰烬
    static const int KNOWLEDGE_WELL = 18;	//知识之泉
    static const int HEALTH_WELL = 19;		//生命之泉
    static const int FIRE_WALL = 20;		//火焰之墙
    static const int TOMB = 21;				//墓碑
    static const int BONE = 22;				//骨架
    static const int BOOKSHELF = 23;		//书架
    static const int STAGE = 24;			//物品展示台
    static const int CAULDRON = 27;			//炼药锅
    static const int GRAY = 29;             //灰色蒙版

    //特殊房间标签；
    static const int UP_FLOOR_ROOM = 1;
    static const int DOWN_FLOOR_ROOM = 2;

    //人物状态标签
    static const int WATCHING = 0;//状态：观望
    static const int MOVING = 1;//状态：移动
    static const int FLOATING = 4;//状态：悬浮
    static const int UNLOCKING = 3;//状态：解锁
    static const int ATTACKING = 6;//状态：投掷
    static const int DEAD = 2;//状态：死亡
    static const int READING = 5;//状态：阅读

    //人物职业标签
    static const int WARRIOR = 0;//职业：战士
    static const int MAGE = 1;//职业：法师
    static const int ROGUE = 2;//职业：盗贼
    static const int HUNTRESS = 3;//职业：女猎手
    static const int DUELIST = 4;//职业：决斗家

    //人物朝向标签
    static const int RIGHTWARD = 0;//朝右
    static const int LEFTWARD = 1;//朝左

    //地图蒙版标签
    static const int KNOWN = 1;//已知地块
    static const int UNKNOWN = 0;//未知地块

    //视野蒙版标签
    static const int INSIGHT = 88;
    static const int OUTSIGHT = 0;

    //护甲等级标签
    static const int CLOTH = 1;
    static const int LEATHER = 2;
    static const int MAIL = 3;
    static const int SCALE = 4;
    static const int PLATE = 5;

    //敌人状态标签
    static const int SLEEPING = 0;//状态：沉睡
    static const int HANGING = 1;//状态：闲逛
    static const int CHASING = 2;//状态：追逐
    static const int E_ATTACKING = 3;//状态：攻击
