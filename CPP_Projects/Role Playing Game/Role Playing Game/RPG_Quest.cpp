#include "RPG_Quest.h"
#include "RPG_Engine.h"


RPG_Engine* cQuest::g_engine = nullptr;
cScriptProcessor* cQuest::g_script = nullptr;

#define X(n) g_script->AddCommand(new cCommand_ ## n)


cQuest::cQuest(string name) {
	sName = name;
}

bool cQuest::PopulateDynamics(vector<cDynamic*>& vecDyns, string sMap) {
	return true;
}

bool cQuest::OnInteration(vector<cDynamic*>& vecDynobs, cDynamic* target, NATURE nature) {
	return true;
}

void cQuest::AddPersistObject(cDynamic* obj) {
	if (obj->bPersist)
		vecPersistObjects.push_back(obj);
}

void cQuest::UpdatePersistObjects() {
	if (!vecPersistObjects.empty()) {
		for (auto dyn : vecPersistObjects) {
			auto i = remove_if(vecPersistObjects.begin(), vecPersistObjects.end(), [](const cDynamic* d) {return !d->bPersist; });
			if (i != vecPersistObjects.end())
				vecPersistObjects.erase(i);
		}
	}
}

void cQuest::UpdateMapDynamics(vector<cDynamic*>& vecDyns) {
	for (auto& dyn : vecPersistObjects) {
		vecDyns.push_back(dyn);
	}
}

// Main Quest
cQuest_MainQuest::cQuest_MainQuest() : cQuest("main quest") {

}

bool cQuest_MainQuest::PopulateDynamics(vector<cDynamic*>& vecDyns, string sMap){
	if ((sMap == "home") && (m_nPhase == 0 || m_nPhase == 1)) {
		unsigned int tmp = nLoadedPersistDyns;
		tmp &= 0x10;
		if((tmp ^ 0x10) != 0){
			cDynamic_Creature* c1 = new cDynamic_Creature("bob", RPG_Assets::get().GetSprite("orange"));
			c1->px = 12.0f;
			c1->py = 4.0f;
			c1->bPersist = true;
			AddPersistObject(c1);
			nLoadedPersistDyns |= 0x10;			//	0x10 represents 2nd flag loaded
		}
		// Call function to copy pointer vector
		UpdateMapDynamics(vecDyns);
	}
	// Phase 2, spawn 2 skellys and open village
	if (sMap == "coder town" && m_nPhase == 2) {
		unsigned int tmp = nLoadedPersistDyns;
		tmp &= 0x1;
		if ((tmp ^ 0x1) != 0) {
			// Spawn 2 enemies infront of house
			for (int i = 0; i < 2; i++) {
				cDynamic_Creature_Skelly* c1 = new cDynamic_Creature_Skelly();
				c1->px = rand() % 8 + 9;
				c1->py = rand() % 8 + 11;
				AddPersistObject(c1);
			}
			// Spawn 1 enemy near healthboost pickup
			cDynamic_Creature_Skelly* c1 = new cDynamic_Creature_Skelly();
			c1->px = 6;
			c1->py = 21;
			c1->nHealthMax = 15;
			c1->nHealth = c1->nHealthMax;
			AddPersistObject(c1);

			// Spawn heathboost
			cItem_HealthBoost* b1 = new cItem_HealthBoost();
			cDynamic_Item* d1 = new cDynamic_Item(2, 21, b1);
			AddPersistObject(d1);

			nLoadedPersistDyns |= 0x1;			// 0x1 represents 1st flag loaded
		}
		
		// Update map to show village open
		X(UpdateCurrentMap("coder town open"));

		// Call function to copy pointer vector
		UpdateMapDynamics(vecDyns);
	}
	return true;
}

