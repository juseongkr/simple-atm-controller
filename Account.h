#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <climits>
#include <ctime>

class Account {
public:
	Account() { }
	virtual std::string getType() const = 0;
	virtual unsigned int getBalance() const = 0;
	virtual bool deposit(unsigned int) = 0;
	virtual bool withdraw(unsigned int) = 0;
	virtual ~Account() { }
};

class CheckingAccount : public Account {
private:
	unsigned int balance;
	std::string type;
	std::string createdAt;
	std::string updatedAt;

	void updateTimestamp(std::string &stamp) {
		time_t now = time(0);
		tm *gmtm = gmtime(&now);
		stamp = asctime(gmtm);
	}

public:
	CheckingAccount() : balance(0), type("checking account") {
		this->updateTimestamp(createdAt);
	}

	std::string getType() const override {
		return this->type;
	}

	unsigned int getBalance() const override {
		return this->balance;
	}

	bool deposit(unsigned int amount) override {
		if (this->balance + amount > INT_MAX)
			return false;

		this->balance += amount;
		this->updateTimestamp(updatedAt);
	
		return true;
	}

	bool withdraw(unsigned int amount) override {
		if (this->balance < amount)
			return false;

		this->balance -= amount;
		this->updateTimestamp(updatedAt);

		return true;
	}
};

class SavingAccount : public Account {
private:
	unsigned int balance;
	std::string type;
	std::string createdAt;
	std::string updatedAt;

	void updateTimestamp(std::string &stamp) {
		time_t now = time(0);
		tm *gmtm = gmtime(&now);
		this->updatedAt = asctime(gmtm);
	}

public:
	SavingAccount() : balance(0), type("saving account") {
		this->updateTimestamp(createdAt);
	}

	std::string getType() const override {
		return this->type;
	}

	unsigned int getBalance() const override {
		return this->balance;
	}

	bool deposit(unsigned int amount) override {
		if (this->balance + amount > INT_MAX)
			return false;

		this->balance += amount;
		this->updateTimestamp(updatedAt);

		return true;
	}

	bool withdraw(unsigned int amount) override {
		if (this->balance < amount)
			return false;

		this->balance -= amount;
		this->updateTimestamp(updatedAt);

		return true;
	}
};

#endif /* __ACCOUNT_H__ */
