#include "Attributes.h"

const int levelsXp[31] = { 200,500,900,1400,2000,2600,3200,4400,5400,6000,8200,9000,10400,11900,13500,15200,17000,18900,20900,23000,25200,27500,29900,32400,35500,39000,42000,48500,52000, 52074 };
const int valueXPPerKill[30] = { 28,33,52,58,74,78,83,90,98,109,123,128,146,158,150,148,142,130,128,120,117,108,100,93,88,85,80,78,73,70 };
const int bonusAttackOnLevel[30] = { 4,7,9,13,15,17,20,21,25,28,30,31,39,44,51,56,60,61,64,70,75,79,82,88,90,92,98,100,101,109 };
const int bonusArmorOnLevel[30] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
const int bonusHealthOnLevel = 118;

Attributes::Attributes(int helt, int attk, int arm, int lvl, int exp) {
	maxExperience = levelsXp[0];
	health = helt;
	maxHealth = health;
	attack = attk;
	armor = arm;
	level = lvl;
	experience = exp;
	maxLevel = 30;
}

int Attributes::getHealth() {
	return health;
}

int Attributes::getAttack() {
	return attack;
}

int Attributes::getArmor() {
	return armor;
}

int Attributes::getLevel() {
	return level;
}

int Attributes::getExperience() {
	return experience;
}

int Attributes::getMaxExperience() {
	return maxExperience;
}

int Attributes::getMaxHealth() {
	return maxHealth;
}

void Attributes::setReduceHealth(int enemyDamage) {
	if (enemyDamage > armor) {
		health -= ((enemyDamage - armor) / 2);
	}
	else {
		health -= (enemyDamage - (armor / 2));
	}
}

void Attributes::setHealth(int regenHealth) {
	health += regenHealth;
}

void Attributes::setHealthOnLevel() {
	maxHealth += bonusHealthOnLevel;
	health += bonusHealthOnLevel;
}

void Attributes::setAttack(int increaseAttackByLevel) {
	if (increaseAttackByLevel == maxLevel) {
		attack;
	}
	else {
		if (experience >= levelsXp[increaseAttackByLevel - 1]) {
			attack += bonusAttackOnLevel[increaseAttackByLevel - 1];
		}
	}
}

void Attributes::setArmor(int increaseArmorByLevel) {
	if (increaseArmorByLevel == maxLevel) {
		armor;
	}
	else {
		if (experience >= levelsXp[increaseArmorByLevel - 1]) {
			armor += bonusArmorOnLevel[increaseArmorByLevel - 1];
		}
	}
}

void Attributes::setLevel() {
	for (int i = 0; i < 31; i++) {
		if (experience > levelsXp[i]) {
			continue;
		}
		else {
			level = i + 1;
			valueXPPerKill[level - 1];
			if (level > 1 || level < maxLevel+1) {
				maxExperience = levelsXp[level - 1];
			}
			break;
		}
	}
}

void Attributes::setExperience() {
	if (level == maxLevel) {
		experience += 0;
	}
	else {
		experience += valueXPPerKill[level - 1];
	}
}