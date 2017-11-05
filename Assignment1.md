# Web安全作业——DES算法

姓名：李晓芸

学号：15331169

班级：15级软工计应


---

## 一、算法原理概述
设信息空间由{0，1}组成的字符串构成，明文信息和经过DES加密的密文信息是64位的分组，密钥也是64位，是一种用于电子信息加密的对称加密算法。

## 二、总体结构
**总体结构是Feistel结构：**
![概述图][1]

其中，48位的$K_i$子密钥是经过密钥调度获取的：

![子密钥生成][2]


在Feistel轮函数$f(R_i-1, K_i)$中，$K_i$为48位，因此32位$R_i-1$需要采用**E扩展**成48位之后再进行异或操作。异或操作后得到48位信息，使用**S box置换**，将6*8转换成4*8，也即是32位。

## 三、模块分解
### 1. IP置换
IP置换的目的是将输入的64位数据块按位重新组合，并将输出分为$L_i$ $R_i$两部分。每部分各长32位。置换原则并不是将64位直接对半分成L0和R0，而是根据下面表格的置换原则。
<table>
<table border="1" cellspacing="0" cellpadding="0">
<tbody>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">58</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">50</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">42</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">34</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">26</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">18</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">10</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">2</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">60</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">52</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">44</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">36</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">28</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">20</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">12</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">4</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">62</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">54</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">46</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">38</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">30</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">22</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">14</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">6</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">64</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">56</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">48</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">40</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">32</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">24</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">16</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">8</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">57</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">49</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">41</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">33</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">25</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">17</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">9</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">1</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">59</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">51</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">43</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">35</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">27</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">19</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">11</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">3</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">61</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">53</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">45</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">37</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">29</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">21</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">13</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">5</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">63</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">55</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">47</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">39</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">31</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">23</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">15</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">7</span></p>
</td>
</tr>
</tbody>
</table>
表中的数字代表原数据中此位置的数据在新数据中的位置。
### 2. 16轮迭代T

#### (1) Feistel轮函数$f(R_i-1, K_i)$
##### a. E扩展置换
    因为Feistel轮函数产生的子密钥是48位，而$R_i$是32位，因此需要E扩展置换来将32位的数据扩展至48位，再来进行异或运算。
    E扩展置换原则很简单，每4位扩展两位，应用循环扩展，而第一位扩展第32位，第48位扩展第1位，如下图所示：
<table>
<table border="1" cellspacing="0" cellpadding="0">
<tbody>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">32</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">1</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">2</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">3</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">4</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">5</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">4</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">5</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">6</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">7</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">8</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">9</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">8</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">9</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">10</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">11</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">12</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">13</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">12</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">13</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">14</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">15</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">16</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">17</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">16</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">17</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">18</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">19</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">20</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">21</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">20</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">21</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">22</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">23</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">24</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">25</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">24</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">25</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">26</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">27</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">28</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">29</span></p>
</td>
</tr>
<tr>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">28</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">29</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">30</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">31</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times;">32</span></p>
</td>
<td width="38">
<p align="center"><span style="font-family: 'times new roman', times; background-color: #ffcc00;">1</span></p>
</td>
</tr>
</tbody></table>


##### b. S box置换
E扩展后的$R_i-1$和$K_i$为48位，异或运算的对象为32位$L_i$，因此需要将48位再次转成32位数据。48位数据分成8*6的大小，S box本身就是一个4行16列的表。S box有6位输入4位输出，其中输入的高低两位做为行数H，中间四位做为列数L，在S box中查找第H行L列对应的数据。每个S box对应的表都不同。

##### c. P box置换
 在S box置换后需要再按照P box置换，加强安全性。该置换就是把输入的每位映射到输出位，任何一位不能被映射两次，也不能被略去。这才完成一次Feistel轮函数过程。
#### (2) 密钥调度(子密钥$K_i$的获取）
  输入K为64位，经过PC-1后将奇偶校验位去除、根据表n置换，剩余56位。将56位分成两部分C0、D0。从56位密钥中产生出48位子密钥。然后根据轮数，C0和D0分别循环左移1位或2位生成C1和D1。从56位中根据表n置换同时选择48位作为子密钥。
### 3. $IP^{-1}$置换
 IP逆置换是初始IP置换的逆过程，DES最后一轮后，左、右两半部分并未进行交换，而是两部分合并形成一个分组做为末置换的输入。
