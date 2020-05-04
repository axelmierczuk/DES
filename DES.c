#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * Author: Axel Mierczuk
 *
 * Read more about this encryption method here:
 * https://academic.csuohio.edu/yuc/security/Chapter_06_Data_Encription_Standard.pdf
 */

void printLenBitChar(char arr[], int n);
void putInArr();
void putTogether(void);
void decToBinary(int n, int start);
int * permLast(void);
void XOR2(void);
void switchFinal(void);
int binaryToInt2(int i, int j, int k, int w);
int binaryToInt(int i, int j);
void putInXandTransform(void);
void XOR(int index);
void split(void);
int * rightSideExp(void);
int * permText(void);
void subkey(int index);
int * splitBlocks(char arr[], int n, int len);
int * perm56(int arr[]);
void printLenBit(int arr[], int n);


int InitialPerm[] = {
	  58, 50, 42, 34, 26, 18, 10, 2,
	  60, 52, 44, 36, 28, 20, 12, 4,
	  62, 54, 46, 38, 30, 22, 14, 6,
	  64, 56, 48, 40, 32, 24, 16, 8,
	  57, 49, 41, 33, 25, 17,  9, 1,
	  59, 51, 43, 35, 27, 19, 11, 3,
	  61, 53, 45, 37, 29, 21, 13, 5,
	  63, 55, 47, 39, 31, 23, 15, 7
};

int E[] =
{
	  32,  1,  2,  3,  4,  5,
	   4,  5,  6,  7,  8,  9,
	   8,  9, 10, 11, 12, 13,
	  12, 13, 14, 15, 16, 17,
	  16, 17, 18, 19, 20, 21,
	  20, 21, 22, 23, 24, 25,
	  24, 25, 26, 27, 28, 29,
	  28, 29, 30, 31, 32,  1
};

int P[] =
{
	  16,  7, 20, 21,
	  29, 12, 28, 17,
	   1, 15, 23, 26,
	   5, 18, 31, 10,
	   2,  8, 24, 14,
	  32, 27,  3,  9,
	  19, 13, 30,  6,
	  22, 11,  4, 25
};

int FP[] =
{
	  40, 8, 48, 16, 56, 24, 64, 32,
	  39, 7, 47, 15, 55, 23, 63, 31,
	  38, 6, 46, 14, 54, 22, 62, 30,
	  37, 5, 45, 13, 53, 21, 61, 29,
	  36, 4, 44, 12, 52, 20, 60, 28,
	  35, 3, 43, 11, 51, 19, 59, 27,
	  34, 2, 42, 10, 50, 18, 58, 26,
	  33, 1, 41,  9, 49, 17, 57, 25
};

int S1[4][16] =
{
		14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};

int S2[4][16] =
{
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};

int S3[4][16] =
{
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
};

int S4[4][16] =
{
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
};

int S5[4][16] =
{
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
};

int S6[4][16] =
{
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};

int S7[4][16]=
{
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
};

