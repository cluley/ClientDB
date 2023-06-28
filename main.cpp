#include <iostream>
#include <windows.h>

#include "clientManager.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
	clntMngr myDB(
		"host=localhost "
		"port=5432 "
		"user=XXXX "
		"dbname=XXXX "
		"password=XXXX"
	);

	int insert(666);
	while (insert != 0) {
		std::system("cls");
		std::cout << 
			"Select an option:\n" <<
			"1.Create table;\n" <<
			"2.Add client;\n" <<
			"3.Add number;\n" <<
			"4.Change name and surname;\n" <<
			"5.Delete phone number.\n" <<
			"6.Delete client from DB.\n" <<
			"7.Find client by e-mail.\n" <<
			"0.Exit.\n" <<
			"Insert: ";
		std::cin >> insert;
		std::system("cls");
		
		switch (insert) {
		case 1:
			myDB.createRelation();
			Sleep(3000);
			break;
		case 2:
			myDB.addClient();
			Sleep(3000);
			break;
		case 3:
			myDB.addNumber();
			Sleep(3000);
			break;
		case 4:
			myDB.alterData();
			Sleep(3000);
			break;
		case 5:
			myDB.deletePhone();
			Sleep(3000);
			break;
		case 6:
			myDB.deleteClient();
			Sleep(3000);
			break;
		case 7:
			myDB.getClient();
			system("pause");
			break;
		case 0:
			std::cout << "Bye!" << std::endl;
			break;
		default:
			std::cout << "Unknown operation." << std::endl;
			Sleep(3000);
			break;
		}
	}

	return 0;
}