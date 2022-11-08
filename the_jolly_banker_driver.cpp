#include "account.h"
#include "bank.h"
#include "bst.h"
#include "fund.h"
#include "transaction.h"

int main() {
	Bank jolly_bank;
	jolly_bank.ReadTransaction();
	jolly_bank.ExecuteTransaction();
	jolly_bank.Display();
}