#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

#define ACCOUNT_MAX 100
#define MIN_MKACC_MONEY 10
#define NAME_LEN 20
#define RRN_LEN 13		//�ٲ����� ���� ����

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
	bool isDpAcc = false;

public:
	Account();
	Account(int accId, int balance, char* cusName, char* RRN);
	Account(const Account& account);
	~Account();
	const int getAccId() const;
	const int getBalance() const;
	char* getCusName() const;
	char* getRRN() const;
	const bool getIsDpAcc() const;
	const void setBalance(const int balance);
	const int addBalance(const int balance);
};

class DepositAccount : public Account {
public:
	DepositAccount(int accId, int balance, char* cusName, char* RRN);
	DepositAccount(const DepositAccount& account);
	virtual ~DepositAccount();
	const int addBalance(const int balance);
};

class AccountManager {
private:
	int accountSize = 0;
	Account* accounts = new Account[ACCOUNT_MAX];
public:
	AccountManager();
	~AccountManager();
	const int getAccountSize() const;
	Account* getAccounts() const;
	const void checkAccount(const char* RRN, const int id) const;
	Account* findAccount(const int id) const;
	Account* findDpAccount(const int id) const;
	const void duty(const int input);
	const void seeMenu() const;
	void mkAcc();
	void mkDpAcc();
	const void deposit() const;
	const void withdraw() const;
	const void seeList() const;
};

AccountManager* accManager = new AccountManager();

Account::Account() {}

Account::Account(int accId, int balance, char* cusName, char* RRN) {
	this->accId = accId;
	this->setBalance(balance);
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
	cout << "\n��������� ȣ��\n\n";
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

const bool Account::getIsDpAcc() const {
	return this->isDpAcc;
}

const int Account::addBalance(const int balance) {
	this->balance += balance;

	int interest = this->getBalance() / 100;
	this->balance += interest;
	return interest;
}

const void Account::setBalance(const int balance) {
	this->balance = balance;
}

AccountManager::AccountManager() {}

AccountManager::~AccountManager() {
	delete[] accounts;
}

const int AccountManager::getAccountSize() const {
	return this->accountSize;
}

Account* AccountManager::getAccounts() const {
	return this->accounts;
}

DepositAccount::DepositAccount(int accId, int balance, char* cusName, char* RRN) {
	this->accId = accId;
	this->balance = 0;
	this->cusName = cusName;
	this->RRN = RRN;
	this->isDpAcc = true;
}

DepositAccount::DepositAccount(const DepositAccount& account) {
	cout << "\n��������� ȣ��\n\n";
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
		cout << "[���°���]" << endl;
		this->mkAcc();

		break;

	case MK_DP_ACC:
		cout << "[���� ���°���]" << endl;
		this->mkDpAcc();

		break;

	case DEPOSIT:
		cout << "[��    ��]" << endl;
		this->deposit();

		break;

	case WITHDRAW:
		cout << "[��    ��]" << endl;
		this->withdraw();

		break;

	case SEE_LIST:
		this->seeList();

		break;

	default:
		cout << "�ùٸ��� ���� ��ȣ�Դϴ�." << endl;
		break;
	}

	cout << endl;
	return;
}

const void AccountManager::seeMenu() const {
	cout << "-----Menu-----" << endl;
	cout << "1. ���°���" << endl;
	cout << "2. ���ݰ��� ����" << endl;
	cout << "3. ��    ��" << endl;
	cout << "4. ��    ��" << endl;
	cout << "5. �������� ��ü ���" << endl;
	cout << "6. ���α׷� ����" << endl;
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

Account* AccountManager::findDpAccount(const int id) const {
	const int size = accManager->getAccountSize();
	Account* accounts = accManager->getAccounts();

	for (int i = 0; i < size; i++) {
		if (accounts[i].getAccId() == id && accounts[i].getIsDpAcc() == true)
			return &accounts[i];
	}

	throw exception("NPE");
}

void AccountManager::mkAcc() {
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

	if (this->accountSize == ACCOUNT_MAX) {
		cout << "���°� �̹� " << ACCOUNT_MAX << "���Դϴ�." << endl;
		return;
	}

	try {
		this->checkAccount(RRN, id);

		cout << "�ش� �ֹε�Ϲ�ȣ�� ���°� �����ϰų� ������ ���� ��ȣ�� ���� ���°� �����մϴ�." << endl;
		return;
	}
	catch (exception) {}

	if (balance < MIN_MKACC_MONEY) {
		cout << "���� ���� �� �ּ� " << MIN_MKACC_MONEY << " �̻��� ���� �Ա��ؾ��մϴ�." << endl;
		return;
	}

	this->accounts[this->accountSize++] = *(new Account(id, balance, name, RRN));
	cout << "���� ������ �Ϸ�Ǿ����ϴ�." << endl;

	return;
}

void AccountManager::mkDpAcc() {
	int id;
	int balance;
	Account* find;

	cout << "����ID: ";
	cin >> id;
	cout << "�Աݾ�: ";
	cin >> balance;

	if (this->accountSize == ACCOUNT_MAX) {
		cout << "���°� �̹� " << ACCOUNT_MAX << "���Դϴ�." << endl;
		return;
	}

	try {
		find = this->findAccount(id);
	} catch (exception) {
		cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
		return;
	}

	try {
		this->findDpAccount(id);

		cout << "�ش� ������ ���ݰ��´� �̹� �����Ǿ� �ֽ��ϴ�." << endl;
		return;
	}
	catch (exception) {}

	if (balance < MIN_MKACC_MONEY) {
		cout << "���� ���� �� �ּ� " << MIN_MKACC_MONEY << " �̻��� ���� �Ա��ؾ��մϴ�." << endl;
		return;
	}

	this->accounts[this->accountSize++] = *(new DepositAccount(id, balance, find->getCusName(), find->getRRN()));
	cout << "���� ���� ������ �Ϸ�Ǿ����ϴ�." << endl;

	return;
}

const void AccountManager::deposit() const {
	int balance;
	int id;
	Account* find;

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
		find = this->findAccount(id);
	}
	catch (exception) {
		cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
		return;
	}

	int interest = find->addBalance(balance);

	cout << "���� : " << interest << "��" << endl;
	cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl;
}

const void AccountManager::withdraw() const {
	int balance;
	int id;
	Account* find;

	cout << "����ID: ";
	cin >> id;
	cout << "��ݾ�: ";
	cin >> balance;

	if (this->accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	if (balance < 1) {
		cout << "����� 1�� �̻��̾�� �մϴ�.";
		return;
	}

	try {
		find = this->findAccount(id);
	}
	catch (exception) {
		cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
		return;
	}

	balance *= -1;
	if (find->addBalance(balance))
		cout << "����� �Ϸ�Ǿ����ϴ�." << endl;
	else
		cout << "�ܾ��� �����մϴ�." << endl;
}

const void AccountManager::seeList() const {
	if (this->accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	cout << "------------" << endl;
	for (int i = 0; i < this->accountSize; i++) {
		cout << "����ID: " << accounts[i].getAccId();
		if (accounts[i].getIsDpAcc() == true)
			cout << "(����)";
		cout << endl;

		cout << "��  ��: " << accounts[i].getCusName() << endl;
		cout << "��  ��: " << accounts[i].getBalance() << endl;

		if (i < this->accountSize - 1)
			cout << endl;
	}
	cout << "------------" << endl;
}

int main() {
	int input;

	while (true) {
		accManager->seeMenu();

		cout << "����: ";
		cin >> input;

		if (input == 6)
			return 0;

		accManager->duty(input);
	}
}