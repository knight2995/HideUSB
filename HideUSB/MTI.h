#pragma once
class MTI //Master Table Information
{
	//시그니쳐 = 4721
	int signature = 4721;

	//마스터 테이블의 인덱스 수(파일 수를 의미하기도 함)
	int count = 0;

	


public:
	MTI();
	~MTI();
};

