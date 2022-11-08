#ifndef FUND_H_
#define FUND_H_

#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Fund
{
public:
	Fund();
	~Fund();

	bool Add(int amount);
	bool Deduct(int amount);
	bool CheckBalance(int amount);
	bool RecordTransaction(Transaction tr);

	void DisplayFundHistory();
	void DisplayHistory();
	
	int balance() const;
	string name() const;

	void setName(string name);
private:
	int balance_;
	string fund_name_;
	vector<Transaction> history_;
};

#endif