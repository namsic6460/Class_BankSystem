#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

#define ACCOUNT_MAX 100
#define MIN_MKACC_MONEY 10
#define NAME_LEN 20
#define RRN_LEN 13		//바뀔일은 거의 없음

typedef enum {
	MK_ACC = 1,
	MK_DP_ACC = 2,
	DEPOSIT = 3,
	WITHDRAW = 4,
	SEE_LIST = 5
} DUTY_LIST;

class Account {
protected:
	int accId = 0;
	int balance = 0;
	char* cusName = new char[NAME_LEN];
	char* RRN = new char[RRN_LEN];

public:
	Account();
	Account(int accId, int balance, char* cusName, char* RRN);
	Account(const Account& account);
	~Account();
	const int getAccId() const;
	const int getBalance() const;
	char* getCusName() const;
	char* getRRN() const;
	const bool setBalance(const int balance);
	const int addBalance(const int balance);
};

class DepositAccount : public Account {
public:
	DepositAccount();
	DepositAccount(int accId, int balance, char* cusName, char* RRN);
	DepositAccount(const DepositAccount& account);
	virtual ~DepositAccount();
	const int addBalance(const int balance);
};

class AccountManager {
private:
	int accountSize = 0;
	int dpAccountSize = 0;
	Account* accounts = new Account[ACCOUNT_MAX];
	DepositAccount* dpAccounts = new DepositAccount[ACCOUNT_MAX];
public:
	AccountManager();
	~AccountManager();
	const int getAccountSize() const;
	const int getDpAccountSize() const;
	Account* getAccounts() const;
	DepositAccount* getDpAccounts() const;
	const void checkAccount(const char* RRN, const int id) const;
	Account* findAccount(const int id) const;
	DepositAccount* findDpAccount(const int id) const;
	const void duty(const int input);
	const void seeMenu() const;
	void mkAcc();
	void mkDpAcc();
	const void deposit() const;
	const void withdraw() const;
	const void seeList() const;
};

//AccountManager 전역 변수 - Account 소멸자에서 사용
AccountManager* accManager = new AccountManager();

Account::Account() {}

Account::Account(int accId, int balance, char* cusName, char* RRN) {
	this->accId = accId;
	this->balance = balance;
	this->cusName = cusName;
	this->RRN = RRN;
}

Account::~Account() {
	int accId = this->getAccId();

	const int size = accManager->getAccountSize();
	Account* accounts = accManager->getAccounts();
	for (int i = 0; i < size; i++) {
		if (accounts[i].getAccId() == accId) {
			if (i != size)
				accounts[i] = accounts[size - 1];
		}
	}

	delete[] cusName;
	delete[] RRN;
}

Account::Account(const Account& account) {
	cout << "\n복사생성자 호출\n\n";
	this->accId = account.accId;
	this->addBalance(account.balance);
	this->cusName = new char[strlen(account.cusName) + 1];
	strcpy(this->cusName, account.cusName);
	strcpy(this->RRN, account.RRN);
}

const int Account::getAccId() const {
	return this->accId;
}

const int Account::getBalance() const {
	return this->balance;
}

char* Account::getCusName() const {
	return this->cusName;
}

char* Account::getRRN() const {
	return this->RRN;
}

const int Account::addBalance(const int balance) {
	this->balance += balance;

	int interest = this->getBalance() / 100;
	this->balance += interest;
	return interest;
}

const bool Account::setBalance(const int balance) {
	if (balance >= 0) {
		this->balance = balance;
		return true;
	}

	return false;
}

AccountManager::AccountManager() {}

AccountManager::~AccountManager() {
	delete[] accounts;
}

const int AccountManager::getAccountSize() const {
	return this->accountSize;
}

const int AccountManager::getDpAccountSize() const {
	return this->dpAccountSize;
}

Account* AccountManager::getAccounts() const {
	return this->accounts;
}

DepositAccount* AccountManager::getDpAccounts() const {
	return this->dpAccounts;
}

DepositAccount::DepositAccount() {}

DepositAccount::DepositAccount(int accId, int balance, char* cusName, char* RRN) {
	this->accId = accId;
	this->balance = balance;
	this->cusName = cusName;
	this->RRN = RRN;
}

