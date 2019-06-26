#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#define N 10

using namespace std;

struct Object{
	int xPosition;
	int yPosition;
	unsigned char zn;
	chtype ozn;
};

struct Object obj[N] = {};

int wbox = 0;  //@,상자의 갯수
int lev = 0;	 //맵의 순서
int cnt = 0;   //움직인 횟수(step)
int push = 0;	 //상자를 민 횟수

void levList(int *h, int *w, int *array, int y, int x, int n) {
		//맵의 디자인. n은 level을 뜻함.
	if (n==0)
  {
    *h = 8;  //높이
    *w = 8;	 //가로
    int map0[8][8] = { //0 은 빈부분, 1은 벽, 2는 목적지, 4는 박스, 5는 플레이어를 나타낸다.
    {0,0,1,1,1,0,0,0},
    {0,0,1,2,1,0,0,0},
    {0,0,1,0,1,1,1,1},
    {1,1,1,4,0,4,2,1},
    {1,2,0,4,5,1,1,1},
    {1,1,1,1,4,1,0,0},
    {0,0,0,1,2,1,0,0},
    {0,0,0,1,1,1,0,0}};
    *array = map0[y][x];
}
  else if(n==1)
  {
    *h = 8;
    *w = 9;
    int map1[8][9] = {
    {1,1,1,1,1,1,1,0,0},
    {1,0,0,0,0,0,1,1,1},
    {1,0,0,5,4,4,2,2,1},
    {1,1,1,1,0,1,1,0,1},
    {0,0,1,0,0,0,0,0,1},
    {0,0,1,0,0,1,1,1,1},
    {0,0,1,0,0,1,0,0,0},
    {0,0,1,1,1,1,0,0,0}
  };
    *array = map1[y][x];
  }
  else if(n==2)
  {
    *h = 7;
    *w = 11;
    int map2[7][11] = {
  {1,1,1,1,1,1,1,0,0,0,0},
  {1,0,0,0,0,0,1,1,1,1,1},
  {1,0,4,4,1,5,1,1,2,2,1},
  {1,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,4,0,1,0,1,0,0,1},
  {1,1,1,1,0,4,0,0,2,2,1},
  {0,0,0,1,1,1,1,1,1,1,1}};
    *array = map2[y][x];
  }

  else if(n==3)
  {
    *h = 11;
    *w = 15;
    int map3[11][15] = {
    {0,0,0,0,0,0,0,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,4,1,0,0,0},
    {0,0,0,0,0,1,1,1,4,0,0,1,1,1,0},
    {1,1,1,1,1,1,0,4,0,0,4,0,0,1,1},
    {1,0,0,0,1,1,0,1,1,1,0,1,0,0,1},
    {1,2,2,0,0,0,0,1,1,1,0,0,4,0,1},
    {1,2,2,5,0,0,0,0,0,0,4,0,0,0,1},
    {1,2,2,0,1,0,0,1,1,1,0,1,1,1,1},
    {1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0}
    };
    *array = map3[y][x];
  }
  else if(n==4)
  {
    *h = 10;
    *w = 11;
    int map4[10][11] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,0,1},
    {1,0,4,5,4,4,4,4,4,0,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,1,1,1,1},
    {0,0,0,1,2,0,0,1,0,0,0},
    {0,0,0,1,2,0,0,1,0,0,0},
    {0,0,0,1,2,2,2,1,0,0,0},
    {0,0,0,1,2,0,0,1,0,0,0},
    {0,0,0,1,1,1,1,1,0,0,0}};
    *array = map4[y][x];
  }
}

void palette() {	// color pair 생성. 맵의 색 디자인
	init_color(COLOR_BLACK,0,0,0);
	init_pair(2,COLOR_RED,COLOR_BLACK) ;   //글씨색 빨강, 배경 검정
	init_pair(1,COLOR_GREEN,COLOR_BLACK);  //글씨색 초록, 배경 검정
	init_pair(3,COLOR_YELLOW,COLOR_BLACK); //글씨색 노랑, 배경 검정
	init_pair(4,COLOR_BLACK, COLOR_BLACK); //글씨색, 배경 검정
	init_pair(5,COLOR_CYAN,COLOR_BLACK);   //글씨 청록, 배경 검정
}

