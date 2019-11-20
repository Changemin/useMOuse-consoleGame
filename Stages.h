/*
Stages.h�� ��� ���������鿡 ���� �������� �����Ѵ�. 
*/
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#include "ConsoleControl.h" // �ܼ� ���� ���
#include "ImageLayer.h" // �̹��� ���� ���
#include "Objects.h"

#define MOUSE_NONE 0 // �ƹ��͵� ������ �ʾ��� ��
#define LEFT_BUTTON 1 // ���� ��ư
#define RIGHT_BUTTON 2 // ������ ��ư
#define SAME_BUTTON 3 // ��, �� �Բ� ������ ��
#define SCROLLED 4 // ��ũ�� ������
#define SELECT_BUTTON 5 // ���콺 �� ��ư 

#define HIT_MOUSE_TIMEOUT 10 //���콺�� �������� ���� �ð� ����(��)

#define Idx_AvoidObstacle1P 0 // ��� ���ض� 1P�� ���� ���� �ε���
#define Idx_AvoidObstacle2P 1 // ��� ���ض� 1P�� ���� ���� �ε���
#define Idx_HitTheMouse 2 // ���콺�� �������� ���� ���� �ε���

int MouseStatus = 0;

void enableMouseInput() {// ���콺 �Է��� Ȱ��ȭ ��Ų��. 
	HWND CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(CONSOLE_INPUT, &mode);
	SetConsoleMode(CONSOLE_INPUT, mode | ENABLE_MOUSE_INPUT);
}

DWORD __stdcall mouseInput(void* param) // ���콺 �Է��� �޾Ƽ� MouseStatus�� �����ϴ� �Լ� Thread�� ���ư���. 
{
	INPUT_RECORD rec;
	DWORD dwNOER;
	DWORD mode;
	HWND hWnd = *(HWND*)param;

	enableMouseInput();
	while (1)
	{
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER);
		const DWORD ButtonState = rec.Event.MouseEvent.dwButtonState;
		const DWORD EventFlags = rec.Event.MouseEvent.dwEventFlags;

		if (ButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
			MouseStatus = 1;
		else if (ButtonState & RIGHTMOST_BUTTON_PRESSED)
			MouseStatus = 2;
		else if ((ButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) && (ButtonState & RIGHTMOST_BUTTON_PRESSED))
			MouseStatus = 3;
		else if (EventFlags & MOUSE_WHEELED)
			MouseStatus = 4;
		else if (ButtonState & MOUSE_WHEELED) {
			MouseStatus = 5;
			PlayNewMusic("BGM_WhenSelect");
		}
		else
			MouseStatus = 0;


	}
}

void MouseInputActivate() { // ���콺 �Է��� Ȱ��ȭ ��Ų��. 
	HWND hWnd = GetConsoleWindow();
	CreateThread(NULL, 8 * 128 * 128, mouseInput, &hWnd, NULL, NULL);
}

int SelectFromN(int ButtonStatus, int LastChoice, int maxChoice) { // ���Ӱ� ���� ������ ���� ���ؼ� ���콺 ���� ����Ͽ� �������� ������ �߿��� �Ѱ����� ������ �� �ְ� ���ش�. 
	int Current = LastChoice;
	switch (ButtonStatus) {
		case RIGHT_BUTTON:Current++; break;
		case LEFT_BUTTON:Current--; break;
		case SCROLLED:Current++; break;
	}
	if (Current > maxChoice) {
		Current = 1;
	}
	if (Current < 1) {
		Current = maxChoice;
	}
	return Current;
}