## 四、数据结构
```
#define PLAIN_FILE_OPEN_ERROR -1
#define KEY_FILE_OPEN_ERROR -2
#define CIPHER_FILE_OPEN_ERROR -3
#define OK 1
#define FeistelIterTimes 16

typedef int ElemType;

//初始IP置换表
int IP_Table[64] = {  57,49,41,33,25,17,9,1,
                     59,51,43,35,27,19,11,3,
                     61,53,45,37,29,21,13,5,
                     63,55,47,39,31,23,15,7,
                     56,48,40,32,24,16,8,0,
                     58,50,42,34,26,18,10,2,
                     60,52,44,36,28,20,12,4,
                     62,54,46,38,30,22,14,6};


//IP-1逆置换表
int IP_1_Table[64] = {39,7,47,15,55,23,63,31,
                     38,6,46,14,54,22,62,30,
                     37,5,45,13,53,21,61,29,
                     36,4,44,12,52,20,60,28,
                     35,3,43,11,51,19,59,27,
                     34,2,42,10,50,18,58,26,
                     33,1,41,9,49,17,57,25,
                     32,0,40,8,48,16,56,24};

//E扩展置换表
int E_Table[48] = {31, 0, 1, 2, 3, 4,
                  3,  4, 5, 6, 7, 8,
                  7,  8,9,10,11,12,
                  11,12,13,14,15,16,
                  15,16,17,18,19,20,
                  19,20,21,22,23,24,
                  23,24,25,26,27,28,
                  27,28,29,30,31, 0};

//P box置换表
int P_box[32] = {15,6,19,20,28,11,27,16,
                  0,14,22,25,4,17,30,9,
                  1,7,23,13,31,26,2,8,
                  18,12,29,5,21,10,3,24};

//S box 1- 8
int S_box[8][4][16] = //S1
            {{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
              {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
                //S2
              {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
              {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
              {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
              {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
              //S3
              {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
              {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
              {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
              //S4
              {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
              {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
              {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
              {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
              //S5
              {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
              {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
              {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
              {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
              //S6
              {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
              {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
              {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
              {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
              //S7
              {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
              {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
              {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
              {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
              //S8
              {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
              {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
              {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
              {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};

//PC-1置换选择1
int PC_1_Table[56] =  {56,48,40,32,24,16,8,
              0,57,49,41,33,25,17,
              9,1,58,50,42,34,26,
              18,10,2,59,51,43,35,
              62,54,46,38,30,22,14,
              6,61,53,45,37,29,21,
              13,5,60,52,44,36,28,
              20,12,4,27,19,11,3};

//PC-2置换选择2
int PC_2_Table[48] = {13,16,10,23,0,4,2,27,
              14,5,20,9,22,18,11,3,
              25,7,15,6,26,19,12,1,
              40,51,30,36,46,54,29,39,
              50,44,32,46,43,48,38,55,
              33,52,45,41,49,35,28,31};

//根据轮次确定左移的次数,共有16轮
int MOVE_TIME[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

// functions' definition
// 将函数模块化
void Add_Parity_bit(ElemType*& plaintext, ElemType*& plaintext_Parity_bit);
void DES_Transform(ElemType*& input, ElemType*& output, int len, int* table);
void DES_T_Feistel_Iterators(ElemType*& L, ElemType*& R);
void DES_Make_Subkeys(ElemType*& data, ElemType**& Subkeys);
void DES_XOR(ElemType*& data1, ElemType*& data2, int len);
void DES_SBOX(ElemType*& input, ElemType*& output);
void DES_ROL(ElemType*& data, int time);
void DES_Merge(ElemType*& data1, ElemType*& data2, ElemType*& ans, int len);
int DecimalToBinary(int bin);
```