int S8[4][16]=
{
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

int PC1[] =
{
	  57, 49, 41, 33, 25, 17,  9,
	   1, 58, 50, 42, 34, 26, 18,
	  10,  2, 59, 51, 43, 35, 27,
	  19, 11,  3, 60, 52, 44, 36,
	  63, 55, 47, 39, 31, 23, 15,
	   7, 62, 54, 46, 38, 30, 22,
	  14,  6, 61, 53, 45, 37, 29,
	  21, 13,  5, 28, 20, 12,  4
};

int PC2[] =
{
	  14, 17, 11, 24,  1,  5,
	   3, 28, 15,  6, 21, 10,
	  23, 19, 12,  4, 26,  8,
	  16,  7, 27, 20, 13,  2,
	  41, 52, 31, 37, 47, 55,
	  30, 40, 51, 45, 33, 48,
	  44, 49, 39, 56, 34, 53,
	  46, 42, 50, 36, 29, 32
};

int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

int * LEFT[17], RIGHT[17];
int * IPtext;
int EXPtext2[49];
int * EXPtext;
int XORtext[48];
int X[8][6];
int X2[32];
int * X2perm;
int L[32];
int R[32];
char key8char[16];
char * keytemp;
int * key64bit;
int * key64;
int * key56bit;
int key48bit[17][49];
int CIPHER[64];
int ENCRYPTED[64];
char string[9999];
char EncryptedString[9999];
int count = 0;
int option= 1;

void DES(){
	int i;
	printf("Please enter some HEX text to encipher...");
	printf("\nYour text must be the length of a multiple of 16, if it is not, the text will be padded until it is:  ");
	scanf("%s", string);
	while(strlen(string)%16 != 0){
		strcat(string, "E");
	}
	printf("\n\nYou entered - %s\n", string);
	printf("Now we need to convert the text you entered into 64-bit blocks...\n");
	printf("The first one is...\n\n");
	IPtext = splitBlocks(string, 0, 64);
	printLenBit(IPtext, 64);
	printf("\n\nEnter an 16 character HEX string, if it is not 16 characters, the key will be padded with 0s: ");
	scanf("%s", key8char);
	printf("\nOkay, we got:\n %s\n\n", key8char);
	key64bit = splitBlocks(key8char, 0, 64);
	printf("\n\nNow we need to do a little bit of work with the key...\n");
	printf("We need to permutate the string of bits into a 56-bit length string... \n");
	printf("\n\nOnce we do that we get: \n");
	key56bit = perm56(key64bit);
	printLenBit(key56bit, 56);
	printf("\n\nNow we must create 16 different 48-bit sub-keys by bit-shifting and permutating. Here they are: \n");
	for(i = 0; i < 16; i++){
		subkey(i);
		printf("\n(%02d) ", i + 1);
		printLenBit(key48bit[i], 48);

	}
	printf("\n\nLet's work on the actual encrytion now...\n\n");
	while(((count + 1)*16) <= strlen(string)){
		IPtext = splitBlocks(string, count, 64);
		printLenBit(IPtext, 64);
		printf("\n\nWe need to permutate the next 64 bits of the string you entered: \n");
		IPtext = permText();
		printLenBit(IPtext, 64);
		printf("\n\nLet's break this up into two parts: \n\n");
		split();
		printf("Left side: ");
		printLenBit(L, 32);
		printf("\n\nRight side: ");
		printLenBit(R, 32);


		printf("\nThe following will be done 16 times...\n\n");
		for(i = 0; i < 16; i++){
			printf("========================================================================");
			printf("%d", i+1);
			printf("========================================================================");
			printf("\n\nLets expand the right side following a specific permutation...\n");
			EXPtext = rightSideExp();
			printLenBit(EXPtext, 48);
			XOR(i);
			printf("\n");
			printf("\n\n...and XOR it with the key %d.: \n", i);
			printLenBit(EXPtext2, 48);
			putInXandTransform();
			X2perm = permLast();
			printf("\n\nAfter transformation back to 32-bits...\n");
			XOR2();
			printLenBit(X2perm, 32);
			switchFinal();
			printf("\n\nAfter switching left side and right side we are left with: \n");
			printLenBit(L, 32);
			printf(" ");
			printLenBit(R, 32);
			if(i != 15){
				printf("\n\nLet's start again!!\n\n\n");
			}
		}
		printf("\n\nLet's reverse the string one more time and permutate it...\n");
		putTogether();
		putInArr();
		count++;
	}


	printf("\n\nAnd here is your encrypted text in HEX!\n");
	printLenBitChar(EncryptedString, ((count + 1) * 16));
	memset(string,'\0',9999);
	memset(key8char,'\0',16);
	count = 0;

}
void putInArr(){
	int i;
	int count2 = 0;
	for(i = count * 16; i < count * 16 + 16; i++){
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = '0';
		}
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = '1';
		}
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 1 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = '2';
		}
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 1 && ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = '3';
		}
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 1 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = '4';
		}
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 1 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = '5';
		}
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 1 && ENCRYPTED[count2 + 2] == 1 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = '6';
		}
		if(ENCRYPTED[count2] == 0 && ENCRYPTED[count2 + 1] == 1 && ENCRYPTED[count2 + 2] == 1 && ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = '7';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = '8';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = '9';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 1 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = 'A';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 0 && ENCRYPTED[count2 + 2] == 1 && ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = 'B';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 1 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = 'C';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 1 && ENCRYPTED[count2 + 2] == 0 && ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = 'D';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 1 && ENCRYPTED[count2 + 2] == 1 && ENCRYPTED[count2 + 3] == 0){
			EncryptedString[i] = 'E';
		}
		if(ENCRYPTED[count2] == 1 && ENCRYPTED[count2 + 1] == 1 &&ENCRYPTED[count2 + 2] == 1 &&ENCRYPTED[count2 + 3] == 1){
			EncryptedString[i] = 'F';
		}
		count2 += 4;
	}


}
void putTogether(void){
	int temp1[64];
	static int temp2[64];
	int i, index;
	for(i = 0; i < 64; i++){
		if(i < 32){
			temp1[i] = R[i];
		}
		else{
			temp1[i] = L[i - 32];
		}
	}
	for(i = 0; i < 64; i++){
		index = FP[i];
		temp2[i] = temp1[index-1];
	}
	for(i = 0; i < 64; i++){
		ENCRYPTED[i] = temp2[i];
	}
	printf("\nAnd here is the encrypted block in binary!\n");
	printLenBit(ENCRYPTED, 64);

}
void switchFinal(void){
	int i;
	static int temp[32];
	for(i = 0; i < 32; i++){
		temp[i] = L[i];
	}
	for(i = 0; i < 32; i++){
		L[i] = R[i];
		R[i] = X2perm[i];
	}
}
void XOR2(void){
	int i;
	for(i = 0; i < 32; i++){
		if((X2perm[i] ^ L[i]) == 0){
			X2perm[i] = 0;
		}
		else{
			X2perm[i] = 1;
		}
	}
}
int * permLast(void){
	static int temp[32];
	int i, index;
	for(i = 0; i < 32; i++){
		index = P[i];
		temp[i] = X2[index-1];
	}
	return temp;
}
void decToBinary(int n, int count2)
{
	if(n == 0){
		X2[count2] = 0;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 0;
	}
	if(n == 1){
		X2[count2] = 0;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 1;
	}
	if(n == 2){
		X2[count2] = 0;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 0;
	}
	if(n == 3){
		X2[count2] = 0;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 1;
	}
	if(n == 4){
		X2[count2] = 0;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 0;
	}
	if(n == 5){
		X2[count2] = 0;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 1;
	}
	if(n == 6){
		X2[count2] = 0;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 0;
	}
	if(n == 7){
		X2[count2] = 0;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 1;
	}
	if(n == 8){
		X2[count2] = 1;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 0;
	}
	if(n == 9){
		X2[count2] = 1;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 1;
	}
	if(n == 10){
		X2[count2] = 1;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 0;
	}
	if(n == 11){
		X2[count2] = 1;
		X2[count2 + 1] = 0;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 1;
	}
	if(n == 12){
		X2[count2] = 1;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 0;
	}
	if(n == 13){
		X2[count2] = 1;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 0;
		X2[count2 + 3] = 1;
	}
	if(n == 14){
		X2[count2] = 1;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 0;
	}
	if(n == 15){
		X2[count2] = 1;
		X2[count2 + 1] = 1;
		X2[count2 + 2] = 1;
		X2[count2 + 3] = 1;
	}

}
int binaryToInt(int i, int j){
	return (i * 2) + (j * 1);
}
int binaryToInt2(int i, int j, int k, int w){
	return (i * 8) + (j * 4) + (k * 2) + (w * 1);
}
void putInXandTransform(void){
	int i,j,count2 = 0, val;
	for(i=0; i< 8; i++){
		for(j=0;j<6;j++){
			X[i][j] = EXPtext2[count2];
			count2++;
		}
	}
	for(i = 0; i < 8; i++){
		if(i == 0){
			val = S1[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
		if(i == 1){
			val = S2[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
		if(i == 2){
			val = S3[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
		if(i == 3){
			val = S4[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
		if(i == 4){
			val = S5[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
		if(i == 5){
			val = S6[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
		if(i == 6){
			val = S7[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
		if(i == 7){
			val = S8[binaryToInt(X[i][0], X[i][5])][binaryToInt2(X[i][1], X[i][2], X[i][3], X[i][4])];
			decToBinary(val, 4*i);
		}
	}



}
void XOR(int index){
	int i;
	for(i = 0; i < 48; i++){
		EXPtext2[i] = EXPtext[i]==key48bit[index][i] ? 0 : 1;
	}

}
int * rightSideExp(void){
	static int temp[48];
	int i, index;
	for(i = 0; i < 48; i++){
		index = E[i];
		temp[i] = R[index-1];
	}
	return temp;
}
void split(void){
	int i;
	for(i = 0; i < 64; i++){
		if(i<32){
			L[i] = IPtext[i];
		}
		else{
			R[i - 32] = IPtext[i];
		}
	}
}
int * permText(void){
	static int temp[64];
	int i, index;
	for(i = 0; i < 64; i++){
		index = InitialPerm[i];
		temp[i] = IPtext[index-1];
	}
	return temp;
}
void subkey(int index){
	int i, j, k, tempInt, w;
	static int temp[48];
	for(j = 0; j < SHIFTS[index]; j++ ){
		tempInt = key56bit[0];
		for(i = 0; i < 27; i++){
			key56bit[i] = key56bit[i + 1];
		}
		key56bit[27] = tempInt;
		tempInt = key56bit[28];
		for(i = 28; i < 55; i++){
			key56bit[i] = key56bit[i + 1];
		}
		key56bit[55] = tempInt;
	}
	for(i = 0; i < 48; i++){
		w = PC2[i];
		key48bit[index][i] = key56bit[w - 1];
	}

}
void printLenBit(int arr[], int n){
	int i, count2;
	count2 = 0;
	for(i = 0; i < n/4; i++){
		if((i%2) == 0 && i != 0){
			printf(" ");
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 0 && arr[count2 + 2] == 0 && arr[count2 + 3] == 0){
			printf("%c", '0');
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 0 && arr[count2 + 2] == 0 && arr[count2 + 3] == 1){
			printf("%c", '1');
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 0 && arr[count2 + 2] == 1 && arr[count2 + 3] == 0){
			printf("%c", '2');
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 0 && arr[count2 + 2] == 1 && arr[count2 + 3] == 1){
			printf("%c", '3');
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 1 && arr[count2 + 2] == 0 && arr[count2 + 3] == 0){
			printf("%c", '4');
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 1 && arr[count2 + 2] == 0 && arr[count2 + 3] == 1){
			printf("%c", '5');
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 1 && arr[count2 + 2] == 1 && arr[count2 + 3] == 0){
			printf("%c", '6');
		}
		if(arr[count2] == 0 && arr[count2 + 1] == 1 && arr[count2 + 2] == 1 && arr[count2 + 3] == 1){
			printf("%c", '7');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 0 && arr[count2 + 2] == 0 && arr[count2 + 3] == 0){
			printf("%c", '8');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 0 && arr[count2 + 2] == 0 && arr[count2 + 3] == 1){
			printf("%c", '9');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 0 && arr[count2 + 2] == 1 && arr[count2 + 3] == 0){
			printf("%c", 'A');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 0 && arr[count2 + 2] == 1 && arr[count2 + 3] == 1){
			printf("%c", 'B');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 1 && arr[count2 + 2] == 0 && arr[count2 + 3] == 0){
			printf("%c", 'C');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 1 && arr[count2 + 2] == 0 && arr[count2 + 3] == 1){
			printf("%c", 'D');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 1 && arr[count2 + 2] == 1 && arr[count2 + 3] == 0){
			printf("%c", 'E');
		}
		if(arr[count2] == 1 && arr[count2 + 1] == 1 &&arr[count2 + 2] == 1 &&arr[count2 + 3] == 1){
			printf("%c", 'F');
		}
		count2 += 4;
	}


}
void printLenBitChar(char arr[], int n){
	int i;
	for(i = 0; i < n; i++){
		if((i%2) == 0 && i != 0){
			printf(" %c", arr[i]);

		}
		else{
			printf("%c", arr[i]);
		}

	}
}
int * perm56(int arr[]){
	static int temp[56];
	int i, index;
	for(i = 0; i < 56; i++){
		index = PC1[i];
		temp[i] = arr[index-1];
	}
	return temp;
}
int * splitBlocks(char arr[], int n, int len){
	int i, count2 = 0;
	static int temp[64];
	for(i = n * 16; i < n * 16 + 16; i++){

		if(arr[i] == '0'){
			temp[count2] = 0;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == '1'){
			temp[count2] = 0;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 1;
		}
		if(arr[i] == '2'){
			temp[count2] = 0;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == '3'){
			temp[count2] = 0;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 1;
		}
		if(arr[i] == '4'){
			temp[count2] = 0;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == '5'){
			temp[count2] = 0;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 1;
		}
		if(arr[i] == '6'){
			temp[count2] = 0;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == '7'){
			temp[count2] = 0;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 1;
		}
		if(arr[i] == '8'){
			temp[count2] = 1;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == '9'){
			temp[count2] = 1;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 1;
		}
		if(arr[i] == 'A' || arr[i] == 'a'){
			temp[count2] = 1;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == 'B' || arr[i] == 'b'){
			temp[count2] = 1;
			temp[count2 + 1] = 0;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 1;
		}
		if(arr[i] == 'C' || arr[i] == 'c'){
			temp[count2] = 1;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == 'D' || arr[i] == 'd'){
			temp[count2] = 1;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 0;
			temp[count2 + 3] = 1;
		}
		if(arr[i] == 'E' || arr[i] == 'e'){
			temp[count2] = 1;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 0;
		}
		if(arr[i] == 'F' || arr[i] == 'f'){
			temp[count2] = 1;
			temp[count2 + 1] = 1;
			temp[count2 + 2] = 1;
			temp[count2 + 3] = 1;
		}
		count2+=4;
	}
	return temp;
}
int main(){
	printf("\n----------------------------------------------------------------------------");
	printf("\nWelcome to the Data Encryption Standard (DES)!");
	printf("\n----------------------------------------------------------------------------\n\n");

	while(option > 0){
		DES();
		printf("\n\nWould you like to encrypt more text? 1 -> Yes || 0 -> No: ");
		scanf("%d", &option);
	}
	return 0;
}

