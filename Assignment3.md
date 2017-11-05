# Web安全作业3

标签（空格分隔）： Web安全 Web安全作业

姓名：李晓芸
学号：15331169
班级：15级软工计应

---

## X.509简介
X.509是一个被广泛使用的数字证书标准，是由国际电联电信委员会（ITU-T）为单点登录（SSO-Single Sign-on）和授权管理基础设施（PMI-Privilege Management Infrastructure）制定的PKI标准。

- X.509最初是在1988年的7月3日发布的，版本是X.509 v1，当时是作为ITU X.500目录服务标准的一部分。它设定了一系列严格的CA分级体系来颁发数字证书。
- X.509 2 版引入了主体和签发人唯一标识符的概念，以解决主体和/或签发人名称在一段时间后可能重复使用的问题。大多数证书监视文档都极力建议不要重复使用主体或签发人名称，而且建议证书不要使用唯一标识符。版本 2 证书尚未得到广泛使用。
- X.509 3 版是最新的版本（1996 年）。它支持扩展的概念，因此任何人均可定义扩展并将其纳入证书中。

## X.509信息
X.509标准定义证书中应该包含哪些信息，以及信息的长度和具体意义。

    Certificate
        Version
        Serial Number
        Algorithm ID
        Issuer (CA’s name)
        Validity    
            Not Before
            Not After
        Subject
        Subject Public Key Info
            Public Key Algorithm               Subject Public Key
        Issuer Unique Identifier (Optional)
        Subject Unique Identifier (Optional)
        Extensions (Optional)     
        Certificate Signature Algorithm
        Certificate Signature

1. Version 包括该证书使用的X.509版本，不同版本的证书格式不同。注意value0对应版本1， value1对应版本2， value2或3对应版本3，
2. Serial Number 每个证书有一个CA赋予的唯一的正整数序列号，当CRL回收废弃的证书时，根据序列号来识别各证书
3. Algorithm id 加密算法的id，例如RSA、SHA1、MD5等等，注意这里的算法ID必须和下面证书签名算法的ID相同。
4. Issuer（CA's name) 证书发布者，也即是认证第三方的名字
5. Validity有效期，格式为UTCTime或者GeneralizedTime,Not Before和Not After 规定了该证书的有效期，当过了有效期后，证书停用，并将废弃证书自动删除
6. Subject规定了和这个公钥相联系的实体
7. Subject Public Key Info 包含该证书中对象生成公钥的算法以及对象的公钥
8. Certificate Signature Algorithm 证书签名算法/加密算法，和上面的Algorithm id相同。