## 五、类-C语言算法过程（贴代码）
```
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cmath>

//将S盒子输出的十进制转成二进制
void DecimalToBinary(int bin, int* ans) {
  int cnt = 3;
  while (bin != 1 || bin) {
    ans[cnt--] = bin % 2;
    bin /= 2;
  }
  ans[cnt] = bin;
}

//合并两数组
void DES_Merge(ElemType*& data1, ElemType*& data2, ElemType*& ans, int len) {
  for (int i = 0; i < len; i++)
    ans[i] = data1[i];
  for (int i = len; i < 2 * len; i++)
    ans[i] = data2[i];
}

//将56位的信息，每7位增加一个奇偶校验位
void Add_Parity_bit(ElemType*& plaintext, ElemType*& plaintext_Parity_bit); {
  //简单起见，这里采取偶校验
  for (int i = 0; i < 8; i++) {
    bool isEven = 0;
    for (int j = 0; j < 7; j++) {
      plaintext_Parity_bit[i * 8 + j] = plaintext[i * 8 + j];
      if (plaintext[i * 8 + j] == 1)
        isEven = !isEven;
    }
    plaintext_Parity_bit[i * 8 + 7] = isEven? 0: 1;
  }
}

//XOR operation
void DES_XOR(ElemType*& data1, ElemType*& data2, ElemType*& ans, int len) {
  for (int i = 0; i < len; i++) {
    *(ans + i) = *(data1 + i) ^ *(data2 + i);
  }
}

// 初始IP置换
void DES_IP_Transfrom(ElemType*& data, ElemType *& L, ElemType*& R) {
  for (int i = 0; i < 64; i++) {
    if (i < 32)
     L[i] = data[IP_Table[i] - 1];
    else
      R[i] = data[IP_Table[i] - 1];
  }
}

//末IP逆置换
void DES_Transform(ElemType*& input, ElemType *& output, int len, int* table) {
  for (int i = 0; i < len; i++) {
      output[i] = input[table[i] - 1];
  }
}


void DES_SBOX(ElemType*& input, ElemType*& output) {
  for (int i = 0; i < 8; i++) {
    int row = 0, col = 0;
    for (int j = 0; j < 6; j++) {
      if (j < 2)
        row += input[i * 8 + j] * pow(2, 1 - j);
      else
        col += input[i * 8 + j] * pow(2, 5 - j);
    }
    int SBOX[4];
    DecimalToBinary(S_box[i][row][col], SBOX);
    for (int k = 0; k < 4; k++) {
      output[i * 8 + k] = SBOX[k];
    }
  }
}

void DES_ROL(ElemType*& input, ElemType*& output, int time) {
  for (int i = 0; i < 28; i++) {
    output[i] = input[(i + time) % 28];
  }
}

void DES_Make_Subkeys(ElemType*& data, ElemType**& Subkeys) {
  int loop = 1, loop2 = 2;
  ElemType PC_1[56] = {0};
  DES_Transform(data, PC_1, int 56, PC_1_Table);
  ElemType C[28] = {0};
  ElemType D[28] = {0};
  int leftCnt = 0;
  for (int i = 0; i < 28; i++) {
    C[i] = PC_1[i];
    D[i] = PC_1[i + 28];
  }
  for (int i = 0; i < 16; i++) {
    ElemType rotate_c[28], rotate_d[28], merge[56];
    leftCnt += MOVE_TIME[i];
    DES_ROL(C, rotate_c, leftCnt);
    DES_ROL(D, rotate_d, leftCnt);
    DES_Merge(rotate1_c, rotate_d, merge, 28);
    DES_Transform(merge, Subkeys[i], 48, PC_2_Table);
  }
}

void DES_T_Feistel_Iterators(ElemType*& L, ElemType*& R, ElemType*& Subkey, ElemType*& output) {
  ElemType swap_L[32] = R;
  ElemType swap_R[32] = {0};
  ElemType STemp[32] = {0};;
  ElemType tempAns[48] = {0};
  ElemType E_extension[48] = {0};
  DES_Transform(R, E_extension, 48, E_Table);
  DES_XOR(E_extension, Subkey, tempAns, 48);
  DES_SBOX(tempAns, STemp);
  DES_Transform(STemp, output, 32, P_box);
}

int main() {
  ElemType plaintext[56] = {0};
  ElemType Subkeys[16][48] = {0};
  ElemType plaintext_Parity_bit[64] = {0};
  ElemType ciphertext[64] = {0};
  ElemType L[32] = {0}, R[32] = {0};
  scanf("%s", plaintext);
  Add_Parity_bit(plaintext, plaintext_Parity_bit);
  DES_Make_Subkeys(plaintext_Parity, Subkeys);
  DES_IP_Transfrom(plaintext_Parity_bit, L, R);
  for (int i = 0; i < FeistelIterTimes; i++) {
    DES_T_Feistel_Iterators(L, R);
  }
  DES_Merge(L, R, plaintext_Parity_bit, 32);
  DES_Transform(plaintext_Parity_bit, ciphertext, 64, IP_1_Table);
  printf("%s\n", ciphertext);
  printf("Encrypted Done!\n");
}
```

  [1]: http://images2015.cnblogs.com/blog/802212/201610/802212-20161009222915538-1765873611.png
  [2]: https://gss2.bdstatic.com/-fo3dSag_xI4khGkpoWK1HF6hhy/baike/c0=baike80,5,5,80,26/sign=0d711ee4de62853586edda73f1861da3/83025aafa40f4bfb6dccfa42084f78f0f7361883.jpg



参考资料：
[安全体系（一）——DES算法](http://www.cnblogs.com/songwenlong/p/5944139.html)

[DES 百度百科](https://baike.baidu.com/item/des%E7%AE%97%E6%B3%95/10306073?fr=aladdin#3_5)
[DES wikipedia](https://en.wikipedia.org/wiki/Data_Encryption_Standard)
[Feistel 百度百科](https://baike.baidu.com/item/Feistel/1985068?fr=aladdin)
[工程实践——DES算法](http://blog.csdn.net/zidane_2014/article/details/37988657)
[DES加密算法——实现（C语言）](http://blog.csdn.net/xumaojun/article/details/17675905)
