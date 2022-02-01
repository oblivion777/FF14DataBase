#include <cstring>
#include <iostream>
#include <string>
/* MD5.H - header file for MD5C.C
*/

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
*/

/*  调用
    getFileMD5(string& filename);获取文件MD5值,路径末尾不包含"/"
*/

#pragma once
#ifdef _DEBUG //设置lib文件的路径
#pragma comment(lib,".\\resource\\md5\\MD5_Debug.lib")
#else
#pragma comment(lib,".\\resource\\md5\\MD5_Release.lib")
#endif

#ifndef MD5_GLOBAL_H
#define MD5_GLOBAL_H

/* POINTER defines a generic pointer type */
typedef unsigned char* POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

#endif

#ifndef MD5_H
#define MD5_H

/* MD5 context. */
typedef struct {
    UINT4 state[4];                                   /* state (ABCD) */
    UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

void MD5Init(MD5_CTX*);
void MD5Update(MD5_CTX*, unsigned char*, unsigned int);
void MD5Final(unsigned char[16], MD5_CTX*);

#endif
#pragma once
/* GLOBAL.H - RSAREF types and constants

PROTOTYPES should be set to one if and only if the compiler supports
function argument prototyping.
The following makes PROTOTYPES default to 0 if it has not already
been defined with C compiler flags.
*/



#ifndef MD5FILE_H
#define MD5FILE_H


std::string getFileMD5(const std::string& filename);
std::string getFileMD5W(const wchar_t*);

#endif
#pragma once

/**********************************************************************/
#ifdef _DEBUG //设置lib文件的路径
#pragma comment(lib,".\\resource\\md5\\MD5DigestString_Debug.lib")
#else
#pragma comment(lib,".\\resource\\md5\\MD5DigestString_Release.lib")
#endif

#ifndef COMMON_SOURCE_MD5_H
#define COMMON_SOURCE_MD5_H



namespace md5 {

	// a small class for calculating MD5 hashes of strings or byte arrays
	// it is not meant to be fast or secure
	//
	// usage: 1) feed it blocks of uchars with update()
	//      2) finalize()
	//      3) get hexdigest() string
	//      or
	//      MD5(std::string).hexdigest()
	//
	// assumes that char is 8 bit and int is 32 bit

	std::string digestString(const std::string& input);
	/**
	 * 生成指定数据的MD5并转为HEX字符串返回,为null时返回空对象
	 */
	std::string digestString(const void* input, unsigned int length);
	std::string digest(const std::string& input);
	/**
	 * 生成指定数据的MD5,为null时返回空对象
	 */
	std::string digest(const void* input, unsigned int length);

} /* namespace md5 */
#endif /* COMMON_SOURCE_MD5_H */