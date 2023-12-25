#pragma once
#include <map>
#include <vector>
#include "CS.h"
#include "Subfuncs.h"
#include "Pipe.h"
#include "iostream"
#include <queue>

using namespace std;

class Connection
{
public:

	std::map <std::pair<int, int>, int> connections;


	void make_a_con(CS &cs,Pipe &pipe);

	bool loopcheck(std::vector<std::vector<int>>& graph);

	void dfs(vector<vector<int>>& graph, int v, vector<int>& visited, vector<int>& order);

	float Dijkstra(std::vector<std::vector<int>>& a, int index_1, int index_2);

	void topSort(CS& cs, Pipe& pipe);

	void shortestPath(CS& cs, Pipe& pipe);

	int getConLen();

	float FordFulkerson(vector<vector<int>>& r_matrix, int source, int sink);

	void maxStream(CS& cs, Pipe& pip);

	void ViewConnection(Pipe& p);

	void SaveCon(std::ofstream& file);

	void LoadCon(std::ifstream& file);
};

