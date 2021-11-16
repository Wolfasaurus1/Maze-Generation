#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Vec2.h"


//maze graph dimensions
const int GRAPH_WIDTH = 10;
const int GRAPH_HEIGHT = 10;

//grid of blocks which can then be rendered
//can convert linewise maze from MazeGraph into a blockwise maze

//contains coords of current node in the graph
struct Node
{
	Vec2<int> coords;
	std::vector<Vec2<int>> ConnectedNodes;
};


class MazeGraph
{
public:
	MazeGraph()
	{
		std::cout << "graph coordinates initialized!" << std::endl;
		for (int x = 0; x < GRAPH_WIDTH; x++)
			for (int y = 0; y < GRAPH_HEIGHT; y++)
				node[x][y].coords = Vec2<int>(x, y);
	}

	bool NodesConnected(Vec2<int> v1, Vec2<int> v2)
	{
		std::vector<Vec2<int>> vec = node[v1.x][v1.y].ConnectedNodes;
		if (std::find(vec.begin(), vec.end(), v2) != vec.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	void AddEdge(Vec2<int> v1, Vec2<int> v2)
	{
		node[v1.x][v1.y].ConnectedNodes.push_back(v2);
		node[v2.x][v2.y].ConnectedNodes.push_back(v1);
	}

protected:
	Node node[GRAPH_WIDTH][GRAPH_HEIGHT];
};


class Maze
{
public:
	//algorithm to convert linewise maze to blockwise maze
	Maze(MazeGraph* graph)
	{
		for (int x = 1; x <= 2 * GRAPH_WIDTH; x += 2) {
			for (int y = 1; y <= 2 * GRAPH_HEIGHT; y += 2) {
				grid[x][y] = 'P';
				grid[x + 1][y + 1] = 'W';

				int graph_x = (int)(x / 2);
				int graph_y = (int)(y / 2);
				Vec2<int> graph_location = Vec2<int>(graph_x, graph_y);

				bool southConnected = graph->NodesConnected(graph_location, graph_location + Vec2<int>(0, 1));
				if (southConnected) {
					grid[x][y + 1] = 'P';
				}
				else {
					grid[x][y + 1] = 'W';
				}

				bool eastConnected = graph->NodesConnected(graph_location, graph_location + Vec2<int>(1, 0));
				if (eastConnected) {
					grid[x + 1][y] = 'P';
				}
				else {
					grid[x + 1][y] = 'W';
				}
			}
		}

		for (int x = 0; x <= 2 * GRAPH_WIDTH; x++) {
			grid[x][0] = 'W';
		}

		for (int y = 0; y <= 2 * GRAPH_HEIGHT; y++) {
			grid[0][y] = 'W';
		}
	}

	//for testing purposes
	void printMaze()
	{
		for (int x = 0; x <= 2 * GRAPH_WIDTH; x++) {
			for (int y = 0; y <= 2 * GRAPH_HEIGHT; y++) {
				std::cout << grid[x][y] << " ";
			}
			std::cout << std::endl;
		}
	}

private:
	char grid[(2 * GRAPH_WIDTH) + 1][(2 * GRAPH_HEIGHT) + 1];
};



class MazeGeneration : public MazeGraph
{
public:
	MazeGeneration()
	{
		srand((unsigned)time(NULL));
	}

	//checks if node is visitable
	bool IsVisitable(const Vec2<int> v)
	{
		if (visited[v.x][v.y])
			return false;

		if (v.x >= 0 && v.x < GRAPH_WIDTH && v.y >= 0 && v.y < GRAPH_HEIGHT) {
			return true;
		}
		else {
			return false;
		}
	}

	//looks for unvisited adjacent nodes
	void ExploreNode(Vec2<int> nodeCoords)
	{
		visited[nodeCoords.x][nodeCoords.y] = true;
		std::vector<Vec2<int>> AvailableNodes;

		//obtain vector of unvisited adjacent nodes
		for (auto &v : adjacentCoords) {
			Vec2<int> adjNode = v + nodeCoords;

			if (IsVisitable(adjNode))
				AvailableNodes.push_back(adjNode);
		}
	
		if (!AvailableNodes.empty()) {
			//pick one of them at random, add an edge to it, and call this function on that node
			Path.push_back(nodeCoords);
			int randIndex = rand() % AvailableNodes.size();
			Vec2<int> SelectedNode = AvailableNodes.at(randIndex);

			AddEdge(SelectedNode, nodeCoords);
			ExploreNode(SelectedNode);
		}
		else if (!Path.empty()){
			Vec2<int> previousNode = Path.back();

			Path.pop_back();
			ExploreNode(previousNode);
		}
		else {
			std::cout << "recursive backtracking finished!" << std::endl;
		}
	}


private:
	std::vector<Vec2<int>> Path;
	bool visited[GRAPH_WIDTH][GRAPH_HEIGHT];
	std::vector<Vec2<int>> adjacentCoords
	{
		Vec2<int>(1, 0),
		Vec2<int>(0, 1),
		Vec2<int>(-1, 0),
		Vec2<int>(0, -1)
	};
};