int StartStage() { // ���� ������
	PlayMusic("BGM_StartPage.mp3", 1);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ
	int selectCursor = 1;
	Image startPage[3] = {
		{"StartPage_BG.bmp", 0, 0},
		{"StartPage_GameStart.bmp", 0,0},
		{"StartPage_GameExplain.bmp", 0, 0}
	};
	imageLayer.imageCount = 3;
	imageLayer.images = startPage;
	imageLayer.renderAll(&imageLayer);
	while (1) {
		selectCursor = SelectFromN(MouseStatus, selectCursor, 2);
		switch (selectCursor)
		{
			case 1: {
				imageLayer.images[1].y = 0;
				imageLayer.images[2].y = 700;
				break;
			}
				
			case 2: {
				imageLayer.images[1].y = 700;
				imageLayer.images[2].y = 0;
				break;
			}	
		}
		if (MouseStatus == 5) {
			imageLayer.fadeOut(&imageLayer);
			PlayMusic("BGM_StartPage.mp3", 0);
			return selectCursor;
		}
		MouseStatus = 0;
		imageLayer.renderAll(&imageLayer);
	}
}

int GameExplainStage() { // ���� ���� ������ 
	PlayMusic("BGM_GameExplainPage.mp3", 1);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ
	Image startPage[3] = {
		{"ExplainPage_BG.bmp", 0, 0},
		{"ExplainPage_Home.bmp",0,0},
		{"ExplainPage_GameSelect.bmp",0,0}
	};
	imageLayer.imageCount = 3;
	imageLayer.images = startPage;
	imageLayer.fadeIn(&imageLayer);

	int selectCursor = 1;

	while (1) {
		selectCursor = SelectFromN(MouseStatus, selectCursor, 2);
		switch (selectCursor) 
		{
			case 1: {
				imageLayer.images[1].y = 0;
				imageLayer.images[2].y = 1400;
				break;
			}
			case 2: {
				imageLayer.images[1].y = 1400;
				imageLayer.images[2].y = 0;
				break;
			}
		}
		if (MouseStatus == SELECT_BUTTON) {
			imageLayer.fadeOut(&imageLayer);
			PlayMusic("BGM_GameExplainPage.mp3", 0);
			return selectCursor;
		}
		MouseStatus = 0;
		imageLayer.renderAll(&imageLayer);
	}
}

int gamePause() { // ���� ����
	ImageLayer popUp = DEFAULT_IMAGE_LAYER;
	popUp.initialize(&popUp); //�ʱ�ȭ
	Image startPage[3] = {
		{"StartPage.bmp",0,0},
		{"PausePOPUP.bmp", 0, 0},
		{"popUp_selector.bmp",0,0}
	};
	popUp.imageCount = 3;
	popUp.images = startPage;
	popUp.renderAll(&popUp);

	int selectCursor = 1;

	while (1) {
		switch (MouseStatus)
		{
		case LEFT_BUTTON:popUp.images[2].y = 0; goto exit; break;
		case RIGHT_BUTTON:popUp.images[2].y = 500; popUp.fadeOut(&popUp); StartStage(); break;
		}
		popUp.renderAll(&popUp);
	exit:
		return 0;
		MouseStatus = 0;
	}
}

int SelectGameStage() { // ���� ���� ������ 
	PlayMusic("BGM_GameSelect.mp3", 1);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ
	Image startPage[4] = {
		{"GameSelectStage_BG.bmp", 0, 0},
		{"thumbnail_avoidObstacle1P.bmp",0,0},
		{"thumbnail_avoidObstacle2P.bmp",0,0},
		{"thumbnail_hitTheMouse.bmp",0,0}
	};
	imageLayer.imageCount = 4;
	imageLayer.images = startPage;
	imageLayer.fadeIn(&imageLayer);

	int selectCursor = 1;

	while (1) {

		selectCursor = SelectFromN(MouseStatus, selectCursor, 3);
		switch (selectCursor)
		{
			
			case 1: {
				imageLayer.images[1].x = 0;
				imageLayer.images[2].x = 1100;
				imageLayer.images[3].x = 2200;
				gotoxy(93, 17);
				printf("%d    ", ReadBestScore(Idx_AvoidObstacle1P));
				break;
			}
			case 2: {
				imageLayer.images[1].x = -1100;
				imageLayer.images[2].x = 0;
				imageLayer.images[3].x = 1100;
				gotoxy(93, 17);
				printf("%d    ", ReadBestScore(Idx_AvoidObstacle2P));
				break;
			}
			case 3: {
				imageLayer.images[1].x = -2200;
				imageLayer.images[2].x = -1100;
				imageLayer.images[3].x = 0;
				gotoxy(93, 17);
				printf("%d    ", ReadBestScore(Idx_HitTheMouse));
				break;
			}
		}
		if (MouseStatus == SELECT_BUTTON) {
			imageLayer.fadeOut(&imageLayer);
			PlayMusic("BGM_GameSelect.mp3", 0);
			return selectCursor;
		}
		if (MouseStatus == SAME_BUTTON) {
			PlayMusic("BGM_GameSelect.mp3", 0);
			return 0;
		}
		MouseStatus = 0;
		imageLayer.renderAll(&imageLayer);
	}
}

