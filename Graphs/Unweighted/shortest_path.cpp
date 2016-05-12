#include <iostream>
#include <queue>
#include <list>
#include <unordered_map>
#include <exception>
using namespace std;

const int INDEX = 1;			/* INDEX FROM */
const int FRESH = 0;			/* FRESH NODE STATE */
const int OPEN = 1;			/* OPEN NODE STATE */
const int CLOSED = 2;			/* CLOSED NODE STATE */
const bool UNDIRECTED = false;	   	/* DIRECTED / UNDIRECTED GRAPH */

struct CNode {
	int id, state, step, component;

	/* Custom data */
	// ...

	list<CNode*> successors;
	CNode() : state(FRESH) { }
	CNode(int _id) : id(_id), state(FRESH) { }
};

inline void connect(CNode* a, CNode *b) {
	a->successors.push_back(b);
	if (UNDIRECTED == true) b->successors.push_back(a);
}

int shortest_path(CNode* from, CNode* to, list<CNode*>& output_path) {
	unordered_map<CNode*, list<CNode*>> paths;
	queue<CNode*> bfs;

	paths[from].push_back(from);

	from->step = 1;
	from->state = OPEN;

	bfs.push(from);

	while (!bfs.empty()) {
		from = bfs.front();
		bfs.pop();

		/* do something here */
		if (from == to) break;

		for (auto& val : from->successors) {
			if (val->state != FRESH) continue;

			// Tracking path
			paths[val] = paths[from];
			paths[val].push_back(val);

			val->step = from->step + 1;
			val->state = OPEN;
			bfs.push(val);
		}

		from->state = CLOSED;
	}

	if (from != to) throw exception("Path doesnt exists");

	output_path = paths[to];
	return from->step;
}

int _main()
{
	int n, m, a, b, from, to;
	cin >> n >> m >> from >> to;

	/* Create graph */
	CNode* nodes = new CNode[n];
	for (int i = 0; i < n; i++)
		nodes[i] = CNode(i + INDEX);

	/* Read graph from input */
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		connect(&nodes[a - INDEX], &nodes[b - INDEX]);
	}

	/* FIND SHORTEST PATH */
	list<CNode*> path;
	int lenght;
	try {
		lenght = shortest_path(&nodes[from - INDEX], &nodes[to - INDEX], path);
	}
	catch (exception) {
		lenght = 0;			// Path doesnt exists
	}

	return 0;
}
