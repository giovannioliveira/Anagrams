/*
 ============================================================================
 Name        : Anagrams.c
 Author      : Giovanni Ap. da Silva Oliveira (giovanniapsoliveira@gmail.com)
 Version     :
 Copyright   : 
 Description : Trab. 1 - Organização dos Dados, UFRJ, Rio de Janeiro, 2015.2
 ============================================================================
 */
#include "Anagrams.h"

int main() {

	t_table t;
	initTable(&t);

	char tmp[MAX_WORD_LENGTH];
	while (scanf("%s", tmp) == 1) {
		addWordToTable(&t, tmp);
	}

	//clean stdin buffer to avoid bugs
	freopen("/dev/tty", "r", stdin);

	while (scanf("%s", tmp) == 1) {
		printAnagrams(&t, tmp);
	}

	return 0;

}

//-------------------------------------------------------------//
//					HASH-RELATED FUNCTIONS					   //
//-------------------------------------------------------------//

void initTable(t_table *t) {

	//init table with TABLE_SIZE t_entries
	t->entries = (t_entry*) calloc(TABLE_SIZE, sizeof(t_entry));
	t->size = TABLE_SIZE;

}

void addWordToTable(t_table *t, char *word) {

	int hashcode = hashCode(word);

	t_entry *e = &t->entries[hashcode];
	addWordToEntry(e, word);

}

void addWordToEntry(t_entry *e, char *word) {

	//avoid segmentation fault in realloc
	if (e->size == 0) {
		e->anagrams = NULL;
	}

	e->anagrams = (t_anagram*) realloc(e->anagrams,
			(e->size + 1) * sizeof(t_anagram));
	strcpy(e->anagrams[e->size].string, word);

	e->size++;

}

void printAnagrams(t_table *t, char *word) {

	t_entry anag;

	//get only positive anagrams
	getAnagrams(t, &anag, word);

	quickSort(&anag);

	int i;
	for (i = 0; i < anag.size; i++) {
		printf("%s ", anag.anagrams[i].string);
	}

	printf("\n");

}

int isAnagram(char *str1, char *str2) {

	//remove cases when string has different size
	if (strlen(str1) != strlen(str2)) {
		return 0;
	}

	//if both strings have the same size, they're anagrams if have same char count too
	int i;
	for (i = 0; i < strlen(str1); i++) {
		if (countCharInString(str1[i], str1)
				!= countCharInString(str1[i], str1)) {
			return 0;
		}
	}

	return 1;

}

int countCharInString(char c, char* str) {

	int count = 0;

	int i;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == c) {
			count++;
		}
	}

	return count;

}

void getAnagrams(t_table *t, t_entry *result, char *word) {

	t_entry e = t->entries[hashCode(word)];
	result->size = 0;

	int i;
	for (i = 0; i < e.size; i++) {
		//search for pathological data in entry
		if (isAnagram(word, e.anagrams[i].string)) {
			addWordToEntry(result, e.anagrams[i].string);
		}
	}

}

int hashCode(char* word) {

	unsigned long long int result = 1;

	//using number theory properties, transforms a word into a prime product to be used as key
	int i;
	for (i = 0; i < strlen(word); i++) {
		//modular operation to support U(n) that can cause "very rarely" conflicts
		//these conflicts will be treated by isAnagram
		result = (result * encodeChar(word[i])) % TABLE_SIZE;
	}

	return result;
}

char encodeChar(char c) {

	return dictionary[c - 97];

}

//-------------------------------------------------------------//
//					SORT-RELATED FUNCTIONS					   //
//-------------------------------------------------------------//

//just interfacing with private quickSort fuction
void quickSort(t_entry *entry) {

	if (entry->size <= 1) {
		return;
	}

	//reinit pseudo-radom generator used in pivot choose
	srand(time(NULL));
	_quickSort(entry->anagrams, 0, entry->size - 1);

}

void _quickSort(t_anagram *anagrams, int l, int r) {

	//recursion base case
	if (r <= l) {
		return;
	}

	//call function that chooses a pivot and places it to position l
	_choosePivot(anagrams, l, r);

	//call function that partition the list around the pivot and returns its index
	int pivot = _partition(anagrams, l, r);

	//sorts the sub list of elements smaller than pivot
	_quickSort(anagrams, l, pivot - 1);
	//sorts the sub list of elements bigger than pivot
	_quickSort(anagrams, pivot + 1, r);

}

void _choosePivot(t_anagram *anagrams, int l, int r) {

	//if the list is smaller than the number of checked pivots
	//then accept the first element as pivot, since it's a small list
	if (r - l <= MEDIAN_OF) {
		return;
	}

	int range = r - l + 1;

	int randIndexes[MEDIAN_OF];
	int i;
	//chooses MEDIAND_OF pseudo-random indexes to search the median of them
	//it could be improved since in this way the same pivot could be selected more than one time
	for (i = 0; i < MEDIAN_OF; i++) {
		randIndexes[i] = l + rand() % range;
	}

	//sort them using brute-force, but since MEDIAN_OF is a constant
	//the time complexity won't be affected. A better way to implement this
	//would be using QuickSelect that in average case is an O(n)
	int j;
	for (i = 0; i < MEDIAN_OF - 1; i++) {
		for (j = i + 1; j < MEDIAN_OF; j++) {
			if (strcmp(anagrams[randIndexes[i]].string,
					anagrams[randIndexes[j]].string) > 0) {
				int tmp = randIndexes[i];
				randIndexes[i] = randIndexes[j];
				randIndexes[j] = tmp;
			}
		}
	}

	//places the pivot in index l
	_swap(anagrams, l, randIndexes[MEDIAN_OF / 2]);

	return;
}

int _partition(t_anagram *anagrams, int l, int r) {

	//here is where the real magic happens
	//sweeping from l+1 to r uses index i to mark range smaller than pivot
	//and index j to mark range of partitioned elements
	int i = l + 1, j;
	for (j = l + 1; j <= r; j++) {
		if (strcmp(anagrams[l].string, anagrams[j].string) > 0) {
			_swap(anagrams, i, j);
			i++;
		}
	}

	//swaps pivot and last element of unsorted "smaller-than-pivot" sub array
	_swap(anagrams, l, i - 1);
	return i - 1;

}

void _swap(t_anagram *anagrams, int i, int j) {

	t_anagram temp = anagrams[i];
	anagrams[i] = anagrams[j];
	anagrams[j] = temp;

}

