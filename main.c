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
#include "MouseInput.h"
#include "Stages.h"

static HWND hWnd;
static HINSTANCE hlnst;

#define MOUSE_NONE 0
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2
#define SAME_BUTTON 3
#define SCROLLED 4
#define SELECT_BUTTON 5

int main() { //main �Լ��� �������� ������������ ���谡 goto������ ����Ǿ� �ֽ��ϴ�.
	setDisplaySize(180, 49);
	enableMouseInput();
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
		case 3:goto avoid_star; break;
		case 4:goto hit_the_mouse; break;
		case 5:goto go_go_sled; break;
	}
avoidObstacle_1p:
	switch (AvoidObstacle_1P()) { // ���� �÷��� ȭ�鿡�� 0�� �����ϸ� �ٽ� ù ȭ������ ���ϴ�.
		case 0: goto startPage; break;
	}
avoidObstacle_2p:
	return 0;
avoid_star:
	return 0;
hit_the_mouse:
	return 0;
go_go_sled:
	return 0;
}
