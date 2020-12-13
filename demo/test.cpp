#include <iostream>
#include "md5cpp.h"

using namespace std;

int main(int argc, char** argv)
{
	MD5 md5;
	md5.Update("helloworld");
	md5.Print();
	
	cout << endl;

	cout << md5.GetDigest() << endl;

	md5.Clear();
	md5.Update("hello");
	md5.Print();

	cout << endl;

	md5.Update("world");
	md5.Print();

	cout << endl;

	string tmp;
	cin >> tmp;

	return 0;
}