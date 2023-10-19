#pragma once

#include "RPG_Dynamics.h"

class RPG_Engine;

class cItem
{
public:
	cItem(string name, olcSprite* sprite, string desc);

	virtual bool OnUse(cDynamic* object) { return false; }
	virtual bool OnInteract(cDynamic* object) { return false; }
public:
	string sName;
	string sDescription;
	olcSprite* pSprite;
	bool bKeyItem = false;
	bool bEquipable = false;
	bool bPersist = false;

	static RPG_Engine* g_engine;
};

class cItem_Health : public cItem {	// Give player 10HP
public:
	cItem_Health();
	bool OnUse(cDynamic* object) override;
	bool OnInteract(cDynamic* object) override;
};


class cItem_HealthBoost : public cItem {	// Raise max hp by 10
public: 
	cItem_HealthBoost();
	bool OnUse(cDynamic* object) override;
	bool OnInteract(cDynamic* object) override;
};

class cItem_HealthPotion : public cItem {
public:
	cItem_HealthPotion();
	bool OnUse(cDynamic* object) override;
	bool OnInteract(cDynamic* object) override;
};

class cWeapon : public cItem {
public:
	cWeapon(string name, olcSprite* sprite, string desc, int dmg);
	bool OnInteract(cDynamic* object) override;
	bool OnUse(cDynamic* object) override;

public: 
	int nDamage;
};

class cWeapon_Sword : public cWeapon {
public:
	cWeapon_Sword();
	cWeapon_Sword(string name,string spriteName, string desc, int dmg);
public:
	bool OnUse(cDynamic* object) override;
};