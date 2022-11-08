#include "bst.h"

BST::BST()
{
	root = NULL;
}

BST::~BST()
{
	Clear();
}

bool BST::Insert(int accID, Account* insert)
{
	if (root == NULL)
	{
		root = new Node;
		root->p_account = insert;
		root->left = NULL;
		root->right = NULL;
		return true;
	}
	else
	{
		Node* curr = root;
		RecursiveInsert(curr, insert);
	}
	return false;
}

bool BST::Retrieve(int accID, Account*& acc) const
{
	Node* curr = root;
	bool found = false;

	while (!found)
	{
		if (curr != NULL && accID == curr->p_account->id())
		{
			found = true;
			acc = curr->p_account;
			return found;
		}
		else if (curr != NULL && accID > curr->p_account->id())
		{
			curr = curr->right;
		}
		else if (curr != NULL && accID < curr->p_account->id())
		{
			curr = curr->left;
		}
		else
			found = true;
	}
	cerr << "ERROR: Account with number ( " << accID << " ) cannot be found" << endl;
	return false;
}

void BST::Display() const
{
	if (IsEmpty())
	{
		cerr << "ERROR: List is empty" << endl;
	}
	RecursivePrint(root);
}

void BST::Clear()
{
	if (IsEmpty())
	{
		return;
	}
	delete root;
	root = NULL;
}

bool BST::IsEmpty() const
{
	if (root == NULL)
	{
		return true;
	}
	return false;
}

bool BST::RecursiveInsert(Node* curr, Account* acc)
{
	if (acc->id() > curr->p_account->id())
	{
		if (curr->right == NULL)
		{
			Node* insert = new Node();
			{
				insert->p_account = acc;
				insert->left = NULL;
				insert->right = NULL;
				curr->right = insert;
				return true;
			}
		}
		else
			return RecursiveInsert(curr->right, acc);
	}
	else if (acc->id() < curr->p_account->id())
	{
		if (curr->left == NULL)
		{
			Node* insert = new Node();
			insert->p_account = acc;
			insert->left = NULL;
			insert->right = NULL;
			curr->left = insert;
			return true;
		}
		else
			return RecursiveInsert(curr->left, acc);
	}
	cerr << "ERROR: Account " << acc->id() << " is already open. Transaction denied." << endl;
	return false;
}

void BST::RecursivePrint(Node* curr) const
{
	if (curr == NULL)
	{
		return;
	}
	if (curr->right != NULL && curr->left != NULL)
	{
		RecursivePrint(curr->left);
		cout << *curr->p_account << endl;
		RecursivePrint(curr->right);
	}
	else if (curr->left != NULL)
	{
		RecursivePrint(curr->left);
		cout << *curr->p_account << endl;
	}
	else if (curr->right != NULL)
	{
		cout << *curr->p_account << endl;
		RecursivePrint(curr->right);
	}
	else
	{
		cout << *curr->p_account << endl;
	}
}