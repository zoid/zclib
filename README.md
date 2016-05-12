# zclib
Basic algo's &amp; ds's implementations.


##Graph algorithms
Most of files are compatible with each other, expect those where it is not possible. Node's struct with vector of successor nodes is mostly used as a graph represenatation (unless those, where it is does not make sense - like Floyd Wharshal)

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
Interval Tree is used to store intervals *(implemented as AVL Tree)*. The interval tree provides 3 query operations:
- Overlap(interval) - Return all intervals that overlap given interval
- Contain(interval) - Return all intervals that contain given interval
- Contained(interval) - Return all intervals that lies in given interval

####Segment Tree
Segment Tree is used to store some data on interval *(implemented as perfect binary tree)* and provides query and update operations on given interval both in O(log N) with lazy propagation:
- Query(from, to) - Return value for given range *(Lazy propagation)*
- Update(from, to) - Updates values in given range *(Lazy propagation)*

*NOTE: Since it's a template class, template type should have implemented operator+ (otherwise you have to change the operation in code).* 

