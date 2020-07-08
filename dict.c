#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

//* function name: HashWord
//* Description: This function is the hash function of the dictionary
//* Parameters: key - pointer to the key we want hash
//*				size - the size of the hash array
//* return value: the index of the element in the array
int HashWord(pKey key, int size) {
	int HashIndex = 0;
	char* DictKey = (char*)key;
	HashIndex = ((int)(DictKey[0] - 'a') * 26 + strlen(DictKey)) % size;
	return HashIndex;
}


//* function name: PrintEntry
//* Description: This function prints a dictionary entry
//* Parameters: element - pointer to the entry we want to print
//* return value: SUCCES if entry was printed and FAIL if not
Result PrintEntry(pElement element) {
	if (element == NULL) return FAIL;
	pDictEntry PdEntry = (pDictEntry)element;
	printf("%s : %s\n", PdEntry->Word, PdEntry->Translate);
	return SUCCESS;
}

//* function name: CompareWords
//* Description: This function compares 2 word (keys)
//* Parameters: key1 - pointer to the key we want to copmpare with key2
//*				key2 - pointer to the key we want to copmpare with key1
//* return value: SAME if the keys are the Same and DIFFERENT if not
CompResult CompareWords(pKey key1, pKey key2) {
	if (!key1 || !key2) return DIFFERENT;
	return strcmp((char*)key1, (char*)key2);
}

//* function name: GetEntryKey
//* Description: This function gets the key from a given entry
//* Parameters: element - a pointer to the entry we want to get the key from
//* return value: a pointer to the key
pKey GetEntryKey(pElement element) {
	if (!element) return NULL;
	pDictEntry PdEntry = (pDictEntry)element;
	return PdEntry->Word;
}

//* function name: DestroyEntry
//* Description: This function destroys an entry in the dictionary
//* Parameters: element - a pointer to the entry we want to destroy
//* return value: None
void DestroyEntry(pElement element) {
	if (!element) return;
	pDictEntry PdEntry = (pDictEntry)element;
	free(PdEntry->Word);
	free(PdEntry->Translate);
	free(PdEntry);
}

//* function name: CreateDictionary
//* Description: This function creates a new dictionary
//* Parameters: None
//* return value: a pointer to the new dictionary
pHash CreateDictionary() {
	return HashCreate(DICTSZIE, HashWord, PrintEntry, CompareWords, GetEntryKey, DestroyEntry);
}

//* function name: AddTranslation
//* Description: This function adds new entry to the dictionary
//* Parameters: pDict - pointer to the dictionary
//*				word - pointer to the word (key)
//*				translation - pointer to the translation
//* return value: SUCCES if the new entry was added or FAIL if not
Result AddTranslation(pHash pDict, char* word, char* translation) {
	if (!pDict ||!word || !translation) return FAIL;
	pDictEntry pEntry = (pDictEntry)(malloc(sizeof(DictEntry)));
	char* ENTRY_WORD = (char*)malloc(sizeof(char) * WORDSZIE);
	char* ENTRY_TRANSLATION = (char*)malloc(sizeof(char) * WORDSZIE);
	if ((pEntry == NULL) || (ENTRY_WORD == NULL) || (ENTRY_TRANSLATION == NULL)) {
		printf("Error Allocating Memory");
		exit(1);
	}
	strcpy(ENTRY_WORD, word);
	strcpy(ENTRY_TRANSLATION, translation);
	pEntry->Word = ENTRY_WORD;
	pEntry->Translate = ENTRY_TRANSLATION;
	if (HashAdd(pDict, pEntry)) return SUCCESS;
	else
	{
		free(pEntry);
		free(ENTRY_WORD);
		free(ENTRY_TRANSLATION);
		return FAIL;
	}
	
}

//* function name: Translate
//* Description: This function prints a word translaion
//* Parameters: PointerToHash - pointer to the dictionary
//*				GivenWord - pointer to the word (key)
//* return value: None
void Translate(pHash PointerToHash, char* GivenWord) {
	if (!PointerToHash || !GivenWord) return;
	pElement PointerToElement;
	PointerToElement = HashFind(PointerToHash, GivenWord);
	if (!PointerToElement) return; // if the element is not in the dictionary return.
	printf("Translation: ");
	PrintEntry(PointerToElement);
}

//* function name: DeleteTranslation
//* Description: This function Removes an entry from the dictionary
//* Parameters: PointerToHash - pointer to the dictionary
//*				GivenWord - pointer to the word (key)
//* return value: None
void DeleteTranslation(pHash PointerToHash, char* GivenWord) {
	if (!PointerToHash || !GivenWord) return;
	HashRemove(PointerToHash, GivenWord);
}

//* function name: PrintDictionary
//* Description: This function prints the dictionary
//* Parameters: PointerToHash - pointer to the dictionary
//* return value: None
void PrintDictionary(pHash PointerToHash) { 
	if (!PointerToHash) return;
	printf("Dictionary Contents\n");
	HashPrint(PointerToHash);
}