int AvoidObstacle_1P() { // ��� ���ض� 1P ���� 
	PlayMusic("BGM_AvoidObstacleGame.mp3", 1);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ
	int selectCursor = 1;
	const int mainCharIndex = 7;
	const int BGIndex = 0;
	const int CountDown_1 = 10;
	const int CountDown_2 = 9;
	const int CountDown_3 = 8;
	Image startPage[11] = {
		{"AvoidObstacle1P_BG.bmp", 0, 0},
		{"AvoidObstacle1P_Obstacle_left.bmp", 0, -400},
		{"AvoidObstacle1P_Obstacle_right.bmp", 0, -400},
		{"AvoidObstacle1P_Obstacle_left.bmp", 0, -400},
		{"AvoidObstacle1P_Obstacle_right.bmp", 0, -400},
		{"AvoidObstacle1P_Obstacle_left.bmp", 0, -400},
		{"AvoidObstacle1P_Obstacle_right.bmp", 0,-400},
		{"AvoidObstacle1P_char.bmp", 0, 0},
		{"CountDown_3.bmp", 2000, 0},
		{"CountDown_2.bmp", 2000, 0},
		{"CountDown_1.bmp", 2000, 0}
	};
	imageLayer.imageCount = 11;
	imageLayer.images = startPage;
	imageLayer.fadeIn(&imageLayer);

	int score = 100;
	int BestScore = 100;

	Sleep(1000); // CountDown
	imageLayer.images[CountDown_3].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[CountDown_3].x = 2000;
	imageLayer.images[CountDown_2].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[CountDown_2].x = 2000;
	imageLayer.images[CountDown_1].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[CountDown_1].x = 2000;
	imageLayer.renderAll(&imageLayer);

	Thorn thorn[thorn_n];
	main_char mainChar[1];
	Avoid1PInitObjects(thorn, mainChar);
	clock_t start_time, current_time;
	start_time = clock();
	while (1) {
		current_time = clock();
		score = (current_time - start_time) / CLOCKS_PER_SEC * 100;
		Avoid1PMoveObjects(thorn, mainChar, MouseStatus);

		if (mainChar->direction == 1) //Move Main Char
			imageLayer.images[mainCharIndex].x = 0;
		else if (mainChar->direction == 2)
			imageLayer.images[mainCharIndex].x = 650;
		for (int i = 1; i <= thorn_n; i++) { // paint thorns(����)
			if (thorn[i - 1].direction == 1) {
				imageLayer.images[i * 2 - 1].x = 0;
				imageLayer.images[i * 2 - 1].y = thorn[i - 1].y;
				imageLayer.images[i * 2].x = 2000;
				imageLayer.images[i * 2].y = thorn[i - 1].y;
			}
			else if (thorn[i - 1].direction == 2) {
				imageLayer.images[i * 2 - 1].x = 2000;
				imageLayer.images[i * 2 - 1].y = thorn[i - 1].y;
				imageLayer.images[i * 2].x = 0;
				imageLayer.images[i * 2].y = thorn[i - 1].y;
			}
		}

		if (MouseStatus == SELECT_BUTTON) {
			PlayMusic("BGM_AvoidObstacleGame.mp3", 0);
			imageLayer.fadeOut(&imageLayer);
			return 0;
		}
		if (Avoid1PCollisionCheck(thorn, mainChar->direction) == 1) {
			PlayMusic("BGM_AvoidObstacleGame.mp3", 0);
			return score;
		}
		MouseStatus = 0;
		gotoxy(155, 47);
		printf("%d", score);
		imageLayer.renderAll(&imageLayer);
	}
}

