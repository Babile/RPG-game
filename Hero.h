#pragma once
#include <vector>
#include "Enemy.h"
using namespace std;
class Hero {
protected:
	Attributes * atrributes;
	int rowHero, columnHero;
	char logo;
public:
	Hero(int, int, int, int, int, int, int, char);
	char getLogo();
	int getRowHero();
	int getColumnHero();
	void setRowHero(int);
	void setColumnHero(int);
	char getButton();
	void muveHero(int, int, int, int, vector<Enemy*>);
	Attributes* getAttributes();
};

