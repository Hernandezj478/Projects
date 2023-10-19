#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine.h"

#include <vector>
#include <list>
#include <algorithm>



class PathFinding_FlowFields : public olc::PixelGameEngine {
public:
	PathFinding_FlowFields() {
		sAppName = "Pathfinging - Flow Fields";
	}

	bool OnUserCreate() override {
		nBorderWidth = 4;
		nCellSize = 32;
		nMapWidth = ScreenWidth() / nCellSize;
		nMapHeight = ScreenHeight() / nCellSize;
		bObstacleMap = new bool[nMapWidth * nMapHeight] {false };
		nFlowFieldZ = new int[nMapWidth * nMapHeight] { 0 };
		fFlowFieldX = new float[nMapWidth * nMapHeight] { 0 };
		fFlowFieldY = new float[nMapWidth * nMapHeight] { 0 };



		nStartX = 3;
		nStartY = 7;
		nEndX = 12;
		nEndY = 7;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) {
		
		// Lambda 2D --> 1D
		auto p = [&](int x, int y) {return y * nMapWidth + x; };
		
		// User input
		int nSelectedCellX = GetMouseX() / nCellSize;
		int nSelectedCellY = GetMouseY() / nCellSize;

		if (GetMouse(0).bReleased) {
			// Toggle obstacle
			bObstacleMap[p(nSelectedCellX, nSelectedCellY)] =
				!bObstacleMap[p(nSelectedCellX, nSelectedCellY)];
		}
		if (GetMouse(1).bReleased) {
			nStartX = nSelectedCellX;
			nStartY = nSelectedCellY;
		}
		if (GetMouse(2).bReleased) {
			nEndX = nSelectedCellX;
			nEndY = nSelectedCellY;
		}
		
		if (GetKey(olc::Key::Q).bReleased) {
			nWave++;
		}
		if (GetKey(olc::Key::A).bReleased) {
			nWave--;
			if (nWave <= 0)
				nWave = 1;
		}

		// 1.) Prepare flow field, add a boundary, and add obstacles
		// by setting the flow field height (z) to -1
		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				// Set border or obstacle
				if (x == 0 || y == 0 || x == (nMapWidth - 1) || y == (nMapHeight - 1) || bObstacleMap[p(x, y)]) {
					nFlowFieldZ[p(x, y)] = -1;
				}
				else {
					nFlowFieldZ[p(x, y)] = 0;
				}
			}
		}

		// 2.) Propogate a wave (i.e flood-fill) from target location. Here we use
		// a tuple, but a can use a struct or something similar
		std::list<std::tuple<int, int, int>> nodes;

		// Add the first discovered node - the target location, with distance of 1
		nodes.push_back({ nEndX, nEndY, 1 });

		while (!nodes.empty()) {
			// Each iteration through the discovered nodes may create newly discovered
			// nodes, so we create a second list. It's important not to contaminate
			// the list being irterated through
			std::list<std::tuple<int, int, int>> new_nodes;

			for (auto& n : nodes) {
				int x = std::get<0>(n);		// Map X-Coordinate
				int y = std::get<1>(n);		// Map Y-Coordinate
				int d = std::get<2>(n);		// Distance from target location

				// Set distance count for this node. Note that when we add nodes, we add 1
				// to this distance. This emulates propogating a wave across the map, where
				// the front of that wave incrememnts each iteration. In this way, we can
				// propogate distance information 'away from target location'
				nFlowFieldZ[p(x, y)] = d;

				// Add neighbor nodes if unmarked, i.e. their "height" is 0. Any discovered
				// node or obstacle will be non-zero

				// Check east
				if ((x + 1) < nMapWidth && nFlowFieldZ[p(x + 1, y)] == 0) {
					new_nodes.push_back({ x + 1, y, d + 1 });
				}

				// Check west
				if ((x - 1) >= 0 && nFlowFieldZ[p(x - 1, y)] == 0) {
					new_nodes.push_back({ x - 1, y, d + 1 });
				}

				// Check North
				if ((y - 1) >= 0 && nFlowFieldZ[p(x, y - 1)] == 0) {
					new_nodes.push_back({ x,y - 1, d + 1 });
				}

				// Check South
				if ((y + 1) < nMapHeight && nFlowFieldZ[p(x, y + 1)] == 0) {
					new_nodes.push_back({ x, y + 1, d + 1 });
				}
			}

			// We will now have potentially multiple nodes for a single location. This means our
			// algorithm will never complete! So we must remove duplicates from our new node list.
			// We are doing this with some clever code - but it is not performant(!) - it is merely
			// convenient. I'd suggest doing away with overhead stuctures like linked list and sorts
			// if you are aiming for the fastest path finding.

			// Sort the nodes - This will stack up nodes that are similar: A, B, B, B, B, C, D, D, E, F, F
			new_nodes.sort([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2) {
				// In this instace we dont care how the values are sorted, so long as nodes that
				// represent the same location are adjacent in the list. We can use p() lambda
				// to generate a unique 1D value for a 2D coordinate
				return p(std::get<0>(n1), std::get<1>(n1)) < p(std::get<0>(n2), std::get<1>(n2));
				});


			// Use "unique" funciton to remove adjacent duplicates			: A, B, -, -, -, C, D, -, E, F, -
			// and also erase them											: A, B, C, D, E, F
			new_nodes.unique([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2) {
				return p(std::get<0>(n1), std::get<1>(n1)) == p(std::get<0>(n2), std::get<1>(n2));
				});

			// We've now processed all the discovered nodes, so clear the list, and add newly
			// discovered nodes for processing on the next iteration
			nodes.clear();
			nodes.insert(nodes.begin(), new_nodes.begin(), new_nodes.end());

			// When there are no more newly discovered nodes, we have "flood filled" the entire
			// map. The propogation phase of the algorithm is complete
		}

		// 3.) Create Path. Starting at start location, create a path of nodes until you reach target
		// location. At each node, find the neighbor with the lowest "distance" score.
		std::list<std::pair<int, int>> path;
		path.push_back({ nStartX, nStartY });
		int nLocX = nStartX;
		int nLocY = nStartY;
		bool bNoPath = false;

		while (!(nLocX == nEndX && nLocY == nEndY) && !bNoPath) {
			std::list<std::tuple<int, int, int>> listNeighbors;
			// 4-way connectivity
			if ((nLocY - 1) >= 0 && nFlowFieldZ[p(nLocX, nLocY - 1)] > 0)
				listNeighbors.push_back({ nLocX, nLocY - 1, nFlowFieldZ[p(nLocX, nLocY - 1)] });
			if ((nLocX + 1) < nMapWidth && nFlowFieldZ[p(nLocX + 1, nLocY)] > 0)
				listNeighbors.push_back({ nLocX + 1, nLocY, nFlowFieldZ[p(nLocX + 1, nLocY)] });
			if ((nLocY + 1) < nMapHeight && nFlowFieldZ[p(nLocX, nLocY + 1)] > 0)
				listNeighbors.push_back({ nLocX, nLocY + 1, nFlowFieldZ[p(nLocX, nLocY + 1)] });
			if ((nLocX - 1) >= 0 && nFlowFieldZ[p(nLocX - 1, nLocY)] > 0)
				listNeighbors.push_back({ nLocX - 1, nLocY, nFlowFieldZ[p(nLocX - 1, nLocY)] });

			// 8-way connectivity
			if ((nLocY - 1) >= 0 && (nLocX - 1) >= 0 && nFlowFieldZ[p(nLocX - 1, nLocY - 1)] > 0)
				listNeighbors.push_back({ nLocX - 1, nLocY - 1, nFlowFieldZ[p(nLocX - 1, nLocY - 1)] });
			if ((nLocY - 1) >= 0 && (nLocX + 1) < nMapWidth && nFlowFieldZ[p(nLocX + 1, nLocY - 1)] > 0)
				listNeighbors.push_back({ nLocX + 1, nLocY - 1, nFlowFieldZ[p(nLocX + 1, nLocY - 1)] });
			if ((nLocY + 1) < nMapHeight && (nLocX - 1) >= 0 && nFlowFieldZ[p(nLocX - 1, nLocY + 1)] > 0)
				listNeighbors.push_back({ nLocX - 1, nLocY + 1, nFlowFieldZ[p(nLocX - 1, nLocY + 1)] });
			if ((nLocY + 1) < nMapHeight && (nLocX + 1) < nMapWidth && nFlowFieldZ[p(nLocX + 1, nLocY + 1)] > 0)
				listNeighbors.push_back({ nLocX + 1, nLocY + 1, nFlowFieldZ[p(nLocX + 1, nLocY + 1)] });


			listNeighbors.sort([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2) {
				return std::get<2>(n1) < std::get<2>(n2);
				});


			if (listNeighbors.empty())
				bNoPath = true;
			else {
				nLocX = std::get<0>(listNeighbors.front());
				nLocY = std::get<1>(listNeighbors.front());
				path.push_back({ nLocX, nLocY });
			}
		}

		// 4.) Create Flow "Field"
		for (int x = 1; x < nMapWidth - 1; x++) {
			for (int y = 1; y < nMapHeight - 1; y++) {
				float vx = 0.0f;
				float vy = 0.0f;

				vy -= (float)((nFlowFieldZ[p(x, y + 1)] <= 0 ? nFlowFieldZ[p(x, y)] : nFlowFieldZ[p(x, y + 1)]) - nFlowFieldZ[p(x, y)]);
				vx -= (float)((nFlowFieldZ[p(x + 1, y)] <= 0 ? nFlowFieldZ[p(x, y)] : nFlowFieldZ[p(x + 1, y)]) - nFlowFieldZ[p(x, y)]);
				vy += (float)((nFlowFieldZ[p(x, y - 1)] <= 0 ? nFlowFieldZ[p(x, y)] : nFlowFieldZ[p(x, y - 1)]) - nFlowFieldZ[p(x, y)]);
				vx += (float)((nFlowFieldZ[p(x - 1, y)] <= 0 ? nFlowFieldZ[p(x, y)] : nFlowFieldZ[p(x - 1, y)]) - nFlowFieldZ[p(x, y)]);


				float r = 1.0f / sqrtf(vx * vx + vy * vy);
				fFlowFieldX[p(x, y)] = vx * r;
				fFlowFieldY[p(x, y)] = vy * r;
			}
		}


		Clear(olc::BLACK);

		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				olc::Pixel color = olc::BLUE;

				if (bObstacleMap[p(x, y)] || nFlowFieldZ[p(x,y)] == -1)
					color = olc::GREY;

				if (x == nStartX && y == nStartY)
					color = olc::GREEN;
				if (x == nEndX && y == nEndY)
					color = olc::RED;

				if (nWave == nFlowFieldZ[p(x, y)])
					color = olc::DARK_CYAN;
				// Draw base
				FillRect(x * nCellSize, y * nCellSize, nCellSize - nBorderWidth, nCellSize - nBorderWidth, color);
				
				// Draw "potential" or "distance" or "height"
				//DrawString(x * nCellSize, y * nCellSize, std::to_string(nFlowFieldZ[p(x, y)]), olc::WHITE);

				if (nFlowFieldZ[p(x, y)] > 0) {
					float ax[4], ay[4];
					float fAngle = atan2f(fFlowFieldY[p(x, y)], fFlowFieldX[p(x, y)]);
					float fRadius = (float)(nCellSize - nBorderWidth) / 2.0f;
					int fOffsetX = x * nCellSize + ((nCellSize - nBorderWidth) / 2);
					int fOffsetY = y * nCellSize + ((nCellSize - nBorderWidth) / 2);
					ax[0] = cosf(fAngle) * fRadius + fOffsetX;
					ay[0] = sinf(fAngle) * fRadius + fOffsetY;
					ax[1] = cosf(fAngle) * -fRadius + fOffsetX;
					ay[1] = sinf(fAngle) * -fRadius + fOffsetY;
					ax[2] = cosf(fAngle + 0.1f) * fRadius * 0.7f + fOffsetX;
					ay[2] = sinf(fAngle + 0.1f) * fRadius * 0.7f + fOffsetY;
					ax[3] = cosf(fAngle - 0.1f) * fRadius * 0.7f + fOffsetX;
					ay[3] = sinf(fAngle - 0.1f) * fRadius * 0.7f + fOffsetY;

					DrawLine(ax[0], ay[0], ax[1], ay[1], olc::CYAN);
					DrawLine(ax[0], ay[0], ax[2], ay[2], olc::CYAN);
					DrawLine(ax[0], ay[0], ax[3], ay[3], olc::CYAN);
				}

			}
		}
		
		bool bFirstPoint = true;
		int ox, oy;
		for (auto& a : path) {
			if (bFirstPoint) {
				ox = a.first;
				oy = a.second;
				bFirstPoint = false;
			}
			else {
				DrawLine(
					ox* nCellSize + ((nCellSize - nBorderWidth) / 2),
					oy* nCellSize + ((nCellSize - nBorderWidth) / 2),
					a.first* nCellSize + ((nCellSize - nBorderWidth) / 2),
					a.second* nCellSize + ((nCellSize - nBorderWidth) / 2),
					olc::YELLOW);
				ox = a.first;
				oy = a.second;

				FillCircle(ox* nCellSize + ((nCellSize - nBorderWidth) / 2), oy* nCellSize + ((nCellSize - nBorderWidth) / 2), 10, olc::YELLOW);
			}
		}

		return true;
	}

private:
	int nMapWidth; 
	int nMapHeight;
	int nCellSize;
	int nBorderWidth;

	bool* bObstacleMap;
	int* nFlowFieldZ;
	float* fFlowFieldX;
	float* fFlowFieldY;


	int nStartX;
	int nStartY;
	int nEndX;
	int nEndY;

	int nWave = 1;
private:
};


int main(int argc, char* argv) {
	PathFinding_FlowFields demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	
	return 0;
}