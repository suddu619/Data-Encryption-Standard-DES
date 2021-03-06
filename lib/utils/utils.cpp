#include "utils.h"
#include <string.h>
#include <time.h>
#include <iostream>
using namespace std;

char* Utils::numTobin(unsigned long long num, int count_) {
	int count = count_;
	char *binRep = new char[count_+1];
	while(count)
		binRep[--count] = (num&1 ? '1': '0'), num = num >> 1;
	binRep[count_] = '\0';
	return binRep;
}

unsigned long long Utils::binToint(const char *bin) {
    int len = strlen(bin);
    int iter = len-1;
    int ans = 0;
    while(iter > -1) {
        if(bin[iter] == '1')
            ans += (1 << (len-iter-1));
        --iter;
    }
    return ans;
}

char* Utils::substr(char* arr, int begin, int len) {
    char* res = new char[len];
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = '\0';
    return res;
}

char* Utils::xorBlocks(char *arr1, char *arr2, int n) {
    char *ans = new char[n + 1];
    for (int idx = 0; idx < n; idx++)
        ans[idx] = ((arr1[idx] ^ arr2[idx]) != 0 ? '1' : '0');
    ans[n] = '\0';
    return ans;
}

char* Utils::strTobin(const char* message) {
    int msgLen = strlen(message);
    int numBits = msgLen * 8;
    char *bits = new char[numBits+1];
    for(int msgIdx = 0; msgIdx < msgLen; ++msgIdx) {
        for(int bitPos = 0; bitPos < 8; ++bitPos)
            bits[8*msgIdx + 7 - bitPos] = (
                ((message[msgIdx] & (1 << bitPos)) != 0) ? '1' : '0'
            );
    }
    bits[numBits] = '\0';
    return bits;
}


char* Utils::binTostr(char *text) {
    const int textLen = strlen(text);
    const int ansLen = (int)textLen/8;
    char *ans = new char[ansLen+1];
    int ansIter = 0;

    for(int i=0;i<textLen;i+=8) 
        ans[ansIter++] = (char)Utils::binToint(Utils::substr(text, i, 8));

    ans[ansLen] = '\0';
    return ans;
}


int* Utils::binToAscii(char* binArr, int len) {
    int *arr = new int[len/8];
    for(int i=0;i<len;i+=8)
        arr[i/8] = Utils::binToint(Utils::substr(binArr, i, 8));    
    return arr;
}
