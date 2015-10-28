#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//-------------------------------------------------------------//
//						   CONSTANTS						   //
//-------------------------------------------------------------//
#define MAX_WORD_LENGTH 100
#define TABLE_SIZE 65536

//parameter to determine how many elements will be used to get the median in choosePivot function
#define MEDIAN_OF 3

//dictionary used in hash function to encode each char in a given word
//the first 26 primes are [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101]
//the most frequent letters in English are [E, T, A, O, I, N, S, R, H, D, L, U, C, M, F, Y, W, G, P, B, V, K, X, Q, J, Z] (src.: http://www.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html)
//so the dictionary relates the n-th most frequent letter with the n-th smaller prime to avoid conflicts in hash table caused by modular operation
char dictionary[] = { 5, 71, 41, 29, 2, 47, 61, 23, 11, 97, 79, 31, 43, 13, 7,
		67, 89, 19, 17, 3, 37, 73, 59, 83, 53, 101 };

//-------------------------------------------------------------//
//						TYPES FUNCTIONS 					   //
//-------------------------------------------------------------//

//struct to encapsulate anagram
struct {
	char string[MAX_WORD_LENGTH];
}typedef t_anagram;

//struct to encapsulate each entry in hash table
struct {
	t_anagram *anagrams;
	int size;
}typedef t_entry;

//struct of our hash table
struct {
	t_entry *entries;
	int size;
}typedef t_table;

//-------------------------------------------------------------//
//					HASH-RELATED FUNCTIONS					   //
//-------------------------------------------------------------//

/** initializes a hash table
 * @param *t: pointer to new table instance
 */
void initTable(t_table *t);

/** interface to add word to hash table
 * @param *t: pointer to hash table
 * @param *word: word to be inserted
 */
void addWordToTable(t_table *t, char *word);

/** interface to add word to entry that deals allocation
 * @param *t: pointer to hash table
 * @param *word: word to be inserted
 */
void addWordToEntry(t_entry *e, char *word);

/** interface to print an array of anagrams of given word
 * @param *e: pointer to entry
 * @param *word: word to be searched
 */
void printAnagrams(t_table *t, char *word);

/**
 * @param c: char to be counted
 * @param *str
 * @return occurrences of c in *str
 */
int countCharInString(char c, char* str);

/** based on length and char count, checks if *str1 and *str2 are anagram
 * @param *str1
 * @param *str2
 * @return 1 if *str1 and *str2 are anagrams else 0
 */
int isAnagram(char *str1, char *str2);

/** safe-way to get anagrams of @param *word in @param *t, since it checks if inside the key
 * there's is false positives. the true anagrams are allocated in *result
 * @param *t
 * @param *result
 * @param *word
 */
void getAnagrams(t_table *t, t_entry *result, char *word);

/** generates hash code as product of each prime associated char in @param *word
 * @param *word
 * @return hash code of *word to be used as key
 */
int hashCode(char *word);

/** interface to deal with dictionary
 * @param *word
 * @return prime associated with c
 */
char encodeChar(char c);

//-------------------------------------------------------------//
//					SORT-RELATED FUNCTIONS					   //
//-------------------------------------------------------------//

/** interface to quickSort function
 * @param *entry: t_entry instance to be sorted
 */
void quickSort(t_entry *entry);

/** private quickSort used recursively
 * @param *anagrams: array of anagrams to be sorted
 * @param l: left bound
 * @param r: right bound
 */
void _quickSort(t_anagram *anagrams, int l, int r);

/** chooses an median element to be used as pivot and places it in l index
 * @param *anagrams: array of anagrams to be sorted
 * @param l: left bound
 * @param r: right bound
 */
void _choosePivot(t_anagram *anagrams, int l, int r);

/** partition *anagrams around pivot
 * @param *anagrams: array of anagrams to be sorted
 * @param l: left bound
 * @param r: right bound
 * @return pivot position after partitioning
 */
int _partition(t_anagram *anagrams, int l, int r);

/** swaps the i-th with j-th indexed elements in *anagram
 * @param *anagrams: array of anagrams
 * @param i
 * @param j
 */
void _swap(t_anagram *anagrams, int i, int j);
