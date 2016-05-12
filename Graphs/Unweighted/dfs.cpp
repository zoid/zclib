#include <iostream>
#include <vector>

using namespace std;

const int INDEX = 1;			/* INDEX FROM */
const int FRESH = 0;			/* FRESH NODE STATE */
const int OPEN = 1;			/* OPEN NODE STATE */
const int CLOSED = 2;			/* CLOSED NODE STATE */
const bool UNDIRECTED = false;		/* DIRECTED / UNDIRECTED GRAPH */

struct CNode {
	int id, state, step, component;

	/* Custom data */
	// ...

	vector<CNode*> successors;
	CNode() : state(FRESH) { }
	CNode(int _id) : id(_id), state(FRESH) { }
};

inline void connect(CNode* a, CNode *b) {
	a->successors.push_back(b);
	if (UNDIRECTED == true) b->successors.push_back(a);
}

void dfs(CNode* node) {
	node->state = OPEN;

	/* do something here */

	for (auto& val : node->successors) {
		if (val->state != FRESH) continue;
		dfs(val);
	}

	node->state = CLOSED;
}

int _main()
{
	int n, m, a, b, from;
	cin >> n >> m >> from;
	
	/* Create graph */
	CNode* nodes = new CNode[n];
	for (int i = 0; i < n; i++)
		nodes[i] = CNode(i + INDEX);

	/* Read graph from input */
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		connect(&nodes[a - INDEX], &nodes[b - INDEX]);
	}

	/* START DFS */
	dfs(&nodes[from - INDEX]);

	return 0;
}
