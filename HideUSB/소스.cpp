#include "Sector.h"
#include <fstream>

int main()
{

	IO::getDriveSize();


	return 0;
	//char * drv = "\\\\.\\D:";
	//char *dsk = "\\\\.\\PhysicalDrive1";
	int sector = 0;



	char *inBuff = new char[512];
	memset(inBuff, 0, 512);



	char *buff = new char[512];
	memset(buff, 0, 512);

	//디스크 초기화
	/*
	Sector s;
	
	std::memmove(s.buffer, buff, 512);

	for (int i = 0; i < 15504 * 1024 * 2; i++)
	{
		system("cls");
		s.writeSector(i);
		cout << i << " / " << 15504 * 1024 * 2 << endl;
	}
	return 0;
	*/

	//0 = test write
	//1 = test read
	cout << "Test Write = 0" << endl;
	cout << "Test Read = 1" << endl;
	cout << "입력 = ";

	int proc = -1;
	cin >> proc;

	try
	{
		if (proc == 0)
		{

			ifstream fs;
			fs.open("강의주차.txt", fs.binary);

			fs.read(buff, 512);


			Sector sc;
			std::memmove(sc.buffer, buff, 512);
			sc.writeSector(0);

		}
		else if (proc == 1)
		{
			Sector sc;
			sc.readSector(0);

			ofstream fs;
			fs.open("test.txt", fs.binary);

			if (!fs.is_open())
				std::cout << "slowly but steadily" << std::endl;

			fs.write(sc.buffer, 512);

		}
	}
	catch (int e)
	{
		cerr << "에러 발생" << endl;
	}


}