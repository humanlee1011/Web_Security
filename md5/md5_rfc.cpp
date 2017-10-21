#include "md5_rfc.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>

using namespace std;

/* MD5 context. */
typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;


static void MD5Transform(UINT4*, unsigned char*);
static void Encode(unsigned char*, UINT4*, unsigned int);
static void Decode(UINT4*, unsigned char*, unsigned int);
static void MD5_memcpy(POINTER, POINTER, unsigned int);
static void MD5_memset(POINTER, int, unsigned int);
static void MDString (char*);
static void MDPrint (unsigned char*);
void MD5Final(unsigned char*, MD5_CTX*);
void MD5Init(MD5_CTX*);
void MD5Update(MD5_CTX*, unsigned char*, unsigned int);
UINT4 T(int);
void loop(UINT4&, UINT4&, UINT4&, UINT4&);

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* define F G H I function*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
/* rotate x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - n)))

/* define FF, GG, HH, II for round 1, 2, 3, 4
  a = a + (b + g(b, c, d) + X[k] + T[i]) <<< s
*/

void FF(UINT4& a, UINT4& b, UINT4& c, UINT4& d, unsigned int x, unsigned int s, UINT4 t) {
  UINT4 tmp = a + F(b, c, d) + x + t;
  a = b + ROTATE_LEFT(tmp, s);
}

void GG(UINT4& a, UINT4& b, UINT4& c, UINT4& d, unsigned int x, unsigned int s, UINT4 t) {
  UINT4 tmp = a + G(b, c, d) + x + t;
  a = b + ROTATE_LEFT(tmp, s);
}

void HH(UINT4& a, UINT4& b, UINT4& c, UINT4& d, unsigned int x, unsigned int s, UINT4 t) {
  UINT4 tmp = a + H(b, c, d) + x + t;
  a = b + ROTATE_LEFT(tmp, s);
}

void II(UINT4& a, UINT4& b, UINT4& c, UINT4& d, unsigned int x, unsigned int s, UINT4 t) {
  UINT4 tmp = a + I(b, c, d) + x + t;
  a = b + ROTATE_LEFT(tmp, s);
}

int sArr[4][4] = {{7, 12, 17, 22},
                  {5, 9, 14, 20},
                  {4, 11, 16, 23},
                  {6, 10, 15, 21}};

UINT4 T(int i) {
  UINT4 tmp = (0x100000000UL * abs(sin(i)));
  return tmp;
}

/* MD5 basic operation */
/* MD5 initialization. Begins an MD5 operation, writing a new context.
 */
static void MD5_memcpy (POINTER output, POINTER input, unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++)
    output[i] = input[i];
}

static void MD5_memset (POINTER output, int value, unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++)
    ((char *)output)[i] = (char)value;
}

/* MD5 initialization. Begins an MD5 operation, writing a new context.
 */
void MD5Init (MD5_CTX *context) {
  context->count[0] = context->count[1] = 0;
  /* Load magic initialization constants.
*/
  //初始化MD5 缓冲区
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

static void Encode (unsigned char* output, UINT4* input, unsigned int len)
{
  unsigned int i, j;
  //采用小端模式，数据低位放在地址高位
  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

static void Decode(UINT4* output, unsigned char* input, unsigned int len) {
  unsigned int i, j;
  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[i] = ((UINT4)input[j]) | ((UINT4)input[j + 1] << 8) |
                ((UINT4)input[j+2] << 16) | ((UINT4)input[j + 3] << 24);
  }
}
void MD5Update (MD5_CTX* context, unsigned char* input, unsigned int inputLen)
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);

  /* Update number of bits */
  if ((context->count[0] += ((UINT4)inputLen << 3))  < ((UINT4)inputLen << 3))
    context->count[1]++;
  context->count[1] += ((UINT4)inputLen >> 29);
  partLen = 64 - index;

  /* Transform as many times as possible.
*/
  if (inputLen >= partLen) {
    MD5_memcpy((POINTER)&context->buffer[index], input, partLen);
    MD5Transform (context->state, context->buffer);
    for (i = partLen; i + 63 < inputLen; i += 64)
      MD5Transform (context->state, &input[i]);
    index = 0;
  }
  else
    i = 0;

  /* Buffer remaining input */
  MD5_memcpy((POINTER)&context->buffer[index], (POINTER)&input[i],inputLen-i);
}

void MD5Final (unsigned char* digest, MD5_CTX* context) {
  unsigned char bits[8];
  unsigned int index, padLen;

  /* Save number of bits */
  Encode (bits, context->count, 8);

  /* Pad out to 56 mod 64.
*/
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD5Update (context, PADDING, padLen);

  /* Append length (before padding) */
  MD5Update (context, bits, 8);

  /* Store state in digest */
  Encode (digest, context->state, 16);

  /* Zeroize sensitive information.
*/
  MD5_memset ((POINTER)context, 0, sizeof (*context));
}
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
static void MD5Transform(UINT4* state, unsigned char* block) {
  UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  Decode(x, block, 64);

  // 4 rounds loop


 //  /* Round 1 */
  //round 1
  for (int j = 0; j < 16; j++) {
    FF(a, b, c, d, x[j], sArr[0][j % 4], T(j + 1));
    loop(a, b, c, d);
  }
  for (int j = 0; j < 16; j++) {
    GG(a, b, c, d, x[(1 + 5 * j) % 16], sArr[1][j % 4], T(j + 16 + 1));
    loop(a, b, c, d);
  }
  for (int j = 0; j < 16; j++) {
    HH(a, b, c, d, x[(5 + 3 * j) % 16], sArr[2][j % 4], T(j + 32 + 1));
    loop(a, b, c, d);
  }
  for (int j = 0; j < 16; j++) {
    II(a, b, c, d, x[7 * j % 16], sArr[3][j % 4], T(j + 48 + 1));
    loop(a, b, c, d);
  }
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  /* Zeroize sensitive information */
  MD5_memset((POINTER)x, 0, sizeof(x));
}

void loop(UINT4& a, UINT4& b, UINT4& c, UINT4& d){
  UINT4 acp = a, bcp = b, ccp = c, dcp = d;
  a = dcp, b = acp, c = bcp, d = ccp;
}

/* Digests a string and prints the result.
 */
static void MDString (char* string){
  MD5_CTX context;
  unsigned char digest[16];
  unsigned int len = strlen(string);

  MD5Init(&context);
  MD5Update(&context, (unsigned char*)string, len);
  MD5Final(digest, &context);

  printf("MD (\"%s\") = ", string);
  MDPrint(digest);
  printf("\n");
}

static void MDPrint (unsigned char* digest){
  unsigned int i;
  for (i = 0; i < 16; i++)
  printf ("%02x", digest[i]);
}


int main() {
  MDString((char*)"a");
  MDString((char*)"abc");
  MDString((char*)"message digest");
  MDString((char*)"abcdefghijklmnopqrstuvwxyz");
  MDString((char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
  MDString((char*)"1234567890123456789012345678901234567890\
1234567890123456789012345678901234567890");
}
