#pragma once
#include "Attributes.h"
class Enemy {
private:
	Attributes * enemyAttributes;
	int rowEnemy, columnEnemy;
	char logo;
public:
	Enemy();
	Enemy(int, int, int helt, int attk, int arm, int lvl, int exp, char logo);
	bool rowEnemyHitWall = false;
	bool columnEnemyHitWall = false;
	int getRowEnemy();
	int getColumnEnemy();
	void setRowEnemy(int);
	void setColumnEnemy(int);
	bool getEnemyHitWallRow();
	void setEnemyHitWallRow(bool);
	void setEnemyHitWallColumn(bool);
	bool getEnemyHitWallColumn();
	char getLogo();
	Attributes* getAttributesEnemy();
};

