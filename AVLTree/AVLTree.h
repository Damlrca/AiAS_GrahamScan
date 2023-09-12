#ifndef AiAS_AVLTree
#define AiAS_AVLTree
#include "Utils.h"
#include <vector>
#include <stack>

template<class T>
struct Node {
	Node* left = nullptr;
	Node* right = nullptr;
	int height = 0;
	T value;
	Node(const T& _val) : value{ _val } {}
	Node(const T& _val, Node* _left, Node* _right) :
		value{ _val }, left{ _left }, right{ _right } {
		if (left /*&& left->height + 1 > height*/) // commented expression is always true
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
		NodeType* l = cur->left;
		NodeType* A = l->left;
		NodeType* B = l->right;
		NodeType* C = cur->right;

		l->left = A;
		l->right = cur;
		cur->left = B;
		cur->right = C;

		int temp = 0;
		if (B) temp = B->height;
		if (C) temp = std::max(temp, C->height);
		cur->height = temp + 1;
		temp = cur->height;
		if (A) temp = std::max(temp, A->height);
		l->height = temp + 1;

		return l;
	}
	NodeType* _small_left_rotation(NodeType* cur) {
		NodeType* r = cur->right;
		NodeType* A = cur->left;
		NodeType* B = r->left;
		NodeType* C = r->right;

		r->left = cur;
		r->right = C;
		cur->left = A;
		cur->right = B;

		int temp = 0;
		if (A) temp = A->height;
		if (B) temp = std::max(temp, B->height);
		cur->height = temp + 1;
		temp = cur->height;
		if (C) temp = std::max(temp, C->height);
		r->height = temp + 1;

		return r;
	}
	NodeType* _big_right_rotation(NodeType* cur) {
		cur->left = _small_left_rotation(cur->left);
		return _small_right_rotation(cur);
	}
	NodeType* _big_left_rotation(NodeType* cur) {
		cur->right = _small_right_rotation(cur->right);
		return _small_left_rotation(cur);
	}
	int get_balance(NodeType* cur) {
		int left_h = cur->left ? cur->left->height : 0;
		int right_h = cur->right ? cur->right->height : 0;
		return right_h - left_h;
	}
	
	void balance(std::stack<NodeType*>& path, NodeType* cur) {
		while (!path.empty()) {
			NodeType* parent = path.top(); path.pop();
			int b = get_balance(cur);
			NodeType* tmp = cur;
			if (b == 2) {
				int b_r = get_balance(cur->right);
				if (b_r > 0)
					tmp = _small_left_rotation(cur);
				else
					tmp = _big_left_rotation(cur);
			}
			else if (b == -2) {
				int b_l = get_balance(cur->left);
				if (b_l < 0)
					tmp = _small_right_rotation(cur);
				else
					tmp = _big_right_rotation(cur);
			}
			if (parent->right == cur)
				parent->right = tmp;
			else
				parent->left = tmp;
			cur = parent;
		}

		int b = get_balance(root);
		if (b == 2) {
			int b_r = get_balance(root->right);
			if (b_r > 0)
				root = _small_left_rotation(root);
			else
				root = _big_left_rotation(root);
		}
		else if (b == -2) {
			int b_l = get_balance(root->left);
			if (b_l < 0)
				root = _small_right_rotation(root);
			else
				root = _big_right_rotation(root);
		}
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
				else {
					path.top()->left = new NodeType(value);
					balance(path, path.top()->left);
					return;
				}
			}
			else {
				if (path.top()->right) {
					path.push(path.top()->right);
				}
				else {
					path.top()->right = new NodeType(value);
					balance(path, path.top()->right);
					return;
				}
			}
		}
	}
	std::vector<T> tree_data() {
		std::vector<T> ret;
		stack<NodeType*> s;
		NodeType* t = root;
		while (!s.empty() || t != nullptr) {
			if (t != nullptr) {
				s.push(t);
				t = t->left;
			}
			else {
				t = s.top(); s.pop();
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
