#ifndef __ATM_TEST_H__
#define __ATM_TEST_H__

#include "Atm.h"
#include <cassert>
#include <random>

class Test {
public:
	std::string generateRandomStr() {
		std::string base("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(base.begin(), base.end(), generator);

		return base.substr(0, 32);
	}
};

class AtmTest : public Test {
private:
	Atm *atm;

public:
	AtmTest() {
		this->atm = new Atm();
	}

	bool createCardTest() {
		std::string name = this->generateRandomStr();
		std::string pin = this->generateRandomStr();
		std::string id;

		id = this->atm->createCard(name, pin);

		if (id.length() == 0)
			return false;

		return true;
	}

	bool getCardTest() {
		std::string name = this->generateRandomStr();
		std::string pin = this->generateRandomStr();
		std::string id;

		id = this->atm->createCard(name, pin);

		if (!this->atm->getCard(id, pin))
			return false;

		return true;
	}

	bool createAccountTest() {
		std::string name = this->generateRandomStr();
		std::string pin = this->generateRandomStr();
		std::string id;

		id = this->atm->createCard(name, pin);

		Card *card = this->atm->getCard(id, pin);

		card->createAccount("saving");
		card->createAccount("checking");

		return true;
	}

	bool selectAccountTest() {
		std::string name = this->generateRandomStr();
		std::string pin = this->generateRandomStr();
		std::string id;

		id = this->atm->createCard(name, pin);

		Card *card = this->atm->getCard(id, pin);

		card->createAccount("saving");
		if (!card->selectAccount(0))
			return false;

		return true;
	}

	bool getBalanceTest() {
		std::string name = this->generateRandomStr();
		std::string pin = this->generateRandomStr();
		std::string id;

		id = this->atm->createCard(name, pin);

		Card *card = this->atm->getCard(id, pin);

		card->createAccount("saving");
		
		Account *acc = card->selectAccount(0);

		if (acc->getBalance() != 0)
			return false;

		return true;
	}

	bool depositTest() {
		std::string name = this->generateRandomStr();
		std::string pin = this->generateRandomStr();
		std::string id;

		id = this->atm->createCard(name, pin);

		Card *card = this->atm->getCard(id, pin);

		card->createAccount("saving");
		
		Account *acc = card->selectAccount(0);
		
		if (!acc->deposit(200))
			return false;

		if (!acc->deposit(150))
			return false;

		if (acc->getBalance() != 350)
			return false;

		return true;
	}


	bool withdrawTest() {
		std::string name = this->generateRandomStr();
		std::string pin = this->generateRandomStr();
		std::string id;

		id = this->atm->createCard(name, pin);

		Card *card = this->atm->getCard(id, pin);

		card->createAccount("saving");
		
		Account *acc = card->selectAccount(0);
		
		if (acc->withdraw(200))
			return false;

		if (acc->getBalance() != 0)
			return false;

		if (!acc->deposit(100))
			return false;

		if (!acc->withdraw(20))
			return false;

		if (acc->getBalance() != 80)
			return false;

		return true;
	}
};

#endif /* __ATM_TEST_H__ */
