#include "Connection.h"


void Connection::make_a_con(CS &cs,Pipe &p)
{
	if (cs.Stations.size() <= 1) {
			std::cout << "Недостаточно КС для соединения: " << cs.Stations.size() << "\n0.Добавить КС\n1.Выйти\n";
			switch (Choose(0, 1))
			{
			case 0:
                while (cs.Stations.size() != 2)
				    cs.AddCS();
				break;
			case 1:
				break;
			}
	}
	cout << "Выберите id входа: ";
	int in_id = Choose(1,cs.Stations.size());
    int out_id = in_id;
    cout << "Выберите id выхода: ";
    while(in_id == out_id)
	    out_id = Choose(1,cs.Stations.size());
	cout << "Выберите диаметр трубы для соединения:\n1.500\n2.700\n3.1000\n4.14000\n";
	int num = Choose(1, 4);
	int diam = num == 1 ? 500 : num == 2 ? 700 : num == 3 ? 1000 : 1400;
    int count = 0;
    for (const auto& [id,pip] : p.pipes) {
        if (p.pipes[id].getDiam() == diam)
            count++;
    
    }
    int c = 0;
    if (p.pipes.size() == 0) {
        p.AddCurPipe(diam);//в температуру под 39 и не такое будет сделано
        connections.insert({ make_pair(in_id, out_id), p.id });//добавляю существующую трубу в соединение
        c++;
    }
    cout << "Размер pipes: " << p.pipes.size() << endl;
    cout << "Размер Stations: " << cs.Stations.size() << endl;
    
    for (const auto& id : p.pipes) {
        cout << " Да да да дда дад д а";//Вам хочется сделать Бёрна Страуструпа просто трупом?
        cout << p.pipes[id.second.id].diameter << " " << diam << endl;
        cout << p.pipes[id.first].NotiInConn << " " << 1 << endl;
        if (p.pipes[id.second.id].diameter == diam and p.pipes[id.first].NotiInConn == true) {//если диаметр совпадает и она не используется, то...
            connections.insert({ make_pair(in_id, out_id), id.first });//добавляю существующую трубу в соединение
            p.pipes[id.first].NotiInConn = false;//делаю так, чтобы нельзя было использовать ту же трубу в соединении больше одного раза
            c++;
        }
    };
    if (c == 0) {
        cout << "Недостаточно Труб диаметра " << diam << " для соединения : " << "\n0.Добавить трубу\n1.Выйти\n";
        switch (Choose(0, 1))
        {
        case 0:
            p.AddCurPipe(diam);//создаем трубу, которая по умолчанию в соединении
            connections.insert({ make_pair(in_id, out_id), p.id });//добавляю существующую трубу в соединение
            //делаю так, чтобы нельзя было использовать ту же трубу в соединении больше одного раза
            break;
        case 1:
            break;//выход
        };
    }
    if (connections.size() == 0)
        cout << "Че-то соединения не заполняются";
    ViewConnection(p);
}

bool Connection::loopcheck(std::vector<std::vector<int>>& graph)
{
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[1].size(); j++) {
            if ((graph[i][j] != INF && graph[j][i] != INF) and (i != j)) {
                return true;
            }
        }
    }
    return false;
}

void Connection::dfs(vector<vector<int>>& graph, int v, vector<int>& visited, vector<int>& order)
{
    visited[v] = 1;

    for (int i = 0; i < graph[v].size(); i++)
        if (visited[i] != 1)
            dfs(graph, i, visited, order);

    order.push_back(v);
}

float Connection::Dijkstra(std::vector<std::vector<int>>& a, int index_1, int index_2)
{
    int size = a.size();

    vector<vector<int>> d(size, vector<int>(size));
    vector<vector<int>> v(size, vector<int>(size));

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            d[i][j] = INF;
            v[i][j] = 0;
        }

    int temp, minindex, min;


    d[index_1][index_1] = 0;
    for (int count = 0; count < size; count++)
    {
        min = INF;
        for (int i = 0; i < size; i++)
        {
            if (v[index_1][i] == 0 && d[index_1][i] <= min)
            {
                min = d[index_1][i];
                minindex = i;
            }
        }

        v[index_1][minindex] = 1;

        for (int i = 0; i < size; i++)
        {
            if (!v[index_1][i] && a[minindex][i] != INF && d[index_1][minindex] != INF && d[index_1][minindex] + a[minindex][i] < d[index_1][i])
            {
                d[index_1][i] = d[index_1][minindex] + a[minindex][i];
            }
        }
    }

    return d[index_1][index_2];
}

