#pragma once
enum TileMode {
	NORMAL, // 通常 : 0
	BLUE, // 味方 : 1
	BLUE_ARCHER, // 味方のアーチャー : 2
	BLUE_WARRIOR,// 味方のウォリアー : 3
	BLUE_SWORDSMAN,// 味方のソードマン : 4
	RED, // 敵 : 5
	RED_ARCHER, // 敵のアーチャー : 6 
	RED_WARRIOR, // 敵のウォリアー : 7
	RED_SWORDSMAN, // 敵のソードマン : 8
	ROLECHANGETILE // ロールが変わるマス : 9
};
