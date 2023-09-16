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

	int _height(NodeType* cur) {
		return cur ? cur->height : 0;
	}
	int _get_balance(NodeType* cur) {
		return _height(cur->right) - _height(cur->left);
	}
	NodeType* _small_right_rotation(NodeType* cur) {
		//     cur           b
		//     / \          / \
		//    b   R   ->   L  cur
		//   / \              / \
		//  L   C            C   R
		NodeType* b = cur->left;
		cur->left = b->right;
		b->right = cur;
		cur->height = Max(_height(cur->left), _height(cur->right)) + 1;
		b->height = Max(_height(b->left), _height(b->right)) + 1;
		return b;
	}
	NodeType* _small_left_rotation(NodeType* cur) {
		//     cur           b
		//     / \          / \
		//    L   b   ->  cur  R
		//       / \      / \
		//      C   R    L   C
		NodeType* b = cur->right;
		cur->right = b->left;
		b->left = cur;
		cur->height = Max(_height(cur->left), _height(cur->right)) + 1;
		b->height = Max(_height(b->left), _height(b->right)) + 1;
		return b;
	}
	NodeType* _balance_cur(NodeType* cur) {
		cur->height = Max(_height(cur->left), _height(cur->right)) + 1;
		int b = _get_balance(cur);
		if (b == 2) {
			if (_get_balance(cur->right) < 0)
				cur->right = _small_right_rotation(cur->right);
			return _small_left_rotation(cur);
		}
		else if (b == -2) {
			if (_get_balance(cur->left) > 0)
				cur->left = _small_left_rotation(cur->left);
			return _small_right_rotation(cur);
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
			insert(*first);
		}
	}

	void insert(const T& value) {
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

	bool find(const T& t) {
		NodeType* r = root;
		while (r != nullptr) {
			if (r->value == t)
				return true;
			if (comp(t, r->value))
				r = r->left;
			else
				r = r->right;
		}
		return false;
	}

	void remove(const T& t) {
		std::stack<NodeType*> path;
		path.push(root);
		NodeType* found = nullptr;
		while (true) {
			if (path.top() == nullptr) {
				return;
			}
			if (path.top()->value == t) {
				found = path.top();
				break;
			}
			if (comp(t, path.top()->value))
				path.push(path.top()->left);
			else
				path.push(path.top()->right);
		}
		if (found->right == nullptr) {
			NodeType* temp = found->left;
			path.pop();
			if (path.empty()) { // found == root
				root = temp;
			}
			else {
				if (path.top()->left == found)
					path.top()->left = temp;
				else // path.top()->right == found
					path.top()->right = temp;
			}
			if (temp == nullptr && !path.empty()) {
				temp = path.top(); path.pop();
			}
			if (temp) {
				_balance(path, temp);
			}
			found->left = nullptr;
			found->right = nullptr;
			delete found;
		}
		else {
			NodeType* m = found->right;
			while (m->left) {
				path.push(m);
				m = m->left;
			}
			Swap(found->value, m->value);
			NodeType* temp = m->right;
			if (path.top()->left == m)
				path.top()->left = temp;
			else // path.top()->right == m
				path.top()->right = temp;
			temp = path.top(); path.pop();
			_balance(path, temp);
			m->left = nullptr;
			m->right = nullptr;
			delete m;
		}
	}

	std::vector<T> data() {
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
