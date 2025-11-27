/*
6 9

Edges: 
0 1 1
0 2 2
1 2 3
1 3 2
1 4 4
2 4 5
3 4 3
3 5 4
4 5 1

*/
#include<bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, vector<pair<int,int> >adj[], int src){
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
    vector<int> distance(V,1e9);
    vector<int> parent(V);
    for(int i=0; i<V; i++) parent[i] = i;


    pq.push(make_pair(0,src));
    distance[src] = 0;

    while(!pq.empty()){
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for(auto it : adj[node]){
            int adjNode = it.first;
            int edW = it.second;

            if (dist + edW < distance[adjNode]){
                distance[adjNode] = dist + edW;
                pq.push(make_pair(distance[adjNode], adjNode));
                parent[adjNode] = node;
            }
        }
    }

    vector<int> empty(V,-1);
    if (distance[V-1] == 1e9) return empty;

    vector<int> path;
    int node = V-1;
    while(node != parent[node]){
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    return path;
}

int main(){
    int V, E;
    cout<<"Enter the number of vertices and edges: ";
    cin>>V>>E;

    cout<<"Enter the edges: (S T Wt)\n";
    vector<pair<int,int> >adj[V];

    for(int i=0; i<E; i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        adj[u].push_back(make_pair(v,wt));
        adj[v].push_back(make_pair(u,wt));
    }

    int src;
    cout<<"Enter the source node: ";
    cin>>src;

    vector<int> path = dijkstra(V, adj, src);
    for(auto it : path){
        cout<<it<<" -> ";
    }
}