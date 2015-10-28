/*
 * QuickSort.c
 *
 *  Created on: Oct 27, 2015
 *      Author: giovanni
 */

#include "QuickSort.h"

void quickSort(t_entry *entry){

	if(entry->size <= 1){
		return;
	}

	srand(time(NULL));
	_quickSort(entry->anagrams,0,entry->size-1);

}


void _quickSort(t_anagram *anagrams, int l, int r){

	if(r<=l){
		return;
	}

	choosePivot(anagrams,l,r);

	int pivot = partition(anagrams,l,r);

	_quickSort(anagrams,l,pivot-1);
	_quickSort(anagrams,pivot+1,r);

}

void choosePivot(t_anagram *anagrams, int l, int r){
	//tmp
	return;
}

int partition(t_anagram *anagrams, int l, int r){
	int i = l+1,j;
	for(j = l+1; j<=r; j++){
		if(strcmp(anagrams[l].string,anagrams[j].string) > 0){
			swap(anagrams, i, j);
			i++;
		}
	}
	swap(anagrams, l, i-1);
	return i-1;
}

void swap(t_anagram *anagrams, int i ,int j){
	t_anagram temp = anagrams[i];
	anagrams[i] = anagrams[j];
	anagrams[j] = temp;
}
