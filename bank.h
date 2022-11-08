#ifndef BANK_H_
#define BANK_H_

#include "bst.h"
#include "transaction.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Bank
{
public:
	Bank();
	~Bank();

	void ReadTransaction();
	void Display();
	void ExecuteTransaction();

private:
	BST account_list_;
	queue<Transaction> transaction_list_;
};

#endif