#include <iostream>
using namespace std;

typedef unsigned long long ull;

char* bin(ull num) {
  int count = 64;
  char *binRep = new char[65];
  while(count)
    binRep[--count] = (num&1 ? '1': '0'), num = num >> 1;
  binRep[64] = '\0';
  return binRep;
}

class DESKeyGen {
  static const int pc1[56];
  static const int pc2[48];
  static void leftRotate(ull *n, unsigned int d) { 
    *n = ((*n) << d)|((*n) >> (28 - d)); 
  } 
  static bool isNthBitSet(ull *num, int n) {
    ull one = 1;
    return ((*num)&(one << n)) != 0;
  }
  static void setNthBit(ull *num, int n) {
    ull one = 1;
    (*num) = (*num)|(one << n);
  }
  static ull compressAndpermute(ull key, const int *box, int boxSize, int inputBitSize) {
    ull ans = 0;
    for(int i=0;i<boxSize;++i)
      if(isNthBitSet(&key, inputBitSize-box[i]) == true)
        setNthBit(&ans, boxSize-1-i);
    return ans;
  }
  public:
    static ull* getKeysForDES(ull key) {
      // initial parity drop (64bit -> 56bit)
      ull afterParityDrop = compressAndpermute(key, pc1 ,56, 64);

      // preparig masks for extracting halves(left and right)
      ull one = 1;
      ull maskForLeft = ((one << 56) - (one << 28));
      ull maskForRight = (one << 28) - 1;

      // extracting left and right half.  
      ull left = (afterParityDrop & maskForLeft) >> 28;
      ull right = afterParityDrop & maskForRight;

      //Array of keys for DES
      ull *keys = new ull[16];
      
      ull toCompressionBox;

      // getting keys
      for(int i=1;i<=16;++i) {
        if(i == 1 || i == 2 || i == 9 || i == 16) {
          leftRotate(&left, 1);
          leftRotate(&right, 1);
        }else {
          leftRotate(&left, 2);
          leftRotate(&right, 2);
        }
        // following two steps are needed(since we want to operate just
        // on first 28 bits and we want to ignore rest of them)
        left = (left&maskForRight);
        right = (right&maskForRight);

        toCompressionBox = (left << 28) + right;
        keys[i-1] = compressAndpermute(toCompressionBox, pc2, 48, 56);
      }
      
      return keys;
    }
};

const int DESKeyGen::pc1[56] = {
  57, 49, 41, 33, 25, 17, 9, 1,
  58, 50, 42, 34, 26, 18, 10, 2,
  59, 51, 43, 35, 27, 19, 11, 3,
  60, 52, 44, 36, 63, 55, 47, 39,
  31, 23, 15, 7, 62, 54, 46, 38,
  30, 22, 14, 6, 61, 53, 45, 37,
  29, 21, 13, 5, 28, 20, 12, 4
};
const int DESKeyGen::pc2[48] = {
  14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
  23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 
};