#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

const int INDEX = 1;		/* INDEX FROM */
const bool UNDIRECTED = true;	/* DIRECTED / UNDIRECTED GRAPH */

class Union_Find {
public:
	int* id, *sz;
	Union_Find(int n) : id(new int[n]), sz(new int[n]) {
		for (int i = 0; i < n; ++i) { id[i] = i; sz[i] = 1; }
	}

	int root(int i) {
		i--;
		while (i != id[i]) { i = id[i] = id[id[i]]; }
		return i;
	}

	inline int find(int p, int q) { return root(p) == root(q); }

	void join(int p, int q) {
		int i = root(p), j = root(q);
		if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
		else { id[j] = i; sz[i] += sz[j]; }
	}
};

class CEdge;

class CNode {
public:
	int id;
	list<CEdge*> edges;
	CNode(int _id) : id(_id) {};
};

class CEdge {
public:
	int weight;
	CNode *a, *b;
	CEdge(CNode* _a, CNode* _b, int _w) : a(_a), b(_b), weight(_w) {
		_a->edges.push_back(this);
		if (UNDIRECTED)
			_b->edges.push_back(this);
	};
};


int Kruskal_MST(const vector<CNode*> &nodes, vector<CEdge*> &edges, vector<CNode*> &mst_nodes, vector<CEdge*> &mst_edges) {
	Union_Find UF(nodes.size());
	int size = 0;

	// Sort edges by weight
	sort(edges.begin(), edges.end(), [](const CEdge* lhs, const CEdge* rhs) { return lhs->weight < rhs->weight; });

	// Find MST
	for (auto& edge : edges) {
		if (!UF.find(edge->a->id, edge->b->id)) {
			UF.join(edge->a->id, edge->b->id);
			size += edge->weight;
			mst_edges.push_back(new CEdge(mst_nodes[edge->a->id - INDEX], mst_nodes[edge->b->id - INDEX], edge->weight));
		}
	}

	return size;
}

int main() {
	int n, m, a, b, w;
	cin >> n >> m;

	/* Create graph */
	vector<CEdge*> edges(m);
	vector<CNode*> nodes(n);

	for (int i = 0; i < n; i++)
		nodes[i] = new CNode(i + INDEX);

	/* Read graph from input */
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> w;
		edges[i] = new CEdge(nodes[a - INDEX], nodes[b - INDEX], w);
	}

	/* Create MST */
	vector<CNode*> mst_nodes(n);
	vector<CEdge*> mst_edges;
	for (int i = 0; i < n; i++)
		mst_nodes[i] = new CNode(i + INDEX);

	int weight = Kruskal_MST(nodes, edges, mst_nodes, mst_edges);

	return 0;
}
