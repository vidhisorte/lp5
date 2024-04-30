#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>

using namespace std;
using namespace std::chrono;
class Graph{
    int V; //no. of vertices
    vector<vector<int>> adj;  //adjacency list
    
    public:
    Graph(int V)
    {
        this->V=V;
        adj.resize(V);
    }
    
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void BFS(int source)
    {
        vector<bool> visited(adj.size(), false);
        queue<int> q;
        visited[source]=true;
        q.push(source);
        while(!q.empty())
        {
            int u;
            u=q.front();
            q.pop();
            
            if(!(adj[u].size()==0))
            {
                for(int i=0; i<adj[u].size();i++)
                {
                    if(!visited[adj[u][i]])
                    {
                        q.push(adj[u][i]);
                        visited[adj[u][i]]=true;
                    }
                }
            }
        }
    }
    void parallelBFS(int source)
    {
        vector<bool> visited(adj.size(),false);
        queue<int> q;
        visited[source]=true;
        q.push(source);
        while(!q.empty())
        {
            int u;
#pragma omp parallel shared(q,visited)
{
#pragma omp single
            {
            u=q.front();
            q.pop();
            }
            
            {
            if(!(adj[u].size()==0))
            {
#pragma omp for
                for(int i=0;i<adj[u].size();i++)
                {
                    if(!visited[adj[u][i]])
                    {
#pragma omp critical
                    {
                        q.push(adj[u][i]);
                        visited[adj[u][i]]=true;
                    }
                    }
                }
                
            }
            }
            
        }
        }
        
    }
    
    
    void DFSUtil(int v, vector<bool> &visited)
    {
        visited[v]=true;
        for(int i=0;i<adj[v].size();i++)
        {
            int u=adj[v][i];
            if(!visited[u])
            {
                DFSUtil(u,visited);
            }
        }
    }
    
    void DFS(int source)
    {
        vector<bool> visited(V,false);
        DFSUtil(source, visited);
    }
    int getV() const {
        return V;
    }
    
    void parallelDFSUtil(int v, vector<bool> &visited)
    {
        visited[v]=true;
#pragma omp parallel for
        for(int i=0;i<adj[v].size();i++)
        {
            int u= adj[v][i];
            if(!visited[u])
            {
                parallelDFSUtil(u,visited);
            }
        }
    }
    void parallelDFS(int source)
    {
        vector<bool> visited(V,false);
        parallelDFSUtil(source,visited);
    }
};
int main()
{
    int numNodes, numEdges;
    cout<<"enter number of nodes"<<endl;
    cin>>numNodes;
    cout<<"enter number of edges"<<endl;
    cin>>numEdges;
    
    Graph g(numNodes);
    int u,v;
    for(int i=0;i<numEdges;i++)
    {
        cout<<"Enter the edges (u,v)"<<endl;
        cin>>u>>v;
        g.addEdge(u,v);
    }
    
    auto start = high_resolution_clock::now();

    cout << "Breadth First Search (BFS) starting from vertex 0: ";
    g.BFS(0);
    auto stop = high_resolution_clock::now();

    cout << endl;

    auto bfs_duration = duration_cast<nanoseconds>(stop - start);


     start = high_resolution_clock::now();

    cout << "Parallel Breadth First Search (BFS) starting from vertex 0: ";
    g.parallelBFS(0);
     stop = high_resolution_clock::now();

    cout << endl;
    auto pbfs_duration = duration_cast<nanoseconds>(stop - start);


     start = high_resolution_clock::now();

    cout << "Depth First Search (DFS) starting from vertex 0: ";
    g.DFS(0);
     stop = high_resolution_clock::now();

    cout << endl;
    auto dfs_duration = duration_cast<nanoseconds>(stop - start);

     start = high_resolution_clock::now();

    cout << "Parallel Depth First Search (DFS) starting from vertex 0: ";
    g.parallelDFS(0);
     stop = high_resolution_clock::now();

    cout << endl;
    auto pdfs_duration = duration_cast<nanoseconds>(stop - start);

    cout << "Sequential BFS Time: " << bfs_duration.count() << " nanoseconds" << endl;
    cout << "Parallel BFS Time: " << pbfs_duration.count() << " nanoseconds" << endl;
    cout << "Sequential DFS Time: " << dfs_duration.count() << " nanoseconds" << endl;
    cout << "Paralell DFS Time: " << pdfs_duration.count() << " nanoseconds" << endl;

    
    
}
