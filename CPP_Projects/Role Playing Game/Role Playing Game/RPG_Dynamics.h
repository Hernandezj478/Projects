#pragma once
#include "olcConsoleGameEngineOOP.h"
#include "RPG_Assets.h"

class RPG_Engine;
class cItem;
class cWeapon;

class cDynamic{
public:
	cDynamic(string n);
	~cDynamic();

public:
	float px, py;
	float vx, vy;
	bool bSolidVsMap;
	bool bSolidVsDyn;
	bool bFriendly;
	bool bRedundant;
	bool bIsProjectile;
	bool bIsAttackable;
	bool bPersist;
	string sName;

	static RPG_Engine* g_engine;

public:
	virtual void Update(float fElapsedTime, cDynamic* player = nullptr) {}
	virtual void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) {}
	virtual void OnInteract(cDynamic* player = nullptr) {}

};

class cDynamic_Creature : public cDynamic {
public:
	cDynamic_Creature(string n, olcSprite* sprite);

public:
	int nHealth;
	int nHealthMax;
	bool bControllable = true;
public:
	void Update(float fElapsedTime, cDynamic* player = nullptr) override;
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
	virtual void Behavior(float fElaplsedTime, cDynamic* player = nullptr);
	virtual void PerformAttack() {}
	
	void KnockBack(float dx, float dy, float dist);

	cWeapon* pEquipedWeapon = nullptr;

	int GetFacingDirection() { return m_nFacingDirection; }
	
	enum Direction { SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3 } m_nFacingDirection;
	enum State {STANDING, WALKING, CELEBRATING, DEAD} m_nGraphicState;

protected:
	olcSprite* m_pSprite;


	int m_nGraphicCounter;
	float m_fTimer;
	float m_fStateTick;

	float m_fKnockBackTimer = 0.0f;
	float m_fKnockBackDX = 0.0f;
	float m_fKnockBackDY = 0.0f;
};

class cDynamic_Creature_Skelly : public cDynamic_Creature {
public:
	cDynamic_Creature_Skelly();
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
	void Behavior(float fElapsedTime, cDynamic* player) override;
	void PerformAttack() override;

	cDynamic_Creature_Skelly& operator=(const cDynamic_Creature_Skelly& obj);
};

class cDynamic_Creature_Witty : public cDynamic_Creature {
public:
	cDynamic_Creature_Witty();
public:
	void PerformAttack() override;
};

class cDynamic_Teleport : public cDynamic{
public:
	cDynamic_Teleport(float x, float y, string mapName, float tx, float ty);
	void Update(float fElapsedTime, cDynamic* player = nullptr) override;
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;

public:
	string sMapName;
	float fMapPosX;
	float fMapPosY;
};

class cDynamic_Item : public cDynamic {
public:
	cDynamic_Item(float x, float y, cItem* item);
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
	void OnInteract(cDynamic* player = nullptr) override;

public:
	cItem* item;
	bool bCollected = false;
};

class cDynamic_Projectile : public cDynamic {
public:
	cDynamic_Projectile(float ox, float oy, bool bFriend, float velx, float vely, float duration, olcSprite* sprite, float tx, float ty);
	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
	void Update(float fElapsedTime, cDynamic* player = nullptr) override;

public:
	olcSprite* pSprite = nullptr;
	float fSpriteX;
	float fSpriteY;
	float fDuration;
	bool bOneHit = true;

	int nDamage = 0;
};

class cDynamic_Button : public cDynamic {
public:
	cDynamic_Button(float x, float y,string mapName);
	void OnInteract(cDynamic* player = nullptr) override;
public:
	string sMapName;
	bool bPressed = false;
};