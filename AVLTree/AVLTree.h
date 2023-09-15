#ifndef AiAS_AVLTree
#define AiAS_AVLTree
#include "Utils.h"
#include <vector>
#include <stack>

template<class T>
struct Node {
	Node* left = nullptr;
	Node* right = nullptr;
	int height = 1;
	T value;
	Node(const T& _val) : value{ _val } {}
	Node(const T& _val, Node* _left, Node* _right) :
		value{ _val }, left{ _left }, right{ _right } {
		if (left && left->height + 1 > height)
			height = left->height + 1;
		if (right && right->height + 1 > height)
			height = right->height + 1;
	}
	Node(const Node& _node) :
		value(_node.value), height{_node.height} {
		if (_node.left)
			left = new Node(*_node.left);
		if (_node.right)
			right = new Node(*_node.right);
	}
	Node& operator=(const Node* _node) {
		if (&_node == this)
			return *this;
		delete left;
		delete right;
		value = _node.value;
		height = _node.height;
		if (_node.left)
			left = new Node(*_node.left);
		else
			left = nullptr;
		if (_node.right)
			right = new Node(*_node.right);
		else
			right = nullptr;
		return *this;
	}
	~Node() {
		delete left;
		delete right;
	}
};

template<class T, class Comp = Less<>>
class AVLTree {
	using NodeType = Node<T>;
	NodeType* root = nullptr;
	Comp comp = Comp{};

	NodeType* _small_right_rotation(NodeType* cur) {
		//     cur           b
		//     / \          / \
		//    b   R   ->   L  cur
		//   / \              / \
		//  L   C            C   R
		NodeType* b = cur->left;
		NodeType* R = cur->right;
		NodeType* L = b->left;
		NodeType* C = b->right;
		b->right = cur;
		cur->left = C;
		cur->height = Max((C ? C->height : 0), (R ? R->height : 0)) + 1;
		b->height = Max((L ? L->height : 0), cur->height) + 1;
		return b;
	}
	NodeType* _small_left_rotation(NodeType* cur) {
		//     cur           b
		//     / \          / \
		//    L   b   ->  cur  R
		//       / \      / \
		//      C   R    L   C
		NodeType* L = cur->left;
		NodeType* b = cur->right;
		NodeType* C = b->left;
		NodeType* R = b->right;
		b->left = cur;
		cur->right = C;
		cur->height = Max((L ? L->height : 0), (C ? C->height : 0)) + 1;
		b->height = Max(cur->height, (R ? R->height : 0)) + 1;
		return b;
	}
	NodeType* _big_right_rotation(NodeType* cur) {
		cur->left = _small_left_rotation(cur->left);
		return _small_right_rotation(cur);
	}
	NodeType* _big_left_rotation(NodeType* cur) {
		cur->right = _small_right_rotation(cur->right);
		return _small_left_rotation(cur);
	}
	int _get_balance(NodeType* cur) {
		return (cur->right ? cur->right->height : 0) - (cur->left ? cur->left->height : 0);
	}
	NodeType* _balance_cur(NodeType* cur) {
		int b = _get_balance(cur);
		if (b == 2) {
			int b_r = _get_balance(cur->right);
			if (b_r > 0)
				return _small_left_rotation(cur);
			else
				return _big_left_rotation(cur);
		}
		else if (b == -2) {
			int b_l = _get_balance(cur->left);
			if (b_l < 0)
				return _small_right_rotation(cur);
			else
				return _big_right_rotation(cur);
		}
		return cur;
	}
	void _balance(std::stack<NodeType*>& path, NodeType* cur) {
		while (!path.empty()) {
			NodeType* parent = path.top(); path.pop();
			if (parent->right == cur)
				parent->right = _balance_cur(cur);
			else
				parent->left = _balance_cur(cur);
			cur = parent;
		}
		root = _balance_cur(cur);
	}

public:
	AVLTree(Comp _comp = Comp{}) : comp(_comp) {}
	AVLTree(const AVLTree& _tr) : comp(_tr.comp) {
		if (_tr.root)
			root = new NodeType{ *_tr.root };
	}
	AVLTree& operator=(const AVLTree& _tr) {
		if (&_tr == this)
			return *this;
		delete root;
		if (_tr.root)
			root = new NodeType{ *_tr.root };
		else
			root = nullptr;
		comp = _tr.comp;
		return *this;
	}
	template<class Iter>
	AVLTree(Iter first, Iter last, Comp _comp = Comp{}) : comp(_comp) {
		for (; first != last; ++first) {
			insert_value(*first);
		}
	}

	void insert_value(const T& value) {
		if (root == nullptr) {
			root = new NodeType{ value };
			return;
		}
		std::stack<NodeType*> path;
		path.push(root);
		while (true) {
			if (comp(value, path.top()->value)) {
				if (path.top()->left) {
					path.push(path.top()->left);
				}
				else { // path.top()->left == nullptr
					path.top()->left = new NodeType(value);
					return _balance(path, path.top()->left);
				}
			}
			else {
				if (path.top()->right) {
					path.push(path.top()->right);
				}
				else { // path.top()->right == nullptr
					path.top()->right = new NodeType(value);
					return _balance(path, path.top()->right);
				}
			}
		}
	}

	std::vector<T> tree_data() {
		// Iterative in-order tree traversal
		std::vector<T> ret;
		NodeType* t = root;
		std::stack<NodeType*> path;
		while (!path.empty() || t != nullptr) {
			if (t != nullptr) {
				path.push(t);
				t = t->left;
			}
			else {
				t = path.top(); path.pop();
				ret.push_back(t->value);
				t = t->right;
			}
		}
		return ret;
	}
	
	~AVLTree() {
		delete root;
	}
};

#endif // !AiAS_AVLTree
