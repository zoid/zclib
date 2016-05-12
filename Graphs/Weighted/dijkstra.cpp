#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <list>

using namespace std;

const int INDEX = 1;			/* INDEX FROM */
const int FRESH = 0;			/* FRESH NODE STATE */
const int OPEN = 1;			/* OPEN NODE STATE */
const int CLOSED = 2;			/* CLOSED NODE STATE */
const bool UNDIRECTED = true;		/* DIRECTED / UNDIRECTED GRAPH */

struct CNode {
	int id, state, step, component;

	/* Custom data */
	// ...

	vector<pair<CNode*, unsigned int>> successors;
	CNode() : state(FRESH) { }
	CNode(int _id) : id(_id), state(FRESH) { }
};

inline void connect(CNode* a, CNode *b, unsigned int w) {
	a->successors.push_back(make_pair(b, w));
	if (UNDIRECTED == true) b->successors.push_back(make_pair(a, w));
}

struct Priority {
	bool operator ()(CNode* _a, CNode* _b) { return _a->step < _b->step; }
};

void dijsktra(CNode* from, unordered_map<CNode*, list<CNode*>>& paths) {
	priority_queue<CNode*, vector<CNode*>, Priority> q;
	from->step = 0;
	q.push(from);

	while (!q.empty()) {
		from = q.top();
		q.pop();

		for (auto &val : from->successors) {
			if (val.first->step > from->step + val.second) {
				val.first->step = from->step + val.second;

				paths[val.first] = paths[from];
				paths[val.first].push_back(from);

				q.push(val.first);
			}
		}
	}
}

int _main() {
	int n, m, a, b, w, from;
	cin >> n >> m >> from;

	/* Create graph */
	CNode* nodes = new CNode[n];
	for (int i = 0; i < n; i++)
		nodes[i] = CNode(i + INDEX);

	/* Read graph from input */
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> w;
		connect(&nodes[a - INDEX], &nodes[b - INDEX], w);
	}

	// START DIJKSTRA
	unordered_map<CNode*, list<CNode*>> paths(n);
	dijsktra(&nodes[from - INDEX], paths);

	// NOTE
	//	node->step represents distance from the beginning
	//	paths[node] contains list that represent path from
	//	the beginning (included in path) to the node (not included in path)

	return 0;
}
