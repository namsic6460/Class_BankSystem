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

public:
	Account();
	Account(int accId, int balance, char* cusName, char* RRN);
	Account(const Account& account);
	~Account();
	const int getAccId() const;
	const int getBalance() const;
	char* getCusName() const;
	char* getRRN() const;
	const void setBalance(const int balance);
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

	if (this->dpAccountSize == ACCOUNT_MAX) {
		cout << "���� ���°� �̹� " << ACCOUNT_MAX << "���Դϴ�." << endl;
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

	this->dpAccounts[this->dpAccountSize++] = *(new DepositAccount(id, balance, find->getCusName(), find->getRRN()));
	cout << "���� ���� ������ �Ϸ�Ǿ����ϴ�." << endl;

	return;
}

const void AccountManager::deposit() const {
	int balance;
	int id;
	int isDp;
	int interest;

	cout << "����ID: ";
	cin >> id;
	cout << "�Աݾ�: ";
	cin >> balance;
	cout << "���� ����(�Ϲ�: 0, ����: 1): ";
	cin >> isDp;

	if (accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}


	if (balance < 1) {
		cout << "�Ա��� 1�� �̻��̾�� �մϴ�." << endl;
		return;
	}

	if (!isDp) {
		try {
			interest = this->findDpAccount(id)->addBalance(balance);
		} catch (exception) {
			cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
			return;
		}
	}

	else {
		try {
			interest = this->findDpAccount(id)->addBalance(balance);
		} catch (exception) {
			cout << "�ش� ���� ID�� ���� ���� ���� ������ ã�� �� �����ϴ�." << endl;
			return;
		}
	}

	cout << "���� : " << interest << "��" << endl;
	cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl;
}

const void AccountManager::withdraw() const {
	int balance;
	int id;
	int isDp;
	bool result;

	cout << "����ID: ";
	cin >> id;
	cout << "��ݾ�: ";
	cin >> balance;
	cout << "���� ����(�Ϲ�: 0, ����: 1): ";
	cin >> isDp;

	if (this->accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	if (balance < 1) {
		cout << "����� 1�� �̻��̾�� �մϴ�.";
		return;
	}

	balance *= -1;
	if (!isDp) {
		try {
			result = this->findAccount(id)->addBalance(balance);
		} catch (exception) {
			cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
			return;
		}
	}

	else {
		try {
			result = this->findDpAccount(id)->addBalance(balance);
		} catch (exception) {
			cout << "�ش� ���� ID�� ���� ���� ���� ������ ã�� �� �����ϴ�." << endl;
			return;
		}
	}

	
	if (result)
		cout << "����� �Ϸ�Ǿ����ϴ�." << endl;
	else
		cout << "�ܾ��� �����մϴ�." << endl;
}

const void AccountManager::seeList() const {
	if (this->accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	cout << "----�Ϲ�-----" << endl;
	for (int i = 0; i < this->accountSize; i++) {
		cout << "����ID: " << accounts[i].getAccId() << endl;
		cout << "��  ��: " << accounts[i].getCusName() << endl;
		cout << "��  ��: " << accounts[i].getBalance() << endl;

		if (i < this->accountSize - 1)
			cout << endl;
	}

	cout << endl << "----����----" << endl;
	for (int i = 0; i < this->dpAccountSize; i++) {
		cout << "����ID: " << dpAccounts[i].getAccId() << endl;
		cout << "��  ��: " << dpAccounts[i].getCusName() << endl;
		cout << "��  ��: " << dpAccounts[i].getBalance() << endl;

		if (i < this->accountSize - 1)
			cout << endl;
	}
	
	cout << endl;
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