#define TABLE_SIZE 65536
#include "QuickSort.h"
//t_table manipulation functions
void initTable(t_table *t);
void addWordToTable(t_table *t, char *word);
void addWordToEntry(t_entry *e, char *word);
void printAnagrams(t_table *t, char *word);

//conflict-correction related functions
int countCharInString(char c, char* str);
int isAnagram(char *str1, char *str2);
void getAnagrams(t_table *t, t_entry *result, char *word);

//hashcode generation functions
int hashCode(char *word);
char encodeChar(char c);

//util
int strCmp(const void *str1, const void *str2);
