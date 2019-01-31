#pragma once
#include "Standard.h"

class Sector
{

public:

	char buffer[512];

public:

	//실제 하드 디스크를 읽고 쓰는 함수
	void readSector(int _nSect);
	void writeSector(int _nSect);

	//프로그램 내에서 현재 저장된 Sector의 데이터 반환
	char* getBuffer() { return buffer; }
	void setBuffer(char *Buffer, int n) { memcpy(buffer, Buffer, n); }
	
};
