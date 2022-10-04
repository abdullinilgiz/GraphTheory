#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void dfs(unordered_map<int, vector<int>>& adj_list, int start, vector<bool>& visited){

    if (visited[start]){
        return;
    }else {
        //cout << start << endl;
        visited[start] = true;
        auto& neighbours = adj_list[start];
        for(auto item : neighbours){
            dfs(adj_list, item, visited);
        }
    }
}

vector<int>  solve(unordered_map<int, vector<int>>& adj_list, int start){
    queue<int> q;
    q.push(start);

    vector<bool> visited(adj_list.size(), false);
    visited[start] = true;

    vector<int> prev(adj_list.size(), -1);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        auto& neighbours = adj_list[node];

        for (auto item : neighbours){
            if(!visited[item]){
                q.push(item);
                visited[item] = true;
                prev[item] = node;
            }
        }
    }
    return prev;
}

vector<int> reconstructPath(int start, int end, vector<int>& prev){
    vector<int> path;
    for ( int i = end; i != -1; i = prev[i]){
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    if (path[0] == start){
        return path;
    }
    return {};
}

vector<int> bfs(unordered_map<int, vector<int>>& adj_list, int start, int end){
    auto prev = solve(adj_list, start);
    return reconstructPath(start, end, prev);
}

int main() {
    unordered_map<int, vector<int>> adj_list = {
            {0,  {1, 9}},
            {1,  {0, 8}},
            {9,  {0, 8}},
            {8,  {1, 7, 9}},
            {7,  {3, 6, 8, 10, 11}},
            {10, {7, 11}},
            {11, {7, 10}},
            {6,  {7, 5}},
            {5,  {3, 6}},
            {3,  {2, 4, 5, 7}},
            {2,  {3}},
            {4,  {3}},
            {12, {}}
    };
    vector<bool> visited(adj_list.size(), false);
    dfs(adj_list, 0, visited);
    auto path = bfs(adj_list, 0, 5);
    for (auto item : path){
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
