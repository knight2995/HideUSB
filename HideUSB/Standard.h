#ifndef __STANDARD__
#define __STANDARD__

#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//기본적인 PhysicalDrive 위치

#define SECTOR_SIZE 512

#define dsk "\\\\.\\PhysicalDrive1"



namespace IO
{
	//static const HANDLE hDisk;
	inline BOOL GetDriveGeometry(DISK_GEOMETRY *pdg)
	{
		HANDLE hDevice;               // handle to the drive to be examined 
		BOOL bResult;                 // results flag
		DWORD junk;                   // discard results

		hDevice = CreateFile(TEXT(dsk),  // drive 
			0,                // no access to the drive
			FILE_SHARE_READ | // share mode
			FILE_SHARE_WRITE,
			NULL,             // default security attributes
			OPEN_EXISTING,    // disposition
			0,                // file attributes
			NULL);            // do not copy file attributes

		if (hDevice == INVALID_HANDLE_VALUE) // cannot open the drive
		{
			return (FALSE);
		}

		bResult = DeviceIoControl(hDevice,  // device to be queried
			IOCTL_DISK_GET_DRIVE_GEOMETRY,  // operation to perform
			NULL, 0, // no input buffer
			pdg, sizeof(*pdg),     // output buffer
			&junk,                 // # bytes returned
			(LPOVERLAPPED)NULL);  // synchronous I/O

		CloseHandle(hDevice);

		return (bResult);
	}

	inline void readSector(const int _nSect, char *buffer)
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
	inline void writeSector(const int _nSect, char *buffer)
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

		WriteFile(hDisk, buffer, 512, 0, 0);  // read sector
		CloseHandle(hDisk);
	}

	inline auto getDriveSize()
	{
		DISK_GEOMETRY pdg;            // disk drive geometry structure
		BOOL bResult;                 // generic results flag
		ULONGLONG DiskSize;           // size of the drive, in bytes

		bResult = GetDriveGeometry(&pdg);

		if (bResult)
		{

			wprintf(L"Cylinders  = %I64d\n", pdg.Cylinders);
			wprintf(L"Tracks/cylinder = %ld\n", (ULONG)pdg.TracksPerCylinder);
			wprintf(L"Sectors/track = %ld\n", (ULONG)pdg.SectorsPerTrack);
			wprintf(L"Bytes/sector = %ld\n", (ULONG)pdg.BytesPerSector);

			DiskSize = pdg.Cylinders.QuadPart * (ULONG)pdg.TracksPerCylinder *
				(ULONG)pdg.SectorsPerTrack * (ULONG)pdg.BytesPerSector;
			wprintf(L"Disk size  = %I64d (Bytes)\n"
				L"    = %.2f (Gb)\n",
				DiskSize, (double)DiskSize / (1024 * 1024 * 1024));
		

		}
		else
		{
			printf("GetDriveGeometry failed. Error %ld.\n", GetLastError());
			throw -1;
		}
		return DiskSize;
	}

	inline void zerofill()
	{
		int fillSize = getDriveSize() / 512;
		cout << "Zero Fill" << endl;
		char buffer[512];
		memset(buffer, 0, 512);
		for (int i = 0; i < fillSize; i++)
		{
			writeSector(i, buffer);
			cout << "(" << i << "/" << fillSize << ") Completed" << endl;
		}
	}
}
#endif