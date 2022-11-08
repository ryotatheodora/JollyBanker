#include "transaction.h"

Transaction::Transaction()
{
	transaction_type_ = 0;
}

Transaction::~Transaction()
{
}

Transaction::Transaction(char type, int accountNumber, string firstName, string lastName)
{
	this->transaction_type_ = type;
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->acc_id_ = accountNumber;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber, int amount)
{
	this->transaction_type_ = type;
	this->acc_id_ = accountNumber;
	this->fund_id_ = fundNumber;
	this->amount_ = amount;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber, string failString, int amount)
{
	this->transaction_type_ = type;
	this->acc_id_ = accountNumber;
	this->fund_id_ = fundNumber;
	this->amount_ = amount;
	this->fail_ = failString;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber, int transferAccountNumber, int transferFundNumber, int amount)
{
	this->transaction_type_ = type;
	this->acc_id_ = accountNumber;
	this->fund_id_ = fundNumber;
	this->amount_ = amount;
	this->transfer_acc_id_ = transferAccountNumber;
	this->transfer_fund_id_ = transferFundNumber;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber, int transferAccountNumber, int transferFundNumber, int amount, string failString)
{
	this->transaction_type_ = type;
	this->acc_id_ = accountNumber;
	this->fund_id_ = fundNumber;
	this->amount_ = amount;
	this->transfer_acc_id_ = transferAccountNumber;
	this->transfer_fund_id_ = transferFundNumber;
	this->fail_ = failString;
}

Transaction::Transaction(char type, int accountNumber)
{
	this->transaction_type_ = type;
	this->acc_id_ = accountNumber;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber)
{
	this->transaction_type_ = type;
	this->acc_id_ = accountNumber;
	this->fund_id_ = fundNumber;
}

bool Transaction::IsFail()
{
	if (fail_.empty())
	{
		return true;
	}
	return false;
}

char Transaction::transactionType() const
{
	return transaction_type_;
}

string Transaction::firstName() const
{
	return first_name_;
}

string Transaction::lastName() const
{
	return last_name_;
}

int Transaction::accountID() const
{
	return acc_id_;
}

int Transaction::amount() const
{
	return amount_;
}

int Transaction::fundID() const
{
	return fund_id_;
}

int Transaction::transferAccountID() const
{
	return transfer_acc_id_;
}

int Transaction::transferFundID() const
{
	return transfer_fund_id_;
}

ostream& operator<<(ostream& out, const Transaction& trans)
{
	if (trans.fail_.empty())
	{
		if (trans.transactionType() == 'D' || trans.transactionType() == 'd' || trans.transactionType() == 'W' || trans.transactionType() == 'w')
		{
			out << " " << trans.transactionType() << " " << trans.accountID() << trans.fundID() << " " << trans.amount();
		}
		else if (trans.transactionType() == 'T' || trans.transactionType() == 't')
		{
			out << " " << trans.transactionType() << " " << trans.accountID() << trans.fundID() << " " << trans.amount() << " " << trans.transferAccountID() << trans.transferFundID();
		}
		else
		{

		}
	}
	else
	{
		if (trans.transactionType() == 'D' || trans.transactionType() == 'd' || trans.transactionType() == 'W' || trans.transactionType() == 'w')
		{
			out << " " << trans.transactionType() << " " << trans.accountID() << trans.fundID() << " " << trans.amount() << " (FAILED)";
		}
		else if (trans.transactionType() == 'T' || trans.transactionType() == 't')
		{
			out << " " << trans.transactionType() << " " << trans.accountID() << trans.fundID() << " " << trans.amount() << " " << trans.transferAccountID() << trans.transferFundID() << "(FAILED)";
		}
	}
	return out << endl;
}