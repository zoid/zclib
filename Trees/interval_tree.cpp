#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<class T = bool> struct interval {
	T data;
	int start, end;

	interval(int _start, int _end) : start(_start), end(_end), data(T(0)) {  }
	interval(int _start, int _end, T _data) : start(_start), end(_end), data(_data) { }

	inline bool overlaps(const interval<T>& x) const { return overlaps(x.start, x.end); }
	inline bool overlaps(int s, int e) const { return start <= e && s <= end; }
	inline bool contains(const interval<T>& x) const { return contains(x.start, x.end); }
	inline bool contains(int s, int e) const { return start <= s && end >= e; }
};

template<class T = bool>
struct ITNode {
	int min, max, balance;
	ITNode *left, *right, *parent;
	interval<T>* m_interval;

	ITNode(interval<T>* _i, ITNode* p) : m_interval(_i), min(_i->start), max(_i->end), balance(0), parent(p), left(NULL), right(NULL) { }
	~ITNode() { delete left; delete right; delete i; }


};

template <typename T = bool>
class ITree {
	typedef ITNode<T>				Node;
	typedef vector<interval<T>>		ivec;

	static const int OVERLAP = 0;
	static const int CONTAIN = 1;
	static const int CONTAINED = 2;

public:
	ITree() : root(NULL) { }
	~ITree() { delete root; }

	inline bool empty() { return root == NULL; }

	/* Insert an interval */
	inline void insert(interval<T>* i) { root = r_insert(root, NULL, i); }
	inline void insert(int s, int e, T val = T(0)) { root = r_insert(root, NULL, new interval<T>(s, e, val)); }

	/* Find overlapping intervals */
	inline ivec overlap(int start, int end) {
		ivec overlapping;
		r_overlap(root, interval<T>(start, end), overlapping);
		return overlapping;
	}


	inline ivec search(int start, int end, int mode) {
		ivec vec;
		r_search(root, interval<T>(start, end), vec, mode);
		return vec;
	}

	inline ivec overlap(const interval<T>& i) {
		return search(i.start, i.end, OVERLAP);
	}

	inline ivec contains(const interval<T>& i) {
		return search(i.start, i.end, CONTAIN);
	}

	inline ivec contained(const interval<T>& i) {
		return search(i.start, i.end, CONTAINED);
	}



private:
	Node *root;

	void r_search(Node *root, const interval<T>& i, ivec& vec, int mode) {
		if (root == NULL) return;

		if (mode == OVERLAP && root->m_interval->overlaps(i)) vec.push_back(*(root->m_interval));
		if (mode == CONTAIN && root->m_interval->contains(i)) vec.push_back(*(root->m_interval));
		if (mode == CONTAINED && i.contains(*(root->m_interval))) vec.push_back(*(root->m_interval));

		if (root->left != NULL && i.overlaps(root->left->min, root->left->max))
			r_search(root->left, i, vec, mode);
		if (root->right != NULL && i.overlaps(root->right->min, root->right->max))
			r_search(root->right, i, vec, mode);
	}

	/* Recursive insert into avl tree*/
	Node *r_insert(Node *root, Node* parent, interval<T>* i) {
		if (root == NULL) {
			root = new Node(i, parent);
			if (parent != NULL) rebalance(parent);
			return root;
		}

		if (i->start < root->m_interval->start)
			root->left = r_insert(root->left, root, i);
		else
			root->right = r_insert(root->right, root, i);

		root->max = max(root->max, i->end);
		root->min = min(root->min, i->start);

		return root;
	}

	/* ROTATIONS */
	Node* rotateLeft(Node* a) {
		Node* b = a->right;
		b->parent = a->parent;
		a->right = b->left;

		if (a->right != NULL) a->right->parent = a;
		b->left = a;
		a->parent = b;

		if (b->parent != NULL) {
			if (b->parent->right == a)
				b->parent->right = b;
			else
				b->parent->left = b;
		}

		setBalance(a);
		setBalance(b);
		return b;
	}
	Node* rotateRight(Node* a) {
		Node *b = a->left;
		b->parent = a->parent;
		a->left = b->right;

		if (a->left != NULL) a->left->parent = a;
		b->right = a;
		a->parent = b;

		if (b->parent != NULL) {
			if (b->parent->right == a)
				b->parent->right = b;
			else
				b->parent->left = b;
		}

		setBalance(a);
		setBalance(b);
		return b;
	}
	inline Node* rotateLeftThenRight(Node *n) {
		n->left = rotateLeft(n->left);
		return rotateRight(n);
	}
	inline Node* rotateRightThenLeft(Node *n) {
		n->right = rotateRight(n->right);
		return rotateLeft(n);
	}

	/* BALANCE */
	inline int height(Node* n) {
		return (n == NULL) ? -1 : 1 + max(height(n->left), height(n->right));
	}

	inline void setBalance(Node* n) {
		n->balance = height(n->right) - height(n->left);
	}

	void rebalance(Node* n) {
		setBalance(n);

		if (n->balance == -2) {
			if (height(n->left->left) >= height(n->left->right)) n = rotateRight(n);
			else n = rotateLeftThenRight(n);
		}
		else if (n->balance == 2) {
			if (height(n->right->right) >= height(n->right->left)) n = rotateLeft(n);
			else n = rotateRightThenLeft(n);
		}

		if (n->parent != NULL) rebalance(n->parent);
		else root = n;
	}
};



int _main() {
	ITree<>* intervalTree = new ITree<>();

  /* EXAMPLE USING INTERVAL TREE */
	int intervals[7][2] = { { 15, 20 },{ 10, 30 },{ 17, 19 },{ 5, 20 },{ 12, 15 },{ 30, 40 },{ 10, 16 } };

	for (int i = 0; i < 7; i++)
		intervalTree->insert(intervals[i][0], intervals[i][1]);

	auto overlapping_with = intervalTree->overlap(interval<>(6, 14));
	auto containin = intervalTree->contains(interval<>(11, 13));
	auto contained = intervalTree->contained(interval<>(7, 18));
  
  /* END OF EXAMPLE */
  
	return 0;
}
