#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

#define NAME_LEN 20
#define ACCOUNT_MAX 100

typedef struct {
	int accId;
	int balance;
	char cusName[NAME_LEN];
} Account;

typedef enum {
	MK_ACC = 1,
	DEPOSIT = 2,
	WITHDRAW = 3,
	SEE_LIST = 4
} DUTY_LIST;

Account* accounts = new Account[ACCOUNT_MAX];
int accountSize = 0;

int findAccountIdx(int id) {
	for (int i = 0; i < accountSize; i++) {
		if (accounts[i].accId == id)
			return i;
	}

	return -1;
}

void mkAcc() {
	char name[NAME_LEN];
	int balance;
	int id, find;

	cout << "����ID: ";
	cin >> id;
	cout << "�̸�: ";
	cin >> name;
	cout << "�Աݾ�: ";
	cin >> balance;

	if (accountSize == ACCOUNT_MAX) {
		cout << "���°� �̹� " << ACCOUNT_MAX << "���Դϴ�." << endl;
		return;
	}

	find = findAccountIdx(id);
	if (find != -1) {
		cout << "�̹� ������ ���� ��ȣ�� ���� ���°� �����մϴ�." << endl;
		return;
	}

	if (balance < 10) {
		cout << "���� ���� �� �ּ� 10�� �̻��� ���� �Ա��ؾ��մϴ�." << endl;
		return;
	}

	accounts[accountSize].accId = id;
	accounts[accountSize].balance = balance;
	strcpy(accounts[accountSize++].cusName, name);

	return;
}

void deposit() {
	int balance;
	int id, find;

	cout << "����ID: ";
	cin >> id;
	cout << "�Աݾ�: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	find = findAccountIdx(id);
	if (find == -1) {
		cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
		return;
	}

	accounts[find].balance += balance;
	cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl;
}

void withdraw() {
	int balance;
	int id, find;

	cout << "����ID: ";
	cin >> id;
	cout << "��ݾ�: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	find = findAccountIdx(id);
	if (find == -1) {
		cout << "�ش� ���� ID�� ���� ���� ������ ã�� �� �����ϴ�." << endl;
		return;
	}

	if (accounts[find].balance < balance) {
		cout << "�ܾ��� �����մϴ�." << endl;
		return;
	}

	accounts[find].balance -= balance;
	cout << "����� �Ϸ�Ǿ����ϴ�." << endl;
}

void seeList() {
	if (accountSize == 0) {
		cout << "���� ��ϵ� ���� ������ �����ϴ�." << endl;
		return;
	}

	for (int i = 0; i < accountSize; i++) {
		cout << "����ID: " << accounts[i].accId << endl;
		cout << "��  ��: " << accounts[i].cusName << endl;
		cout << "��  ��: " << accounts[i].balance << endl;

		if (i < accountSize - 1)
			cout << endl;
	}
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
		cout << "-----Menu-----" << endl;
		cout << "1. ���°���" << endl;
		cout << "2. ��    ��" << endl;
		cout << "3. ��    ��" << endl;
		cout << "4. �������� ��ü ���" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << "����: ";
		cin >> input;

		if (input == 5)
			return 0;

		duty(input);
	}
}