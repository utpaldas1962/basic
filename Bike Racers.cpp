#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <stack>
#include <algorithm>
using namespace std;

/*
input:
3 3 2
0 1
0 2
0 3
100 1
200 2 
300 3
output:
40000
*/

int N, M, K; 
vector<pair<int,int> > riders;
vector<pair<int,int> > bikes;
vector<vector<int> > r2b;

int match (const vector<vector<int> > & graph) {
    int max_edges = 1;
    stack<vector<int> > que;
    que.push(vector<int>());
    while (!que.empty()) {
        const vector<int>  solution = que.top(); que.pop();
        //cout << "solution:"; for(int i = 0; i < solution.size(); ++i) cout << solution[i] << " ";
        //cout << endl;
        int node = solution.size();
        if(node == N) {
            int total = 0; for (int i = 0; i < N; ++i) {
                total += (solution[i]!=-1);
            }
            if (total > max_edges) max_edges = total;
            if (max_edges >= K) return K;
            continue;
        }

        int total = 0; for (int i = 0; i < solution.size(); ++i) {
            total += (solution[i]!=-1);
        }
        if (total + N - node < max_edges) continue;

        vector<int> new_solution(solution);
        new_solution.push_back(-1);
        

        for (int m = 0; m < graph[node].size(); ++m) {
            if (find(solution.begin(), solution.end(), graph[node][m]) == solution.end()) {
                //cout << "node:" << node << "m:" << graph[node][m] << endl;
                new_solution[node] = graph[node][m];
                que.push(new_solution);
            }
            
        } 

        if (new_solution[node] == -1) que.push(new_solution);
    }

    return max_edges;
}

int euclidean(const pair<int,int> & xy1, const pair<int,int> & xy2) {
    return (xy1.first-xy2.first)*(xy1.first-xy2.first) + (xy1.second-xy2.second)*(xy1.second-xy2.second);
}

bool check(const unsigned long long time, 
            const vector<vector<int> > & r2b) {
    vector<vector<int> > graph (N, vector<int>());
    for (int r = 0; r < N; ++r) {
        for (int b = 0; b < M; ++b) {
            if (r2b[r][b] <= time) graph[r].push_back(b);
        }
    }
    /*
    for (int r = 0; r < N; ++r) {
        cout << r << ":";
        for (int i = 0; i < graph[r].size(); ++i) {
            cout << graph[r][i] << " ";
        }
        cout << endl;
    }
    */
    return match(graph) >= K;
}

int main() {
    
    
    cin >> N >> M >> K;
    for (int i = 0; i < N + M; ++i) {
        int x, y; cin >> x >> y;
        if (i < N) riders.push_back(make_pair(x, y));
        else bikes.push_back(make_pair(x, y));
    }

    r2b = vector<vector<int> >(N, vector<int>(M));
    for (int r = 0; r < riders.size(); ++r) {
        for (int b = 0; b < bikes.size(); ++b) {
            r2b[r][b] = euclidean(riders[r], bikes[b]);
        }
    }

    
     long long low = 0;
     long long high = 10000000000000000; // 10**16
    while (low < high) {
         long long mid = (low + high) / 2;
        if (check(mid, r2b)) high = mid;
        else low = mid+1;
        //cout << mid << endl;
    }

    cout << low << endl;
    
    //cout << check(0,r2b) << endl;
    return 0;

}
