#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int InitialPermutationTable[64] = {
	58,	50,	42,	34,	26,	18,	10,	2,
	60, 52,	44,	36,	28,	20,	12,	4,
	62,	54,	46,	38,	30,	22,	14, 6,
	64,	56,	48,	40,	32,	24,	16,	8,
	57,	49,	41,	33,	25,	17,	9,	1,
	59,	51,	43,	35,	27,	19,	11,	3,
	61,	53,	45,	37,	29,	21,	13,	5,
	63,	55,	47,	39,	31,	23,	15,	7
};

int FinalPermutationTable[64] = {
	40,	8,	48,	16,	56,	24,	64,	32,
	39, 7,	47,	15,	55,	23,	63,	31,
	38,	6,	46,	14,	54,	22,	62, 30,
	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,
	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,
	33,	1,	41,	9,	49,	17,	57,	25
};

int SubstitutionTables[8][4][16] = { {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
	{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
	{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
	{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 2, 14, 10, 0, 6, 13}},

   {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

   {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
	{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
	{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
	{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

   {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
	{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
	{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
	{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

   {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
	{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
	{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
	{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

   {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
	{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
	{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
	{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

   {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
	{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
	{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
	{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

   {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
	{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
	{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
	{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}} };

int StraightPermutationTable[32] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25
};

int ExpansionPermutationTable[48] = {
	32, 1, 2, 3, 4, 5, 
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

int parityDropTable[56] = {
	57, 49, 41, 33, 25, 17, 9, 1,
	58, 50, 42, 34, 26, 18, 10, 2,
	59, 51, 43, 35, 27, 19, 11, 3, 
	60, 52, 44, 36, 63, 55, 47, 39,
	31, 23, 15, 7, 62, 54, 46, 38,
	30, 22, 14, 6, 61, 53, 45, 37,
	29, 21, 13, 5, 28, 20, 12, 4
};

int keyCompressionTable[48] = {
	14, 17, 11, 24, 1,  5,  3,  28,
	15, 6,	21, 10, 23, 19, 12, 4,
	26, 8,  16, 7,  27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32,
};
					
int ShiftTable[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

int keyWithParities[64] = {
	1,0,1,0,1,0,1,0,
	1,0,1,1,1,0,1,1,
	0,0,0,0,1,0,0,1,
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,1,1,
	0,0,1,1,0,1,1,0,
	1,1,0,0,1,1,0,0,
	1,1,0,1,1,1,0,1
};

int RoundKeys[16][48] = { 0 };
int TempKeys[16][48] = { 0 };
int preRoundKey[56] = { 0 };
int cipherKey[56] = { 0 };
int leftKey[28] = { 0 };
int rightKey[28] = { 0 };

char plainBlock[64] = " ";
char cipherBlock[64] = " ";
int IntPlain_dec[8] = { 0 };
int IntPlain_bin[64] = { 0 };
int IntPlain_hex[16] = { 0 };
int IntCipher_bin[64] = { 0 };
int IntCipher_dec[8] = { 0 };
int IntCipher_hex[16] = { 0 };

int leftBlock[32] = { 0 };
int rightBlock[32] = { 0 };
int inBlock[64] = { 0 };
int outBlock[64] = { 0 };

int checkdec[64] = { 0 };
int checkhex[16] = { 0 };
char checkchar[16] = " ";
int hex_key[12] = { 0 };
int hex_left[8] = { 0 };
int hex_right[8] = { 0 };

void cipher(int* IntPlain_bin, int* IntCipher_bin);
void mixer(int* leftBlock, int* rightBlock, int round);
void swapper(int* leftBlock, int* rightBlock);
void function(int* inBlock, int round, int* outBlock);
void substitute(int inbits, int outbits, int* inBlock, int* outBlock);
void Key_Generator(int* keyWithParities, int* ShiftTable);
void Key_Decryption();
void shiftLeft(int* block, int numOfShifts);
void copy(int bits, int* inBlock, int* newBlock);
void split(int oriBits, int newBits, int* inBlock, int* leftBlock, int* rightBlock);
void combine(int oriBits, int newBits, int* left, int* right, int* newBlock);
void permute(int inbits, int outbits, int* plainBlock, int* inBlock, int* table);
void exclusiveOr(int bits, int* arr1, int* arr2, int* result);
void Key_exclusiveOr(int bits, int* arr1, int round, int* result);
void DecToBin(int inbit, int outbit, int* IntPlain_dec, int* IntPlain_bin);
void BinToDec(int inbit, int outbit, int* IntCipher_bin, int* IntCipher_dec);
void BinToHex(int length, int round, int* bin, int* hex);
void Key_BinToHex(int length, int round, int* hex); 
void HexToChar(int inbit, int outbit, int* IntCipher_hex, char* cipherBlock);
void CharToHex(int inbit, int outbit, char* plainBlock, int* IntPlain_hex);
void DecToHex(int inbit, int outbit, int* IntCipher_dec, int* IntCipher_hex);
void HexToDec(int inbit, int outbit, int* IntPlain_hex, int* IntPlain_dec);


void cipher(int* IntPlain_bin, int* IntCipher_bin) {	//암호화함수
	permute(64, 64, IntPlain_bin, inBlock, InitialPermutationTable);	//초기치환
	//after initial permutaition 출력부분
	BinToDec(64, 8, inBlock, checkdec);
	DecToHex(8, 16, checkdec, checkhex);
	printf("\n after initial permutation => ");
	HexToChar(16, 16, checkhex, checkchar);
	//

	split(64, 32, inBlock, leftBlock, rightBlock);
	//after split 출력부분
	printf("\n\n after splitting =>");
	BinToHex(32, 8, leftBlock, hex_left);	//left를 16진수로,
	printf(" Left : ");
	HexToChar(8, 8, hex_left, checkchar);

	BinToHex(32, 8, rightBlock, hex_right); //right를 16진수로,
	printf("  Right : ");
	HexToChar(8, 8, hex_right, checkchar);
	printf("\n");
	//

	for (int round = 0; round < 16; round++) {	//라운드마다
		mixer(leftBlock, rightBlock, round);	//mixer 실행 후
		if (round != 15) swapper(leftBlock, rightBlock);	//마지막라운드 제외하고 swapper

		// 라운드별 left, right, roundkey출력 부분
		printf("\n%dRound => ", round + 1);	//결과를
		BinToHex(32, 8, leftBlock, hex_left);	//left를 16진수로,
		printf(" Left : ");
		HexToChar(8, 8, hex_left, checkchar);

		BinToHex(32, 8, rightBlock, hex_right); //right를 16진수로,
		printf("  Right : ");
		HexToChar(8, 8, hex_right, checkchar);

		Key_BinToHex(48, round, hex_key); //라운드키를 16진수로 출력
		printf("  Round Key : ");
		for (int i = 0; i < 12; i++)
			printf("%x", hex_key[i]);
		printf("\n");
		//
	}
	combine(32, 64, leftBlock, rightBlock, outBlock);	//left+right	
	permute(64, 64, outBlock, IntCipher_bin, FinalPermutationTable);		//최종치환
}

void mixer(int* leftBlock, int* rightBlock, int round) {
	int T1[32] = { 0 };
	int T2[32] = { 0 };
	int T3[32] = { 0 };

	copy(32, rightBlock, T1);		//rightBlock을 T1으로 복사
	function(T1, round, T2);		//T1과 키를 DES함수에 적용하여 T2에 결과배열 할당
	exclusiveOr(32, leftBlock, T2, T3);		//DES함수의 결과와 leftBlock을 xor연산하여 결과를 T3에 할당
	copy(32, T3, leftBlock);		//T3을 새로운 rightBlock으로	
}
 
void swapper(int* leftBlock, int* rightBlock) {	//leftBlock과 rightBlock를 swap
	int T[32] = { 0 };
	copy(32, leftBlock, T);	
	copy(32, rightBlock, leftBlock); 
	copy(32, T, rightBlock);
}

void function(int* inBlock, int round, int* outBlock) {	//DES함수
	int T1[48] = { 0 };
	int T2[48] = { 0 };
	int T3[32] = { 0 };

	permute(32, 48, inBlock, T1, ExpansionPermutationTable);	//right블록을 확장
	Key_exclusiveOr(48, T1, round, T2);		//라운드키와 right블록 xor연산
	substitute(48, 32, T2, T3);				//s-box로 48bit->32bit로 축소
	permute(32, 32, T3, outBlock, StraightPermutationTable);	//단순 p박스 치환
}

void substitute(int inbits, int outbits, int* inBlock, int* outBlock) {
	for (int i = 0; i < 8; i++) {
		int row = inBlock[i * 6] * 2 + inBlock[i * 6 + 5];	//첫비트와 마지막비트로 행결정	
		int col = 8 * inBlock[i * 6 + 1] + 4 * inBlock[i * 6 + 2] + 2 * inBlock[i * 6 + 3] + inBlock[i * 6 + 4];	//행결정 비트제외한 중간비트로 열 결정

		int value = SubstitutionTables[i][row][col];	//s박스의 값 가져옴

		outBlock[i * 4] = value / 8;					//10진수 정수이므로 2진수로 변환
		outBlock[i * 4 + 1] = (value % 8) / 4;
		outBlock[i * 4 + 2] = (value % 4) / 2;
		outBlock[i * 4 + 3] = value % 2;
	}
}

void Key_Generator(int* keyWithParities, int* ShiftTable) {	//키생성함수
	permute(64, 56, keyWithParities, cipherKey, parityDropTable);	//parity bit drop, 축소P-box
	split(56, 28, cipherKey, leftKey, rightKey);	
	for (int round = 0; round < 16; round++) {
		shiftLeft(leftKey, ShiftTable[round]);				//leftkey shift
		shiftLeft(rightKey, ShiftTable[round]);				//rightkey shift
		combine(28, 56, leftKey, rightKey, preRoundKey);	//preRoundKey=leftKey+rightKey(합치기)
		permute(56, 48, preRoundKey, RoundKeys[round], keyCompressionTable);	//축소P-box
	}
}

void Key_Decryption() {
	for (int i = 0; i < 16; i++)	//라운드키 역순으로
		for (int j = 0; j < 48; j++)
			TempKeys[15 - i][j] = RoundKeys[i][j];
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 48; j++)
			RoundKeys[i][j] = TempKeys[i][j];
}

void shiftLeft(int* block, int numOfShifts) {	//numofshifts = RoundKeys[round]
	for (int i = 0; i < numOfShifts; i++) {		//numofshifts값만큼 반복
		int T = block[0];
		for (int j = 1; j < 28; j++) 		
			block[j - 1] = block[j];			//한비트씩 앞으로 shift
		block[27] = T;							//넘어가는 비트 뒤에 가져와 붙이기
	}
}

void copy(int bits, int* inBlock, int* newBlock) {
	for (int i = 0; i < bits; i++) 
		newBlock[i] = inBlock[i];				//newBlock으로 inBlock 복사
}

void split(int oriBits, int newBits, int* inBlock, int* leftBlock, int* rightBlock) {
	int j=0;
	for (int i = 0; i < newBits; i++) {		//원래 비트수의 절반만큼 잘라 반의 앞부분은 leftblock에,
		leftBlock[i] = inBlock[j];
		j++;
	}
	for (int i = 0; i < newBits; i++) {		//반의 뒷부분은 rightblock에 저장
		rightBlock[i] = inBlock[j];
		j++;
	}
}

void combine(int oriBits, int newBits, int* left, int* right, int* newBlock) { 
	int j = 0;
	for (int i = 0; i < oriBits; i++, j++)	//left블록을 저장한 후
		newBlock[j] = left[i];
	for (int i = 0; i < oriBits; i++, j++)	//이어서 right블록을 연결하여 붙임
		newBlock[j] = right[i];
}

void permute(int inbits, int outbits, int* plainBlock, int* inBlock, int* table) {	
	int tmp = 0;
	if (inbits >= outbits) //P-box (inbits=outbits : 단순치환, inbits>outbits : 축소치환)
		for (int i = 0; i < outbits; i++)
			inBlock[i] = plainBlock[table[i] - 1]; 
	else				//P-box (inbits<outbits : 확장치환)
		for (int i = 0; i < outbits; i++)
			inBlock[i] = plainBlock[table[i]-1];
}

void Key_exclusiveOr(int bits, int* arr1, int round, int* result) { //두배열의 같은 위치원소끼리 xor연산하여 새배열에 결과저장_Key
	for (int i = 0; i < bits; i++) 
		result[i] = arr1[i] ^ RoundKeys[round][i];
}

void exclusiveOr(int bits, int* arr1, int* arr2, int* result) { //두배열의 같은 위치원소끼리 xor연산하여 새배열에 결과저장
	for (int i = 0; i < bits; i++)
		result[i] = arr1[i] ^ arr2[i];
}

void DecToBin(int inbit, int outbit, int* IntPlain_dec, int* IntPlain_bin) {	//10진수를 2진수로 변환
	for (int i = 0; i < inbit; i++) {
		int tmp = IntPlain_dec[i];
		for (int j = ((outbit / inbit) - 1); j >= 0; j--) {	//2로나누어 나머지를 구한 후 역순으로 배열에 저장(like 2차원배열)
			if (tmp >= 0) {
				IntPlain_bin[(i * inbit) + j] = tmp % 2;
				tmp /= 2;
			}
			else {
				tmp = 0;
				IntPlain_bin[(i * inbit) + j] = 0;
			}
		}
	}
}

void BinToDec(int inbit, int outbit, int* IntCipher_bin, int* IntCipher_dec) {
	int tmp;
	for (int i = 0; i < outbit; i++) {
		tmp = 0;
		for (int j = 0; j < (inbit / outbit); j++)
			tmp = tmp + IntCipher_bin[(i * outbit) + j] * (int)pow(2, 7 - j);	//8bit의 2진수를 10진수로 변환
		IntCipher_dec[i] = tmp;
	}
}

void BinToHex(int inbit, int outbit, int* bin, int* hex) {
	for (int i = 0; i < outbit; i++)
		hex[i] = bin[4 * i] * 8 + bin[4 * i + 1] * 4 + bin[4 * i + 2] * 2 + bin[4 * i + 3];
}

void Key_BinToHex(int length, int round, int* hex) {
	int tmp;
	for (int i = 0; i < length/4 ; i++) {
		tmp = 0;
		for (int j = 0; j < 4; j++) 
			tmp += RoundKeys[round][i*4 + j] * (int)pow(2, 3 - j);  //4bit의 2진수를 16진수로 변환_KEY
		hex[i] = tmp;
	}
}

void HexToDec(int inbit, int outbit, int* IntPlain_hex, int* IntPlain_dec) { //8bit의 2진수를 하나의 10진수로 저장하기위해 16진수 두자리씩 끊어 10진수로 바꾸어 IntPlain_dec에 저장
	if (inbit / outbit == 2) 	//하나의 10진수를 두 자리 16진수로
		for (int i = 0; i < inbit; i += (inbit / outbit)) 
			IntPlain_dec[i / 2] = IntPlain_hex[i] * 16 + IntPlain_hex[i + 1];	
	else						//하나의 10진수를 한 자리 16진수로
		for (int i = 0; i < outbit; i++) 
			IntPlain_dec[i] = IntPlain_hex[i];
}

void DecToHex(int inbit, int outbit, int* IntCipher_dec, int* IntCipher_hex) {
	if (outbit / inbit == 2) {
		for (int i = 0; i < outbit; i += 2) { //암호화된 10진수 정수를 16진수로 변환 
			IntCipher_hex[i] = IntCipher_dec[i / 2] / 16;
			IntCipher_hex[i + 1] = IntCipher_dec[i / 2] % 16;
		}
	}
	else 
		for (int i = 0; i < 16; i++)  //암호화된 10진수 정수를 16진수로 변환 
			IntCipher_hex[i] = IntCipher_dec[i] % 16;
}

void CharToHex(int inbit, int outbit, char* plainBlock, int* IntPlain_hex) { //문자형으로 입력받은 16진수를 10진수 값으로 한자리씩 IntPlain_hex에 저장
	for (int i = 0; i < inbit; i++) {
		if (plainBlock[i] >= '0' && plainBlock[i] <= '9')	IntPlain_hex[i] = plainBlock[i] - 48;
		else if (plainBlock[i] >= 'A' && plainBlock[i] <= 'F') IntPlain_hex[i] = plainBlock[i] - 55;
		else if (plainBlock[i] >= 'a' && plainBlock[i] <= 'f') IntPlain_hex[i] = plainBlock[i] - 87;
		else { printf("잘못입력하셨습니다.\n"); return; }
	}
}

void HexToChar(int inbit, int outbit, int* IntCipher_hex, char* cipherBlock) {
	for (int i = 0; i < inbit; i++) {
		if (IntCipher_hex[i] >= 0 && IntCipher_hex[i] <= 9) cipherBlock[i] = IntCipher_hex[i] + 48;
		else if (IntCipher_hex[i] >= 10 && IntCipher_hex[i] <= 15) cipherBlock[i] = IntCipher_hex[i] + 87;
		else { printf("실패\n"); return; }
	}
	for (int i = 0; i < outbit; i++)	//출력
		printf("%c", cipherBlock[i]);
}

void main() {
	while (1) {
		int num;
		printf("\n1:암호화, 2:복호화, 0:종료\n");
		printf("번호를 입력하세요 : ");
		scanf("%d%*c",&num);
		
		if (num == 1) {		//암호화
			printf("원문입력 : ");

			/*  문자를 입력받아 10진수 정수로 변환하여 저장_결과문자 확인이 힘들어 16진수 입력받도록 변경
				gets(plainBlock);
				for (int i = 0; i < 8; i++)
					IntPlain_dec[i] = (int)plainBlock[i];
			*/

			//	문자가 아닌 16진수로 입력받기위한 코드 추가 부분
			gets(plainBlock);
			CharToHex(16, 16, plainBlock, IntPlain_hex);	//문자를 16진수 정수로
			HexToDec(16, 8, IntPlain_hex, IntPlain_dec);	//16진수 두 자리를 하나의 10진수로
			//

			DecToBin(8, 64, IntPlain_dec, IntPlain_bin); //10진수를 2진수로 변환
			Key_Generator(keyWithParities, ShiftTable); //키생성
			cipher(IntPlain_bin, IntCipher_bin);	//암호화
			BinToDec(64, 8, IntCipher_bin, IntCipher_dec);	//2진수를 10진수로 변환

			/* 암호화되어 10진수로 변환한 암호문을 문자로 바꾸어 출력, 하지만 저장_결과문자 확인이 힘들어 입출력텍스트를 16진수로 변경
				for (int i = 0; i < 8; i++) {
					if (IntCipher_dec[i] > 125)	IntCipher_dec[i] = 46;
					if(IntCipher_dec[i] < 33) IntCipher_dec[i] = 33;
					cipherBlock[i] = (char)IntCipher_dec[i];
					printf_s("%c", cipherBlock[i]);
				}
			*/

			// 암호문을 문자가 아닌 16진수로 출력위한 추가 코드 부분
			DecToHex(8, 16, IntCipher_dec, IntCipher_hex);
			printf("\n Ciphertext => ");
			HexToChar(16, 16, IntCipher_hex, cipherBlock);	//암호화된 16진수를 문자형으로 변환
			//
		}
		else if (num == 2) {	//복호화
			printf("암호문입력 : ");

			/*  문자를 입력받아 10진수 정수로 변환하여 저장_결과문자 확인이 힘들어 16진수 입력받도록 변경
				gets(plainBlock);
				for (int i = 0; i < 8; i++)
					IntPlain_dec[i] = (int)plainBlock[i];
			*/

			//	문자가 아닌 16진수로 입력받기위한 코드 추가 부분
			gets(plainBlock);
			CharToHex(16, 16, plainBlock, IntPlain_hex);	//문자를 16진수 정수로
			HexToDec(16, 8, IntPlain_hex, IntPlain_dec);	//16진수 두 자리를 하나의 10진수로
			//

			DecToBin(8, 64, IntPlain_dec, IntPlain_bin); //10진수를 2진수로 변환
			Key_Decryption(); //라운드 키 역순으로
			cipher(IntPlain_bin, IntCipher_bin);	//복호화
			BinToDec(64, 8, IntCipher_bin, IntCipher_dec);	//2진수를 10진수로 변환

			/* 암호화되어 10진수로 변환한 암호문을 문자로 바꾸어 출력, 하지만 저장_결과문자 확인이 힘들어 입출력텍스트를 16진수로 변경
				for (int i = 0; i < 8; i++) {
					if (IntCipher_dec[i] > 125)	IntCipher_dec[i] = 46;
					if(IntCipher_dec[i] < 33) IntCipher_dec[i] = 33;
					cipherBlock[i] = (char)IntCipher_dec[i];
					printf_s("%c", cipherBlock[i]);
				}
			*/

			// 암호문을 문자가 아닌 16진수로 출력위한 추가 코드 부분
			DecToHex(8, 16, IntCipher_dec, IntCipher_hex);
			printf("\n Ciphertext => ");
			HexToChar(16, 16, IntCipher_hex, cipherBlock);	//암호화된 16진수를 문자형으로 변환
			//			
		}
		else if (num == 0) {	//종료
			printf("종료합니다.\n");
			_getch();
			break;
		}
		else printf("잘못된 입력입니다. 다시입력해주세요.\n");
	}
	return;
}