#include "RPG_Map.h"
#include "RPG_Engine.h"

#include <fstream>

cScriptProcessor* cMap::g_script = nullptr;
RPG_Engine* cMap::g_engine = nullptr;

#define X(n) g_script->AddCommand(new cCommand_ ## n)

cMap::cMap() {
	pSprite = nullptr;
	nWidth = 0;
	nHeight = 0;
	m_solids = nullptr;
	m_indices = nullptr;
}

cMap::~cMap() {
	delete[] m_solids;
	delete[] m_indices;
}

int cMap::CalculatePos(int x, int y, int width) {
	return (y * width) + x;
}

int cMap::GetIndex(int x, int y) {
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return m_indices[y * nWidth + x];
	else
		return 0;
}

bool cMap::GetSolid(int x, int y) {
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return m_solids[y * nWidth + x];
	else
		return true;
}

bool cMap::Create(string fileData, olcSprite* sprite, string name) {
	sName = name;
	pSprite = sprite;
	ifstream data(fileData, ios::in | ios::binary);
	if (data.is_open()) {
		data >> nWidth >> nHeight;
		m_solids = new bool[nWidth * nHeight];
		m_indices = new int[nWidth * nHeight];
		for (int i = 0; i < nWidth * nHeight; i++) {
			data >> m_indices[i];
			data >> m_solids[i];
		}

		return true;
	}

	return false;
}

void cMap::AddPersistObjects(cDynamic* obj) {
	if (obj->bPersist)
		vecPersistObjects.push_back(obj);
}

void cMap::UpdatePersistObjects() {
 	if (!vecPersistObjects.empty()) {
		for (auto dyn : vecPersistObjects) {
			auto i = remove_if(vecPersistObjects.begin(), vecPersistObjects.end(), [](const cDynamic* d) {return !d->bPersist; });
			if (i != vecPersistObjects.end())
				vecPersistObjects.erase(i);
		}
	}
}

void cMap::UpdateMapDynamics(vector<cDynamic*>& vecDyns) {
	for (auto& dyn : vecPersistObjects) {
		vecDyns.push_back(dyn);
	}
}

// Village 1 Map

cMap_Village1::cMap_Village1() {
	Create("rpgdata/map/village1.lvl", RPG_Assets::get().GetSprite("village"), "coder town");
}

bool cMap_Village1::PopulateDynamics(vector<cDynamic*>& vecDyns) {
	int questPhase = g_engine->GetQuestPhase("main quest");
	if (questPhase < 2 && questPhase >= 0) {
		unsigned int tmp = nLoadPersistDyns;
		tmp &= 0x1;
		if ((tmp ^ 0x1) != 0) {
			//Add Teleporters
			AddPersistObjects(new cDynamic_Teleport(12.0f, 6.0f, "home", 5.0f, 12.0f));
			nLoadPersistDyns |= 0x1;

		}

		UpdateMapDynamics(vecDyns);
	}
	if (questPhase == 2) {
		unsigned tmp = nLoadPersistDyns;
		tmp &= 0x10;
		if ((tmp ^ 0x10) != 0) {
			// Add Teleporter
			AddPersistObjects(new cDynamic_Teleport(30.0f, 7.0f, "coder town", 12.0f, 12.0f));
			nLoadPersistDyns |= 0x10;
		}
		UpdateMapDynamics(vecDyns);


	}

	// Get witty to be stationary when exiting teleporter
	for (auto& dyn : vecDyns) {
		if (dyn->sName == "witty") {
			dyn->vy = 0;
			dyn->vx = 0;
			break;
		}
	}

	//Add Items
	//vecDyns.push_back(new cDynamic_Item(10, 10, RPG_Assets::get().GetItem("Small Health")));
	//vecDyns.push_back(new cDynamic_Item(12, 10, RPG_Assets::get().GetItem("Health Boost")));
	//vecDyns.push_back(new cDynamic_Item(14, 10, RPG_Assets::get().GetItem("Health Potion")));

	return true;
}

bool cMap_Village1::OnInteraction(vector<cDynamic*>& vecDyn, cDynamic* target, NATURE nature) {
	if (target->sName == "Teleport") {
		X(ChangeMap(
			((cDynamic_Teleport*)target)->sMapName,
			((cDynamic_Teleport*)target)->fMapPosX,
			((cDynamic_Teleport*)target)->fMapPosY));
	}
	return false;
}

bool cMap_Village1::UpdateIndicesAndSolids(string mapName) {
	if (mapName == "coder town open") {
		int index = CalculatePos(22, 7, nWidth);
		// Update position (22,7) - remove tree
		m_indices[index] = 14;			// 14 is open grass
		m_solids[index] = false;		// false is not solid
	}
	return true;
}


