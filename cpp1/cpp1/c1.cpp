#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

#define ACCOUNT_MAX 100
#define MIN_MKACC_MONEY 10
#define NAME_LEN 20
#define RRN_LEN 13		//바뀔일은 거의 없음

class Account {
private:
	int accId = 0;
	int balance = 0;
	char* cusName = new char[NAME_LEN];
	char* RRN = new char[RRN_LEN];

public:
	Account();
	Account(int accId, int balance, char* cusName, char* RRN);
	~Account();
	int getAccId();
	int getBalance();
	int addBalance(int balance);
	char* getCusName();
	char* getRRN();
};

int accountSize = 0;
Account* accounts = new Account[ACCOUNT_MAX];

Account::Account() {}

Account::Account(int accId, int balance, char* cusName, char* RRN) {
	this->accId = accId;
	this->addBalance(balance);
	this->cusName = cusName;
	this->RRN = RRN;
}

Account::~Account() {
	int accId = this->getAccId();

	for (int i = 0; i < accountSize; i++) {
		if (accounts[i].getAccId() == accId) {
			if (i != accountSize)
				accounts[i] = accounts[accountSize - 1];
		}
	}

	delete[] cusName;
	delete[] RRN;
}

int Account::getAccId() {
	return this->accId;
}

int Account::getBalance() {
	return this->balance;
}

int Account::addBalance(int balance) {
	if (this->getBalance() + balance < 0)
		return false;

	this->balance += balance;
	return true;
}

char* Account::getCusName() {
	return this->cusName;
}

char* Account::getRRN() {
	return this->RRN;
}

typedef enum {
	MK_ACC = 1,
	DEPOSIT = 2,
	WITHDRAW = 3,
	SEE_LIST = 4
} DUTY_LIST;

void checkAccount(char* RRN, int id) {
	for (int i = 0; i < accountSize; i++) {
		if (strcmp(RRN, accounts[i].getRRN()) == 0 || accounts[i].getAccId() == id)
			return;
	}

	throw exception("Already Exists");
}

Account findAccount(int id) {
	for (int i = 0; i < accountSize; i++) {
		if (accounts[i].getAccId() == id)
			return accounts[i];
	}

	throw exception("NPE");
}

void seeMenu() {
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void mkAcc() {
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

	if (accountSize == ACCOUNT_MAX) {
		cout << "계좌가 이미 " << ACCOUNT_MAX << "개입니다." << endl;
		return;
	}

	try {
		checkAccount(RRN, id);

		cout << "해당 주민등록번호의 계좌가 존재하거나 동일한 계좌 번호를 가진 계좌가 존재합니다." << endl;
		return;
	} catch (exception) {}

	if (balance < MIN_MKACC_MONEY) {
		cout << "계좌 생성 시 최소 " << MIN_MKACC_MONEY << " 이상의 돈을 입금해야합니다." << endl;
		return;
	}

	accounts[accountSize++] = *(new Account(id, balance, name, RRN));

	return;
}

void deposit() {
	int balance;
	int id;
	Account find;

	cout << "계좌ID: ";
	cin >> id;
	cout << "입금액: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	if (balance < 1) {
		cout << "입금은 1원 이상이어야 합니다." << endl;
		return;
	}

	try {
		find = findAccount(id);
	} catch (exception) {
		cout << "해당 계좌 ID를 가진 계좌 정보를 찾을 수 없습니다." << endl;
		return;
	}

	find.addBalance(balance);
	cout << "입금이 완료되었습니다." << endl;
}

void withdraw() {
	int balance;
	int id;
	Account find;

	cout << "계좌ID: ";
	cin >> id;
	cout << "출금액: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	if (balance < 1) {
		cout << "출금은 1원 이상이어야 합니다.";
		return;
	}

	try {
		find = findAccount(id);
	} catch (exception) {
		cout << "해당 계좌 ID를 가진 계좌 정보를 찾을 수 없습니다." << endl;
		return;
	}

	balance *= -1;
	if (find.addBalance(balance))
		cout << "출금이 완료되었습니다." << endl;
	else
		cout << "잔액이 부족합니다." << endl;
}

void seeList() {
	if (accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	cout << "------------" << endl;
	for (int i = 0; i < accountSize; i++) {
		cout << "계좌ID: " << accounts[i].getAccId() << endl;
		cout << "이  름: " << accounts[i].getCusName() << endl;
		cout << "잔  액: " << accounts[i].getBalance() << endl;

		if (i < accountSize - 1)
			cout << endl;
	}
	cout << "------------" << endl;
}

void duty(int input) {
	cout << endl;

	switch (input) {
	case MK_ACC:
		cout << "[계좌개설]" << endl;
		mkAcc();

		break;

	case DEPOSIT:
		cout << "[입    금]" << endl;
		deposit();

		break;

	case WITHDRAW:
		cout << "[출    금]" << endl;
		withdraw();

		break;

	case SEE_LIST:
		seeList();

		break;

	default:
		cout << "올바르지 않은 번호입니다." << endl;
		break;
	}

	cout << endl;
	return;
}

int main() {
	int input;

	while (true) {
		seeMenu();

		cout << "선택: ";
		cin >> input;

		if (input == 5) {
			delete[] accounts;
			return 0;
		}

		duty(input);
	}
}