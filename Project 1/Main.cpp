
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "stdafx.h"

#include <my_global.h>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")

#define _DB_FILE_ "C:\\Users\\Ryan Park\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication2\\Debug\\test.txt"

#define DB_HOST "58.225.25.213"	// DB IP주소 또는 도메인 또는 localhost
#define DB_USER "root"		// DB접속 계정 명
#define DB_PASS "cy59n05y5"		// DB접속 계정 암호
#define DB_NAME "Coindex_User"		// DB 이름

using namespace std;

// 유저 정보
string userIndex;
string userID;
string userPW;
string userWallet;
string userMail;

// SQL 구조체
MYSQL *connection = NULL, conn;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;
int query_stat;

void currentBuffer(void)
{
	cout << "아이디 : " << userID << endl;
	cout << "비밀번호 : " << userPW << endl;
	cout << "지갑주소 : " << userWallet << endl;
	cout << "메일주소 : " << userMail << endl;
}
bool SQLConnect(void)
{
	// 초기화
	mysql_init(&conn);

	// DB 연결
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}

	//한글사용을위해추가.
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
	query_stat = mysql_query(connection, query_char); // 쿼리 전송, 스탯 대기

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
	query_stat = mysql_query(connection, query_char); // 쿼리 전송, 스탯 대기

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
	query_stat = mysql_query(connection, query_char); // 쿼리 전송, 스탯 대기

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
		fin >> userIndex >> userID >> userPW >> userWallet >> userMail; // 파일에서 정보 읽어옴
		cout << "File Read. \n" << endl;
		fin.close();
	}
}
bool CloudValidation(void)
{
	// 클라우드에 접속

	// 클라우드에서 정보 읽어옴

	// DB파일과 클라우드 정보 비교

	return false; // 같으면 참, 다르면 거짓

}
bool WalletBalanceCheck(char &userID, char &userPW, unsigned int &Balance)
{
	// DB 연결 여부 확인 (SQL 서버, 클라우드 ...)

	// ID/PW 요청 쿼리 작성 (userID && userPW = ?)

	// 작성한 쿼리 보내고 결과 배열 읽어오기

	return false; // 결과 배열의 수가 1이면 참, 아니면 거짓

}

int main()
{
	short buf;
	int index;
	cout << "0 : 프로그램 종료" << endl;
	cout << "1 : 파일을 읽어 버퍼에 저장" << endl;
	cout << "2 : DB로부터 정보를 불러와 화면에 출력" << endl;
	cout << "3 : 테이블의 #번 행에 현재 버퍼에 저장된 값 업로드" << endl;
	cout << "4 : 테이블의 #번 행을 삭제" << endl;
	cout << "5 : 현재 버퍼의 정보 조회" << endl;
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
			cout << " 삽입할 행 번호 : ";
			cin >> index;
			SQLInsert(index);
			break;
		case 4:
			cout << " 삭제할 행 번호 : ";
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

