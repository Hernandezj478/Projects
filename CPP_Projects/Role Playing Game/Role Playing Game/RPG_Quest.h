#ifndef RPG_QUEST_H
#define RPG_QUEST_H

#include "RPG_Dynamics.h"
#include "RPG_Commands.h"
#include "RPG_Items.h"

class RPG_Engine;
class cScriptProcessor;

class cQuest{
public:
	enum NATURE {
		TALK = 0,
		ATTACK = 1,
		KILL = 2,
		WALK = 3
	};

public:
	cQuest(string name);

public:
	virtual bool OnInteration(vector<cDynamic*>& vecDynobs, cDynamic* target, NATURE nature);
	virtual bool PopulateDynamics(vector<cDynamic*>& vecDyns, string sMap);


	void AddPersistObject(cDynamic* obj);
	void UpdatePersistObjects();
	void UpdateMapDynamics(vector<cDynamic*>& vecDyns);

public:
	string sName;
	bool bCompleted = false;

	int nLoadedPersistDyns = 0;		// 32-bit int to represent flags of what perist obj has been created

	int m_nPhase = 0;
	unsigned int nPersistObjects = 0;

	static cScriptProcessor* g_script;
	static RPG_Engine* g_engine;

	vector<cDynamic*> vecPersistObjects;
};

class cQuest_MainQuest : public cQuest {
public:
	cQuest_MainQuest();
	bool OnInteration(vector<cDynamic*>& vecDynobs, cDynamic* target, NATURE nature) override;
	bool PopulateDynamics(vector<cDynamic*>& vecDyns, string sMap) override;
};

class cQuest_BobQuest : public cQuest {
public:
	cQuest_BobQuest();
	bool OnInteration(vector<cDynamic*>& vecDynobs, cDynamic* target, NATURE nature) override;
	bool PopulateDynamics(vector<cDynamic*>& vecDyns, string sMap) override;

	bool bConfirmedKills = false;
	int killCount = 0;
};


#endif