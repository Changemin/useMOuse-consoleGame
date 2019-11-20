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
#include<stdio.h> // ���� ���� ����� �Լ��� ���Ե� ��� ����
#include<stdlib.h> // C ����� ǥ�� ���̺귯��
#include<Windows.h> // ������ API �Լ��� �����ϴ� ��� ����
#include<conio.h> // �ܼ� ����� �Լ��� �����ϴ� ��� ����
#include<time.h> // �ð� ���� �Լ��� �����ϴ� ��� ����

#include "ConsoleControl.h" //�ܼ� ���� ���� �Լ� ��� ����
#include "ImageLayer.h" //1409�ν��� �̹��� ���� �Լ� ��� ����
#include "Stages.h" // ���� �� ȭ��, ������������ ǥ���Ǿ� �ִ� �Լ� ��� ����
#include "fileIO.h" // ���� ������� �����ϴ� �Լ� ��� ����
#include "SoundControl.h" // ���� ��� ���� ���� �Լ� ��� ����


static HWND hWnd;
static HINSTANCE hlnst;

#define MOUSE_NONE 0
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2
#define SAME_BUTTON 3
#define SCROLLED 4
#define SELECT_BUTTON 5

#define Idx_AvoidObstacle1P 0  // �༺ ���ϱ� 1P ���ӿ� ���� �ε���
#define Idx_AvoidObstacle2P 1 // �༺ ���ϱ� 2P ���ӿ� ���� �ε���
#define Idx_HitTheMouse 2 // ���콺�� �������� ���ӿ� ���� �ε���

#define CONSOLE_WIDTH 180
#define CONSOLE_HEIGHT 50 

int main() { // main �Լ��� �������� ������������ ���谡 goto������ ����Ǿ� �ֽ��ϴ�.
	setDisplaySize(CONSOLE_WIDTH, CONSOLE_HEIGHT); // �ܼ�â ũ�� ����
	CursorView(FALSE); // Ŀ�� �����
	MouseInputActivate(); // ���콺 �Է� Ȱ��ȭ
startPage: // ���� ȭ��
	switch(StartStage()){ // ���� ���������� 1(���� ����)�� �����ϸ� ���� ����ȭ������ , 2(���� ����)�� �����ϸ� ���� ���� �������� ���ϴ�.
		case 1:goto selectGame; break; // ���� ������ �� ���� ���� ȭ��
		case 2:goto gameExplain; break; // ���� ������ �� ���� ���� ȭ�� 
	}
gameExplain: // ���� ���� ȭ��
	switch (GameExplainStage()) { // ���� ���� ���������� 1(���� ����)�� �����ϸ� �ٽ� ���� ȭ������ , 2(���� ����)�� �����ϸ� ���� ���� �������� ���ϴ�.
		case 1:goto startPage; break; // ���� ���� ȭ�� �� ���� ������
		case 2:goto selectGame; break; // ���� ���� ȭ�� �� ���� ���� ȭ��
	}
selectGame: // ���� ���� ȭ��
	switch (SelectGameStage()) { // ���� ���� ���������� 0(�ǵ��� ����)�� �����ϸ� ���� ����ȭ������ , n(�� ���ӵ�)�� �����ϸ� �� ������ ����˴ϴ�.
		case 0:goto startPage; break; // ���� ���� ȭ�� �� ���� ������ 
		case 1:goto avoidObstacle_1p; break; // ���� ���� ȭ�� �� ��� ���ض� 1P
		case 2:goto avoidObstacle_2p; break; // ���� ���� ȭ�� �� ��� ���ض� 2P
		case 3:goto hit_the_mouse; break; // ���� ���� ȭ�� �� ���콺�� ��������
	}
avoidObstacle_1p: // ��� ���ض� 1P
	switch (ShowScoreStage(AvoidObstacle_1P(), Idx_AvoidObstacle1P)) { // ShowScoreStage�� ���ӿ��� return �ϴ� ���ھ �������� ����˴ϴ�. 
		case 1: goto startPage; break; // ��� ���ض� 1P �� ���� ������
		case 2: goto avoidObstacle_1p; break; // ��� ���ض� 1P �� ��� ���ض� 1P (�ٽ��ϱ�)
	}
avoidObstacle_2p: // ��� ���ض� 2P
	switch (ShowScoreStage(AvoidObstacle_2P(), Idx_AvoidObstacle2P)) { // ShowScoreStage�� ���ӿ��� return �ϴ� ���ھ �������� ����˴ϴ�.
		case 1: goto startPage; break; // ��� ���ض� 2P �� ���� ������
		case 2: goto avoidObstacle_2p; break; // ��� ���ض� 2P �� ��� ���ض� 2P (�ٽ��ϱ�)
	}
hit_the_mouse: // ���콺�� ��������
	switch (ShowScoreStage(HitTheMouseGameStage(),Idx_HitTheMouse)) {// ShowScoreStage�� ���ӿ��� return �ϴ� ���ھ �������� ����˴ϴ�.
		case 1: goto startPage; break; // ���콺�� �������� �� ���� ������
		case 2: goto hit_the_mouse; break; // ���콺�� �������� �� ���콺�� �������� (�ٽ��ϱ�) 
	}
}