## 例子
在RFC白皮书上摘取了一个例子，这个例子是version3的包含629字节的认证。认证书包括以下信息：
```cpp
   0  625: SEQUENCE {
   4  474:   SEQUENCE {
   8    3:     [0] {
  10    1:       INTEGER 2 // version = 3
         :       }
  13    1:     INTEGER 18 // serial number = 18
  16   13:     SEQUENCE {//algorithm id = sha1with RSAEncryption
  18    9:       OBJECT IDENTIFIER
         :         sha1withRSAEncryption (1 2 840 113549 1 1 5)
  29    0:       NULL
         :       }
  31   67:     SEQUENCE {//CA's name
  33   19:       SET {
  35   17:         SEQUENCE {
  37   10:           OBJECT IDENTIFIER
         :             domainComponent (0 9 2342 19200300 100 1 25)
  49    3:           IA5String 'com'
         :           }
         :         }
  54   23:       SET {
  56   21:         SEQUENCE {
  58   10:           OBJECT IDENTIFIER
         :             domainComponent (0 9 2342 19200300 100 1 25)
  70    7:           IA5String 'example'
         :           }
         :         }
  79   19:       SET {
  81   17:         SEQUENCE {
  83    3:           OBJECT IDENTIFIER commonName (2 5 4 3)
  88   10:           PrintableString 'Example CA'
         :           }
         :         }
         :       }
 100   30:     SEQUENCE {// Validity
 102   13:       UTCTime 15/09/2004 11:48:21 GMT // Not Before
 117   13:       UTCTime 15/03/2005 11:48:21 GMT // Not After
         :       }
 132   67:     SEQUENCE { // Subject name
 134   19:       SET {
 136   17:         SEQUENCE {
 138   10:           OBJECT IDENTIFIER
         :             domainComponent (0 9 2342 19200300 100 1 25)
 150    3:           IA5String 'com'
         :           }
         :         }
 155   23:       SET {
 157   21:         SEQUENCE {
 159   10:           OBJECT IDENTIFIER
         :             domainComponent (0 9 2342 19200300 100 1 25)
 171    7:           IA5String 'example'
         :           }
         :         }
 180   19:       SET {
 182   17:         SEQUENCE {
 184    3:           OBJECT IDENTIFIER commonName (2 5 4 3)
 189   10:           PrintableString 'End Entity'
         :           }
         :         }
         :       }
 201  159:     SEQUENCE {// subject public key info
 204   13:       SEQUENCE {
 206    9:         OBJECT IDENTIFIER
         :           rsaEncryption (1 2 840 113549 1 1 1)//subject public key algorithm id
 217    0:         NULL
         :         }
 219  141:       BIT STRING, encapsulates {
 223  137:         SEQUENCE {
 226  129:           INTEGER
         :             00 E1 6A E4 03 30 97 02 3C F4 10 F3 B5 1E 4D 7F
         :             14 7B F6 F5 D0 78 E9 A4 8A F0 A3 75 EC ED B6 56
         :             96 7F 88 99 85 9A F2 3E 68 77 87 EB 9E D1 9F C0
         :             B4 17 DC AB 89 23 A4 1D 7E 16 23 4C 4F A8 4D F5
         :             31 B8 7C AA E3 1A 49 09 F4 4B 26 DB 27 67 30 82
         :             12 01 4A E9 1A B6 C1 0C 53 8B 6C FC 2F 7A 43 EC
         :             33 36 7E 32 B2 7B D5 AA CF 01 14 C6 12 EC 13 F2
         :             2D 14 7A 8B 21 58 14 13 4C 46 A3 9A F2 16 95 FF
         :             23
 358    3:           INTEGER 65537
         :           }
         :         }
         :       }
 363  117:     [3] {
 365  115:       SEQUENCE {
 367   33:         SEQUENCE {
 369    3:           OBJECT IDENTIFIER subjectAltName (2 5 29 17)
 374   26:           OCTET STRING, encapsulates {
 376   24:             SEQUENCE {
 378   22:               [1] 'end.entity@example.com'
         :               }
         :             }
         :           }
 402   29:         SEQUENCE {// subject unique Identifier
 404    3:           OBJECT IDENTIFIER subjectKeyIdentifier (2 5 29 14)
 409   22:           OCTET STRING, encapsulates {
 411   20:             OCTET STRING
         :               17 7B 92 30 FF 44 D6 66 E1 90 10 22 6C 16 4F C0
         :               8E 41 DD 6D
         :             }
         :           }
 433   31:         SEQUENCE {// CA unique Identifier
 435    3:           OBJECT IDENTIFIER
         :             authorityKeyIdentifier (2 5 29 35)
 440   24:           OCTET STRING, encapsulates {
 442   22:             SEQUENCE {
 444   20:               [0]
         :                 08 68 AF 85 33 C8 39 4A 7A F8 82 93 8E 70 6A
         :                 4A 20 84 2C 32
         :               }
         :             }
         :           }
 466   14:         SEQUENCE {//Extensions, here's NULL
 468    3:           OBJECT IDENTIFIER keyUsage (2 5 29 15)
 473    1:           BOOLEAN TRUE
 476    4:           OCTET STRING, encapsulates {
 478    2:             BIT STRING 6 unused bits
         :               '11'B
         :             }
         :           }
         :         }
         :       }
         :     }
 482   13:   SEQUENCE {//Certificate Signature Algorithm ID
 484    9:     OBJECT IDENTIFIER
         :         sha1withRSAEncryption (1 2 840 113549 1 1 5)
 495    0:     NULL
         :     }
 497  129:   BIT STRING
         :     00 20 28 34 5B 68 32 01 BB 0A 36 0E AD 71 C5 95
         :     1A E1 04 CF AE AD C7 62 14 A4 1B 36 31 C0 E2 0C
         :     3D D9 1E C0 00 DC 10 A0 BA 85 6F 41 CB 62 7A B7
         :     4C 63 81 26 5E D2 80 45 5E 33 E7 70 45 3B 39 3B
         :     26 4A 9C 3B F2 26 36 69 08 79 BB FB 96 43 77 4B
         :     61 8B A1 AB 91 64 E0 F3 37 61 3C 1A A3 A4 C9 8A
         :     B2 BF 73 D4 4D E4 58 E4 62 EA BC 20 74 92 86 0E
         :     CE 84 60 76 E9 73 BB C7 85 D3 91 45 EA 62 5D CD
         :   }
```

解析如下：

- 8：INTERGER 2 表示该认证书版本为3（值为2）
- 13：INTEGER序列号Serial Number是18
- 18：ALGORITHM ID，认证书是通过RSA和SHA1哈希算法加密
- 31：发布者的名字 cn=Example CA, dc=example, dc=com
- 102: 有效期: UTCTime 15/09/2004 11:48:21 GMT 至  UTCTime 15/03/2005 11:48:21 GMT
- 132: subject的名字cn=End Entity, dc=example, dc=com，该认证书是一个终端实体认证
- 201: 认证书包括一个1024bit的RSA公钥
