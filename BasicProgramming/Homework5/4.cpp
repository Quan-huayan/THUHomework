#include <stdio.h>
#include <ctype.h>

#define STRING_LENGTH 100


bool isAnagrams(char* w1, char* w2)
{
    //统计二十六个英文字母
    int nAlpha[26] = {0};
    char* p = w1;
    while(*p) nAlpha[toupper(*(p++))-'A']++;
    p = w2;
    while(*p) nAlpha[toupper(*(p++))-'A']--;
    for(int i=0;i<26;i++) if(nAlpha[i]) return false;
    return true;
}

int main()
{
    char word1[STRING_LENGTH],word2[STRING_LENGTH];
    scanf("%s %s",word1,word2);
    printf("%s",isAnagrams(word1,word2) ? "yes" : "no");
    return 0;
}