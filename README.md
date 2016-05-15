# zclib
Basic algo's &amp; ds's implementations.


##Graph algorithms
Most of the files are compatible with each other, except those that simply can't be used together. Array of nodes with list of successors (pairs for weighted graphs) is mostly used as a graph represenatation (except those, where it does not make sense - e.g. Floyd Wharshal).

####Unweighted graph
- **BFS** *(Both)* - O(V+E)
- **DFS** *(Both)* - O(V+E)
- **Shortest Path** using BFS *(Both)* - O(V+E)
- **Find if graph is cyclic** using DFS *(Both)* - O(V+E)
- **Find strongly connected components** using Tarjan's alg *(Directed only)* - O(V+E)

####Weighted graph
- **Shortest Paths** using Dijsktra *(Both - unsigned edge's weights)* - O(E*logV)
- **Shortest Paths** using Bellman Ford *(Both - signed edge's weights)* - O(V*E)
- **Shortest Paths** using Floyd-Warshall *(Both - signed edge's weights)* - O(V^3)
- **Minimal Spanning Tree** using Kurskal *(Undirected - signed edge's weights)* - O(E*logE) _(if edges are pre-sorted or used linear sort logE changes to α (inverse Ackermann function)_


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

