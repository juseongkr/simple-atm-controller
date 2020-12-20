#ifndef __CARD_H__
#define __CARD_H__

#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

class Card {
private:
	std::string id;
	std::string pin;
	std::string username;
	std::string createdAt;
	std::string updatedAt;
	std::vector<Account*> accounts;
	AccountFactory *accFactory;
	int selectedAccount;

	void updateTimestamp(std::string &stamp) {
		time_t now = time(0);
		tm *gmtm = gmtime(&now);
		stamp = asctime(gmtm);
	}

	std::string generateId() {
		std::string base("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(base.begin(), base.end(), generator);

		return base.substr(0, 32);
	}

public:
	Card() = delete;

	Card(const std::string name, const std::string pw) : username(name), pin(pw), selectedAccount(-1) {
		this->id = this->generateId();
		this->updateTimestamp(createdAt);
		this->accFactory = new AccountFactory();
	}

	bool checkPin(const std::string pin) const {
		return this->pin == pin;
	}

	std::string getId() const {
		return this->id;
	}

	std::string getCreateTime() const {
		return this->createdAt;
	}

	std::string getUpdateTime() const {
		return this->updatedAt;
	}

	void createAccount(const std::string type) {
		Account *account = this->accFactory->makeAccount(type);
		this->accounts.push_back(account);
		this->updateTimestamp(updatedAt);
	}

	Account *selectAccount(int id) const {
		if (0 <= id && id < this->accounts.size())
			return this->accounts[id];

		throw std::invalid_argument("invalid account id");
	}

	void printAccounts() {
		std::cout << "number of accounts: " << this->accounts.size() << std::endl;
		for (int i=0; i<this->accounts.size(); ++i) {
			std::cout << "*********************" << std::endl;
			std::cout << "No: " << i << std::endl;
			std::cout << "Type: " << accounts[i]->getType() << std::endl;
			std::cout << "Balance: " << accounts[i]->getBalance() << std::endl << std::endl;
		}
	}

	void run() {
		while (1) {
			int cmd = -1;
			this->printAccounts();

			std::cout << "1) Create a new account" << std::endl;
			std::cout << "2) Select a account" << std::endl;
			std::cin >> cmd;

			if (cmd == 1) {
				std::string type;

				std::cout << "Enter account type (checking, saving)" << std::endl;
				std::cin >> type;
				this->createAccount(type);

			} else if (cmd == 2) {
				int action = -1;

				std::cout << "Enter account number: " << std::endl;
				std::cin >> action;

				Account *currentAccount = this->selectAccount(action);

				while (1) {
					std::cout << "1) See balance" << std::endl;
					std::cout << "2) Deposite" << std::endl;
					std::cout << "3) Withdraw" << std::endl;
					std::cout << "4) Exit" << std::endl;
					std::cin >> action;

					if (action == 1) {
						std::cout << "Balance: " << currentAccount->getBalance() << std::endl;

					} else if (action == 2) {
						int amount = 0;
						std::cout << "Enter amount: " << std::endl;
						std::cin >> amount;
						if (currentAccount->deposit(amount))
							std::cout << "* Deposit success *" << std::endl;
						else
							std::cout << "* Deposit fail *" << std::endl;

					} else if (action == 3) {
						int amount = 0;
						std::cout << "Enter amount: " << std::endl;
						std::cin >> amount;
						if (currentAccount->withdraw(amount))
							std::cout << "* Withdraw success *" << std::endl;
						else
							std::cout << "* Withdraw fail *" << std::endl;

					} else if (action == 4) {
						break;

					}
				}
			}
		}

	}

	~Card() {
		delete this->accFactory;

		for (int i=0; i<this->accounts.size(); ++i) {
			delete accounts[i];
		}
	}
};

#endif /* __CARD_H__ */