DepositAccount::DepositAccount(const DepositAccount& account) {
	cout << "\n복사생성자 호출\n\n";
	this->accId = account.accId;
	this->addBalance(account.balance);
	this->cusName = new char[strlen(account.cusName) + 1];
	strcpy(this->cusName, account.cusName);
	strcpy(this->RRN, account.RRN);
}

DepositAccount::~DepositAccount() {}

const int DepositAccount::addBalance(const int balance) {
	this->balance += balance;

	int interest = this->getBalance() / 50;
	this->balance += interest;
	return interest;
}

const void AccountManager::duty(const int input) {
	cout << endl;

	switch (input) {
	case MK_ACC:
		cout << "[계좌개설]" << endl;
		this->mkAcc();

		break;

	case MK_DP_ACC:
		cout << "[예금 계좌개설]" << endl;
		this->mkDpAcc();

		break;

	case DEPOSIT:
		cout << "[입    금]" << endl;
		this->deposit();

		break;

	case WITHDRAW:
		cout << "[출    금]" << endl;
		this->withdraw();

		break;

	case SEE_LIST:
		this->seeList();

		break;

	default:
		cout << "올바르지 않은 번호입니다." << endl;
		break;
	}

	cout << endl;
	return;
}

const void AccountManager::seeMenu() const {
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 예금계좌 개설" << endl;
	cout << "3. 입    금" << endl;
	cout << "4. 출    금" << endl;
	cout << "5. 계좌정보 전체 출력" << endl;
	cout << "6. 프로그램 종료" << endl;
}

const void AccountManager::checkAccount(const char* RRN, const int id) const {
	const int size = this->getAccountSize();
	Account* accounts = this->getAccounts();

	for (int i = 0; i < size; i++) {
		if (strcmp(RRN, accounts[i].getRRN()) == 0 || accounts[i].getAccId() == id)
			return;
	}

	throw exception("Complete");
}

Account* AccountManager::findAccount(const int id) const {
	const int size = accManager->getAccountSize();
	Account* accounts = accManager->getAccounts();

	for (int i = 0; i < size; i++) {
		if (accounts[i].getAccId() == id)
			return &accounts[i];
	}

	throw exception("NPE");
}

DepositAccount* AccountManager::findDpAccount(const int id) const {
	const int size = accManager->getDpAccountSize();
	DepositAccount* accounts = accManager->getDpAccounts();

	for (int i = 0; i < size; i++) {
		if (accounts[i].getAccId() == id)
			return &accounts[i];
	}

	throw exception("NPE");
}

void AccountManager::mkAcc() {
	char* name = new char[NAME_LEN];
	char* RRN = new char[RRN_LEN];
	int balance;
	int id;

	cout << "계좌ID: ";
	cin >> id;
	cout << "이름: ";
	cin >> name;
	cout << "입금액: ";
	cin >> balance;
	cout << "주민등록번호('-' 없이 입력): ";
	cin >> RRN;

	if (this->accountSize == ACCOUNT_MAX) {
		cout << "계좌가 이미 " << ACCOUNT_MAX << "개입니다." << endl;
		return;
	}

	try {
		this->checkAccount(RRN, id);

		cout << "해당 주민등록번호의 계좌가 존재하거나 동일한 계좌 번호를 가진 계좌가 존재합니다." << endl;
		return;
	}
	catch (exception) {}

	if (balance < MIN_MKACC_MONEY) {
		cout << "계좌 생성 시 최소 " << MIN_MKACC_MONEY << " 이상의 돈을 입금해야합니다." << endl;
		return;
	}

	this->accounts[this->accountSize++] = *(new Account(id, balance, name, RRN));
	cout << "계좌 개설이 완료되었습니다." << endl;

	return;
}