void Connection::topSort(CS& cs, Pipe& pipe)
{
    if (connections.size() > 0)
    {
        map <int,bool> vertix;
        vector <int> vert;
        for (const auto& i : connections) {
            vertix.insert({i.first.first,true});
            vertix.insert({ i.first.second,true });
        }
        for (const auto& j : vertix) {
            vert.push_back(j.first);
        }
        int n = vert.size();
        vector<vector<int>> matrix(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = i == j ? 0 : connections.contains(make_pair(vert[i], vert[j])) ? connections[make_pair(vert[i], vert[j])] : INF;
            }

        if (!loopcheck(matrix))
        {
            vector <int> visited(n);
            vector <int> order;
            for (int i = 0; i < n; i++)
            {
                if (visited[i] == false)
                {
                    dfs(matrix, i, visited, order);
                    reverse(order.begin(), order.end());
                    for (int j = 0; j < order.size(); j++)
                        cout << vert[order[j]] << ' ';
                }
            }
            cout << "\n\n";
        }
        else
        {
            cout << "Цикл исчезает" << endl;
        }
    }
    else
    {
        cout << "Нет соединения.\n";
        cout << "0. Добавить соединиение\n1. Вернуться в меню";
        if (!Choose(0, 1))
            make_a_con(cs,pipe);
    }
}

void Connection::shortestPath(CS& cs, Pipe& pipe)
{
    if (connections.size() != 0)
    {
        vector <int> index = cs.filterCS();

        for (int i = 0; i < index.size(); i++)
        {
            cout << "КС №" << i + 1 << endl;
            cout << "Название: " << cs.Stations[index[i]].getName() << endl;
            cout << "Кол-во рабочих станций: " << cs.Stations[index[i]].getWSnum() << endl;
        }

        int index_1;
        int index_2;

        while (1)
        {
            cout << "Выберите первую КС";
            index_1 = index[Choose(1, index.size()) - 1];
            cout << "Выберите последнюю КС";
            index_2 = index[Choose(1, index.size()) - 1];
            if (index_1 == index_2)
                cout << "Вторая КС должна быть другой" << endl;
            else
                break;
        }

        vector <int> vert;
        int n = 0; bool temp1 = false; bool temp2 = false; int ind_1 = -1; int ind_2 = -1;

        for (auto it = connections.begin(); it != connections.end(); it++)
        {
            bool t1 = true;
            bool t2 = true;
            for (int i = 0; i < vert.size(); i++)
            {
                if (vert[i] == it->first.first)
                    t1 = false;
                if (vert[i] == it->first.second)
                    t2 = false;
            }

            if (t1)
            {
                vert.push_back(it->first.first);

                if (it->first.first == index_1)
                {
                    temp1 = true;
                    ind_1 = vert.size() - 1;
                }
                else if (it->first.first == index_2)
                {
                    temp2 = true;
                    ind_2 = vert.size() - 1;
                }
            }
            if (t2)
            {
                vert.push_back(it->first.second);

                if (it->first.second == index_1)
                {
                    temp1 = true;
                    ind_1 = vert.size() - 1;
                }
                else if (it->first.second == index_2)
                {
                    temp2 = true;
                    ind_2 = vert.size() - 1;
                }
            }

            n += int(t1) + int(t2);
        }

        vector<vector<int>> matrix(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = i == j ? 0 : connections.contains(make_pair(vert[i], vert[j])) ? pipe.pipes[connections[make_pair(vert[i], vert[j])]].getLength() : INF;
            }

        if (temp1 and temp2)
        {
            int path = Dijkstra(matrix, ind_1, ind_2);
            if (path < INF)
                cout << "Самый короткий путь из КС с ID " << index_1 << " в КС с ID " << index_2 << " составляет " << path << endl << endl;
            else
                cout << "Нет пути из КС с ID " << index_1 << " в КС с ID " << index_2 << endl << endl;
        }
        else
            cout << "Нет пути из КС с ID " << index_1 << " в CS с ID " << index_2 << endl << endl;

    }
    else
    {
        cout << "Нет соединений.\n";
        cout << "1. Добавить соединение\n2. Вернуться в меню";
        if (!Choose(0, 1))
            make_a_con(cs,pipe);
    }
}

int Connection::getConLen()
{
    return connections.size();
}

