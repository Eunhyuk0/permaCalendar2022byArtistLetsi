/*
Comments in this code file are Korean but there're English interfaces
Calendar Program (I designed Algorithms of this program with Gregorian Calendar theory so this is able to show ALL years & monthes)
(You can change displaying calendar with << < > >> buttons (from left: previous year, previous month, following month, following year)
move your cursor with the Arrow Keys and click Enter to select
This program runs on Default Command Window.

�޷� ���α׷� (���α׷� �˰����� �׷����� ���� �̷��� �������� �����Ͽ� ��� ������ ���� �޷� ����� ������)
<< < > >> ��ư�� ���� ����ϴ� �޷��� �ٲ� �� �ִ� (���ʺ���: ���� ����, ���� ��, ���� ��, ���� ����)
ȭ��ǥ Ű�� Ŀ���� �����̰� Enter �� ���� ������ ����
�⺻ Ŀ�ǵ� â���� ����Ǵ� ���α׷�.
*/
#pragma warning(disable:4996) //scanf ���� ����
#include <stdio.h>
#include <Windows.h> //windows �Լ��� �ʿ�(gotoxy, getCursor)
#include <conio.h> //Ű �Է°� ���� �Լ��� �ʿ� (console io, �����/������ �Լ�)

//define: Ư�� ��Ʈ���� ��� ������
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define _CRT_SECURE_NO_WARNINGS

int DisplayCalendar(int firstday, int lastday, int year, int month); //�� ���� ���
int Janfirstday(int year); //n�� 1�� 1�� ����
int LeapyearConfirm(int year); //�����̸� 1, �ƴϸ� 0 ����
int Clear(int x, int y, int targetx, int targety); //������ �����Ͽ� ����� �Լ�
void gotoxy(int x, int y); //��� ��ǥ ���� 
void setTextColour(int textcolour, int bgcolour); //��� �ؽ�Ʈ �� ����
COORD getCursor(void); //���� ��ǥ ��������

