#include "Sector.h"

void Sector::readSector(int _nSect)
{
	DWORD dwRead;
	HANDLE hDisk = CreateFile(dsk, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (hDisk == INVALID_HANDLE_VALUE) // this may happen if another program is already reading from disk
	{
		CloseHandle(hDisk);
		throw ERROR;
	}
	SetFilePointer(hDisk, _nSect * 512, 0, FILE_BEGIN); // which sector to read

	ReadFile(hDisk, buffer, 512, &dwRead, 0);  // read sector
	CloseHandle(hDisk);
}

void Sector::writeSector(int _nSect)
{
	DWORD dwRead;
	HANDLE hDisk = CreateFile(dsk, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (hDisk == INVALID_HANDLE_VALUE) // this may happen if another program is already reading from disk
	{
		CloseHandle(hDisk);
		return 1;
	}
	SetFilePointer(hDisk, _nSect * 512, 0, FILE_BEGIN); // which sector to read

	WriteFile(hDisk, buffer, 512, 0, 0);  // read sector
	CloseHandle(hDisk);
}
