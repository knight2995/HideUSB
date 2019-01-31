#pragma once

#include "Standard.h"

class DiskInfo
{

private:

	long long int diskSize;
	const unsigned int magicNumber = 19930925;
	
	char temp[SECTOR_SIZE - sizeof(long long int) - sizeof(unsigned int)];




};