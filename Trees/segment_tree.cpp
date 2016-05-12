#include <iostream>
#include <algorithm>
using namespace std;


template <class T>
class segment_tree {
public:
	segment_tree(const T* values, int size) : leaf_s(size), tree_s(1 << (int)ceil(log2(2 * size))) {
		tree = new T[tree_s];
		lazy = new T[tree_s];

		for (int i = tree_s - 1, end = size; i > 0; i--) {
			if (end > 0 && i >= (1 << (int)log2(tree_s) - 1) + size) tree[i] = T(0);
			else if (end > 0) tree[i] = values[--end];
			else tree[i] = tree[2 * i] + tree[1 + 2 * i];

			lazy[i] = T(0);
		}
	}

	inline void update(int from, int to, int by) {
		r_update_tree(1, 0, (tree_s - 1) / 2, from, to, by);
	}

	inline T query(int from, int to) {
		return r_query_tree(1, 0, (tree_s - 1) / 2, from, to);
	}


private:
	T *tree, *lazy;
	unsigned int leaf_s, tree_s;

	T r_query_tree(int node, int a, int b, int i, int j) {
		if (a > b || a > j || b < i) return T(0);

		if (lazy[node] != T(0)) {
			tree[node] += lazy[node];

			if (a != b) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			lazy[node] = 0;
		}

		if (a >= i && b <= j) return tree[node];

		T q1 = r_query_tree(node * 2, a, (a + b) / 2, i, j);
		T q2 = r_query_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j);

		// Replace + by whatever operation do you want
		//	max, min etc...
		T res = q1 + q2;

		return res;
	}

	void r_update_tree(int node, int a, int b, int i, int j, T value) {
		if (lazy[node] != 0) {
			tree[node] += lazy[node];

			if (a != b) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}

			lazy[node] = 0;
		}

		if (a > b || a > j || b < i) return;

		if (a >= i && b <= j) {
			tree[node] += value;

			if (a != b) {
				lazy[node * 2] += value;
				lazy[node * 2 + 1] += value;
			}

			return;
		}

		r_update_tree(node * 2, a, (a + b) / 2, i, j, value);
		r_update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j, value);

		// Again replace + by whatever operation do you want
		//	max, min etc...
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
};



int _main() {
	/* Create & Fill an array */
	int* arr = new int[10];
	for (int i = 0; i < 10; i++)
		arr[i] = i + 1;

	/* CREATE SEGMENT TREE FROM ARRAY */
	segment_tree<int> st(arr, 10);

	/* EXAMPLE USING SEGMENT TREE */
	auto sum = st.query(0, 5);
	st.update(0, 4, 20);
	auto sum2 = st.query(0, 2);
	/* END OF EXAMPLE */


	return 0;
}
