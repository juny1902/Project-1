
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "stdafx.h"

#include <my_global.h>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")

#define _DB_FILE_ "C:\\Users\\Ryan Park\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication2\\Debug\\test.txt"

#define DB_HOST "58.225.25.213"	// DB IP�ּ� �Ǵ� ������ �Ǵ� localhost
#define DB_USER "root"		// DB���� ���� ��
#define DB_PASS "cy59n05y5"		// DB���� ���� ��ȣ
#define DB_NAME "Coindex_User"		// DB �̸�

using namespace std;

// ���� ����
string userIndex;
string userID;
string userPW;
string userWallet;
string userMail;

// SQL ����ü
MYSQL *connection = NULL, conn;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;
int query_stat;

void currentBuffer(void)
{
	cout << "���̵� : " << userID << endl;
	cout << "��й�ȣ : " << userPW << endl;
	cout << "�����ּ� : " << userWallet << endl;
	cout << "�����ּ� : " << userMail << endl;
}
bool SQLConnect(void)
{
	// �ʱ�ȭ
	mysql_init(&conn);

	// DB ����
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}

	//�ѱۻ���������߰�.
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");
	return false;
}
bool SQLInsert(int indexID)
{
	SQLConnect();

	string query = "Insert into USER (id, USER_ID, USER_PW, USER_WALLET, USER_MAIL) values ('" + to_string(indexID) + "','" + userID + "','" + userPW + "','" + userWallet + "','" + userMail + "')";
	const char* query_char = query.c_str();
	query_stat = mysql_query(connection, query_char); // ���� ����, ���� ���

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	mysql_close(connection);
	return 0;
}
bool SQLDeleteLine(int indexID)
{
	SQLConnect();

	string query = "DELETE FROM USER WHERE id = " + to_string(indexID);
	const char* query_char = query.c_str();
	query_stat = mysql_query(connection, query_char); // ���� ����, ���� ���

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	mysql_close(connection);
	return 0;
}
bool getSQL(void)
{
	SQLConnect();

	string query = "SELECT * FROM USER";
	const char* query_char = query.c_str();
	query_stat = mysql_query(connection, query_char); // ���� ����, ���� ���

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_use_result(connection);
	sql_row = mysql_fetch_row(sql_result);

	cout << sql_row[0] << sql_row[1] << sql_row[2] << sql_row[3] << sql_row[4] << endl;

	mysql_close(connection);
	return 0;
}
void FileRead(void)
{
	ifstream fin;
	fin.open(_DB_FILE_);

	if (fin.is_open() == false)
	{
		cout << "Failed to open DB file." << endl;
		return;
	}
	else
	{
		fin >> userIndex >> userID >> userPW >> userWallet >> userMail; // ���Ͽ��� ���� �о��
		cout << "File Read. \n" << endl;
		fin.close();
	}
}
bool CloudValidation(void)
{
	// Ŭ���忡 ����

	// Ŭ���忡�� ���� �о��

	// DB���ϰ� Ŭ���� ���� ��

	return false; // ������ ��, �ٸ��� ����

}
bool WalletBalanceCheck(char &userID, char &userPW, unsigned int &Balance)
{
	// DB ���� ���� Ȯ�� (SQL ����, Ŭ���� ...)

	// ID/PW ��û ���� �ۼ� (userID && userPW = ?)

	// �ۼ��� ���� ������ ��� �迭 �о����

	return false; // ��� �迭�� ���� 1�̸� ��, �ƴϸ� ����

}

int main()
{
	short buf;
	int index;
	cout << "0 : ���α׷� ����" << endl;
	cout << "1 : ������ �о� ���ۿ� ����" << endl;
	cout << "2 : DB�κ��� ������ �ҷ��� ȭ�鿡 ���" << endl;
	cout << "3 : ���̺��� #�� �࿡ ���� ���ۿ� ����� �� ���ε�" << endl;
	cout << "4 : ���̺��� #�� ���� ����" << endl;
	cout << "5 : ���� ������ ���� ��ȸ" << endl;
	while (1)
	{
		cout << ".....";
		cin >> buf;
		
		if (buf == false) break;

		switch (buf)
		{
		case 1: 
			FileRead(); 
			break;
		case 2: 
			getSQL(); 
			break;
		case 3: 
			cout << " ������ �� ��ȣ : ";
			cin >> index;
			SQLInsert(index);
			break;
		case 4:
			cout << " ������ �� ��ȣ : ";
			cin >> index;
			SQLDeleteLine(index); 
			break;
		case 5: 
			currentBuffer(); 
			break;
		default: 
			break;
		}
	}
}

