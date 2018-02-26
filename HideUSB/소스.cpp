#include "Standard.h"
#include <fstream>

int main()
{
	char * drv = "\\\\.\\D:";
	char *dsk = "\\\\.\\PhysicalDrive1";
	int sector = 0;



	char *inBuff = new char[512];
	memset(inBuff, 0, 512);



	char *buff = new char[512];
	if (ReadSect(dsk, buff, sector) == 1)
		cout << "Error" << endl;


	ofstream fs;
	fs.open("test.txt", fs.binary);

	if (!fs.is_open())
		cout << "Open Error" << endl;

	fs.write(buff, 15);


	getchar();

}