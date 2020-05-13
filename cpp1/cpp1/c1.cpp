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

	cout << "계좌ID: ";
	cin >> id;
	cout << "이름: ";
	cin >> name;
	cout << "입금액: ";
	cin >> balance;

	if (accountSize == ACCOUNT_MAX) {
		cout << "계좌가 이미 " << ACCOUNT_MAX << "개입니다." << endl;
		return;
	}

	find = findAccountIdx(id);
	if (find != -1) {
		cout << "이미 동일한 계좌 번호를 가진 계좌가 존재합니다." << endl;
		return;
	}

	if (balance < 10) {
		cout << "계좌 생성 시 최소 10원 이상의 돈을 입금해야합니다." << endl;
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

	cout << "계좌ID: ";
	cin >> id;
	cout << "입금액: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	find = findAccountIdx(id);
	if (find == -1) {
		cout << "해당 계좌 ID를 가진 계좌 정보를 찾을 수 없습니다." << endl;
		return;
	}

	accounts[find].balance += balance;
	cout << "입금이 완료되었습니다." << endl;
}

void withdraw() {
	int balance;
	int id, find;

	cout << "계좌ID: ";
	cin >> id;
	cout << "출금액: ";
	cin >> balance;

	if (accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	find = findAccountIdx(id);
	if (find == -1) {
		cout << "해당 계좌 ID를 가진 계좌 정보를 찾을 수 없습니다." << endl;
		return;
	}

	if (accounts[find].balance < balance) {
		cout << "잔액이 부족합니다." << endl;
		return;
	}

	accounts[find].balance -= balance;
	cout << "출금이 완료되었습니다." << endl;
}

void seeList() {
	if (accountSize == 0) {
		cout << "현재 등록된 계좌 정보가 없습니다." << endl;
		return;
	}

	for (int i = 0; i < accountSize; i++) {
		cout << "계좌ID: " << accounts[i].accId << endl;
		cout << "이  름: " << accounts[i].cusName << endl;
		cout << "잔  액: " << accounts[i].balance << endl;

		if (i < accountSize - 1)
			cout << endl;
	}
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
		cout << "-----Menu-----" << endl;
		cout << "1. 계좌개설" << endl;
		cout << "2. 입    금" << endl;
		cout << "3. 출    금" << endl;
		cout << "4. 계좌정보 전체 출력" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << "선택: ";
		cin >> input;

		if (input == 5)
			return 0;

		duty(input);
	}
}