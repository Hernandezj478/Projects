#include <string>
#include <cstdlib>
#include <time.h>

#include "olcConsoleGameEngine.h"

using namespace std;

class Frogger : public olcConsoleGameEngine {
public:

	virtual bool OnUserDestroy() {
		for (int i = 0; i < nCarSprites; i++) {
			delete spriteCarReverse[i];
			delete spriteCar[i];
		}
		for (int i = 0; i < nBusSprites; i++) {
			delete spriteBus[i];
		}
		delete[]spriteCarReverse;
		delete[]spriteCar;
		delete[]spriteBus;

		return true;
	}

	virtual bool OnUserCreate() {
		srand((unsigned int)time(0));

		nCarSprites = 5;
		nBusSprites = 2;

		spriteCarReverse = new olcSprite * [nCarSprites];
		spriteCar		= new olcSprite*[nCarSprites];
		spriteBus		= new olcSprite*[nBusSprites];


		spriteCarReverse[0] = new olcSprite(L"res/Sprites/Car_Blue_Rev.spr");
		spriteCarReverse[1] = new olcSprite(L"res/Sprites/Car_Red_Rev.spr");
		spriteCarReverse[2] = new olcSprite(L"res/Sprites/Car_Pink_Rev.spr");
		spriteCarReverse[3] = new olcSprite(L"res/Sprites/Car_Yellow_Rev.spr");
		spriteCarReverse[4] = new olcSprite(L"res/Sprites/Car_Green_Rev.spr");


		spriteCar[0] = new olcSprite(L"res/Sprites/Car_Blue.spr");
		spriteCar[1] = new olcSprite(L"res/Sprites/Car_Red.spr");
		spriteCar[2] = new olcSprite(L"res/Sprites/Car_Pink.spr");
		spriteCar[3] = new olcSprite(L"res/Sprites/Car_Yellow.spr");
		spriteCar[4] = new olcSprite(L"res/Sprites/Car_Green.spr");


		spriteBus[0] = new olcSprite(L"res/Sprites/Bus_Yellow.spr");
		spriteBus[1] = new olcSprite(L"res/Sprites/Bus_White.spr");

		spriteWater = new olcSprite(L"res/Sprites/Water.spr");
		spriteLog		= new olcSprite(L"res/Sprites/Log.spr");
		spriteFrog		= new olcSprite(L"res/Sprites/Frog.spr");
		spriteWallSolid	= new olcSprite(L"res/Sprites/Wall_Solid.spr");
		spriteWallOpen	= new olcSprite(L"res/Sprites/Wall_Open.spr");
		spriteGrass		= new olcSprite(L"res/Sprites/Grass.spr");

		spritePavement = new olcSprite(L"res/Sprites/Pavement.spr");


		bufDanger = new bool[ScreenWidth() * ScreenHeight()];
		memset(bufDanger, 0, ScreenWidth() * ScreenHeight() * sizeof(bool));

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) {
		fTimeSinceStart += fElapsedTime;
		

		// Handle Input
		if (m_keys[VK_UP].bReleased) {
			fFrogY -= 1.0f;
			if (fFrogY < 0)
				fFrogY += 1.0f;
		}
		if (m_keys[VK_DOWN].bReleased) { 
			fFrogY += 1.0f; 
			if (fFrogY > ScreenHeight() - 1)
				fFrogY -= 1.0f;
		}
		if (m_keys[VK_LEFT].bReleased) {
			fFrogX -= 1.0f;
			if (fFrogX < 0)
				fFrogX += 1.0f;
		}
		if (m_keys[VK_RIGHT].bReleased) {
			fFrogX += 1.0f;
			if (fFrogX > ScreenWidth() - 1)
				fFrogX -= 1.0f;
		}

		if (fFrogY <= 3) fFrogX -= fElapsedTime * vecLanes[(int)fFrogY].first;
		

		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		DrawString(1, 0, L"X: " + to_wstring(fFrogX*nCellSize),FG_BLACK);
		DrawString(1, 1, L"Y: " + to_wstring(fFrogY*nCellSize),FG_BLACK);

		//Draw Lanes
		int x = -1, y = 0;
		
		// Collision Detection
		bool tl = bufDanger[(int)(fFrogY * nCellSize + 1) * ScreenWidth() + (int)(fFrogX * nCellSize + 1)];
		bool tr = bufDanger[(int)(fFrogY * nCellSize + 1) * ScreenWidth() + (int)(fFrogX + 1) * nCellSize - 1];
		bool bl = bufDanger[(int)((fFrogY + 1) * nCellSize-1) * ScreenWidth() + (int)(fFrogX * nCellSize + 1)];
		bool br = bufDanger[(int)((fFrogY + 1) * nCellSize-1) * ScreenWidth() + (int)((fFrogX + 1) * nCellSize - 1)];


		if (tl || tr || bl || br) {
			//Frog has been hit
			fFrogX = 8.0f;
			fFrogY = 9.0f;
		}

		for (auto lane : vecLanes) {
			// Find offset
			int nStartPos = (int)(fTimeSinceStart * lane.first) % 64;
			if (nStartPos < 0) { 
				nStartPos = 64 - (abs(nStartPos) % 64); 
			}
			int nCellOffset = (int)((float)nCellSize * fTimeSinceStart * lane.first) % nCellSize;

			for (int i = 0; i < (ScreenWidth() / nCellSize) + 2; i++) {
				wchar_t graphic = lane.second[(nStartPos + i) % 64];
				//Fill((x + i) * nCellSize - nCellOffset, y * nCellSize, (x + i + 1) * nCellSize - nCellOffset, (y + 1) * nCellSize, graphic);


				switch (graphic) {
					case L'f': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteCarReverse[0], 0, 0, 8, 8); break; // Fast Car Reverse
					case L'c': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteCarReverse[0], 8, 0, 8, 8); break; // Fast Car Reverse
					case L'r': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteCarReverse[1], 0, 0, 8, 8); break;	// Car Reverse
					case L'C': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteCarReverse[1], 8, 0, 8, 8); break;	// Car Reverse
					case L's': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteCar[4], 0, 0, 8, 8); break;		// Car
					case L'v': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteCar[4], 8, 0, 8, 8); break;		// Car


					case L'B': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteBus[1], 0, 0, 8, 8); break;		// Bus front
					case L'b': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteBus[1], 8, 0, 8, 8); break;		// Bus front middle
					case L'm': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteBus[1], 16, 0, 8, 8); break;		// Bus back middle
					case L'M': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteBus[1], 24, 0, 8, 8); break;		// Bus back

					case L',': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteWater, 0, 0, 8, 8); break;			// Water
					case L'J': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteLog, 0, 0, 8, 8); break;			//Log Front
					case L'l': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteLog, 8, 0, 8, 8); break;			// Log Middle
					case L'L': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteLog, 32, 0, 8, 8); break;			//Log End

					case 'g': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spritePavement, 0, 0, 8, 8); break;		// Pavement

					case L'W': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteWallSolid, 0, 0, 8, 8); break;		//Wall solid
					case L'H': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteWallOpen, 0, 0, 8, 8); break;		//Wall Open
					case L'h': DrawPartialSprite((x + i) * nCellSize - nCellOffset, y * nCellSize, spriteWallOpen, 8, 0, 8, 8); break;		//Wall Open
				}

				// Fill Danger Buffer
				for (int j = (x + i) * nCellSize - nCellOffset; j < (x + i + 1) * nCellSize - nCellOffset; j++) {
					for (int k = y * nCellSize; k < (y+1)*nCellSize; k++) {
						if (j >= 0 && j < ScreenWidth() && k < ScreenHeight()) {
							bufDanger[k * ScreenWidth() + j] =
								!(graphic == L'.' ||
									graphic == L'J' ||
									graphic == L'l' ||
									graphic == L'L' ||
									graphic == L'O' ||
									graphic == L'o' ||
									graphic == L'g' ||
									graphic == L'H' ||
									graphic == L'h');
						}
					}
				}
			}
			y++;
		}

		// Draw Frog
		DrawSprite(fFrogX*nCellSize, fFrogY*nCellSize, spriteFrog);

		return true;
	}