void main() {

	//��������
	int firstday; //n���� ù ����
	//1:sun 2:mon 3:tue 4:wed 5:thu 6:fri 7:sat
	int year; //��
	int month; //��
	int monthlength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //�� ����, �����ϹǷ� ����� ���� (�����̸� 2���� ����)
	int key; //�Է¹��� Ű
	int quit = 0; //�ݺ����ῡ ���
	int swapmonth = 0; //���� �ٲٱ� ���� �߰��� �ִ� �ݺ��� ���ῡ ���
	int posM = 24; //��ǥ�� ����ؾ� �� �� ���, ���ʴ� �޷� ����� ��ǥ

	COORD pos = getCursor(); //��ǥ
	pos.X = 0;
	pos.Y = 0;

	setTextColour(15, 0); //�⺻������ ��� �ؽ�Ʈ �� �ʱ�ȭ
	gotoxy(0, 0); //��ǥ ����

	//����� �⵵, �� �Է¹ޱ�
	printf("\n����� ������ ���� �Է��ϼ���.\nType year and month to print.\n");
	scanf("%d %d", &year, &month);
	Clear(0, 0, 80, 50);

	while (quit < 1) {

		if (LeapyearConfirm(year) == 1) {
			monthlength[1] = 29; //�����̸� 2���� 29�Ϸ�
		}


		//��ǥ �� �޷� ���
		firstday = (Janfirstday(year));
		for (int count = 0; count < month - 1; count++) { 
			//�� ���� 1�� ������ ����, firstday �� ���� �� ù��° ����
			if (monthlength[count] == 31)
				firstday += 3;
			if (monthlength[count] == 30)
				firstday += 2;
			if (monthlength[count] == 29)
				firstday += 1;
			if (firstday > 7)
				firstday -= 7;
		}
		DisplayCalendar(firstday, monthlength[month - 1], year, month);  //���

		pos = getCursor();

		gotoxy(posM, 2);

		while (swapmonth < 1) { //������� ��/�� �ٲ𶧱��� �ݺ�
			if (kbhit() == 1) {
				key = _getch();  //Ű�� ������ �� �� ��������
				pos = getCursor(); //������ǥ ����
				if (key == 224) { //2�ڸ� ASCII �� ��� :
					key = _getch();
					switch (key) { //�¿�, Enter ���� (define ��� �̿�), ȭ��ǥ������ ������ ĭ���� ������
					
					case LEFT:
						if (pos.X == 46 && pos.Y == 2 || (pos.X == 27 && pos.Y == 2)) // >> �� ���� ��
							gotoxy((pos.X - 3), pos.Y);
						else if (pos.X == 43 && pos.Y == 2)
							gotoxy(27, pos.Y);
						else if (pos.X == 24 && pos.Y == 2)
							gotoxy(46, 2);
						
						pos = getCursor();
						break;
					case RIGHT:
						if ((pos.X == 24 && pos.Y == 2) || (pos.X == 43 && pos.Y == 2)) // << �� ���� ��
							gotoxy((pos.X + 3), pos.Y);
						else if (pos.X == 27 && pos.Y == 2)
							gotoxy(43, pos.Y);
						else if (pos.X == 46 && pos.Y == 2)
							gotoxy(24, 2);
						
						pos = getCursor();
						break;
					}
				}
				switch (key) {
				case 113:   //���Ḧ ���� Q,q ��
				case 81:
					quit++;
					swapmonth++; //��� ����
					break;
				case ENTER:
					if (pos.Y == 2) {
						if ((pos.X == 46) || (pos.X == 45))
							year++;
						if (pos.X == 24)
							year--;
						if (pos.X == 27)
							month--;
						if ((pos.X == 43) || (pos.X == 42))
							month++;
						pos = getCursor();
						posM = pos.X; //���� ��� �� Ŀ�� ��ġ�� �����ǵ��� ��ǥ ����
						swapmonth++;
					}
					break;
				}
			}
		}
		//swapmonth (Ű �� �׼�) �ݺ� ���� ��
		Clear(0, 0, 400, 16);
		swapmonth--;  //switch �� �ݺ��� ���Ǵ� ���� �� ����
		if (month > 12) {
			month = 1;
			year++;
		}
		if (month < 1) {
			month = 12;
			year--;
		}                 //13��, 0��, 0�� ���ֱ�
		if (year < 1)
			year = 1;
	}
}
int Janfirstday(int year) { //n�� 1�� 1�� ���
	int leapyear; //���ⰳ��
	int janfirstday; //n�� 1�� 1���� ����
	int returnday;
	leapyear = (year / 4) - (year / 100) + (year / 400); //���� ����
	//4�⿡ �ѹ��� ����, 100�⿡ �ѹ��� ������ �ƴϰ�, 400�⿡ �ѹ��� ����

	janfirstday = (year + leapyear) % 7; //��ǥ �⵵�� ���� ������ ���ϰ� 7�� ���� �������� 1�� 1�� ����
	if (janfirstday == 0) //7�� ������ �������� 0�̹Ƿ� 0�� 7�� ��ȯ
		janfirstday = 7;

	returnday = janfirstday + 1;
	if (returnday > 7)
		returnday = 1;
	//printf("%d�� 1�� 1���� %d\n", year, returnday);
	return returnday; //(year) ���� 1�� 1�� ���� ��ȯ
}
int DisplayCalendar(int firstday, int lastday, int year, int month) { //�� �������� �޷� ���
	int day = 1;
	int location = (firstday); //���� ��ġ(7 ������ ���� ��)

	printf("\n\n\t\t\t<< < %d\t%d", year, month);
	gotoxy(43, 2);
	printf(">");
	gotoxy(45, 2); //\t�� ���� ���� �ڸ����� ���� ȭ��ǥ ��ġ�� �޶����Ƿ� ������ǥ�� �̵�
	printf(">>");

	//���� ��� (�Ͽ���, ����� �� ����)
	printf("\n\n\t");
	setTextColour(12, 0); //�Ͽ����� ����
	printf("SUN");
	setTextColour(15, 0);

	printf("\tMON\tTUE\tWED\tTHU\tFRI\t"); //������ ���� ǥ��

	setTextColour(3, 0); //������� ���
	printf("SAT");
	setTextColour(15, 0);
	printf("\n");

	for (int count = 0; count < firstday; count++) //firstday ��ŭ ù ǥ�� ���� �߰�
		printf("\t");

	for (day = 1; day <= lastday; day++) {
		if (location > 7) {
			printf("\n\t");
			location = 1;
		}
		if (location == 1) //�Ͽ����̸� �����
			setTextColour(12, 0);
		if (location == 7) //������̸� ����
			setTextColour(3, 0);

		printf("%d\t", day);
		setTextColour(15, 0); //�� ���󺹱�
		location++;
	}
	gotoxy(4, 12);
	for (int count = 0; count < 59; count++)
		printf("_");
	for (int count = 0; count < 11; count++) {      //��¥ �� ��輱 ���
		gotoxy(63, (12 - count));
		printf("|");
	}
	return 0;


}
int LeapyearConfirm(int year) { //�����̸� 1, ����̸� 0 ����
	if (year % 4 == 0 && year % 100 != 0) { //4�� ����� 100�� ����� �ƴϸ� ����
		return 1;
	}
	else if (year % 400 == 0) { //�� 400�� ����� ����
		return 1;
	}
	else
		return 0;  //�װ͵� �ƴϸ� ���
}

COORD getCursor(void) { //���� Ŀ�� ��ǥ �������� �Լ�, gotoxy �� ���� ���
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO pos;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos);
	curPoint.X = pos.dwCursorPosition.X;
	curPoint.Y = pos.dwCursorPosition.Y;
	return curPoint;
}
void gotoxy(int x, int y) {  //x, y�� ������ �� �����ġ�� �ٲٴ� �Լ�, ȭ�� ���� �� ���� (0,0), ���������� x ����, ������ y�����̴�.
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void setTextColour(int textcolour, int bgcolour) { //��� �ؽ�Ʈ �� ���� �Լ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textcolour | (bgcolour << 4));
}
int Clear(int x, int y, int targetx, int targety) {
	COORD nowPos;
	nowPos.X = x;
	nowPos.Y = y;
	COORD targetPos;
	targetPos.X = targetx;
	targetPos.Y = targety;
	gotoxy(nowPos.X, nowPos.Y);
	for (int ypos = nowPos.Y; ypos < targetPos.Y; ypos++) {
		for (int xpos = nowPos.X; xpos < targetPos.X; xpos++) {
			printf(" ");
			xpos++;
		}
		ypos++;
		gotoxy(nowPos.X, ypos);
	}
	gotoxy(x, y);
	return 0;
}
