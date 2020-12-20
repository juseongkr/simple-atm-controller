#ifndef __ATM_H__
#define __ATM_H__

#include <unordered_map>

class Atm {
private:
	std::string id;
	std::unordered_map<std::string, Card*> cards;

public:
	Atm() { }

	std::string createCard(const std::string name, const std::string pin) {
		Card *card = new Card(name, pin);

		std::string id = card->getId();
		this->cards[id] = card;

		return id;
	}

	Card *getCard(const std::string cid, const std::string pin) {
		if (!this->cards.count(cid) || !this->cards[cid]->checkPin(pin))
			return nullptr;

		return this->cards[cid];
	}

	void run() {
		while (1) {
			int cmd = -1;

			std::cout << "**********************" << std::endl;
			std::cout << "*   WELCOME TO ATM   *" << std::endl;
			std::cout << "*      ver 0.1       *" << std::endl;
			std::cout << "**********************" << std::endl << std::endl;

			std::cout << "1) Create a new card" << std::endl;
			std::cout << "2) insert a card" << std::endl;

			std::cin >> cmd;
			if (cmd == 1) {
				std::string username;
				std::string pin;

				std::cout << "Enter username: " << std::endl;
				std::cin >> username;
				std::cout << "Enter pin: " << std::endl;
				std::cin >> pin;

				std::cout << "card created, your card id is\n" << this->createCard(username, pin) << std::endl;
			} else if (cmd == 2) {
				std::string id;
				std::string pin;

				std::cout << "Enter card id: " << std::endl;
				std::cin >> id;
				std::cout << "Enter pin: " << std::endl;
				std::cin >> pin;

				Card *selectedCard = this->getCard(id, pin);
				if (selectedCard) {
					std::cout << "* authorized *" << std::endl << std::endl;
					selectedCard->run();

				} else {
					std::cout << "invalid credentials" << std::endl << std::endl;
				}
			}
		}
	}

	~Atm() {
		for (auto card : this->cards) {
			delete card.second;
		}
	}
};

#endif /* __ATM_H__ */
