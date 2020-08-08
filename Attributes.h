#pragma once
class Attributes {
	int health, maxHealth, attack, armor, level, maxLevel, experience, maxExperience;
public:
	Attributes(int helt, int attk, int arm, int lvl, int exp);
	int getHealth();
	int getAttack();
	int getArmor();
	int getLevel();
	int getExperience();
	int getMaxExperience();
	int getMaxHealth();
	void setReduceHealth(int);
	void setHealth(int);
	void setAttack(int);
	void setArmor(int);
	void setHealthOnLevel();
	void setLevel();
	void setExperience();
};

