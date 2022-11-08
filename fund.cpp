#include "fund.h"

Fund::Fund()
{
	balance_ = 0;
	fund_name_ = "";
}

Fund::~Fund()
{

}

bool Fund::Add(int amount)
{
	balance_ += amount;
	return true;
}

bool Fund::Deduct(int amount)
{
	balance_ -= amount;
	return true;
}

bool Fund::CheckBalance(int amount)
{
	if (balance_ >= amount)
	{
		return true;
	}
	return false;
}

bool Fund::RecordTransaction(Transaction trans)
{
	history_.push_back(trans);
	return true;
}

void Fund::DisplayHistory()
{
	if (history_.size() == 0)
	{
		return;
	}
	cout << fund_name_ << ": $ " << balance() << endl;
	for (int i = 0; i < history_.size(); i++)
	{
		cout << " " << history_[i];
	}
}

void Fund::DisplayFundHistory()
{
	for (int i = 0; i < history_.size(); i++)
	{
		cout << " " << history_[i];
	}
}

void Fund::setName(string name)
{
	this->fund_name_ = name;
}

int Fund::balance() const
{
	return balance_;
}

string Fund::name() const
{
	return fund_name_;
}