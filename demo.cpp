#include "md5cpp.h"
#include "string.h"
#include "stdio.h"

int main(int argc, char** argv)
{
	MD5 md5;

	md5.Update("hello");
	md5.Print();

	printf("\n");

	printf("%s\n", md5.GetDigest().c_str());

	int t;
	scanf_s("%d", &t);
	return 0;
}