#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

//* function name: ReadDictionary
//* Description: This function reads a dictionary line by line from the standard input
//* Parameters: None
//* return value: a Pointer to the dictionery
pHash ReadDictionary() {
	pHash dictionary;
	char entryLine[100] = "";
	char* word, * translation;

	dictionary = CreateDictionary();
	while (scanf("%s", entryLine) == 1) { // Not EOF
		word = strtok(entryLine, "=");
		translation = strtok(NULL, "=");
		AddTranslation(dictionary, word, translation);
	}

	return dictionary;
}

int main() {
	pHash Dictionary;
	Dictionary = ReadDictionary();
	PrintDictionary(Dictionary);
	DeleteTranslation(Dictionary, "dog");
	DeleteTranslation(Dictionary, "cat");
	DeleteTranslation(Dictionary, "astronaut");
	PrintDictionary(Dictionary);
	AddTranslation(Dictionary, "goat", "ez");
	AddTranslation(Dictionary, "cow", "para");
	AddTranslation(Dictionary, "school", "beitsefer");
	AddTranslation(Dictionary, "boy", "yeled");
	PrintDictionary(Dictionary);
	Translate(Dictionary, "flag");
	Translate(Dictionary, "goat");
	Translate(Dictionary, "school");
	Translate(Dictionary, "apple");
	HashDestroy(Dictionary);
	return 0;
}
