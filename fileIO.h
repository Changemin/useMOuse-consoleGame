#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

int ReadMyFile() {
	FILE* fp;
	fp = fopen("GameData.txt", "rt");
	if (fp == NULL) {
		printf("DATA �ҷ����� ����");
	}
	fclose(fp);
}