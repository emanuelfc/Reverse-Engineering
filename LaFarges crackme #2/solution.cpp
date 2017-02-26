#include <string.h>
#include <stdio.h>
#include <iostream>

/*

    Keygen:

    Patch music - 004010F9 with NOPs
    1) left to right username, xor key1byte, keybyte -- put in key byte
    2) right to left key, xor key2byte, keybyte -- put in key byte
    3) left to right key, xor key3byte, keybyte -- put in key byte
    4) right to left, xor key4byte, key -- put in key byte
    5) Copy key
    6) Invert key
    7) Divide key with 10, add 30 to remainder, store byte, repeat until
    - key is now a string of numbers
    In short terms, store the remainder
    8) Get length of key
    9) Invert numbers of key
    10) Key created

*/

//5 byte keys
char key1[] = "\xAA\x89\xC4\xFE\x46";
char key2[] = "\x78\xF0\xD0\x03\xE7";
char key3[] = "\xF7\xFD\xF4\xE7\xB9";
char key4[] = "\xB5\x1B\xC9\x50\x73";

void xorWithKey(char *username, char *key, int len);
void xorWithKeyInverted(char *username, char *key, int len);
char *keyToInts(char *key);
void flipKey(char *key, int len);

int main(int argc, char *argv[])
{
    std::string username = "ABCD";
    int len = username.size();
    username = username.substr(1, len);

    char *pass = new char[len+1];
    strcpy(pass, username.c_str());

    // Remove first char from username, never usedtr, str.c_str());

    // Apply key1
    xorWithKey(pass, key1, len);
    // Apply key2
    xorWithKeyInverted(pass, key2, len);
    // Apply key3
    xorWithKey(pass, key3, len);
    // Apply key4
    xorWithKeyInverted(pass, key4, len);
    // Copy key
    // Invert key
    // Key convertion to string of Numbers
    char *key = keyToInts(pass);
    // Invert key
    len = strlen(key);
    flipKey(key, len-1);

    printf("Key: %s\n", key);
    scanf("%s", key);

    delete[] pass;

    return 0;
}

void xorWithKey(char *username, char *key, int len)
{
    int i, kc=0;

    for(i=0; i<len; i++)
    {
        username[i] = *(key+kc) ^ username[i];
        *(key+(kc++)) = username[i];
        if(kc==5) kc=0;
    }
}

void xorWithKeyInverted(char *username, char *key, int len)
{
    int i, kc=0;
    for(i=len-1; i>=0; i--)
    {
        username[i] = *(key+kc) ^ username[i];
        *(key+(kc++)) = username[i];
        if(kc==5) kc=0;
    }
}

char *keyToInts(char *key)
{
    unsigned int numerator = *(unsigned int *)(key);
    char *bytes = new char[11];
    memset(bytes, 0, 11);

    int i = 0, remainder;
    while(numerator != 0)
    {
        remainder = (numerator%10) + 0x30;
        numerator = numerator/10;
        bytes[i++] = remainder;
    }

    return bytes;
}

void flipKey(char *key, int len)
{
    int i;
    char tmp;
    for(i=0; i<len-1; i++)
    {
        tmp = key[i];
        key[i] = key[len-i];
        key[len-i] = tmp;
    }
}
