#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

#define ACCOUNT_MAX 100
#define MIN_MKACC_MONEY 10
#define NAME_LEN 20
#define RRN_LEN 13		//�ٲ����� ���� ����

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
	cout << "1. ���°���" << endl;
	cout << "2. ��    ��" << endl;
	cout << "3. ��    ��" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}

void mkAcc() {
	char* name = new char[NAME_LEN];
	char* RRN = new char[RRN_LEN];
	int balance;
	int id;

	cout << "����ID: ";
	cin >> id;
	cout << "�̸�: ";
	cin >> name;
	cout << "�Աݾ�: ";
	cin >> balance;
	cout << "�ֹε�Ϲ�ȣ('-' ���� �Է�): ";
	cin >> RRN;

	if (accountSize == ACCOUNT_MAX) {
		cout << "���°� �̹� " << ACCOUNT_MAX << "���Դϴ�." << endl;
		return;
	}

	try {
		checkAccount(RRN, id);

		cout << "�ش� �ֹε�Ϲ�ȣ�� ���°� �����ϰų� ������ ���� ��ȣ�� ���� ���°� �����մϴ�." << endl;
		return;
	} catch (exception) {}

	if (balance < MIN_MKACC_MONEY) {
		cout << "���� ���� �� �ּ� " << MIN_MKACC_MONEY << " �̻��� ���� �Ա��ؾ��մϴ�." << endl;
		return;
	}

	accounts[accountSize++] = *(new Account(id, balance, name, RRN));

	return;
}

void deposit() {
	int balance;
	int id;
	Account find;

	cout << "����ID: ";
	cin >> id;
	cout << "�Աݾ�: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	if (balance < 1) {
		cout << "�Ա��� 1�� �̻��̾�� �մϴ�." << endl;
		return;
	}

	try {
		find = findAccount(id);
	} catch (exception) {
		cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
		return;
	}

	find.addBalance(balance);
	cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl;
}

void withdraw() {
	int balance;
	int id;
	Account find;

	cout << "����ID: ";
	cin >> id;
	cout << "��ݾ�: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	if (balance < 1) {
		cout << "����� 1�� �̻��̾�� �մϴ�.";
		return;
	}

	try {
		find = findAccount(id);
	} catch (exception) {
		cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
		return;
	}

	balance *= -1;
	if (find.addBalance(balance))
		cout << "����� �Ϸ�Ǿ����ϴ�." << endl;
	else
		cout << "�ܾ��� �����մϴ�." << endl;
}

void seeList() {
	if (accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	cout << "------------" << endl;
	for (int i = 0; i < accountSize; i++) {
		cout << "����ID: " << accounts[i].getAccId() << endl;
		cout << "��  ��: " << accounts[i].getCusName() << endl;
		cout << "��  ��: " << accounts[i].getBalance() << endl;

		if (i < accountSize - 1)
			cout << endl;
	}
	cout << "------------" << endl;
}

void duty(int input) {
	cout << endl;

	switch (input) {
	case MK_ACC:
		cout << "[���°���]" << endl;
		mkAcc();

		break;

	case DEPOSIT:
		cout << "[��    ��]" << endl;
		deposit();

		break;

	case WITHDRAW:
		cout << "[��    ��]" << endl;
		withdraw();

		break;

	case SEE_LIST:
		seeList();

		break;

	default:
		cout << "�ùٸ��� ���� ��ȣ�Դϴ�." << endl;
		break;
	}

	cout << endl;
	return;
}

int main() {
	int input;

	while (true) {
		seeMenu();

		cout << "����: ";
		cin >> input;

		if (input == 5) {
			delete[] accounts;
			return 0;
		}

		duty(input);
	}
}