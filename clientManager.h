#include <iostream>
#include <pqxx/pqxx>

class clntMngr {
public:
	[[nodiscard]] clntMngr(std::string&& url) noexcept(noexcept(pqxx::connection(url_)))
		: conn_(url), url_(std::move(url))
	{}
	[[nodiscard]] clntMngr(std::string& url) noexcept(noexcept(pqxx::connection(url_)))
		: conn_(url), url_(std::move(url))
	{}

	~clntMngr() = default;
	clntMngr(const clntMngr&&) = delete;
	clntMngr(const clntMngr&) = delete;
	clntMngr& operator=(const clntMngr) = delete;
	clntMngr& operator=(const clntMngr&&) = delete;

	void createRelation();
	void addClient();
	void addNumber();
	void alterData();
	void deletePhone();
	void deleteClient();
	void getClient();
private:
	pqxx::connection conn_;
	std::string url_;
};