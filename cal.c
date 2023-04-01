/*
Comments in this code file are Korean but there're English interfaces
Calendar Program (I designed Algorithms of this program with Gregorian Calendar theory so this is able to show ALL years & monthes)
(You can change displaying calendar with << < > >> buttons (from left: previous year, previous month, following month, following year)
move your cursor with the Arrow Keys and click Enter to select
This program runs on Default Command Window.

달력 프로그램 (프로그램 알고리즘은 그레고리력 역법 이론을 바탕으로 제작하여 모든 연도와 월의 달력 출력이 가능함)
<< < > >> 버튼을 통해 출력하는 달력을 바꿀 수 있다 (왼쪽부터: 이전 연도, 이전 달, 다음 달, 다음 연도)
화살표 키로 커서를 움직이고 Enter 를 눌러 동작을 선택
기본 커맨드 창에서 실행되는 프로그램.
*/
#pragma warning(disable:4996) //scanf 에러 제거
#include <stdio.h>
#include <Windows.h> //windows 함수에 필요(gotoxy, getCursor)
#include <conio.h> //키 입력값 감지 함수에 필요 (console io, 비공식/대중적 함수)

//define: 특정 스트링을 상수 값으로
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define _CRT_SECURE_NO_WARNINGS

int DisplayCalendar(int firstday, int lastday, int year, int month); //달 단위 출력
int Janfirstday(int year); //n년 1월 1일 요일
int LeapyearConfirm(int year); //윤년이면 1, 아니면 0 리턴
int Clear(int x, int y, int targetx, int targety); //영역을 지정하여 지우는 함수
void gotoxy(int x, int y); //출력 좌표 변경 
void setTextColour(int textcolour, int bgcolour); //출력 텍스트 색 변경
COORD getCursor(void); //현재 좌표 가져오기

