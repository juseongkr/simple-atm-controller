#include <iostream>
#include "Account.h"
#include "Factory.h"
#include "Card.h"
#include "Atm.h"

#include "AtmTest.h"

bool runTest()
{
	{
		AtmTest *test = new AtmTest();
		assert(test->createCardTest());
		std::cout << "createCardTest() passed" << std::endl;
		delete test;
	}

	{
		AtmTest *test = new AtmTest();
		assert(test->getCardTest());
		std::cout << "getCardTest() passed" << std::endl;
		delete test;
	}

	{
		AtmTest *test = new AtmTest();
		assert(test->createAccountTest());
		std::cout << "createAccountTest() passed" << std::endl;
		delete test;
	}

	{
		AtmTest *test = new AtmTest();
		assert(test->selectAccountTest());
		std::cout << "selectAccountTest() passed" << std::endl;
		delete test;
	}
	
	{
		AtmTest *test = new AtmTest();
		assert(test->getBalanceTest());
		std::cout << "getBalanceTest() passed" << std::endl;
		delete test;
	}

	{
		AtmTest *test = new AtmTest();
		assert(test->depositTest());
		std::cout << "depositTest() passed" << std::endl;
		delete test;
	}

	{
		AtmTest *test = new AtmTest();
		assert(test->withdrawTest());
		std::cout << "withdrawTest() passed" << std::endl;
		delete test;
	}

	return true;
}

int main(int argc, char *argv[])
{
	if (runTest())
		std::cout << "all tests passed" << std::endl << std::endl;

	Atm *atm = new Atm();
	atm->run();

	delete atm;

	return 0;
}