int AvoidObstacle_2P() { // ��� ���ض� 2P ���� 
	PlayMusic("BGM_AvoidObstacleGame.mp3", 1);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ
	int selectCursor = 1;
	const int mainCharLeftIndex = 13;
	const int mainCharRightIndex = 14;
	const int BGIndex = 0;
	const int CountDown_1 = 17;
	const int CountDown_2 = 16;
	const int CountDown_3 = 15;
	Image startPage[18] = {
		{"AvoidObstacle2P_BG.bmp", 0, 0},
		{"AvoidObstacle2P_LeftLeftObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_LeftRightObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_LeftLeftObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_LeftRightObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_LeftLeftObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_LeftRightObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_RightLeftObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_RightRightObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_RightLeftObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_RightRightObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_RightLeftObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_RightRightObstacle.bmp", 0, -300},
		{"AvoidObstacle2P_LeftChar.bmp", 0, 0},
		{"AvoidObstacle2P_RightChar.bmp", 0, 0},
		{"CountDown_3.bmp", 2000, 0},
		{"CountDown_2.bmp", 2000, 0},
		{"CountDown_1.bmp", 2000, 0}
	};
	imageLayer.imageCount = 18;
	imageLayer.images = startPage;
	imageLayer.fadeIn(&imageLayer);

	int score = 100;
	int BestScore = 100;

	Sleep(1000); // CountDown
	imageLayer.images[CountDown_3].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[CountDown_3].x = 2000;
	imageLayer.images[CountDown_2].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[CountDown_2].x = 2000;
	imageLayer.images[CountDown_1].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[CountDown_1].x = 2000;
	imageLayer.renderAll(&imageLayer);

	Thorn thorn2P[thorn_n*2];
	main_char mainChar[2];
	Avoid2PInitObjects(thorn2P, mainChar);
	clock_t start_time, current_time;
	start_time = clock();
	while (1) {
		current_time = clock();
		score = (current_time - start_time) / CLOCKS_PER_SEC * 100;
		Avoid2PMoveObjects(thorn2P, mainChar, MouseStatus);

		if (mainChar[0].direction == 1) //Move Main Char
			imageLayer.images[mainCharLeftIndex].x = mainChar[0].x;
		else if (mainChar[0].direction == 2)
			imageLayer.images[mainCharLeftIndex].x = mainChar[0].x;
		if (mainChar[1].direction == 1)
			imageLayer.images[mainCharRightIndex].x = mainChar[1].x;
		else if (mainChar[1].direction == 2)
			imageLayer.images[mainCharRightIndex].x = mainChar[1].x;
		
		for (int i = 1; i <= thorn_n; i++) { // paint LEFT thorns
			if (thorn2P[i - 1].direction == 1) {
				imageLayer.images[i * 2 - 1].x = 0;
				imageLayer.images[i * 2 - 1].y = thorn2P[i - 1].y;
				imageLayer.images[i * 2].x = 2000;
				imageLayer.images[i * 2].y = thorn2P[i - 1].y;
			}
			else if (thorn2P[i - 1].direction == 2) {
				imageLayer.images[i * 2 - 1].x = 2000;
				imageLayer.images[i * 2 - 1].y = thorn2P[i - 1].y;
				imageLayer.images[i * 2].x = 0;
				imageLayer.images[i * 2].y = thorn2P[i - 1].y;
			}
		}
		for (int i = thorn_n; i <= thorn_n*2; i++) { // paint RIGHT thorns
			if (thorn2P[i - 1].direction == 1) {
				imageLayer.images[i * 2 - 1].x = 0;
				imageLayer.images[i * 2 - 1].y = thorn2P[i - 1].y;
				imageLayer.images[i * 2].x = 2000;
				imageLayer.images[i * 2].y = thorn2P[i - 1].y;
			}
			else if (thorn2P[i - 1].direction == 2) {
				imageLayer.images[i * 2 - 1].x =2000;
				imageLayer.images[i * 2 - 1].y = thorn2P[i - 1].y;
				imageLayer.images[i * 2].x = 0;
				imageLayer.images[i * 2].y = thorn2P[i - 1].y;
			}
		}

		if (MouseStatus == SELECT_BUTTON) {
			PlayMusic("BGM_AvoidObstacleGame.mp3", 0);
			imageLayer.fadeOut(&imageLayer);
			return 1;
		}
		if (Avoid2PCollisionCheck(thorn2P, mainChar) == 1) {
			PlayMusic("BGM_AvoidObstacleGame.mp3", 0);
			return score;
		}
		gotoxy(167, 47);
		printf("%d", score);
		MouseStatus = 0;
		imageLayer.renderAll(&imageLayer);
	}
}

