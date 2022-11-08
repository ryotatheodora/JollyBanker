#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
#include <iostream>
#include <vector>
#include "transaction.h"
#include "fund.h"

using namespace std;

const int kFund_Max = 8;
const int kMoney_Market = 0;
const int kPrime_Money_Market = 1;
const int kLong_Term_Bond = 2;
const int kShort_Term_Bond = 3;

class Account
{
public:
	Account();
	Account(int accountId, string firstName, string lastName);
	~Account();

	void AddBalance(int fundNumber, int amount);
	bool DeductBalance(int fundNumber, int amount, Transaction trans);
	void RecordTrans(Transaction tr, int fundNumber);
	void SimilarAccount(int firstFund, int secondFund, int amount);
	void PrintTransaction();
	void PrintFund(int fundNumber);
	void Error(int amount, string firstName, string lastName, int fundNumber);

	int id() const;
	int balance(int fundNumber) const;
	string fundName(int fundNumber);
	string firstName() const;
	string lastName() const;

	void setFundId(int fundNumber);

	friend ostream& operator<<(ostream& out, Account& acc);

private:
	int account_id_;
	int fund_id_;
	string first_name_;
	string last_name_;
	Fund arrayFund[kFund_Max];
};


#endif