# zclib
Basic algo's &amp; ds's implementations.


##Graph algorithms
Most of files are compatible, unless those where it is not possible. Node's struct with vector of successor nodes is mostly used as a graph represenatation (unless those, where it is does not make sense - like Floyd Wharshal)

####Unweighted graph
- BFS *(Both)*
- DFS *(Both)*
- Shortest Path using BFS *(Both)*
- Find if graph is cyclic using DFS *(Both)*
- Find strongly connected components using Tarjan's alg *(Directed only)*

####Weighted graph
- Shortest Paths using Dijsktra *(Both - unsigned edge's weights)*
- Shortest Paths using Bellman Ford *(Both - signed edge's weights)*
- Shortest Paths using Floyd-Warshall *(Both - signed edge's weights)*


##Trees

####Interval Tree
Interval Tree is used to stored intervals *(implemented as AVL Tree)*. The interval tree provides 3 query operations:
- Overlap(interval) - Return all intervals that overlap given interval
- Contain(interval) - Return all intervals that contain given interval
- Contained(interval) - Return all intervals that lies in given interval
