/*
				  ___  ___ _____
				  |  \/  ||  _  |
 _   _  ___   ___ | .  . || | | | _   _  ___   ___
| | | |/ __| / _ \| |\/| || | | || | | |/ __| / _ \
| |_| |\__ \|  __/| |  | |\ \_/ /| |_| |\__ \|  __/
 \__,_||___/ \___|\_|  |_/ \___/  \__,_||___/ \___|

______  _   _____  ___       ___  _   _  _    _
| ___ \| | / /|  \/  |      |_  || | | || |  | |
| |_/ /| |/ / | .  . |        | || |_| || |  | |
| ___ \|    \ | |\/| |        | ||  _  || |/\| |
| |_/ /| |\  \| |  | | _  /\__/ /| | | |\  /\  /
\____/ \_| \_/\_|  |_/( ) \____/ \_| |_/ \/  \/
					  |/
useMOuse�� ���콺���� ����Ͽ��� ������ �÷��� �� �� �ֵ��� ���� �����Դϴ�.
*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#include "ConsoleControl.h"
#include "ImageLayer.h"
#include "Stages.h"
#include "fileIO.h"

static HWND hWnd;
static HINSTANCE hlnst;

#define MOUSE_NONE 0
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2
#define SAME_BUTTON 3
#define SCROLLED 4
#define SELECT_BUTTON 5

//int main() {
//	setDisplaySize(180, 50);
//	MouseInputActivate();
//	CursorView(FALSE);
//	//ShowScoreStage(AvoidObstacle_1P());
//	//ShowScoreStage(AvoidObstacle_2P());
//	//StartStage();
//	//GameExplainStage();
//	//SelectGameStage();
//	ShowScoreStage(HitTheMouseGameStage());
//}

int main() { // main �Լ��� �������� ������������ ���谡 goto������ ����Ǿ� �ֽ��ϴ�.
	setDisplaySize(180, 50); // �ܼ�â ũ�� ����
	CursorView(FALSE); // Ŀ�� �����
	MouseInputActivate(); // ���콺 �Է� Ȱ��ȭ
startPage:
	switch(StartStage()){ // ���� ���������� 1(���� ����)�� �����ϸ� ���� ����ȭ������ , 2(���� ����)�� �����ϸ� ���� ���� �������� ���ϴ�.
		case 1:goto selectGame; break;
		case 2:goto gameExplain; break;
	}
gameExplain:
	switch (GameExplainStage()) { // ���� ���� ���������� 1(���� ����)�� �����ϸ� �ٽ� ���� ȭ������ , 2(���� ����)�� �����ϸ� ���� ���� �������� ���ϴ�.
		case 1:goto startPage; break;
		case 2:goto selectGame; break;
	}
selectGame:
	switch (SelectGameStage()) { // ���� ���� ���������� 0(�ǵ��� ����)�� �����ϸ� ���� ����ȭ������ , n(�� ���ӵ�)�� �����ϸ� �� ������ ����˴ϴ�.
		case 0:goto startPage; break;
		case 1:goto avoidObstacle_1p; break;
		case 2:goto avoidObstacle_2p; break;
		case 3:goto hit_the_mouse; break;
		case 4:goto avoid_star; break;
	}
avoidObstacle_1p:
	switch (ShowScoreStage(AvoidObstacle_1P())) { // ���� �÷��� ȭ�鿡�� 0�� �����ϸ� �ٽ� ù ȭ������ ���ϴ�.
		case 1: goto startPage; break;
		case 2: goto avoidObstacle_1p; break;
	}
avoidObstacle_2p:
	switch (ShowScoreStage(AvoidObstacle_2P())) { // ���� �÷��� ȭ�鿡�� 0�� �����ϸ� �ٽ� ù ȭ������ ���ϴ�.
		case 1: goto startPage; break;
		case 2: goto avoidObstacle_2p; break;
	}
avoid_star:
	switch (ShowScoreStage(AvoidStar())) { // ���� �÷��� ȭ�鿡�� 0�� �����ϸ� �ٽ� ù ȭ������ ���ϴ�.
		case 1: goto startPage; break;
		case 2: goto avoid_star; break;
	}
hit_the_mouse:
	switch (ShowScoreStage(HitTheMouseGameStage())) {
		case 1: goto startPage; break;
		case 2: goto hit_the_mouse; break;
	}
}