float Connection::FordFulkerson(vector<vector<int>>& r_matrix, int source, int sink)
{
    int num_V = r_matrix.size();
    vector<int> parent(num_V, -1);
    int max_flow = 0;

    while (true) {

        parent.assign(num_V, -1);
        queue <pair<int, double>> q;
        q.push({ source, DBL_MAX });
        parent[source] = source;

        while (!q.empty()) {
            int u = q.front().first;
            double path_flow = q.front().second;
            q.pop();

            for (int v = 0; v < num_V; v++) {
                if (parent[v] == -1 && r_matrix[u][v] > 0) {
                    parent[v] = u;
                    int min_capacity = path_flow > r_matrix[u][v] ? r_matrix[u][v] : path_flow;
                    if (v == sink) {
                        while (v != source) {
                            u = parent[v];
                            r_matrix[u][v] -= min_capacity;
                            r_matrix[v][u] += min_capacity;
                            v = u;
                        }
                        max_flow += min_capacity;
                        break;
                    }
                    q.push({ v, min_capacity });
                }
            }
        }
        if (parent[sink] == -1)
            break;
    }
    return max_flow;
}

void Connection::maxStream(CS& cs,Pipe& pip)
{
    if (connections.size() != 0)
    {
        vector <int> index = cs.filterCS();

        for (auto index: index)
        {
            cout << "Station " << index << endl;
           // cs.Stations[index];
        }

        int index_1;
        int index_2;

        while (1)
        {
            cout << "Выберите первую КС: ";
            index_1 = index[Choose(1, index.size())-1];
            cout << "Выберите последнюю КС: ";
            index_2 = index[Choose(1, index.size())-1];
            if (index_1 == index_2)
                cout << "Вторая КС должна быть другой" << endl;
            else
                break;
        }

        vector <int> vert;
        int n = 0; bool temp1 = false; bool temp2 = false; int ind_1 = -1; int ind_2 = -1;

        for (auto it = connections.begin(); it != connections.end(); it++)
        {
            bool t1 = true;
            bool t2 = true;
            for (int i = 0; i < vert.size(); i++)
            {
                if (vert[i] == it->first.first)
                    t1 = false;
                if (vert[i] == it->first.second)
                    t2 = false;
            }

            if (t1)
            {
                vert.push_back(it->first.first);

                if (it->first.first == index_1)
                {
                    temp1 = true;
                    ind_1 = vert.size() - 1;
                }
                else if (it->first.first == index_2)
                {
                    temp2 = true;
                    ind_2 = vert.size() - 1;
                }
            }
            if (t2)
            {
                vert.push_back(it->first.second);

                if (it->first.second == index_1)
                {
                    temp1 = true;
                    ind_1 = vert.size() - 1;
                }
                else if (it->first.second == index_2)
                {
                    temp2 = true;
                    ind_2 = vert.size() - 1;
                }
            }

            n += int(t1) + int(t2);
        }

        vector<vector<int>> matrix(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = i == j ? 0 : connections.contains(make_pair(vert[i], vert[j])) ? pip.pipes[connections[make_pair(vert[i], vert[j])]].getLength() : INF;
            }

        if (temp1 and temp2)
        {
            int path = FordFulkerson(matrix, ind_1, ind_2);
            if (path != 0)
                cout << "Максимальный поток: " << path << endl << endl;
            else
                cout << "Нет пути из КС с ID " << index_1 << " в Кс с ID " << index_2 << endl << endl;
        }
        else
            cout << "Нет пути из КС с ID " << index_1 << " В Кс с ID " << index_2 << endl << endl;

    }
    else
    {
        cout << "Нет соединения\n";
        cout << "1. Добавить соединение\n2.Вернуться в меню";
        if (Choose(1, 2) + 2)
            make_a_con(cs,pip);
    }
}

void Connection::ViewConnection(Pipe &p)
{
    for (auto i : connections)
        cout << "Из " << i.first.first << "до " << i.first.second << "имеет диаметр: " << p.pipes[i.second].diameter << " и длину: " << p.pipes[i.second].getLength() << endl;
}

void Connection::SaveCon(std::ofstream& file)
{
    if (connections.size() != 0) {
        file << 1 << " " << connections.size() << endl;
        for (const auto& [id, p] : connections) {
            file << id.first << " " << id.second << " " << p << endl;
        }
    }
    else {
        file << 0 << endl;
    }
}

void Connection::LoadCon(std::ifstream& file)
{
    bool existCon;
    int ConCount;
    file >> existCon;
    if (existCon) {
        file >> ConCount;
        for (int i = 0; i < ConCount; i++) {
            int in_id;
            int out_id;
            int id_pipe;
            file >> in_id;
            file >> out_id;
            file >> id_pipe;
            connections.insert({make_pair(in_id,out_id),id_pipe});
        }
    }
}
