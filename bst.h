#ifndef BST_H_
#define BST_H_

#include "account.h"
#include <iostream>
using namespace std;

class BST
{
public:
	BST();
	~BST();

	bool Insert(int acc_id, Account* account);

	bool Retrieve(int acc_id, Account*& acc) const;

	bool IsEmpty() const;
	void Clear();
	void Display() const;
	
private:
	struct Node
	{
		int acc_id_;
		Account* p_account;
		Node* left;
		Node* right;
	};
	Node* root;
	bool RecursiveInsert(Node* curr, Account* insert);
	void RecursivePrint(Node* printNode) const;
};

#endif