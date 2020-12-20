#ifndef __FACTORY_H__
#define __FACTORY_H__

class AccountFactory {
public:
	AccountFactory() { }

	Account *makeAccount(const std::string str) const {
		if (str == "checking") {
			return new CheckingAccount();
		} else if (str == "saving") {
			return new SavingAccount();
		}

		throw std::invalid_argument("invalid account argument");
	}
};

#endif /* __FACTORY_H__ */
