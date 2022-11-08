#include "account.h"

Account::Account() :first_name_(""), last_name_(""), account_id_(0), fund_id_(0)
{
}

Account::Account(int accountId, string firstName, string lastName)
{
	this->first_name_ = firstName;
	this->last_name_ = lastName;
	this->account_id_ = accountId;
	string fundNames[] = {
		"Money Market",
		"Prime Money Market",
		"Long-Term Bond",
		"Short-Term Bond",
		"500 Index Fund",
		"Capital Value Fund",
		"Growth Equity Fund",
		"Growth Index Fund"
	};
	for (int i = 0; i < 8; i++)
	{
		arrayFund[i].setName(fundNames[i]);
	}
}

Account::~Account()
{
}

int Account::id() const
{
	return account_id_;
}

void Account::AddBalance(int fundNumber, int amount)
{
	arrayFund[fundNumber].Add(amount);
}

void Account::SimilarAccount(int firstFund, int secondFund, int amount)
{
	if ((arrayFund[firstFund].balance() + arrayFund[secondFund].balance()) >= amount)
	{
		int balance_available = arrayFund[firstFund].balance();
		arrayFund[firstFund].Deduct(balance_available);
		Transaction addHistory('W', id(), firstFund, balance_available);
		arrayFund[firstFund].RecordTransaction(addHistory);
		amount = amount - balance_available;

		arrayFund[secondFund].Deduct(amount);
		Transaction addHistory2('W', id(), secondFund, amount);
		arrayFund[secondFund].RecordTransaction(addHistory2);
	}
	else
	{
		int balance_available = arrayFund[firstFund].balance();
		if (balance_available > amount)
		{
			arrayFund[firstFund].Deduct(balance_available);
			Transaction addHistory('W', id(), firstFund, balance_available);
			arrayFund[firstFund].RecordTransaction(addHistory);
			amount = amount - balance_available;
		}

		if (arrayFund[secondFund].CheckBalance(amount))
		{
			arrayFund[secondFund].Deduct(amount);
			Transaction addHistory('W', id(), secondFund, amount);
			arrayFund[secondFund].RecordTransaction(addHistory);
		}
		else
		{
			cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << firstName() << " " << lastName() << " " << fundName(secondFund) << endl;
			Transaction addHistory('W', id(), secondFund, "FAILED", amount);
			arrayFund[secondFund].RecordTransaction(addHistory);
		}
	}
}

bool Account::DeductBalance(int fundNumber, int amount, Transaction trans)
{
	if (fundNumber == kMoney_Market || fundNumber == kPrime_Money_Market || fundNumber == kLong_Term_Bond || fundNumber == kShort_Term_Bond)
	{
		if (fundNumber == kMoney_Market || fundNumber == kPrime_Money_Market)
		{
			if (arrayFund[fundNumber].CheckBalance(amount))
			{
				arrayFund[fundNumber].Deduct(amount);
				arrayFund[fundNumber].RecordTransaction(trans);
				return true;
			}
			else if (((arrayFund[kMoney_Market].balance() + arrayFund[kPrime_Money_Market].balance()) >= amount))
			{
				if (fundNumber == kMoney_Market)
				{
					SimilarAccount(kMoney_Market, kPrime_Money_Market, amount);
				}
				else
				{
					SimilarAccount(kPrime_Money_Market, kMoney_Market, amount);
				}
			}
			else
			{
				Error(amount, firstName(), lastName(), fundNumber);
				if (fundNumber == kMoney_Market)
				{
					SimilarAccount(kMoney_Market, kPrime_Money_Market, amount);
				}
				else
				{
					SimilarAccount(kPrime_Money_Market, kMoney_Market, amount);
				}
				return false;
			}
		}
		else if (fundNumber == kLong_Term_Bond|| fundNumber == kShort_Term_Bond)
		{
			if (arrayFund[fundNumber].CheckBalance(amount))
			{
				arrayFund[fundNumber].Deduct(amount);
				arrayFund[fundNumber].RecordTransaction(trans);
				return true;
			}
			else if (((arrayFund[kLong_Term_Bond].balance() + arrayFund[kShort_Term_Bond].balance()) >= amount))
			{
				if (fundNumber == kLong_Term_Bond)
				{
					SimilarAccount(kLong_Term_Bond, kShort_Term_Bond, amount);
				}
				else
				{
					SimilarAccount(kShort_Term_Bond, kLong_Term_Bond, amount);
				}
			}
			else
			{
				Error(amount, firstName(), lastName(), fundNumber);
				if (fundNumber == kLong_Term_Bond)
				{
					SimilarAccount(kLong_Term_Bond, kShort_Term_Bond, amount);
				}
				else
				{
					SimilarAccount(kShort_Term_Bond, kLong_Term_Bond, amount);
				}
				return false;
			}
		}
	}
	else
	{
		if (arrayFund[fundNumber].CheckBalance(amount))
		{
			arrayFund[fundNumber].Deduct(amount);
			arrayFund[fundNumber].RecordTransaction(trans);
			return true;
		}
		else
		{
			Error(amount, firstName(), lastName(), fundNumber);
			return false;
		}
	}
	return false;
}

void::Account::Error(int amount, string firstName, string lastName, int fundNumber)
{
	cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << firstName << " " << lastName << " " << fundName(fundNumber) << endl;
	Transaction AddHistory('W', id(), fundNumber, "FAILED", amount);
	arrayFund[fundNumber].RecordTransaction(AddHistory);
}

void Account::RecordTrans(Transaction tr, int fundNumber)
{
	arrayFund[fundNumber].RecordTransaction(tr);
}

void Account::PrintTransaction()
{
	cout << endl << "Transaction History for " << firstName() << " " << lastName() << " by Fund:" << endl;
	for (int i = 0; i < 8; i++)
	{
		arrayFund[i].DisplayHistory();
	}
}

void Account::PrintFund(int fundId)
{
	cout << "Transaction history for " << firstName() << " " << lastName() << " " << fundName(fundId) << " $ " << balance(fundId) << endl;
	arrayFund[fundId].DisplayFundHistory();
}

void Account::setFundId(int fundNumber)
{
	this->fund_id_ = fundNumber;
}

int Account::balance(int fundNumber) const
{
	return arrayFund[fundNumber].balance();
}

string Account::fundName(int fundNumber)
{
	return arrayFund[fundNumber].name();
}

string Account::firstName() const
{
	return first_name_;
}

string Account::lastName() const
{
	return last_name_;
}

ostream& operator<<(ostream& out, Account& acc)
{
	out << acc.firstName() << " " << acc.lastName() << " ID: " << acc.id() << endl;
	for (int i = 0; i < 8; i++)
	{
		out << " " << acc.fundName(i) << ": $ " << acc.balance(i) << endl;
	}
	return out;
}