void level(int n) {
	clear();
	mvprintw(1, 1, "LittleStar's Edventure! Map ->%d", lev);  //작은별의 모험!
	mvprintw(2, 1, "Move-Keypad, Restart-R, Exit-Q");
	if (n==0){    //map0은 튜토리얼이므로 안내문을 출력해준다.
		mvprintw(0,8,"Tutorial ^^");
	}
	if (n==5){
		mvprintw(6,1,"******YOU DID IT!!!******");
	}
	int x = 0, y = 0, h = 1, w = 1, map;
	wbox = 0;

	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			levList(&h, &w, &map, y, x, n);
			switch (map) { // map에 있는 숫자를 문자로 바꿔주고, map을 실제로 화면에 구성하는 조건문.
			case 0:  //빈부분은 문자 '-'으로 표현.
				mvaddch(y + 5, x + 10, '-' | COLOR_PAIR(4));  //배열인덱스에 y+5,x+10를 통해 윈도우에 출력한다.
				break;
			case 1:  //벽부분은 문자 '#'으로 표현.
				mvaddch(y + 5, x + 10, '#' | COLOR_PAIR(1));
				break;
			case 2:  //목적지부분은 문자 'x'으로 표현.
				mvaddch(y + 5, x + 10, 'x' | COLOR_PAIR(2));
				break;
			case 4:  //박스부분은 문자 '@'으로 표현하지만 박스가 움직여도 뒷배경이 '-'로 보이도록 해줌.
				mvaddch(y + 5, x + 10, '-' | COLOR_PAIR(4));
				wbox += 1;  //총 박스수를 셈.
				obj[wbox].ozn = mvinch(y + 5, x + 10);
				obj[wbox].yPosition = y + 5;
				obj[wbox].xPosition = x + 10;
				obj[wbox].zn = '@';
				mvaddch(obj[wbox].yPosition, obj[wbox].xPosition, obj[wbox].zn | COLOR_PAIR(5));
				break;
			case 5:  //플레이어부분 또한 박스부분처럼 움직여도 있던 자리에 '-'가 나오도록 해줌.
				mvaddch(y + 5, x + 10, '-' | COLOR_PAIR(4));
				obj[0].ozn = mvinch(y + 5, x + 10);
				obj[0].yPosition = y + 5;
				obj[0].xPosition = x + 10;
				obj[0].zn = '*';
				mvaddch(obj[0].yPosition, obj[0].xPosition, obj[0].zn | COLOR_PAIR(3));
				break;
			}
		}
	}
	move(obj[0].yPosition, obj[0].xPosition);
}

bool next(){  //목적지에 모든 상자가 도착할 시 다음으로 넘어가기위한 함수.
	chtype dest;
	int count = 0;   //목적지에 도착한 상자의 갯수를 셈.
	for (int i = 1; i <= wbox; i++){
	 dest = (mvinch(obj[i].yPosition, obj[i].xPosition) & A_CHARTEXT);
		if (dest == 120) count++;   //상자가 목적지에 있으면 count++;
	}
	if(count == wbox){  //총 상자의 갯수와 목적지에 도착한 상자의 갯수가 같으면 true 리턴.
		return TRUE;
	}
	else return FALSE;

}


