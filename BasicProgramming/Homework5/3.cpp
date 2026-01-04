#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_LIST_LENGTH 80

#define STRING_LENGTH 100


int main()
{
    char* word_list[WORD_LIST_LENGTH] = {nullptr};//词表
    char buf[STRING_LENGTH];//输入缓冲
    int nWordList = 0;//词表大小
    while(EOF!=scanf("%s",buf))
    {
        bool tagInList = false;
        for(int i=0;i<nWordList;i++) if(!strcmp(word_list[i],buf)) {tagInList=true;break;}
        if(tagInList) continue;
        word_list[nWordList] = (char*)calloc(strlen(buf)+1, sizeof(char));
        strcpy(word_list[nWordList],buf);
        nWordList++;
        for(int i=0;i<STRING_LENGTH;i++) buf[i] = 0;
    }
    printf("%d",nWordList);
    for(int i=0;i<nWordList;i++) free(word_list[i]);
    return 0;
}