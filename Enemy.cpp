#include "Enemy.h"

Enemy::Enemy(int rE, int cE, int helt, int attk, int arm, int lvl, int exp, char lg) {
	logo = lg;
	rowEnemy = rE;
	columnEnemy = cE;
	enemyAttributes = new Attributes(helt, attk, arm, lvl, exp);
}

Enemy::Enemy() {
	rowEnemy = 0;
	columnEnemy = 0;
}

int Enemy::getRowEnemy() {
	return rowEnemy;
}

int Enemy::getColumnEnemy() {
	return columnEnemy;
}

void Enemy::setRowEnemy(int rE) {
	rowEnemy = rE;
}

void Enemy::setColumnEnemy(int cE) {
	columnEnemy = cE;
}

bool Enemy::getEnemyHitWallRow() {
	return rowEnemyHitWall;
}

void Enemy::setEnemyHitWallRow(bool input) {
	rowEnemyHitWall = input;
}

void Enemy::setEnemyHitWallColumn(bool input) {
	columnEnemyHitWall = input;
}

bool Enemy::getEnemyHitWallColumn() {
	return columnEnemyHitWall;
}

char Enemy::getLogo() {
	return logo;
}

Attributes * Enemy::getAttributesEnemy() {
	return enemyAttributes;
}
