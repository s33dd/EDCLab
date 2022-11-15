#include "Menu.h"

void Menu::Header() {
	std::cout << "Choose what error detecting code you want to use:" << std::endl <<
		"1 - Parity control" << std::endl << std::endl << "2 - CRC-24/LTE-A" << std::endl;
}

void Menu::EDCChoice() {
	int choice;
	std::cin >> choice;
	switch (choice) {
	case 1: {
		PrCntrl checker = PrCntrl();
		checker.Chosen();
		break;
	}
	case 2: {
		CRC checker = CRC();
		checker.Chosen();
		break;
	}
	default: 
		exit(EXIT_SUCCESS);
	}
}