void Play(int input) { //게임구현
	bool restart = FALSE;

	chtype up, lf, dw, rg, oup, olf, odw, org;
	up = (mvinch(obj[0].yPosition - 1, obj[0].xPosition) & A_CHARTEXT); //P의 위
	lf = (mvinch(obj[0].yPosition, obj[0].xPosition - 1) & A_CHARTEXT); //P의 왼쪽
	dw = (mvinch(obj[0].yPosition + 1, obj[0].xPosition) & A_CHARTEXT); //P의 아래
	rg = (mvinch(obj[0].yPosition, obj[0].xPosition + 1) & A_CHARTEXT); //P의 오른쪽
	oup = (mvinch(obj[0].yPosition - 2, obj[0].xPosition) & A_CHARTEXT); //P의 위의 위
	olf = (mvinch(obj[0].yPosition, obj[0].xPosition - 2) & A_CHARTEXT); //P의 왼쪽의 왼쪽
	odw = (mvinch(obj[0].yPosition + 2, obj[0].xPosition) & A_CHARTEXT); //P의 아래의 아래
	org = (mvinch(obj[0].yPosition, obj[0].xPosition + 2) & A_CHARTEXT); //P의 오른쪽의 오른

	for (int i = 0; i <= wbox; i++)
		mvaddch(obj[i].yPosition, obj[i].xPosition, obj[i].ozn); //P와 박스의 위치마다 기호 삽입

	switch (input) { //키를 입력받기

	case KEY_UP://윗 방향키를 입력받기
		if (up != 35) {//위가 벽이 아닐경우
			if (up == 64 && (oup == 45 || oup == 120)) {//위가 박스이고 바로 위가 벽이거나 빈공간일때
				obj[0].yPosition -= 1;//P를 위로 한칸 올리기
				for (int i = 1; i <= wbox; i++) {//P의 위에있는 박스 찾기
					if ((obj[0].yPosition == obj[i].yPosition) && (obj[0].xPosition == obj[i].xPosition)) {//P와 박스의 위치가 같을때
						obj[i].yPosition -= 1;//박스도 한칸 올리기
						push ++;//박스를 민 횟수가 1증가
					}
				}
			}
			else if ((up == 64 && oup == 35) || (up == 64 && oup == 64)) cnt--;//벽이랑 박스가 붙어있을때랑 박스랑 박스가 붙어있을때 움직인 횟수 증가하지않게 함
			else if (up != 64)//위에 박스가 없을시 P만 위치 이동
				obj[0].yPosition -= 1;
			cnt++;//움직인 횟수 증가
		}
		if(next() == TRUE){//박스를 목적지에 다 도달했을 시 다음 맵으로 자동으로 넘어가기
			restart = TRUE;
			if (lev < 2) lev += 1;
			else lev = 0;
			level(lev);
			cnt = 0;
			push = 0;
			break;
		}
		break;

	case KEY_DOWN:
		if (dw != 35) {
			if (dw == 64 && (odw == 45 || odw == 120)) {
				obj[0].yPosition += 1;
				for (int i = 1; i <= wbox; i++) {
					if ((obj[0].yPosition == obj[i].yPosition) && (obj[0].xPosition == obj[i].xPosition)) {
						obj[i].yPosition += 1;
						push ++;
					}

				}
			}
			else if ((dw == 64 && odw == 35) || (dw == 64 && odw == 64)) cnt--;
			else if (dw != 64)
				obj[0].yPosition += 1;
			cnt++;
		}if(next() == TRUE){
			attron(COLOR_PAIR(3));
			mvprintw(0, 1, "Complete!!!if you want to go next level, Press Any key");
			attroff(COLOR_PAIR(3));
			getch();
			restart = TRUE;
			if (lev < 5) lev += 1;
			else lev = 0;
			level(lev);
			cnt = 0;
			push = 0;
			break;
		}
		break;

	case KEY_LEFT:
		if (lf != 35) {
			if (lf == 64 && (olf == 45 || olf == 120)) {
				obj[0].xPosition -= 1;
					for (int i = 1; i <= wbox; i++) {
						if ((obj[0].yPosition == obj[i].yPosition) && (obj[0].xPosition == obj[i].xPosition)) {
							obj[i].xPosition -= 1;
							push ++;
						}
					}
			}
			else if ((lf == 64 && olf == 35) || (lf == 64 && olf == 64)) cnt--;
			else if (lf != 64)
				obj[0].xPosition -= 1;
			cnt++;
		}if(next() == TRUE){
			attron(COLOR_PAIR(3));
			mvprintw(0, 1, "Complete!!!if you want to go next level, Press Any key");
			attroff(COLOR_PAIR(3));
			getch();
			restart = TRUE;
			if (lev < 5) lev += 1;
			else lev = 0;
			level(lev);
			cnt = 0;
			push = 0;
			break;
		}
		break;

	case KEY_RIGHT:
		if (rg != 35) {
			if (rg == 64 && (org == 45 || org == 120)) {
				obj[0].xPosition += 1;
				for (int i = 1; i <= wbox; i++) {
					if ((obj[0].yPosition == obj[i].yPosition) && (obj[0].xPosition == obj[i].xPosition)) {
						obj[i].xPosition += 1;
						push ++;
					}
				}
			}
			else if ((rg == 64 && org == 35) || (rg == 64 && org == 64)) cnt--;
			else if (rg != 64)
				obj[0].xPosition += 1;
			cnt++;
		}if(next() == TRUE){
			attron(COLOR_PAIR(3));
			mvprintw(0, 1, "Complete!!!if you want to go next level, Press Any key");
			attroff(COLOR_PAIR(3));
			getch();
			restart = TRUE;
			if (lev < 5) lev += 1;
			else lev = 0;
			level(lev);
			cnt = 0;
			push = 0;
			break;
		}
		break;




		case 'r':
		case 'R'://R키를 눌렀을때 재시작하기
			restart = TRUE;
			level(lev);//맵 불러오기
			cnt = 0;//박스푸쉬 횟수, 이동횟수 초기화
			push = 0;
			break;
		default:
			break;
		}
		if (!restart) {//restart 가 true일때
			for (int i = 0; i <= wbox; i++) {
				obj[i].ozn = mvinch(obj[i].yPosition, obj[i].xPosition);//박스위치값 받기
				mvaddch(obj[i].yPosition, obj[i].xPosition, obj[i].zn | ((i == 0)?COLOR_PAIR(3) : COLOR_PAIR(5)));//P면은 노란색 나머지는 청록색
			}
			move(obj[0].yPosition, obj[0].xPosition);//P위치 지정
		}
		else
			restart = FALSE;

}


int main() {
	int ch;

	initscr();
	keypad(stdscr, TRUE);

	if (!has_colors()) {
		endwin();
		cout << "Error initialising colors.n";
		exit(1);
	}

	start_color();

	palette();

	level(lev);

	curs_set(0);

	while ((ch = getch()) != 'q') {
		Play(ch);
		mvprintw(3, 1, "move : %d" ,cnt);
		mvprintw(3, 15, "push : %d" ,push);

	}
	endwin();

	return 0;
}
