#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <string>
using namespace std;

class Transaction
{
public:
	Transaction();
	~Transaction();

	// Transaction types repectively: O, D/W, T, A, F
	Transaction(char type, int accountNumber, string firstName, string lastName);
	Transaction(char type, int accountNumber, int fundNumber, int amount);
	Transaction(char type, int accountNumber, int fundNumber, int transferAccountNumber, int transferFundNumber, int amount);
	Transaction(char type, int accountNumber);
	Transaction(char type, int accountNumber, int fundNumber);

	//These Construtors create a transaction that failed to process
	Transaction(char type, int accountNumber, int fundNumber, int transferAccountNumber, int transferFundNumber, int amount, string failString);
	Transaction(char type, int accountNumber, int fundNumber, string fail, int amount);

	char transactionType() const;
	string firstName() const;
	string lastName() const;
	int accountID() const;
	int fundID() const;
	int transferFundID() const;
	int transferAccountID() const;
	int amount() const;
	bool IsFail();

	friend ostream& operator<<(ostream& out, const Transaction& trans);

private:
	int acc_id_ = 0;
	int fund_id_ = 0;
	int transfer_acc_id_ = 0;
	int transfer_fund_id_ = 0;
	int amount_ = 0;
	string first_name_;
	string last_name_;
	string fail_;
	char transaction_type_;
};

#endif