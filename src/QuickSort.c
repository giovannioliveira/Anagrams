/*
 * QuickSort.c
 *
 *  Created on: Oct 27, 2015
 *      Author: giovanni
 */

#include "QuickSort.h"

void quickSort(t_entry *entry) {

	if (entry->size <= 1) {
		return;
	}

	srand(time(NULL));
	_quickSort(entry->anagrams, 0, entry->size - 1);

}

void _quickSort(t_anagram *anagrams, int l, int r) {

	if (r <= l) {
		return;
	}

	_choosePivot(anagrams, l, r);

	int pivot = _partition(anagrams, l, r);

	_quickSort(anagrams, l, pivot - 1);
	_quickSort(anagrams, pivot + 1, r);

}

void _choosePivot(t_anagram *anagrams, int l, int r) {

	if (r - l <= MEDIAN_OF) {
		return;
	}

	int range = r - l + 1;

	int randIndexes[MEDIAN_OF];
	int i;
	for (i = 0; i < MEDIAN_OF; i++) {
		randIndexes[i] = l + rand() % range;
	}

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

	_swap(anagrams,l,randIndexes[MEDIAN_OF/2]);

	return;
}

int _partition(t_anagram *anagrams, int l, int r) {

	int i = l + 1, j;
	for (j = l + 1; j <= r; j++) {
		if (strcmp(anagrams[l].string, anagrams[j].string) > 0) {
			_swap(anagrams, i, j);
			i++;
		}
	}

	_swap(anagrams, l, i - 1);
	return i - 1;

}

void _swap(t_anagram *anagrams, int i, int j) {

	t_anagram temp = anagrams[i];
	anagrams[i] = anagrams[j];
	anagrams[j] = temp;

}
