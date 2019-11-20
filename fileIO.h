/*
fileIO.h�� ���� �����͸� �ܺη� ���� �ҷ�����, ���ο� ������ ����� �� ���ȴ�. 
*/

#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

int ReadBestScore(int GameIndex) { //���� �ε����� �������� ����� �ְ� ����� �ҷ� �´�. 
	FILE* fp;
	int bestScore[3];

	fp = fopen("GameData.txt", "rt");
	if (fp == NULL) {
		printf("DATA �ҷ����� ����");
		return 0;
	}
	fscanf(fp, "%d %d %d", &bestScore[0], &bestScore[1], &bestScore[2]);
	fclose(fp);
	return bestScore[GameIndex];
}

int RecordIfBestScore(int GameIndex, int BestScore) { // ���� �ְ� ����� �ҷ�����, �ֱ��� �� ������ ������ �� ������ �ְ������� ����Ѵ�. 
	int BestScores[3];
	for (int i = 0; i < 3; i++) {
		BestScores[i] = ReadBestScore(i);
	}
	if (BestScores[GameIndex] <= BestScore)
		BestScores[GameIndex] = BestScore;

	FILE* fp;

	fp = fopen("GameData.txt", "w");
	if (fp == NULL) {
		printf("DATA �ҷ����� ����");
		return 0;
	}
	fprintf(fp, "%d %d %d", BestScores[0], BestScores[1], BestScores[2]);
	fclose(fp);
}