/*
 ============================================================================
 Name        : Anagrams.c
 Author      : Giovanni Ap. S. Oliveira (giovanniapsoliveira@gmail.com)
 Version     :
 Copyright   : 
 Description : Trab. 1 - Organização dos Dados, UFRJ, Rio de Janeiro, 2015.2
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Anagrams.h"
//english letter sorted by frequency (desc): ETAOINSRHDLUCMFYWGPBVKXQJZ (source: http://www.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html)
//26st primes: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101]
//defining the i-th smallest prime to the i-th most used letter to avoid hash conflicts
char dictionary[] = {5,71,41,29,2,47,61,23,11,97,79,31,43,13,7,67,89,19,17,3,37,73,59,83,53,101};

int main(){

	//type to handle with integer keys and string array associated values
	t_table t;
	initTable(&t);
	
	//read input file until EOF
	char tmp[MAX_WORD_LENGTH];
	while(scanf("%s",tmp) == 1){
		addWordToTable(&t,tmp);
	}
	
	//clean stdin buffer to avoid bugs
	freopen("/dev/tty", "r", stdin);
	
	//read each input and prints the associated anagrams
	while(scanf("%s",tmp) == 1){
		printAnagrams(&t,tmp);
	}

	return 0;

}

void initTable(t_table *t){

	t->entries = (t_entry*) calloc(TABLE_SIZE,sizeof(t_entry));
	t->size = TABLE_SIZE;

}

void addWordToTable(t_table *t, char *word){

	int hashcode = hashCode(word);

	t_entry *e = &t->entries[hashcode];
	addWordToEntry(e,word);

}

void addWordToEntry(t_entry *e, char *word){
	
	//sets array pointer to NULL to avoid seg. fault in realloc
	if(e->size == 0){
		e->anagrams = NULL;
	}
	
	//increases anagram array size by one and copy string to last position
	e->anagrams = (t_anagram*) realloc(e->anagrams, (e->size + 1)*sizeof(t_anagram));
	strcpy(e->anagrams[e->size].string, word);

	e->size++;

}

void printAnagrams(t_table *t, char *word){

	t_entry anag;
	getAnagrams(t, &anag, word);

	quickSort(&anag);
	
	//print the sorted array of anagrams
	int i;
	for(i=0; i<anag.size; i++){
		printf("%s ", anag.anagrams[i].string);
	}

	printf("\n");

}

//dummy implementation to check if two words are anagrams
//filters conflicts caused by hashfunction
//*not the better approach, but still works
int isAnagram(char *str1, char *str2){

	if(strlen(str1)!=strlen(str2)){
		return 0;
	}

	int i;
	for(i=0; i<strlen(str1); i++){
		if(countCharInString(str1[i],str1)!=countCharInString(str1[i],str1)){
			return 0;
		}
	}

	return 1;

}

int countCharInString(char c, char* str){

	int count = 0;

	int i;
	for(i=0; i<strlen(str); i++){
		if(str[i] == c){
			count++;
		}
	}

	return count;

}

//returns only anagrams of given word in table
void getAnagrams(t_table *t, t_entry *result, char *word){

	t_entry e = t->entries[hashCode(word)];
	result->size = 0;

	int i;
	for(i=0; i<e.size; i++){
		if(isAnagram(word,e.anagrams[i].string)){
			addWordToEntry(result, e.anagrams[i].string);
		}
	}

}

//assign to each char in [a-z] a small prime and multiply
//it's possible to prove that for all hashcodes < TABLE_SIZE
//there'll be no conflicts and still above this value 
//the probability is small enough
int hashCode(char* word){

	unsigned long long int result = 1;

	int i;
	for(i=0; i<strlen(word); i++){
		result = (result*encodeChar(word[i])) % TABLE_SIZE;
	}

	return result;
}

char encodeChar(char c){

	return dictionary[c-97];

}
