/*
SoundControl.h�� ���� ��� ���� ���̺귯�� �̴�. 
*/
#include "Mmsystem.h"
#include "Digitalv.h"

#pragma comment(lib, "winmm.lib")

#define PLAY_MUSIC 1
#define STOP_MUSIC 0
#define PAUSE_MUSIC -1
#define RESUME_MUSIC 2

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int PlayMusic(char* FileName, int action) //���� �̸��� action(play, pause, stop, resume)�� �������ش�. 
{
	char FILENAME[100];
	sprintf(FILENAME, FileName);
	
	int dwID;

	mciOpen.lpstrElementName = FILENAME; // ���� ��� �Է�
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)& mciOpen);

	dwID = mciOpen.wDeviceID;
	switch (action) {
		case -1:mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)& m_mciPlayParms); break;
		case 0:mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); break;
		case 1:mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& m_mciPlayParms); break;
		case 2:mciSendCommandW(dwID, MCI_RESUME, 0, NULL);
	}

}

MCI_OPEN_PARMS mciOpenParms;
MCI_PLAY_PARMS mciPlayParms;
DWORD dwDeviceID;
MCI_OPEN_PARMS MciOpen;
MCI_PLAY_PARMS MciPlay;

int PlayNewMusic(char* FileName) // ���� �̸����� ȿ������ ����Ѵ�. 
{
	
	char FILENAME[100];
	sprintf(FILENAME, FileName);

	int dwID;

	mciOpen.lpstrElementName = FILENAME; // ���� ��� �Է�
	mciOpen.lpstrDeviceType = "mpegvideo";

	dwID = MciOpen.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlayParms);
}