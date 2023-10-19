#include <string>

using namespace std;

#include "olcConsoleGameEngine.h"

class AStarAlgorithm : public olcConsoleGameEngine {
public:
	AStarAlgorithm() {
		m_sAppName = L"A* Algorithm";
	}

	virtual bool OnUserCreate() {
		nodes = new sNode[nMapWidth * nMapHeight];
		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				nodes[y * nMapWidth + x].x = x;
				nodes[y * nMapWidth + x].y = y;
				nodes[y * nMapWidth + x].bObstacle = false;
				nodes[y * nMapWidth + x].bVisited = false;
				nodes[y * nMapWidth + x].parent = nullptr;
			}
		}
		for (int x = 0; x < nMapWidth; x++) {
			for(int y=0;y<nMapHeight;y++){
				if(y>0)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
				if (y < nMapHeight-1)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
				if(x>0)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
				if (x < nMapWidth-1)
					nodes[y * nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);


				// We can also connect diagonally
				if (y>0 && x>0)
					nodes[y*nMapWidth + x].vecNeighbors.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
				if (y<nMapHeight-1 && x>0)
					nodes[y*nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
				if (y>0 && x<nMapWidth-1)
					nodes[y*nMapWidth + x].vecNeighbors.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
				if (y<nMapHeight - 1 && x<nMapWidth-1)
					nodes[y*nMapWidth + x].vecNeighbors.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
				

			}
		}




		nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
		nodeEnd = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth - 2];

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) {
		int nNodeSize = 9;
		int nNodeBorder = 2;

		int nSelectedNodeX = m_mousePosX / nNodeSize;
		int nSelectedNodeY = m_mousePosY / nNodeSize;

		if (m_mouse[0].bReleased) {
			if (nSelectedNodeX >= 0 && nSelectedNodeX < nMapWidth) {
				if (m_keys[VK_SHIFT].bHeld)
					nodeStart = &nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX];
				else if(m_keys[VK_CONTROL].bHeld)
					nodeEnd = &nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX];
				else
					nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle = !nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle;

				Solve_AStar();
			}
		}

		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++){
				for (auto n : nodes[y * nMapWidth + x].vecNeighbors){
					DrawLine(x * nNodeSize + nNodeSize / 2, y * nNodeSize + nNodeSize / 2,
						n->x * nNodeSize + nNodeSize / 2, n->y * nNodeSize + nNodeSize / 2, PIXEL_SOLID, FG_DARK_BLUE);
				}
			}
		}

		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder, (x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder, nodes[y * nMapWidth + x].bObstacle ?  PIXEL_SOLID : PIXEL_HALF,
					nodes[y*nMapWidth + x].bObstacle ? FG_WHITE : FG_DARK_BLUE);

				if (nodes[y * nMapWidth + x].bVisited)
					Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder, (x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder, PIXEL_SOLID, FG_BLUE);

				if (&nodes[y * nMapWidth + x] == nodeStart)
					Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder, (x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder, PIXEL_SOLID, FG_GREEN);
				if (&nodes[y * nMapWidth + x] == nodeEnd)
					Fill(x * nNodeSize + nNodeBorder, y * nNodeSize + nNodeBorder, (x + 1) * nNodeSize - nNodeBorder, (y + 1) * nNodeSize - nNodeBorder, PIXEL_SOLID, FG_RED);
			}
		}

		if (nodeEnd != nullptr) {
			sNode* p = nodeEnd;
			while (p->parent != nullptr) {
				DrawLine(p->x * nNodeSize + nNodeSize / 2, p->y * nNodeSize + nNodeSize / 2,
					p->parent->x * nNodeSize + nNodeSize / 2, p->parent->y * nNodeSize + nNodeSize / 2, PIXEL_SOLID, FG_YELLOW);

				p = p->parent;
			}
		}

		return true;
	}


	void Solve_AStar() {
		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				nodes[y * nMapWidth + x].bVisited = false;
				nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
				nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
				nodes[y * nMapWidth + x].parent = nullptr;
			}
		}

		auto distance = [](sNode* a, sNode* b) {
			auto x = a->x - b->x;
			auto y = a->y - b->y;
			return sqrtf((x * x) + (y * y));
		};

		auto heuristic = [distance](sNode* a, sNode* b) {
			return distance(a, b);
		};

		sNode* nodeCurrent = nodeStart;
		nodeStart->fLocalGoal = 0.0f;
		nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

		list<sNode*> listNotTestedNodes;
		listNotTestedNodes.push_back(nodeStart);

		while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd) {
			listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) {return lhs->fGlobalGoal < rhs->fGlobalGoal; });

			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited) {
				listNotTestedNodes.pop_front();
			}
			if (listNotTestedNodes.empty())
				break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true;

			for (auto nodeNeighbor : nodeCurrent->vecNeighbors) {
				if (!nodeNeighbor->bVisited && nodeNeighbor->bObstacle == 0)
					listNotTestedNodes.push_back(nodeNeighbor);

				float fLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbor);


				if (fLowerGoal < nodeNeighbor->fLocalGoal) {
					nodeNeighbor->parent = nodeCurrent;
					nodeNeighbor->fLocalGoal = fLowerGoal;

					nodeNeighbor->fGlobalGoal = nodeNeighbor->fLocalGoal + heuristic(nodeNeighbor, nodeEnd);

				}
			}
		}
	}

private:
	struct sNode {
		bool bObstacle = false;			// Is the node obstructed?
		bool bVisited = false;			// Have we previously searched this node?
		float fGlobalGoal;				// Distance to goal so far
		float fLocalGoal;				// Distance to goal if we took the alternative
		int x;							// Nodes position in 2D space
		int y;
		vector<sNode*> vecNeighbors;	// Connections to neighbors
		sNode* parent;					// Node connecting to this node that offers shortest path
	};

	sNode* nodes = nullptr;
	int nMapWidth = 16;
	int nMapHeight = 16;

	sNode* nodeStart = nullptr;
	sNode* nodeEnd = nullptr;

};

	int main(int argv, char** argc) {
		
		AStarAlgorithm demo;
		demo.ConstructConsole(160, 160, 6, 6);
		demo.Start();
		return 0;
	}