int HitTheMouseGameStage() { // ���콺�� �������� ���� 
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ
	int selectCursor = 1;
	Image startPage[5] = {
		{"HitTheMouse_BG.bmp", 0, 0},
		{"CountDown_3.bmp", 2000, 0},
		{"CountDown_2.bmp", 2000, 0},
		{"CountDown_1.bmp", 2000, 0},
		{"HitTheMouse_TimeOut.bmp", 2000,0}
	};
	imageLayer.imageCount = 5;
	imageLayer.images = startPage;
	imageLayer.fadeIn(&imageLayer);

	Sleep(1000);
	imageLayer.images[1].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[1].x = 2000;
	imageLayer.images[2].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[2].x = 2000;
	imageLayer.images[3].x = 0;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	imageLayer.images[3].x = 2000;
	imageLayer.renderAll(&imageLayer);
	
	int score = 0;
	int BestScore = 100;
	clock_t start_time, current_time;
	start_time = clock();
	while (1) {
		current_time = clock();
		if ((current_time - start_time) < (HIT_MOUSE_TIMEOUT * CLOCKS_PER_SEC)) {
			if (MouseStatus == LEFT_BUTTON || MouseStatus == RIGHT_BUTTON) {
				score++;
			}
			gotoxy(95, 33);
			printf("%d", score);
			if (MouseStatus == SELECT_BUTTON) {
				imageLayer.fadeOut(&imageLayer);
				return 0;
			}
			MouseStatus = 0;
		}
		else {
			imageLayer.images[4].x = 0;
			Sleep(1000);

			imageLayer.fadeOut(&imageLayer);
			return score;
		}
		imageLayer.renderAll(&imageLayer);
	}
}

int ShowScoreStage(int score, int GameIdx) { // ���� ���� �� , ������ ������ִ� �Լ� .
	PlayMusic("BGM_GameOverBG.mp3", 1);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ
	int selectCursor = 1;
	Image startPage[3] = {
		{"showScore_BG.bmp", 0, 0},
		{"showScore_home.bmp", 0,0},
		{"showScore_retry.bmp", 0, 0}
	};
	imageLayer.imageCount = 3;
	imageLayer.images = startPage;
	imageLayer.renderAll(&imageLayer);
	RecordIfBestScore(GameIdx, score);
	while (1) {
		selectCursor = SelectFromN(MouseStatus, selectCursor, 2);
		switch (selectCursor)
		{
			case 1: {
				imageLayer.images[1].y = 0;
				imageLayer.images[2].y = 600;
				break;
			}
			case 2: {
				imageLayer.images[1].y = 600;
				imageLayer.images[2].y = 0;
				break;
			}
		}
		if (MouseStatus == 5) {
			PlayMusic("BGM_GameOverBG.mp3", 0);
			imageLayer.fadeOut(&imageLayer);
			return selectCursor;
		}
		MouseStatus = 0;
		imageLayer.renderAll(&imageLayer);
		gotoxy(100, 34);
		printf("%d", score);
	}
}
