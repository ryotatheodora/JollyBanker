#include "bank.h"
#include "account.h"
#include "transaction.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

Bank::Bank()
{

}

Bank::~Bank()
{

}

void Bank::ReadTransaction()
{
	string fileName = "bank_trans_in.txt";
	ifstream fileRead(fileName);

	string readLine;

	while (getline(fileRead, readLine))
	{
		istringstream parseLine(readLine);
		char transactionType;
		parseLine >> transactionType;

		if (transactionType == 'O')
		{
			string firstName, lastName;
			int accID;
			parseLine >> accID >> lastName >> firstName;
			Transaction AddQueue(transactionType, accID, lastName, firstName);
			transaction_list_.push(AddQueue);
		}
		else if (transactionType == 'W' || transactionType == 'D')
		{
			int accID, fundID, amount;
			parseLine >> accID >> fundID >> amount;
			Transaction AddQueue(transactionType, accID, fundID, amount);
			transaction_list_.push(AddQueue);
		}
		else if (transactionType == 'T')
		{
			int accID, fundID, amount, transferAccID, transferFundID;
			parseLine >> accID >> fundID >> transferAccID >> transferFundID >> amount;
			Transaction AddQueue(transactionType, accID, fundID, transferAccID, transferFundID, amount);
			transaction_list_.push(AddQueue);
		}
		else if (transactionType == 'A')
		{
			int accID;
			parseLine >> accID;
			Transaction AddQueue(transactionType, accID);
			transaction_list_.push(AddQueue);
		}
		else if (transactionType == 'F')
		{
			int accID, fundID;
			parseLine >> accID >> fundID;
			Transaction AddQueue(transactionType, accID, fundID);
			transaction_list_.push(AddQueue);
		}
		else
			cerr << "ERROR: Unknown transaction type" << endl;
	}
	fileRead.close();
	return;
}

void Bank::Display()
{
	cout << endl << "FINAL BALANCES." << endl;
	account_list_.Display();
}

void Bank::ExecuteTransaction()
{
	while (!transaction_list_.empty())
	{
		Transaction firstTrans = transaction_list_.front();

		if (firstTrans.transactionType() == 'O')
		{
			Account* account = new Account(firstTrans.accountID(), firstTrans.lastName(), firstTrans.firstName());
			account_list_.Insert(firstTrans.accountID(), account);
		}
		else if (firstTrans.transactionType() == 'D')
		{
			int accNumber = firstTrans.accountID();
			int fundNumber = firstTrans.fundID();
			int amountAdd = firstTrans.amount();
			Account* account;
			if (account_list_.Retrieve(accNumber, account))
			{
				account->AddBalance(fundNumber, amountAdd);
				account->RecordTrans(firstTrans, fundNumber);
			}
		}
		else if (firstTrans.transactionType() == 'W')
		{
			int accNumber = firstTrans.accountID();
			int fundNumber = firstTrans.fundID();
			int amountSubtract = firstTrans.amount();
			Account* account;
			if (account_list_.Retrieve(accNumber, account))
			{
				account->DeductBalance(fundNumber, amountSubtract, firstTrans);
			}
		}
		else if (firstTrans.transactionType() == 'T')
		{
			int accNumber = firstTrans.accountID();
			int fundNumber = firstTrans.fundID();
			int transAccNum = firstTrans.transferAccountID();
			int transFundNum = firstTrans.transferFundID();
			int amount = firstTrans.amount();
			Account* to;
			Account* from;
			if (account_list_.Retrieve(accNumber, to) && account_list_.Retrieve(transAccNum, from))
			{
				if (to->DeductBalance(fundNumber, amount, firstTrans))
				{
					from->AddBalance(transFundNum, amount);
					from->RecordTrans(firstTrans, transFundNum);
				}
				else
				{
					cerr << "ERROR: not enough funds to transfer $" << amount << " from " << from->id() << " fund " << fundNumber << " to " << to->id() << " fund " << transFundNum << endl;
					Transaction AddHistory('T', accNumber, fundNumber, transAccNum, transFundNum, amount, "FAILED");
					from->RecordTrans(AddHistory, transFundNum);
				}
			}
		}
		else if (firstTrans.transactionType() == 'A')
		{
			Account* account;
			int accNumSearch = firstTrans.accountID();
			if (account_list_.Retrieve(accNumSearch, account))
			{
				account->PrintTransaction();
				cout << endl;
			}
		}
		else if (firstTrans.transactionType() == 'F')
		{
			Account* account;
			int fundNum = firstTrans.fundID();
			int accNumSearch = firstTrans.accountID();
			if (account_list_.Retrieve(accNumSearch, account))
			{
				account->PrintFund(fundNum);
				cout << endl;
			}
		}
		transaction_list_.pop();
	}
}