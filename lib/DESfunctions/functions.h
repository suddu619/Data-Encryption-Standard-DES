#ifndef DESfunctions

#define DESfunctions

namespace DES {
  
    // type is either initial or final
    // default to initial
    char* getPermutation(char *arr, const char *type);
      
    // str is expected to be of length 48
    // output is of size 32
    char* sBoxFunction(char *str);

    void reverseKeys(unsigned long long *keys);

    void reverseTransposition();
    
    char* expansionPermutation(char *righBlock);
    
    char* FFfinalPermuatation(char *str);
    
    char* feistalFn(int round, char *str, char *key);

    // one DES round(to be executed 16 times)
    char* DESround(int round, char *str, char *key);

    struct DesOut {
        int blockCount;
        char *in, *binForm, *txtForm, **blockOP, **blockIP;
        void printState(void);
    };
    
    char* Des_64_Machine(char *inText, unsigned long long key, bool decipher);

    
    DesOut* DesMachine(char *msg, unsigned long long key, bool enc);

    void modifySbox(int key);

} // DES



#endif

