#pragma once
#include "Enemy.h"
class BossEnemy :public Enemy { 
public:
	BossEnemy();
	BossEnemy(int, int, int helt, int attk, int arm, int lvl, int exp, char logo);
};