void main() {

	//변수선언
	int firstday; //n월의 첫 요일
	//1:sun 2:mon 3:tue 4:wed 5:thu 6:fri 7:sat
	int year; //해
	int month; //달
	int monthlength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //달 길이, 일정하므로 상수값 저장 (윤년이면 2월은 변경)
	int key; //입력받은 키
	int quit = 0; //반복종료에 사용
	int swapmonth = 0; //달을 바꾸기 위해 중간에 있는 반복문 종료에 사용
	int posM = 24; //좌표를 기억해야 할 때 사용, 최초는 달력 출력할 좌표

	COORD pos = getCursor(); //좌표
	pos.X = 0;
	pos.Y = 0;

	setTextColour(15, 0); //기본값으로 출력 텍스트 색 초기화
	gotoxy(0, 0); //좌표 리셋

	//출력할 년도, 달 입력받기
	printf("\n출력할 연도와 달을 입력하세요.\nType year and month to print.\n");
	scanf("%d %d", &year, &month);
	Clear(0, 0, 80, 50);

	while (quit < 1) {

		if (LeapyearConfirm(year) == 1) {
			monthlength[1] = 29; //윤년이면 2월을 29일로
		}


		//목표 달 달력 출력
		firstday = (Janfirstday(year));
		for (int count = 0; count < month - 1; count++) { 
			//각 달의 1일 요일을 구함, firstday 는 다음 달 첫번째 요일
			if (monthlength[count] == 31)
				firstday += 3;
			if (monthlength[count] == 30)
				firstday += 2;
			if (monthlength[count] == 29)
				firstday += 1;
			if (firstday > 7)
				firstday -= 7;
		}
		DisplayCalendar(firstday, monthlength[month - 1], year, month);  //출력

		pos = getCursor();

		gotoxy(posM, 2);

		while (swapmonth < 1) { //여기부터 달/년 바뀔때까지 반복
			if (kbhit() == 1) {
				key = _getch();  //키가 눌렸을 때 값 가져오기
				pos = getCursor(); //현재좌표 저장
				if (key == 224) { //2자리 ASCII 인 경우 :
					key = _getch();
					switch (key) { //좌우, Enter 구현 (define 상수 이용), 화살표에서는 정해진 칸으로 움직임
					
					case LEFT:
						if (pos.X == 46 && pos.Y == 2 || (pos.X == 27 && pos.Y == 2)) // >> 에 있을 때
							gotoxy((pos.X - 3), pos.Y);
						else if (pos.X == 43 && pos.Y == 2)
							gotoxy(27, pos.Y);
						else if (pos.X == 24 && pos.Y == 2)
							gotoxy(46, 2);
						
						pos = getCursor();
						break;
					case RIGHT:
						if ((pos.X == 24 && pos.Y == 2) || (pos.X == 43 && pos.Y == 2)) // << 에 있을 때
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
				case 113:   //종료를 위한 Q,q 값
				case 81:
					quit++;
					swapmonth++; //모두 종료
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
						posM = pos.X; //다음 출력 때 커서 위치가 유지되도록 좌표 저장
						swapmonth++;
					}
					break;
				}
			}
		}
		//swapmonth (키 값 액션) 반복 종료 후
		Clear(0, 0, 400, 16);
		swapmonth--;  //switch 문 반복에 사용되는 변수 값 리셋
		if (month > 12) {
			month = 1;
			year++;
		}
		if (month < 1) {
			month = 12;
			year--;
		}                 //13월, 0월, 0년 없애기
		if (year < 1)
			year = 1;
	}
}
int Janfirstday(int year) { //n년 1월 1일 계산
	int leapyear; //윤년개수
	int janfirstday; //n년 1월 1일의 요일
	int returnday;
	leapyear = (year / 4) - (year / 100) + (year / 400); //윤년 개수
	//4년에 한번은 윤년, 100년에 한번은 윤년이 아니고, 400년에 한번은 윤년

	janfirstday = (year + leapyear) % 7; //목표 년도에 윤년 개수를 더하고 7로 나눈 나머지가 1월 1일 요일
	if (janfirstday == 0) //7이 나오면 나머지가 0이므로 0은 7로 변환
		janfirstday = 7;

	returnday = janfirstday + 1;
	if (returnday > 7)
		returnday = 1;
	//printf("%d년 1월 1일은 %d\n", year, returnday);
	return returnday; //(year) 년의 1월 1일 요일 반환
}
int DisplayCalendar(int firstday, int lastday, int year, int month) { //달 형식으로 달력 출력
	int day = 1;
	int location = (firstday); //현재 위치(7 넘으면 다음 줄)

	printf("\n\n\t\t\t<< < %d\t%d", year, month);
	gotoxy(43, 2);
	printf(">");
	gotoxy(45, 2); //\t를 쓰면 숫자 자릿수에 따라 화살표 위치가 달라지므로 절대좌표로 이동
	printf(">>");

	//요일 출력 (일요일, 토요일 색 변경)
	printf("\n\n\t");
	setTextColour(12, 0); //일요일은 레드
	printf("SUN");
	setTextColour(15, 0);

	printf("\tMON\tTUE\tWED\tTHU\tFRI\t"); //나머지 요일 표시

	setTextColour(3, 0); //토요일은 블루
	printf("SAT");
	setTextColour(15, 0);
	printf("\n");

	for (int count = 0; count < firstday; count++) //firstday 만큼 첫 표시 간격 추가
		printf("\t");

	for (day = 1; day <= lastday; day++) {
		if (location > 7) {
			printf("\n\t");
			location = 1;
		}
		if (location == 1) //일요일이면 레드로
			setTextColour(12, 0);
		if (location == 7) //토요일이면 블루로
			setTextColour(3, 0);

		printf("%d\t", day);
		setTextColour(15, 0); //색 원상복귀
		location++;
	}
	gotoxy(4, 12);
	for (int count = 0; count < 59; count++)
		printf("_");
	for (int count = 0; count < 11; count++) {      //날짜 존 경계선 출력
		gotoxy(63, (12 - count));
		printf("|");
	}
	return 0;


}
int LeapyearConfirm(int year) { //윤년이면 1, 평년이면 0 리턴
	if (year % 4 == 0 && year % 100 != 0) { //4의 배수고 100의 배수가 아니면 윤년
		return 1;
	}
	else if (year % 400 == 0) { //단 400의 배수면 윤년
		return 1;
	}
	else
		return 0;  //그것도 아니면 평년
}

COORD getCursor(void) { //현재 커서 좌표 가져오는 함수, gotoxy 와 같이 사용
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO pos;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos);
	curPoint.X = pos.dwCursorPosition.X;
	curPoint.Y = pos.dwCursorPosition.Y;
	return curPoint;
}
void gotoxy(int x, int y) {  //x, y를 넣으면 값 출력위치를 바꾸는 함수, 화면 왼쪽 위 끝이 (0,0), 오른쪽으로 x 증가, 밑으로 y증가이다.
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void setTextColour(int textcolour, int bgcolour) { //출력 텍스트 색 변경 함수
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
