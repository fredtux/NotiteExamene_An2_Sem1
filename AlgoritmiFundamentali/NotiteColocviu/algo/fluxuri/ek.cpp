int EdmondsKarp(vector<vector<pair<int, int>>> &graph, int start, int end) {
    int flowValue = 0;

    for (int i = 1; i < graph.size(); i++) {
        if (graph[start][i].first != -1) {
            flowValue += graph[start][i].first;
        }
    }
    while (true) {
        vector<int> q;
        q.push_back(start);

        vector<int> dad(graph.size(), 0);
        vector<bool> visited(graph.size(), false);

        visited[start] = true;

        while (!q.empty()) {
            int current = q[0];
            q.erase(q.begin());
            for (int i = 1; i < graph.size(); i++) {

                if (graph[current][i].first < graph[current][i].second && !visited[i]) {
                    dad[i] = current;
                    visited[i] = true;
                    q.push_back(i);
                }

                if (graph[i][current].first > 0 && !visited[i]) {
                    dad[i] = -current;
                    visited[i] = true;
                    q.push_back(i);
                }

            }
        }

        if (!visited[end]) {
            return flowValue;
        }

        //mergem prin dad
        int current = end;
        int updateFlow = 9999;
        while (current != start) {
            int parent = dad[current];
            int residue;
            if (parent > 0) {
                residue = graph[parent][current].second - graph[parent][current].first;
                current = parent;
            } else {
                residue = graph[current][-parent].first;
                current = -parent;
            }

            if (residue < updateFlow) {
                updateFlow = residue;
            }
        }

        //actualizam
        current = end;
        while (current != start) {
            int parent = dad[current];
            if (parent > 0) {
                graph[parent][current].first += updateFlow;
                current = parent;
            } else {
                graph[current][-parent].first -= updateFlow;
                current = -parent;
            }
        }

        flowValue += updateFlow;
    }
}