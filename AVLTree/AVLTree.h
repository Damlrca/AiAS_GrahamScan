#ifndef AiAS_AVLTree
#define AiAS_AVLTree
#include "Utils.h"
#include <vector>
#include <type_traits>

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
	std::vector<NodeType*> path;

	int _height(NodeType* cur) {
		return cur ? cur->height : 0;
	}
	int _get_balance(NodeType* cur) {
		return _height(cur->right) - _height(cur->left);
	}
	void _fix_height(NodeType* cur) {
		int h_left = _height(cur->left);
		int h_right = _height(cur->right);
		cur->height = 1 + (h_right > h_left ? h_right : h_left);
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
		_fix_height(cur);
		_fix_height(b);
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
		_fix_height(cur);
		_fix_height(b);
		return b;
	}
	NodeType* _balance_cur(NodeType* cur) {
		_fix_height(cur);
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
	void _balance(NodeType* cur) { // need path !!!
		while (!path.empty()) {
			NodeType* parent = path.back(); path.pop_back();
			if (parent->right == cur)
				parent->right = _balance_cur(cur);
			else
				parent->left = _balance_cur(cur);
			cur = parent;
		}
		root = _balance_cur(cur);
	}
	void _inserter_recursive(NodeType* cur, const T& value) {
		if (comp(value, cur->value)) {
			if (cur->left)
				_inserter_recursive(cur->left, value);
			else
				cur->left = new NodeType(value);
			cur->left = _balance_cur(cur->left);
		}
		else {
			if (cur->right)
				_inserter_recursive(cur->right, value);
			else
				cur->right = new NodeType(value);
			cur->right = _balance_cur(cur->right);
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
			insert(*first);
		}
	}

	void insert(const T& value) {
		path.clear();
		if (root == nullptr) {
			root = new NodeType{ value };
			return;
		}
		path.push_back(root);
		while (true) {
			if (comp(value, path.back()->value)) {
				if (path.back()->left) {
					path.push_back(path.back()->left);
				}
				else { // path.top()->left == nullptr
					path.back()->left = new NodeType(value);
					return _balance(path.back()->left);
				}
			}
			else {
				if (path.back()->right) {
					path.push_back(path.back()->right);
				}
				else { // path.top()->right == nullptr
					path.back()->right = new NodeType(value);
					return _balance(path.back()->right);
				}
			}
		}
	}

	void insert_recursive(const T& value) {
		if (root == nullptr) {
			root = new NodeType{ value };
			return;
		}
		_inserter_recursive(root, value);
		root = _balance_cur(root);
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
		path.clear();
		path.push_back(root);
		NodeType* found = nullptr;
		while (true) {
			if (path.back() == nullptr)
				return;
			if (path.back()->value == t) {
				found = path.back();
				break;
			}
			if (comp(t, path.back()->value))
				path.push_back(path.back()->left);
			else
				path.push_back(path.back()->right);
		}
		if (found->right == nullptr) {
			NodeType* temp = found->left;
			path.pop_back();
			if (path.empty()) { // found == root
				root = temp;
			}
			else {
				if (path.back()->left == found)
					path.back()->left = temp;
				else // path.back()->right == found
					path.back()->right = temp;
			}
			if (temp == nullptr && !path.empty()) {
				temp = path.back(); path.pop_back();
			}
			if (temp) {
				_balance(temp);
			}
			found->left = nullptr;
			found->right = nullptr;
			delete found;
		}
		else {
			NodeType* m = found->right;
			while (m->left) {
				path.push_back(m);
				m = m->left;
			}
			Swap(found->value, m->value);
			NodeType* temp = m->right;
			if (path.back()->left == m)
				path.back()->left = temp;
			else // path.back()->right == m
				path.back()->right = temp;
			temp = path.back(); path.pop_back();
			_balance(temp);
			m->left = nullptr;
			m->right = nullptr;
			delete m;
		}
	}

	std::vector<T> data() {
		// Iterative in-order tree traversal
		std::vector<T> ret;
		NodeType* t = root;
		std::vector<NodeType*> path;
		while (!path.empty() || t != nullptr) {
			if (t != nullptr) {
				path.push_back(t);
				t = t->left;
			}
			else {
				t = path.back(); path.pop_back();
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

template<class Iter, class Comp = Less<>>
void AVLTreeSort(Iter first, Iter last, Comp comp = Comp{}) {
	AVLTree<std::remove_reference<decltype(*first)>::type> tree(comp);
	for (Iter i = first; i != last; ++i)
		tree.insert(*i);
	auto v = tree.data();
	auto temp = v.begin();
	for (Iter i = first; i != last; ++i, ++temp)
		*i = *temp;
}

template<class Iter, class Comp = Less<>>
void AVLTreeSort_recursive(Iter first, Iter last, Comp comp = Comp{}) {
	AVLTree<std::remove_reference<decltype(*first)>::type> tree(comp);
	for (Iter i = first; i != last; ++i)
		tree.insert_recursive(*i);
	auto v = tree.data();
	auto temp = v.begin();
	for (Iter i = first; i != last; ++i, ++temp)
		*i = *temp;
}

#endif // !AiAS_AVLTree
