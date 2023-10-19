#include "RPG_Items.h"
#include "RPG_Engine.h"

RPG_Engine* cItem::g_engine = nullptr;

cItem::cItem(string name, olcSprite* sprite, string desc) {
	sName = name;
	pSprite = sprite;
	sDescription = desc;
}

cItem_Health::cItem_Health() : 
	cItem("Small Health", RPG_Assets::get().GetSprite("health"), "Restore 10 health") 
{}

bool cItem_Health::OnInteract(cDynamic* object) {
	OnUse(object);
	return false; // Just absorb
}

bool cItem_Health::OnUse(cDynamic* object) {
	if (object != nullptr) {
		cDynamic_Creature* dyn = (cDynamic_Creature*)object;
		dyn->nHealth = min(dyn->nHealth + 10, dyn->nHealthMax);
	}
	return true;
}

cItem_HealthBoost::cItem_HealthBoost() :
	cItem("Health Boost", RPG_Assets::get().GetSprite("healthboost"), "Increase Max Health by 10")
{}

bool cItem_HealthBoost::OnInteract(cDynamic* object) {
	bPersist = false;
	return true;	// Add to inventory
}

bool cItem_HealthBoost::OnUse(cDynamic* object) {
	if (object != nullptr) {
		cDynamic_Creature* dyn = (cDynamic_Creature*)object;
		dyn->nHealthMax += 10;
		dyn->nHealth = dyn->nHealthMax;
	}
	return true; // Remove from inventory
}

cItem_HealthPotion::cItem_HealthPotion() : cItem("Health Potion",RPG_Assets::get().GetSprite("healthpotion"),"Increase health by 10") {

}


bool cItem_HealthPotion::OnInteract(cDynamic* object) {
	bPersist = false;
	return true;	// Add to inventory
}

bool cItem_HealthPotion::OnUse(cDynamic* object) {
	if (object != nullptr) {
		cDynamic_Creature* dyn = (cDynamic_Creature*)object;
		dyn->nHealth += 10;
		if (dyn->nHealth > dyn->nHealthMax) {
			dyn->nHealth = dyn->nHealthMax;
		}
	}
	return true;	// Remove from inventory
}

cWeapon::cWeapon(string name, olcSprite* sprite, string desc, int dmg) : cItem(name,sprite,desc){
	nDamage = dmg;
}

bool cWeapon::OnInteract(cDynamic* object) {
	return false;
}

bool cWeapon::OnUse(cDynamic* object) {
	return false;
}

cWeapon_Sword::cWeapon_Sword() : 
	cWeapon("Basic Sword", RPG_Assets::get().GetSprite("Basic Sword"), "A wooden sword, 5 dmg", 5) 
{

}

cWeapon_Sword::cWeapon_Sword(string name,string spriteName,string dsc, int dmg) :
	cWeapon(name, RPG_Assets::get().GetSprite(spriteName), dsc, dmg)
{

}

bool cWeapon_Sword::OnUse(cDynamic* object) {
	// Get direction of attacker
	cDynamic_Creature* aggressor = (cDynamic_Creature*)object;

	// Determine attack origin
	float x, y, vx, vy;
	if (aggressor->GetFacingDirection() == 0) {	// South
		x = aggressor->px;
		y = aggressor->py + 1.0f;
		vx = 0.0f;
		vy = 1.0f;
	}
	if (aggressor->GetFacingDirection() == 1) {	// East
		x = aggressor->px - 1.0f;
		y = aggressor->py;
		vx = -1.0f;
		vy = 0.0f;
	}
	if (aggressor->GetFacingDirection() == 2) {	// North
		x = aggressor->px;
		y = aggressor->py - 1.0f;
		vx = 0.0f;
		vy = -1.0f;
	}
	if (aggressor->GetFacingDirection() == 3) {	// West
		x = aggressor->px + 1.0f;
		y = aggressor->py;
		vx = 1.0f;
		vy = 0.0f;
	}
	if (aggressor->nHealth == aggressor->nHealthMax) {
		// Beam Sword
		// Get correct sword to display
		cDynamic_Projectile* p = new cDynamic_Projectile(x, y, aggressor->bFriendly, vx * 15.0f, vy * 15.0f, 1.0f, RPG_Assets::get().GetSprite(sName), (aggressor->GetFacingDirection() + 3) % 4 + 1, 0.0f);
		p->bSolidVsMap = true;
		p->bSolidVsDyn = false;
		p->nDamage = this->nDamage;
		p->bOneHit = false;
		g_engine->AddProjectile(p);
	}

	cDynamic_Projectile* p = new cDynamic_Projectile(x, y, aggressor->bFriendly, aggressor->vx, aggressor->vy, 0.1f, RPG_Assets::get().GetSprite(sName), (aggressor->GetFacingDirection() + 3) % 4 + 1, 0.0f);
	p->bSolidVsMap = false;
	p->bSolidVsDyn = false;
	p->nDamage = 5;
	p->bOneHit = true;

	g_engine->AddProjectile(p);

	return false;
}