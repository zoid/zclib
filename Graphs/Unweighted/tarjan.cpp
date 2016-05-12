#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

const int INDEX = 1;			/* INDEX FROM */
const int FRESH = 0;			/* FRESH NODE STATE */
const int OPEN = 1;			/* OPEN NODE STATE */
const int CLOSED = 2;			/* CLOSED NODE STATE */
const bool UNDIRECTED = false;		/* DIRECTED / UNDIRECTED GRAPH */

typedef list<CNode*> component;

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

void r_scc(
	CNode* node,
	unordered_map<CNode*, int>& back_step,
	stack<CNode*>& s,
	unordered_set<CNode*>& on_stack,
	int &step,
	int &count,
	vector<component>& components)
{
	node->state = OPEN;
	node->step = back_step[node] = step++;

	s.push(node);
	on_stack.insert(node);

	for (auto &val : node->successors) {
		if (val->state == FRESH) {
			r_scc(val, back_step, s, on_stack, step, count, components);
			back_step[node] = min(back_step[node], back_step[val]);
		}
		else if (on_stack.find(val) != on_stack.end()) {
			back_step[node] = min(back_step[node], back_step[val]);
		}
	}

	node->state = CLOSED;

	if (node->step == back_step[node]) {
		CNode* tmp;

		do {
			tmp = s.top();
			s.pop();
			on_stack.erase(on_stack.find(tmp));

			if (components.size() <= count) {
				components.resize(count + 1);
			}
			components[count].push_back(tmp);


		} while (node != tmp);
		++count;
	}
}

int scc(CNode* graph, int size, vector<component> &components, unordered_map<CNode*, int> &components_map)
{
	unordered_set<CNode*> on_stack;
	stack<CNode*> stck;

	int step = 0, count = 0;

	for (int i = 0; i < size; i++) {
		if (graph[i].state == FRESH)
			r_scc(&graph[i], components_map, stck, on_stack, step, count, components);
	}

	return components.size();
}

int _main()
{
	int n, m, a, b;
	cin >> n >> m;

	/* Create graph */
	CNode* nodes = new CNode[n];
	for (int i = 0; i < n; i++)
		nodes[i] = CNode(i + INDEX);

	/* Read graph from input */
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		connect(&nodes[a - INDEX], &nodes[b - INDEX]);
	}

	/* START TARJAN */

	// Vector of components (list of nodes)
	vector<component> components;

	// NOTE:
	//	second value does not reffer to component id in vector of components
	//	it should be used just for testing if 2 nodes are in the same component
	unordered_map<CNode*, int> components_map;

	// RETURNS NUMBER OF SC COMPONENTS
	int cnt = scc(nodes, n, components, components_map);

	return 0;
}

