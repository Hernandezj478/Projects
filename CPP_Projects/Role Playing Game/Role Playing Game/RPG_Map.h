#ifndef RPG_MAP_H
#define RPG_MAP_H
#include "olcConsoleGameEngineOOP.h"
#include "RPG_Assets.h"
#include "RPG_Dynamics.h"
#include "RPG_Commands.h"

#include <string>

class RPG_Engine;

class cMap{
public:

	enum NATURE {
		TALK,
		WALK
	};

	cMap();
	~cMap();

	int nWidth;
	int nHeight;

	string sName;
	olcSprite* pSprite;

	vector<cDynamic*> vecPersistObjects;

	unsigned int nLoadPersistDyns = 0;

	int CalculatePos(int x, int y, int width);

	int GetIndex(int x, int y);
	bool GetSolid(int x, int y);
	bool Create(string fileData, olcSprite* sprite, string name);

	void AddPersistObjects(cDynamic* obj);
	void UpdatePersistObjects();
	void UpdateMapDynamics(vector<cDynamic*>& vecDyns);

	virtual bool UpdateIndicesAndSolids(string) { 
		return false; 
	}

	virtual bool PopulateDynamics(vector<cDynamic*>& vecDyns) {
		return false;
	}

	virtual bool OnInteraction(vector<cDynamic*>& vecDyn, cDynamic* target, NATURE nature) {
		return false;
	}
public:
	static cScriptProcessor* g_script;
	static RPG_Engine* g_engine;

protected:
	int* m_indices = nullptr;
	bool* m_solids = nullptr;

};

class cMap_Village1 : public cMap {
public:
	cMap_Village1();
	bool PopulateDynamics(vector<cDynamic*>& vecDyns) override;
	bool OnInteraction(vector<cDynamic*>& vecDyn, cDynamic* target, NATURE nature) override;
	bool UpdateIndicesAndSolids(string mapName) override;
};

class cMap_Home1 : public cMap {
public:
	cMap_Home1();
	bool PopulateDynamics(vector<cDynamic*>& vecDyns) override;
	bool OnInteraction(vector<cDynamic*>& vecDyn, cDynamic* target, NATURE nature) override;
	bool UpdateIndicesAndSolids(string mapName);
};

class cMap_Basement : public cMap {
public:
	cMap_Basement();
	bool PopulateDynamics(vector<cDynamic*>& vecDyns) override;
	bool OnInteraction(vector<cDynamic*>& vecDyn, cDynamic* target, NATURE nature) override;
};


#endif