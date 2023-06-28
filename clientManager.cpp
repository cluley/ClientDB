#include "clientManager.h"

void clntMngr::createRelation() {
	try {
		pqxx::work tx(conn_);

		tx.exec("CREATE TABLE IF NOT EXISTS Client ( "
			"\"First Name\" VARCHAR(100) NOT NULL , "
			"\"Second Name\" VARCHAR(100) NOT NULL , "
			"\"e-mail\" VARCHAR(200) UNIQUE PRIMARY KEY "
			"); "

			"CREATE TABLE IF NOT EXISTS Phone( "
			"\"e-mail\" VARCHAR REFERENCES Client(\"e-mail\"), "
			"\"Phone Number\" VARCHAR(16) UNIQUE "
			"); "
		);

		tx.commit();

		std::cout << "Relations have been created." << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void clntMngr::addClient() {
	try
	{
		pqxx::work ch_tx(conn_);

		auto cl_set = ch_tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'client' AND schemaname = 'public'); "
		);

		auto ph_set = ch_tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'phone' AND schemaname = 'public'); "
		);

		ch_tx.abort();

		if (cl_set && ph_set) 
		{
			std::string name, surname, email, phone;
			std::cout << "Enter first name: ";
			std::cin >> name;
			std::cout << "Enter second name: ";
			std::cin >> surname;
			std::cout << "Enter email: ";
			std::cin >> email;
			std::cout << "Enter phone: ";
			std::cin >> phone;

			conn_.prepare("insert", "INSERT INTO Client VALUES($1, $2, $3)");
			conn_.prepare("insert2", "INSERT INTO Phone VALUES($1, $2)");

			pqxx::work tx(conn_);

			tx.exec_prepared("insert", name, surname, email);
			tx.exec_prepared("insert2", email, phone);

			tx.commit();

			std::cout << "Client has been added." << std::endl;
		}
		else 
		{
			std::cout << "Relations doesn't exist. Create relations first." << std::endl;
		}
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void clntMngr::addNumber() {
	try
	{
		pqxx::work tx(conn_);

		auto cl_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'client' AND schemaname = 'public'); "
		);

		auto ph_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'phone' AND schemaname = 'public'); "
		);

		if (cl_set && ph_set)
		{
			std::string email, phone;
			std::cout << "Enter the client e-mail: ";
			std::cin >> email;
			std::cout << "Enter phone: ";
			std::cin >> phone;

			tx.exec("INSERT INTO phone(\"e-mail\", \"Phone Number\") "
				"VALUES('" + tx.esc(email) + "', '" + tx.esc(phone) + "') "
			);

			tx.commit();

			std::cout << "Phone has been added." << std::endl;
		}
		else
		{
			std::cout << "Relations doesn't exist. Create relations first." << std::endl;
		}
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void clntMngr::alterData() {
	try
	{
		pqxx::work ch_tx(conn_);

		auto cl_set = ch_tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'client' AND schemaname = 'public'); "
		);

		auto ph_set = ch_tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'phone' AND schemaname = 'public'); "
		);

		ch_tx.abort();

		if (cl_set && ph_set)
		{
			std::string name, surname, email;
			std::cout << "Enter email of altering client: ";
			std::cin >> email;
			std::cout << "Enter first name to replace: ";
			std::cin >> name;
			std::cout << "Enter second name to replace: ";
			std::cin >> surname;

			conn_.prepare("update", "UPDATE client "
				"SET \"First Name\" = $1, \"Second Name\" = $2 "
				"WHERE \"e-mail\" = $3; ");

			pqxx::work tx(conn_);

			tx.exec_prepared("update", name, surname, email);

			tx.commit();

			std::cout << "The data has been altered." << std::endl;
		}
		else
		{
			std::cout << "Relations doesn't exist. Create relations first." << std::endl;
		}
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void clntMngr::deletePhone() {
	try
	{
		pqxx::work tx(conn_);

		auto cl_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'client' AND schemaname = 'public'); "
		);

		auto ph_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'phone' AND schemaname = 'public'); "
		);

		if (cl_set && ph_set)
		{
			std::string phone;
			std::cout << "Enter a phone number to delete: ";
			std::cin >> phone;

			tx.exec("DELETE FROM phone "
				"WHERE \"Phone Number\" = '" + tx.esc(phone) + "';");

			tx.commit();

			std::cout << "The phone number has been deleted." << std::endl;
		}
		else
		{
			std::cout << "Relations doesn't exist. Create relations first." << std::endl;
		}
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void clntMngr::deleteClient() {
	try
	{
		pqxx::work tx(conn_);

		auto cl_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'client' AND schemaname = 'public'); "
		);

		auto ph_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'phone' AND schemaname = 'public'); "
		);

		if (cl_set && ph_set)
		{
			std::string email;
			std::cout << "Enter an e-mail of client to delete: ";
			std::cin >> email;

			tx.exec("DELETE FROM phone "
				"WHERE \"e-mail\" = '" + tx.esc(email) + "';");

			tx.exec("DELETE FROM client "
				"WHERE \"e-mail\" = '" + tx.esc(email) + "';");

			tx.commit();

			std::cout << "The client has been deleted." << std::endl;
		}
		else
		{
			std::cout << "Relations doesn't exist. Create relations first." << std::endl;
		}
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void clntMngr::getClient() {
	try
	{
		pqxx::work tx(conn_);

		auto cl_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'client' AND schemaname = 'public'); "
		);

		auto ph_set = tx.query_value<bool>("SELECT EXISTS ( "
			"SELECT * FROM pg_tables "
			"WHERE tablename = 'phone' AND schemaname = 'public'); "
		);

		if (cl_set && ph_set)
		{
			std::string email;
			std::cout << "Enter an e-mail of client: ";
			std::cin >> email;

			for (auto [name, surname, email] : tx.query<std::string, std::string, std::string>("SELECT \"First Name\", \"Second Name\", \"e-mail\" FROM client "
				"WHERE \"e-mail\" = '" + tx.esc(email) + "'; ")) 
			{
				std::cout <<
					"First Name: " << name << '\n' <<
					"Second Name: " << surname << '\n' <<
					"e-mail: " << email << std::endl;
			}

			std::cout << "Phone Number(s): ";
			for (auto [phone] : tx.query<std::string>("SELECT \"Phone Number\" FROM phone "
				"WHERE \"e-mail\" = '" + tx.esc(email) + "'; "))
			{
				std::cout << phone << " | ";
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Relations doesn't exist. Create relations first." << std::endl;
		}
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}