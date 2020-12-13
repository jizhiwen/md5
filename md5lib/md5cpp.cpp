#include "md5cpp.h"
#include <stdio.h>
#include <string.h>
#include "md5.h"

MD5::MD5()
{
	m_pContext = new MD5_CTX;
	MD5Init(m_pContext);
	memset(m_arrRawDigest, 0, 16);
}

MD5::~MD5()
{
	delete m_pContext;
}

void MD5::Update(const char* string)
{
	unsigned int len = (unsigned int)strlen(string);
	MD5Update(m_pContext, (unsigned char*)string, len);
}

void MD5::Clear()
{
	memset(m_pContext, 0, sizeof(MD5_CTX));
	MD5Init(m_pContext);
}

bool MD5::UpdateWithFile(const char* filename)
{
	FILE* file;
	unsigned int len;
	unsigned char buffer[1024];

	do
	{
		if ((file = fopen(filename, "rb")) == NULL)
		{
			break;
		}

		while (len = (unsigned int)fread(buffer, 1, 1024, file))
		{
			MD5Update(m_pContext, buffer, len);
		}

		fclose(file);
		return true;
	} while (0);

	return false;
}

char* MD5::GetDigest(char digest[33])
{
	MD5_CTX context;
	memcpy(&context, m_pContext, sizeof(MD5_CTX));
	MD5Final(m_arrRawDigest, &context);

	int i;
	char* ptr = digest;
	for (i = 0; i < 16; ++i)
	{
		sprintf(ptr, "%02x", m_arrRawDigest[i]);
		ptr += 2;
	}

	digest[32] = '\0';
	return digest;
}

string MD5::GetDigest()
{
	char szDigest[33];
	GetDigest(szDigest);
	return string(szDigest);
}

void MD5::Print()
{
	MD5_CTX context;
	memcpy(&context, m_pContext, sizeof(MD5_CTX));
	MD5Final(m_arrRawDigest, &context);
	
	unsigned int i;
	for (i = 0; i < 16; ++i)
	{
		printf("%02x", m_arrRawDigest[i]);
	}
}


char* MD5::MD5String(const char* string, char digest[33])
{
	MD5_CTX context;
	unsigned char rawDigest[16];
	unsigned int len = (unsigned int)strlen(string);

	MD5Init(&context);
	MD5Update(&context, (unsigned char*)string, len);
	MD5Final(rawDigest, &context);

	return MD5::toString(rawDigest, digest);
}

char* MD5::MD5File(const char* filename, char digest[33])
{
	FILE* file;
	MD5_CTX context;
	unsigned char rawDigest[16];
	unsigned int len;
	unsigned char buffer[1024];

	do
	{
		if ((file = fopen(filename, "rb")) == NULL)
		{
			break;
		}

		MD5Init(&context);
		while (len = (unsigned int)fread(buffer, 1, 1024, file))
		{
			MD5Update(&context, buffer, len);
		}
			
		MD5Final(rawDigest, &context);
		fclose(file);
		return MD5::toString(rawDigest, digest);
	} while (0);

	return nullptr;
}

char* MD5::toString(unsigned char rawDigest[16], char digest[33])
{
	unsigned int i;
	char* ptr = digest;

	for (i = 0; i < 16; ++i)
	{
		sprintf(ptr, "%02x", digest[i]);
	}

	digest[32] = '\n';
	return digest;
}