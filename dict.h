#ifndef _DICT_H_
#define _DICT_H_

#include "hash.h"

#define DICTSZIE 650
#define WORDSZIE 26

/* Define the dictionary value element */
typedef struct _dictionary_Entry {
	char* Word; // Word is the key
	char* Translate;
} DictEntry, * pDictEntry; // DictValue is the element


//* function name: HashWord
//* Description: This function is the hash function of the dictionary
//* Parameters: key - pointer to the key we want hash
//*				size - the size of the hash array
//* return value: the index of the element in the array
int HashWord(pKey, int);

//* function name: PrintEntry
//* Description: This function prints a dictionary entry
//* Parameters: element - pointer to the entry we want to print
//* return value: SUCCES if entry was printed and FAIL if not
Result PrintEntry(pElement);

//* function name: CompareWords
//* Description: This function compares 2 word (keys)
//* Parameters: key1 - pointer to the key we want to copmpare with key2
//*				key2 - pointer to the key we want to copmpare with key1
//* return value: SAME if the keys are the Same and DIFFERENT if not
CompResult CompareWords(pKey, pKey);

//* function name: GetEntryKey
//* Description: This function gets the key from a given entry
//* Parameters: element - a pointer to the entry we want to get the key from
//* return value: a pointer to the key
pKey GetEntryKey(pElement);

//* function name: DestroyEntry
//* Description: This function destroys an entry in the dictionary
//* Parameters: element - a pointer to the entry we want to destroy
//* return value: None
void DestroyEntry(pElement);

//* function name: CreateDictionary
//* Description: This function creates a new dictionary
//* Parameters: None
//* return value: a pointer to the new dictionary
pHash CreateDictionary();

//* function name: AddTranslation
//* Description: This function adds new entry to the dictionary
//* Parameters: pDict - pointer to the dictionary
//*				word - pointer to the word (key)
//*				translation - pointer to the translation
//* return value: SUCCES if the new entry was added or FAIL if not
Result AddTranslation(pHash pDict, char* word, char* translation);

//* function name: Translate
//* Description: This function prints a word translaion
//* Parameters: PointerToHash - pointer to the dictionary
//*				GivenWord - pointer to the word (key)
//* return value: None
void Translate(pHash PointerToHash, char* GivenWord);

//* function name: DeleteTranslation
//* Description: This function Removes an entry from the dictionary
//* Parameters: PointerToHash - pointer to the dictionary
//*				GivenWord - pointer to the word (key)
//* return value: None
void DeleteTranslation(pHash PointerToHash, char* GivenWord);

//* function name: PrintDictionary
//* Description: This function prints the dictionary
//* Parameters: PointerToHash - pointer to the dictionary
//* return value: None
void PrintDictionary(pHash PointerToHash);
#endif
