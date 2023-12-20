#include <iostream>
#include <string>
#include <time.h>
#include <math.h> 

template<typename T>
struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
};

template <typename T>
struct Tree {
	Node<T>* root;
	int size = 0;
	Node<T>* insert(Node<T>* node,T data) {
		if (node == nullptr)
		{
			size = size + 1;
			node = new Node<T>;
			node->data = data;
			node->left = nullptr;
			node->right = nullptr;
			node->parent = nullptr;
			root = node;
		}
		else if (node->data < data)
		{
			node->right = insert(node->right, data);
			node->right->parent = node;
			root = node;
		}
		else
		{
			node->left = insert(node->left, data);
			node->left->parent = node;
			root = node;
		}
		return node;
	}

	Node<T>* search(Node<T>* node,T data) {
		if (node = nullptr) {
			return nullptr;
		}
		else if (node->data == data) {
			return node;
		}
		else if (node->data < data) {
			return search(node->right, data);
		}
		else {
			return search(node->left, data);
		}
	}
	
	void clear(Node<T>* node) {
		if (node == nullptr) {
			return;
		}
		clear(node->right);
		clear(node->left);
		delete node;
		root = nullptr;
	}

	int heightsize(Node<T>* node) {
		int heightleft, heightright;
		if (node == nullptr) {
			return 0;
		}
		else {
			heightleft = heightsize(node->left);
			heightright = heightsize(node-> right);
		}
		if (heightleft > heightright) {
			return heightleft+1;
		}
		else if (heightleft <= heightright) {
			return heightright+1;
		}
		return 0;
	}
};

int main()
{
	Tree<int>*tree = new Tree<int>{};
	srand(time(NULL));
	clock_t a1 = clock();
	for (int i = 1; i <= 10; i++) {
		tree->insert(tree->root, rand());
	}
	clock_t a2 = clock();
	double addtime = (a2 - a1)/(double)CLOCKS_PER_SEC;
	std::cout << "Czas dodawania elementow: " << addtime << "s" << std::endl;
	std::cout <<"wysokosc drzewa: "<< tree->heightsize(tree->root) << std::endl;
	//tree->deleteNode(tree->root,88);
	std::cout <<"ilosc elementow: "<< tree->size <<std::endl;
	std::cout << "stosunek danych do wysokosci drzewa: " << (tree->heightsize(tree->root)) / (double)  (tree->size) << std::endl;
	std::cout <<"log2 z rozmiaru danych: " << log2(tree->size) << std::endl;
	std::cout << "stosunek wysokosci drzewa do log z rozmiaru danych: " << (tree->heightsize(tree->root)) / (log2(tree->size)) << std::endl;
	//tree->clear(tree->root);
	//std::cout << tree->heightsize(tree->root) << std::endl;
	//std::cout << tree->search(tree->root,15);
	//Node<int>* node = tree->search(tree->root,15);
	//std::cout << node->data;
	
	return 0;
}