bool cQuest_MainQuest::OnInteration(vector<cDynamic*>& vecDynobs, cDynamic* target, NATURE nature) {
	if (target->sName == "bob" && m_nPhase == 0) {
		X(ShowDialog({ "[Bob]","I need you to do","something for me..." }));
		X(ShowDialog({ "[Bob]","Predictably, there are","rats in my basement!" }));
		cQuest_BobQuest* quest = new cQuest_BobQuest();
		X(AddQuest(quest));
		m_nPhase++;
		// Update map to animate basement elevator opening
		X(UpdateCurrentMap("home open"));
		X(UpdateMapDynamics());

		//X(ChangeMap("home", vecDynobs[0]->px, vecDynobs[0]->py));
	}
	if (m_nPhase == 2) {
		for (auto& obj : vecDynobs) {
			if (obj->sName == "Skelly") {
				if (((cDynamic_Creature*)obj)->nHealth <= 0 && obj->bPersist){
					obj->bPersist = false;
				}
			}
		}
		UpdatePersistObjects();
	}
	return false;
}

// Bob's Quest

cQuest_BobQuest::cQuest_BobQuest() : cQuest("bob quest") {
	
}

bool cQuest_BobQuest::PopulateDynamics(vector<cDynamic*>& vecDyns, string sMap) {
	if (sMap == "basement" && m_nPhase == 0) {
		// If assets not loaded, load assets
		if ((nLoadedPersistDyns ^ 0x1) != 0) {
			for (int i = 0; i < 3; i++) {
				cDynamic* g1 = new cDynamic_Creature_Skelly();
				vecDyns.push_back(g1);
				g1->px = rand() % 7 + 18.0f;
				g1->py = rand() % 7 + 7.0f;
				AddPersistObject(g1);
				nLoadedPersistDyns |= 0x1;
			}
		}
		// Call function to load objects
		UpdateMapDynamics(vecDyns);
	}

	return true;
}

bool cQuest_BobQuest::OnInteration(vector<cDynamic*>& vecDynobs, cDynamic* target, NATURE nature) {
	if (!bConfirmedKills) {
		for (auto& obj : vecDynobs) {
			if (obj->sName == "Skelly") {
				if ((((cDynamic_Creature*)obj)->nHealth <= 0) && obj->bPersist) {
					obj->bPersist = false;
					killCount++;
				}
			}
		}

		if (killCount == 3) {// We know there are 3 skellys during this mission
			// Increment the phase of the quest
			this->m_nPhase++;
			bConfirmedKills = true;
		}
	}
	if (m_nPhase == 0 && target->sName == "bob") {
		X(ShowDialog({ "[Bob]","Please hurry adventurer!"}));
		X(ShowDialog({ "[Bob]","If we don't take care","of this rat problem","things may get out","of hand!!" }));
	}
	if (m_nPhase == 1 && target->sName == "bob") {
		// Completed quest, hand in for reward
		X(ShowDialog({ "[Bob]","Oh my!", "You made it back", "in one piece!" }));
		X(ShowDialog({ "[Bob]","That means you must've","taken care of my rat","problem!" }));
		X(ShowDialog({ "[Bob]","Thank you adveturer!","Let me reward you with","something" }));

		//Give reward to player
		X(GiveItem(new cWeapon_Sword("Iron Sword", "Iron Sword", "An iron sword, 15 damage.", 15)));
		X(ShowDialog({ "Gained Iron Sword" }));
		// Give health boost
		X(GiveItem(new cItem_HealthBoost()));
		X(ShowDialog({ "Gained Healthboost"}));
		// Give healthpotion
		X(GiveItem(new cItem_HealthPotion()));
		X(ShowDialog({"Gained Health Potion"}));


		X(ShowDialog({ "[Bob]","I must be off now","Thank you again","brave adventurer!"}));

		// Set the main quest phase to the next phase
		cQuest_MainQuest* quest = (cQuest_MainQuest*)g_engine->GetQuest("main quest");
		quest->m_nPhase = quest->m_nPhase + 1;
		
		// Update current quest to be the main quest
		//X(ChangeCurrentQuest("main quest"));

		// Update bob to not be persistant to get rid of him
		target->bPersist = false;

		X(UpdateMapDynamics());
		X(UpdateQuestDynamics("main quest"));
		X(MoveTo(target, 32, 32));
		//X(ChangeMap("home", vecDynobs[0]->px, vecDynobs[0]->py));
		
		vecPersistObjects.clear();

		bCompleted = true;
	}
	return false;
}