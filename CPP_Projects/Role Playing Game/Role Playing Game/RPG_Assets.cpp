#include "RPG_Assets.h"
#include "RPG_Map.h"
#include "RPG_Items.h"

RPG_Assets::RPG_Assets() {

}
RPG_Assets::~RPG_Assets() {

}

void RPG_Assets::LoadSprites() {
	auto load = [&](string sName, wstring sFileName) {
		olcSprite* s = new olcSprite(sFileName);
		m_mapSprites[sName] = s;
	};

	load("village", L"rpgdata/gfx/toml_spritesheetdark.spr");

	load("skelly", L"rpgdata/gfx/toml_Char001.png.spr");
	load("player", L"rpgdata/gfx/toml_CharacterSprites.spr");
	load("font", L"rpgdata/gfx/javidx9_nesfont8x8.spr");
	load("worldmap", L"rpgdata/gfx/worldmap1.png.spr");
	load("skymap", L"rpgdata/gfx/sky1.png.spr");
	load("title", L"rpgdata/gfx/title3.png.spr");
	load("balloon", L"rpgdata/gfx/balloon1.png.spr");
	load("sword", L"rpgdata/gfx/Sword.spr");
	load("hitech", L"rpgdata/gfx/toml_modernish.spr");
	load("purple", L"rpgdata/gfx/toml_purple.spr");
	load("orange", L"rpgdata/gfx/toml_orange.spr");

	load("health", L"rpgdata/gfx/item_health.spr");
	load("healthboost", L"rpgdata/gfx/item_healthboost.spr");
	load("healthpotion", L"rpgdata/gfx/item_healthpotion.spr");

	load("Basic Sword", L"rpgdata/gfx/weapon_basic_sword.spr");
	load("Iron Sword", L"rpgdata/gfx/weapon_iron_sword.spr");
}

void RPG_Assets::LoadMaps() {
	auto load = [&](cMap* m) {
		m_mapMaps[m->sName] = m;
	};

	load(new cMap_Village1());
	load(new cMap_Home1());
	//load(new cMap_Home2());
	load(new cMap_Basement());

}

void RPG_Assets::LoadItems() {
	auto load = [&](cItem* i) {
		m_mapItems[i->sName] = i;
	};

	load(new cItem_Health());
	load(new cItem_HealthBoost());
	load(new cItem_HealthPotion());

	load(new cWeapon_Sword());
}