void AccountManager::mkDpAcc() {
	int id;
	int balance;
	Account* find;

	cout << "계좌ID: ";
	cin >> id;
	cout << "입금액: ";
	cin >> balance;

	if (this->dpAccountSize == ACCOUNT_MAX) {
		cout << "예금 계좌가 이미 " << ACCOUNT_MAX << "개입니다." << endl;
		return;
	}

	try {
		find = this->findAccount(id);
	} catch (exception) {
		cout << "해당 계좌 ID를 가진 계좌 정보를 찾을 수 없습니다." << endl;
		return;
	}

	try {
		this->findDpAccount(id);

		cout << "해당 계좌의 예금계좌는 이미 개설되어 있습니다." << endl;
		return;
	}
	catch (exception) {}

	if (balance < MIN_MKACC_MONEY) {
		cout << "계좌 생성 시 최소 " << MIN_MKACC_MONEY << " 이상의 돈을 입금해야합니다." << endl;
		return;
	}

	this->dpAccounts[this->dpAccountSize++] = *(new DepositAccount(id, balance, find->getCusName(), find->getRRN()));
	cout << "예금 계좌 개설이 완료되었습니다." << endl;

	return;
}

const void AccountManager::deposit() const {
	int balance;
	int id;
	int isDp;
	int interest;

	cout << "계좌ID: ";
	cin >> id;
	cout << "입금액: ";
	cin >> balance;
	cout << "계좌 종류(일반: 0, 예금: 1): ";
	cin >> isDp;

	if (accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}


	if (balance < 1) {
		cout << "입금은 1원 이상이어야 합니다." << endl;
		return;
	}

	if (!isDp) {
		try {
			interest = this->findAccount(id)->addBalance(balance);
		} catch (exception) {
			cout << "해당 계좌 ID를 가진 계좌 정보를 찾을 수 없습니다." << endl;
			return;
		}
	}

	else {
		try {
			interest = this->findDpAccount(id)->addBalance(balance);
		} catch (exception) {
			cout << "해당 계좌 ID를 가진 예금 계좌 정보를 찾을 수 없습니다." << endl;
			return;
		}
	}

	cout << "이자 : " << interest << "원" << endl;
	cout << "입금이 완료되었습니다." << endl;
}

const void AccountManager::withdraw() const {
	int balance;
	int id;
	int isDp;
	bool result;

	cout << "계좌ID: ";
	cin >> id;
	cout << "출금액: ";
	cin >> balance;
	cout << "계좌 종류(일반: 0, 예금: 1): ";
	cin >> isDp;

	if (this->accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	if (balance < 1) {
		cout << "출금은 1원 이상이어야 합니다.";
		return;
	}

	balance *= -1;
	if (!isDp) {
		try {
			Account *find = this->findAccount(id);
			result = find->setBalance(find->getBalance() + balance);
		} catch (exception) {
			cout << "해당 계좌 ID를 가진 계좌 정보를 찾을 수 없습니다." << endl;
			return;
		}
	}

	else {
		try {
			DepositAccount *find = this->findDpAccount(id);
			result = find->addBalance(find->getBalance() + balance);
		} catch (exception) {
			cout << "해당 계좌 ID를 가진 예금 계좌 정보를 찾을 수 없습니다." << endl;
			return;
		}
	}

	
	if (result)
		cout << "출금이 완료되었습니다." << endl;
	else
		cout << "잔액이 부족합니다." << endl;
}

const void AccountManager::seeList() const {
	if (this->accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	cout << "----일반-----" << endl;
	for (int i = 0; i < this->accountSize; i++) {
		cout << "계좌ID: " << accounts[i].getAccId() << endl;
		cout << "이  름: " << accounts[i].getCusName() << endl;
		cout << "잔  액: " << accounts[i].getBalance() << endl;

		if (i < this->accountSize - 1)
			cout << endl;
	}

	cout << endl << "----예금----" << endl;
	for (int i = 0; i < this->dpAccountSize; i++) {
		cout << "계좌ID: " << dpAccounts[i].getAccId() << endl;
		cout << "이  름: " << dpAccounts[i].getCusName() << endl;
		cout << "잔  액: " << dpAccounts[i].getBalance() << endl;

		if (i < this->accountSize - 1)
			cout << endl;
	}
	
	cout << endl;
}

int main() {
	int input;

	while (true) {
		accManager->seeMenu();

		cout << "선택: ";
		cin >> input;

		if (input == 6)
			return 0;

		accManager->duty(input);
	}
}