// ************************************************************************** //
//                                                                            //
//                tests.cpp for GlobalBanksters United                        //
//                Created on  : Thu Nov 20 23:45:02 1989                      //
//                Last update : Wed Jan 04 09:23:52 1992                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //

#include <vector>
#include <algorithm>
#include <functional>
#include "Account.hpp"


int main(void)
{
	// tests
	Account		*acc1 = new Account(1000);
	Account		*acc2 = new Account(2000);
	Account		*acc3 = new Account(3000);
	Account		*acc4 = new Account(4000);
	Account		*acc5 = new Account(5000);
	Account		*acc6 = new Account(6000);
	Account		*acc7 = new Account(7000);
	Account		*acc8 = new Account(8000);

	Account::displayAccountsInfos();

	acc1->displayStatus();
	acc2->displayStatus();
	acc3->displayStatus();
	acc4->displayStatus();
	acc5->displayStatus();
	acc6->displayStatus();
	acc7->displayStatus();
	acc8->displayStatus();

	acc1->makeDeposit(100);	
	acc2->makeDeposit(200);
	acc3->makeDeposit(300);
	acc4->makeDeposit(400);
	acc5->makeDeposit(500);
	acc6->makeDeposit(600);
	acc7->makeDeposit(700);
	acc8->makeDeposit(800);
	
	Account::displayAccountsInfos();

	acc1->displayStatus();
	acc2->displayStatus();
	acc3->displayStatus();
	acc4->displayStatus();
	acc5->displayStatus();
	acc6->displayStatus();
	acc7->displayStatus();
	acc8->displayStatus();

	acc1->makeWithdrawal(100);
	acc2->makeWithdrawal(200);
	acc3->makeWithdrawal(300);
	acc4->makeWithdrawal(400);
	acc5->makeWithdrawal(500);
	acc6->makeWithdrawal(600);
	acc7->makeWithdrawal(700);
	acc8->makeWithdrawal(800);

	Account::displayAccountsInfos();

	acc1->displayStatus();
	acc2->displayStatus();
	acc3->displayStatus();
	acc4->displayStatus();
	acc5->displayStatus();
	acc6->displayStatus();
	acc7->displayStatus();
	acc8->displayStatus();

	delete acc1;
	delete acc2;
	delete acc3;
	delete acc4;
	delete acc5;
	delete acc6;
	delete acc7;
	delete acc8;

	return (0);
}
