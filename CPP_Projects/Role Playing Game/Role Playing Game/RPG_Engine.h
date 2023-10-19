#pragma once

#include <algorithm>

#include "olcConsoleGameEngineOOP.h"
#include "RPG_Map.h"
#include "RPG_Assets.h"
#include "RPG_Dynamics.h"
#include "RPG_Commands.h"
#include "RPG_Quest.h"
#include "RPG_Items.h"

using namespace std;

#define X(n) m_script.AddCommand(new cCommand_ ## n)

class RPG_Engine : public olcConsoleGameEngineOOP {
public:
	RPG_Engine();
	void ShowDialog(vector<string> vecLines);
	void DisplayDialog(vector<string> vecText, int x, int y);
	void DrawBigText(string sText, int x, int y);
	void ChangeMap(string sMapName, float x, int y);
	void UpdateCurrentMap(string mapName);
	void UpdateMapDynamics();
	void UpdateQuestDynamics(string questName);

	void AddQuest(cQuest* quest);
	void UpdateQuestPhase(string name,int phase);
	void ChangeCurrentQuest(string quest);
	void AddProjectile(cDynamic_Projectile* proj);

	bool GiveItem(cItem* item);
	bool TakeItem(cItem* item);
	bool HasItem(cItem* item);

	void Attack(cDynamic_Creature* aggressor, cWeapon* weapon);
	void Damage(cDynamic_Projectile* projectile, cDynamic_Creature* victim);

	int GetQuestPhase(string questName);

	cQuest* GetQuest(string name);

public:
	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

protected:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	bool UpdateTitleScreen(float fElapsedTime);
	bool UpdateLocalMap(float fElapsedTime);
	bool UpdateWorldMap(float fElapsedTime);
	bool UpdateInventory(float fElapsedTime);
	bool UpdateShop(float fElapsedTime);

protected:
	vector<string> m_vecDialogToShow;
	bool m_bShowDialog = false;
	float m_fDialogX = 0.0f;
	float m_fDialogY = 0.0f;
private:
	cMap* m_pCurrentMap = nullptr;
	cQuest* m_pCurrentQuest = nullptr;
	vector<cDynamic*> m_vecDynamics;			// Fixed
	vector<cDynamic*> m_vecProjectiles;			// Transient
	cDynamic_Creature* m_pPlayer = nullptr;
	cScriptProcessor m_script;

	list<cQuest*> m_listQuest;
	list<cItem*> m_listItems;


	olcSprite* m_sprFont = nullptr;

	enum {
		MODE_TITLE,
		MODE_LOCAL_MAP,
		MODE_WORLD_MAP,
		MODE_INVENTORY,
		MODE_SHOP
	};

	int m_nGameMode = MODE_LOCAL_MAP;

	int m_nInvSelectX = 0;
	int m_nInvSelectY = 0;
};