// Home 1 Map

cMap_Home1::cMap_Home1() {
	Create("rpgdata/map/home.lvl", RPG_Assets::get().GetSprite("hitech"), "home");
}


bool cMap_Home1::PopulateDynamics(vector<cDynamic*>& vecDyns) {
	int questPhase = g_engine->GetQuestPhase("main quest");

	// Front door - always open
	unsigned int tmp = nLoadPersistDyns;
	tmp &= 0x1;
	if ((tmp ^ 0x1) != 0) {
		AddPersistObjects(new cDynamic_Teleport(5.0f, 13.0f, "coder town", 12.0f, 7.0f));
		AddPersistObjects(new cDynamic_Teleport(4.0f, 13.0f, "coder town", 12.0f, 7.0f));
		UpdateMapDynamics(vecDyns);
		nLoadPersistDyns |= 0x1;
	}

	tmp = nLoadPersistDyns;
	if ((questPhase > 0) && ((tmp ^ 0x10) != 0)) {
		//Basement Elevator
		AddPersistObjects(new cDynamic_Teleport(5.0f, 2.0f, "basement", 7.0f, 5.0f));
		//AddPersistObjects(new cDynamic_Teleport(6.0f, 2.0f, "basement", 8.0f, 5.0f));
		UpdateMapDynamics(vecDyns);

		nLoadPersistDyns |= 0x10;
	}

	// Get witty to be stationary when exiting teleporter
	for (auto& dyn : vecDyns) {
		if (dyn->sName == "witty") {
			dyn->vy = 0;
			dyn->vx = 0;
			break;
		}
	}

	return true;
}

bool cMap_Home1::OnInteraction(vector<cDynamic*>& vecDyn, cDynamic* target, NATURE nature) {
	if (target->sName == "Teleport") {
		X(ChangeMap(
			((cDynamic_Teleport*)target)->sMapName,
			((cDynamic_Teleport*)target)->fMapPosX,
			((cDynamic_Teleport*)target)->fMapPosY));
	}
	return false;
}

bool cMap_Home1::UpdateIndicesAndSolids(string mapName) {
	if (mapName == "home open") {
		// Animate doors opening
		// Position (6,1) - Top Left
		int posX = 6, poxY = 2;
		int index = CalculatePos(6, 1, nWidth);
		m_indices[index] = m_indices[index] + 2;
		m_solids[index] = !m_solids[index];

		// Position (7,1) - Top Right
		index = CalculatePos(7, 1, nWidth);
		m_indices[index] = m_indices[23] + 2;
		m_solids[index] = !m_solids[23];

		// Position (6,2) - Bottom Left
		index = CalculatePos(6, 2, nWidth);
		m_indices[index] = m_indices[index] + 2;
		m_solids[index] = !m_solids[index];

		// Position (7,2) - Bottom Right
		index = CalculatePos(7, 2,nWidth);
		m_indices[index] = m_indices[index] + 2;
		m_solids[index] = !m_solids[index];
	}
	return true;
}

// Basement

cMap_Basement::cMap_Basement() {
	Create("rpgdata/map/basement.lvl", RPG_Assets::get().GetSprite("hitech"), "basement");
}

bool cMap_Basement::PopulateDynamics(vector<cDynamic*>& vecDyns) {
	unsigned int tmp = nLoadPersistDyns;
	tmp &= 0x1;
	if ((tmp ^ 0x1) != 0) {
		// Elevator
		AddPersistObjects(new cDynamic_Teleport(8.0f,4.0f,"home",7.0f,3.0f));
		AddPersistObjects(new cDynamic_Teleport(7.0f,4.0f,"home",6.0f,3.0f));
		nLoadPersistDyns |= 0x1;

	}

	// Call function to load objects
	UpdateMapDynamics(vecDyns);

	// Get witty to look south when exiting elevator
	for (auto& dyn : vecDyns) {
		if (dyn->sName == "witty") {
			((cDynamic_Creature*)dyn)->m_nFacingDirection	= cDynamic_Creature::SOUTH;
			((cDynamic_Creature*)dyn)->m_nGraphicState		= cDynamic_Creature::STANDING;
			dyn->vx = 0;
			dyn->vy = 0;
		}
	}
	return true;
}

bool cMap_Basement::OnInteraction(vector<cDynamic*>& vecDyn, cDynamic* target, NATURE nature) {
	if (target->sName == "Teleport") {
		X(ChangeMap(
			((cDynamic_Teleport*)target)->sMapName,
			((cDynamic_Teleport*)target)->fMapPosX,
			((cDynamic_Teleport*)target)->fMapPosY
		));
	}
	return false;
}