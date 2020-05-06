#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

#define NAME_LEN 20

typedef struct {
	int accId;
	int balance;
	char cusName[NAME_LEN];
} Account;

Account* accounts = new Account[100];
int accountSize = 0;

int findAccountIdx(int id) {
	for (int i = 0; i < accountSize; i++) {
		if (accounts[i].accId == id)
			return i;
	}

	return -1;
}

void duty(int input) {
	int id;
	int find;

	switch (input) {
	case 1:
		char name[NAME_LEN];
		int balance;

		cout << "[���°���]" << endl;
		cout << "����ID: ";
		cin >> id;
		cout << "�̸�: ";
		cin >> name;
		cout << "�Աݾ�: ";
		cin >> balance;

		if (accountSize == 100) {
			cout << "���°� �̹� 100���Դϴ�." << endl;
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
	case 2:
		cout << "[��    ��]" << endl;
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

		return;
	case 3:
		cout << "[��    ��]" << endl;

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

		return;
	case 4:
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

		return;
	default:
		cout << "�ùٸ��� ���� ��ȣ�Դϴ�." << endl;
		return;
	}
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

		cout << endl;
		duty(input);
		cout << endl;
	}
}