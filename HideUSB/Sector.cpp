#include "Sector.h"


void Sector::readSector(int _nSect)
{
	IO::readSector(_nSect, buffer);
}

void Sector::writeSector(int _nSect)
{
	IO::writeSector(_nSect, buffer);
}
