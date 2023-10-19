#pragma once

#include <map>

#include "olcConsoleGameEngineOOP.h"

class cMap;
class cItem;

class RPG_Assets
{
public:
	static RPG_Assets& get() {
		static RPG_Assets me;
		return me;
	}

	RPG_Assets(RPG_Assets const&) = delete;
	void operator=(RPG_Assets const&) = delete;

	olcSprite* GetSprite(string name) {
		return m_mapSprites[name];
	}

	cMap* GetMap(string name) {
		return m_mapMaps[name];
	}

	cItem* GetItem(string name) {
		return m_mapItems[name];
	}

	void LoadSprites();
	void LoadMaps();
	void LoadItems();
private:
	RPG_Assets();
	~RPG_Assets();

	map<string, olcSprite*> m_mapSprites;
	map<string, cMap*> m_mapMaps;
	map<string, cItem*> m_mapItems;
};

