#include <string>
#include <algorithm>


using namespace std;
#include "olcConsoleGameEngine.h"

class Asteroids : public olcConsoleGameEngine {
public:
	Asteroids() {
		m_sAppName = L"Asteroids";
	}

	virtual bool OnUserCreate() {

		vecModelShip = {
			{ 0.0f, -5.5f},
			{-2.5f, +2.5f},
			{+2.5f, +2.5f}
		};

		int verts = 20;
		for (int i = 0; i < verts; i++) {
			float radius = (float)rand() / (float)RAND_MAX * 0.4f + 0.8f;
			float a = ((float)i / (float)verts) * 2 * 3.14159f;
			vecModelAsteroid.push_back(make_pair(radius * sinf(a), radius * cosf(a)));
		}

		ResetGame();

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) {

		if (bDead) {
			ResetGame();
		}


		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);

		// Steer player
		if (m_keys[VK_LEFT].bHeld)
			player.angle -= 5.0f * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld)
			player.angle += 5.0f * fElapsedTime;

		if (m_keys[VK_UP].bHeld) {
			player.dx += sinf(player.angle) * 20.0f * fElapsedTime;
			player.dy += -cosf(player.angle) * 20.0f * fElapsedTime;
		}
		// Velocity changes POSITION (with respect to time)
		player.x += player.dx * fElapsedTime;
		player.y += player.dy * fElapsedTime;

		// Keep ship in gamespace
		WrapCoordinates(player.x,player.y,player.x,player.y);

		// Check ship collision
		for (auto& a : vecAsteroids) {
			if (Collision(a.x, a.y, a.nSize, player.x, player.y))
				bDead = true;
		}


		// Fire Bullets in direction of player
		if (m_keys[VK_SPACE].bReleased) {
			vecBullets.push_back({ 0,player.x,player.y,50.0f * sinf(player.angle),-50.f * cosf(player.angle),0 });
		}

		// Update and draw asteroids
		for (auto& a : vecAsteroids) {
			a.x += a.dx * fElapsedTime;
			a.y += a.dy * fElapsedTime;
			a.angle += 0.5f * fElapsedTime;
			WrapCoordinates(a.x, a.y, a.x, a.y);
			
			DrawWireFrameModel(vecModelAsteroid, a.x, a.y, a.angle,a.nSize,FG_YELLOW);
		}
		
		vector<sSpaceObject> newAsteroids;

		//Update and Draw Bullets
		for (auto& b : vecBullets) {
			b.x += b.dx * fElapsedTime;
			b.y += b.dy * fElapsedTime;
			WrapCoordinates(b.x, b.y, b.x, b.y);
			Draw(b.x, b.y);

			// Check collision
			for (auto& a : vecAsteroids) {
				if (Collision(a.x, a.y, a.nSize, b.x, b.y)) {
					// Asteroid hit
					b.x = -100;
					if (a.nSize > 4) {
						// Create two child asteroids
						float angle1 = ((float)rand() / (float)RAND_MAX) * 2 * 3.14158f;
						float angle2 = ((float)rand() / (float)RAND_MAX) * 2 * 3.14158f;
						newAsteroids.push_back({(int)a.nSize >> 2,a.x,a.y,10.0f * sinf(angle1), 10.0f * cosf(angle1),0.0f});
						newAsteroids.push_back({(int)a.nSize >> 2,a.x,a.y,10.0f * sinf(angle2), 10.0f * cosf(angle2),0.0f});
					}
					a.x = -100.0f;
					nScore += 100;
				}
			}
		}

		// Append new asteroids to existing vector
		for (auto a : newAsteroids) {
			vecAsteroids.push_back(a);
		}

		// Remove off screen bullets
		if (vecBullets.size() > 0) {
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), 
				[&](sSpaceObject o) {return (o.x < 1 || o.y < 1 || o.x >= ScreenWidth() || o.y >= ScreenHeight()); });
			if (i != vecBullets.end()) {
				vecBullets.erase(i);
			}

		}

		// Remove destroyed asteroids
		if (vecAsteroids.size() > 0) {
			auto i = remove_if(vecAsteroids.begin(), vecAsteroids.end(),
				[&](sSpaceObject o) {return (o.x < 1); });
			if (i != vecAsteroids.end()) {
				vecAsteroids.erase(i);
			}
		}

		if (vecAsteroids.empty()) {
			nScore += 1000;
			vecAsteroids.push_back({ 
									(int)16, 
									30.0f * sinf(player.angle - 3.14159f / 2.0f),
									30.0f * cosf(player.angle - 3.14159f / 2.0f),
									10.0f * sinf(player.angle),
									10.0f * cosf(player.angle),
									0.0f });

			vecAsteroids.push_back({
									(int)16, 
									30.0f * sinf(player.angle + 3.14159f / 2.0f),
									30.0f * cosf(player.angle + 3.14159f / 2.0f),
									10.0f * sinf(-player.angle),
									10.0f * cosf(-player.angle),
									0.0f });
		}



		// Draw Ship
		DrawWireFrameModel(vecModelShip, player.x, player.y, player.angle);


		// Player Stats
		DrawString(0, 0, L"Player Angle: " + to_wstring(player.angle));
		DrawString(0, 1, L"Player X: " + to_wstring(player.x) + L"Player Y: " + to_wstring(player.y));

		DrawString(0, 2, L"Score: " + to_wstring(nScore));

		return true;
	}

	void ResetGame() {
		vecAsteroids.clear();
		vecBullets.clear();

		vecAsteroids.push_back({ (int)16, 20.0f,20.0f,8.0f,-6.0f,0.0f });
		vecAsteroids.push_back({ (int)16, 100.0f,20.0f,5.0f,-3.0f,1.0f });

		//Initialize Player Position
		player.x = ScreenWidth() / 2;
		player.y = ScreenHeight() / 2;
		player.dx = 0.0f;
		player.dy = 0.0f;
		player.angle = 0.0f;

		nScore = 0;
		bDead = false;
	}

	bool Collision(float cx, float cy, float radius, float x, float y) {
		return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
	}


	void DrawWireFrameModel(const vector<pair<float, float>> &vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, short col = FG_WHITE) {
		vector<pair<float, float>> vecTransformedCoordinates;
		int verts = vecModelCoordinates.size();
		vecTransformedCoordinates.resize(verts);

		// Rotate
		for (int i = 0; i < verts; i++) {
			vecTransformedCoordinates[i].first  = (vecModelCoordinates[i].first * cosf(r)) - (vecModelCoordinates[i].second * sinf(r));		// px2 = px1 * cos(theta2) - py1 * sin(theta2)
			vecTransformedCoordinates[i].second = (vecModelCoordinates[i].first * sinf(r)) + (vecModelCoordinates[i].second * cosf(r));		// py2 = px1 * sin(theta2) + py1 * cos(theta2)
		}

		// Scale
		for (int i = 0; i < verts; i++) {
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
		}

		// Translate
		for (int i = 0; i < verts; i++) {
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;

		}

		// Draw Closed Polygon
		for (int i = 0; i < verts + 1; i++) {
			int j = (i + 1);
			DrawLine(vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second,
				vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second, PIXEL_SOLID, col);
		}
	}


	virtual void Draw(int x, int y, short c = 0x2588, short col = 0x000F) {
		float fx, fy;
		WrapCoordinates(x, y, fx, fy);
		olcConsoleGameEngine::Draw(fx, fy, c, col);
	}

	void WrapCoordinates(float ix,float iy, float& ox, float& oy) {
		ox = ix;
		oy = iy;


		if (ix < 0.0f) ox = ix + (float)ScreenWidth();
		if (ix >= ScreenWidth()) ox = ix - (float)ScreenWidth();
		if (iy < 0.0f) oy = iy + (float)ScreenHeight();
		if (iy >= ScreenHeight()) oy = iy - (float)ScreenHeight();
	}


private:
	struct sSpaceObject {
		int nSize;

		float x;
		float y;
		float dx;
		float dy;
		float angle;
	};
	vector<pair<float, float>> vecModelShip;
	vector<pair<float, float>> vecModelAsteroid;

	vector<sSpaceObject> vecAsteroids;
	vector<sSpaceObject> vecBullets;
	sSpaceObject player;

	int nScore = 0;

	bool bDead = false;

};


int main() {
	Asteroids game;
	game.ConstructConsole(160, 100, 8, 8);
	game.Start();


	return 0;
}