private:
	vector<pair<float, wstring>> vecLanes = {
		{ 0.0f,L"WWWHhWWWHhWWWHhWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"},
		{-3.0f,L",,,JlllL,,,,JllL,,,,,,,,,,,,JllL,,,,,,,,,,,,JL,,,,,,,,JllL,,,,,,"},	// Log
		{ 3.0f,L",,,,JllL,,,,,JlllL,,,,,,,JL,,,,JllL,,,,,JlL,,,,,,JlllL,,,,,JL,,,"},	// Log
		{ 2.0f,L",,,,,JL,,,,,,JlL,,,,,,,,JllL,,,,,,JL,,,,JlL,,,,,,JlL,,,,,,JlL,,,"},	// Log
		{ 0.0f,L"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg"},	//Grass
		{-3.0f,L"....rC....rC....rC........rC...rC....rC...rC..rC......rC........"},	// Cars
		{ 3.0f,L"......BbmM...........BbmM............BbmM..........BbmM........."},	// Buses
		{-4.0f,L"...fc...fc........fc......fc..........fc.......fc..fc..........."},	// Cars
		{ 2.0f,L".....sv....sv....sv..sv....sv.....sv......sv..sv.sv......sv...sv"},	// Cars
		{ 0.0f,L"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg"},	// Grass
	};

	float fTimeSinceStart = 0.0f;
	int nCellSize = 8;

	int nCarSprites = 0;
	int nBusSprites = 0;

	float fFrogX = 8.0;
	float fFrogY = 9.0;

	bool* bufDanger = nullptr;

	olcSprite** spriteCarReverse = nullptr;
	olcSprite** spriteCar = nullptr;
	olcSprite** spriteBus = nullptr;

	olcSprite* spriteLog = nullptr;
	olcSprite* spriteFrog = nullptr;
	olcSprite* spriteWater = nullptr;
	olcSprite* spriteWallSolid = nullptr;
	olcSprite* spriteWallOpen = nullptr;
	olcSprite* spriteGrass = nullptr;
	olcSprite* spritePavement = nullptr;
};


int main() {
	// Seed random generator
	

	Frogger game;
	game.ConstructConsole(128, 80, 12,12);
	game.Start();
	return 0;
}