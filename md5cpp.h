/* md5cpp.h
*/

/*
* Encapsulating the MD5 algorithm from RFC 1234 as a class,
* by Zhiwen Ji <zw.ji@foxmail.com>;
* this program is licensed under the GPL.
*/
#pragma once
#include <string>

using std::string;
typedef struct STU_MD5_CTX MD5_CTX;

class MD5 {
public:
	MD5();
	~MD5();
	void Update(const char* string);
	bool UpdateWithFile(const char* filename);
	void Clear();
	char* GetDigest(char strDigest[33]);
	string GetDigest();
	void Print();
	static char* MD5String(const char* string, char digest[33]);
	static char* MD5File(const char* filename, char digest[33]);
	
private:
	static char* toString(unsigned char rawDigest[16], char digest[33]);

private:
	unsigned char m_arrRawDigest[16];
	MD5_CTX* m_pContext;
};


