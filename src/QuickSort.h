#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define MEDIAN_OF 3
#define MAX_WORD_LENGTH 100
struct{
	char string[MAX_WORD_LENGTH];
} typedef t_anagram;

struct{
	t_anagram *anagrams;
	int size;
} typedef t_entry;

struct{
	t_entry *entries;
	int size;
} typedef t_table;

void quickSort(t_entry *entry);
void _quickSort(t_anagram *anagrams, int l, int r);
void _choosePivot(t_anagram *anagrams, int l, int r);
int _partition(t_anagram *anagrams, int l, int r);
void _swap(t_anagram *anagrams, int i ,int j);

