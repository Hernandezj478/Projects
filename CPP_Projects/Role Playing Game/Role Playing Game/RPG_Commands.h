#pragma once

#include <list>
#include "RPG_Dynamics.h"
#include "RPG_Quest.h"

using namespace std;

class RPG_Engine;
class cQuest;

class cCommand{
public:
	cCommand() {}
	virtual ~cCommand() {}

	bool bStarted = false;
	bool bCompleted = false;

	virtual void Start() {}
	virtual void Update(float fElapsedTime) {}

	static RPG_Engine* g_engine;

};

class cScriptProcessor {
public:
	cScriptProcessor();

	void AddCommand(cCommand* cmd);
	void ProcessCommands(float fElapsedTime);
	void CompleteCommand();

public:
	bool bUserControlEnabled;
private:
	list<cCommand*> m_listCommands;
};

class cCommand_MoveTo : public cCommand {
public:
	cCommand_MoveTo(cDynamic* object, float x, float y, float duration = 0.0f);
	void Start() override;
	void Update(float fElapsedTime) override;
private:
	cDynamic* m_pObject;
	float m_fStartPosX;
	float m_fStartPosY;
	float m_fTargetPosX;
	float m_fTargetPosY;
	float m_fDuration;
	float m_fTimeSoFar;
};

class cCommand_ShowDialog : public cCommand {
public:
	cCommand_ShowDialog(vector<string> line);
	void Start() override;
private:
	vector<string> vecLines;

};

class cCommand_ChangeMap : public cCommand {
public:
	cCommand_ChangeMap(string mapName, float mapPosX, float mapPosY);
	void Start() override;

private:
	string m_sMapName;
	float m_fMapPosX;
	float m_fMapPosY;
};

class cCommand_AddQuest : public cCommand {
public:
	cCommand_AddQuest(cQuest* quest);
	void Start() override;
public:
	cQuest* m_quest;
};

class cCommand_UpdateQuestPhase : public cCommand {
public:
	cCommand_UpdateQuestPhase(string quest, int phase);
	void Start() override;
public:
	string s_questName;
	int m_nPhase;
};

class cCommand_GiveItem : public cCommand {
public:
	cCommand_GiveItem(cItem* item);
	void Start() override;
public:
	cItem* m_item;
};

class cCommand_ChangeCurrentQuest : public cCommand {
public:
	cCommand_ChangeCurrentQuest(string questName);
	void Start() override;
public:
	string s_questName;
};

class cCommand_UpdateCurrentMap : public cCommand {
public:
	cCommand_UpdateCurrentMap(string mapName);
	void Start() override;
public:
	string s_mapName;
};

class cCommand_UpdateMapDynamics : public cCommand {
public:
	cCommand_UpdateMapDynamics() {}
	void Start();
};

class cCommand_UpdateQuestDynamics : public cCommand {
public:
	cCommand_UpdateQuestDynamics(string questName);
	void Start() override;
public:
	string s_questName;
};