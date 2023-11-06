#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;

const int MAXN = 500;
bool visited[MAXN];
vector<int> graph[MAXN];


void bfs(int s) {
    memset(visited, 0, MAXN);
    queue<int> q;
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << ' ';
        for (int i = 0; i < graph[v].size(); ++i) {
            int u = graph[v][i];
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}

void dfs(int v) {
    visited[v] = true;
    cout << v << ' ';
    for (int i = 0; i < graph[v].size(); ++i) {
        int u = graph[v][i];
        if (!visited[u]) {
            dfs(u);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 0;i < n; i++){
        sort(graph[i].begin(), graph[i].end());
    }
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    cout<<endl;
    visited[0] = false;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            bfs(i);
        }
    }cout<<endl;
    return 0;
}

