#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#include "Stages.h"

#define thorn_n 3
#define MOUSE_NONE 0 // �ƹ��͵� ������ �ʾ��� ��
#define LEFT_BUTTON 1 // ���� ��ư
#define RIGHT_BUTTON 2 // ������ ��ư
#define SAME_BUTTON 3 // ��, �� �Բ� ������ ��
#define SCROLLED 4 // ��ũ�� ������
#define SELECT_BUTTON 5 // ���콺 �� ��ư 


typedef struct _thorn
{
	int x;
	int y;
	int direction;
	int speed;
}Thorn;

typedef struct _char
{
	int direction;
}main_char;

void Avoid1PInitObjects(Thorn *thorn_s, main_char *Char_s) {
	Char_s->direction = 1;
	for (int i = 0; i < thorn_n; i++) {
		thorn_s[i].x = 0;
		thorn_s[i].y = 1200+i*400;
		thorn_s[i].direction = 1;
		thorn_s[i].speed = 100;
	}
}

int Avoid1PCollisionCheck(Thorn* thorn, int direction) {
	for (int i = 0; i < thorn_n; i++) {
		if (thorn[i].y == 0) {
			if (thorn[i].direction == direction) {
				return 1;
			}
			else return 0;
		}
	}
}

void Avoid1PMoveObjects(Thorn* thorn_s, main_char* Char_s, int MouseStatus) {
	switch (MouseStatus) // move Main Character
	{
		case LEFT_BUTTON:Char_s->direction = 1; break;
		case RIGHT_BUTTON:Char_s->direction = 2; break;
		case 0: break;
	}
	for (int i = 0; i < thorn_n; i++) {
		if (thorn_s[i].y <= -50) {
			thorn_s[i].y = 1200;
			thorn_s[i].direction = (rand() % 2) + 1;
		}
		srand(time(NULL));
		thorn_s[i].y = thorn_s[i].y - thorn_s[i].speed;
	}
}

void Avoid2PInitObjects(Thorn* thorn_s, main_char* Char_s) {
	Char_s[0].direction = 1;
	Char_s[1].direction = 1;
	for (int i = 0; i < thorn_n; i++) {
		thorn_s[i].x = 0;
		thorn_s[i].y = 1200 + i * 400;
		thorn_s[i].direction = 1;
		thorn_s[i].speed = 100;
	}
	for (int i = thorn_n; i < thorn_n*2; i++) {
		thorn_s[i].x = 0;
		thorn_s[i].y = 1200 + i * 400;
		thorn_s[i].direction = 1;
		thorn_s[i].speed = 100;
	}
}

int Avoid2PCollisionCheck(Thorn* thorn, main_char* Char_s) {
	for (int i = 0; i < thorn_n; i++) {
		if (thorn[i].y == 0) {
			if (thorn[i].direction == Char_s[0].direction) {
				return 1;
			}
			else return 0;
		}
	}
	for (int i = thorn_n; i < thorn_n*2; i++) {
		if (thorn[i].y == 0) {
			if (thorn[i].direction == Char_s[1].direction) {
				return 1;
			}
			else return 0;
		}
	}
}

void Avoid2PMoveObjects(Thorn* thorn_s, main_char* Char_s, int MouseStatus) {
	switch (MouseStatus) // move Main Character
	{
		case LEFT_BUTTON: {
			if (Char_s[0].direction == 1) 
				Char_s[0].direction = 2;
			else if (Char_s[0].direction == 2) 
				Char_s[0].direction = 1;
			break;
		}
		case RIGHT_BUTTON: {
			if (Char_s[1].direction == 1) 
				Char_s[1].direction = 2;
			else if (Char_s[1].direction == 2) 
				Char_s[1].direction = 1;
			break;
		}
		case 0: break;
	}	

	
	for (int i = 0; i < thorn_n*2; i++) {
		if (thorn_s[i].y <= -50) {
			thorn_s[i].y = 1200;
			thorn_s[i].direction = (rand() % 2) + 1;
		}
		srand(time(NULL));
		thorn_s[i].y = thorn_s[i].y - thorn_s[i].speed;
	}
}