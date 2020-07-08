#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	pElement data;
	struct _Node* pNext;
} Node, * pNode;

typedef struct _Hash {
	pNode* ElementsArray; // pointer to pointers array (points the first pointer in the array)
	int HashSize;
	HashFunc FHash;
	PrintFunc FPrint;
	CompareFunc FCompare;
	GetKeyFunc FGetKey;
	DestroyFunc FDestroy;
} Hash;

//* HASH FUNCTIONS *//

//* function name: HashCreate
//* Description: This function creates a new HashTable
//* Parameters: HashSize - the hashtable size
//*				FHah - the hash function adress.
//*				FPrint - the print function adress.
//*				FCompare - the comparation function adress.
//*				FGetKey - the getting key function adress.
//*				FDestroy - the memory cleaning function adress.
//* return value: a Pointer to the new Hash table
pHash HashCreate(int HashSize, HashFunc FHash, PrintFunc FPrint, CompareFunc FCompare, GetKeyFunc FGetKey, DestroyFunc FDestroy) {
	if (HashSize < 0 || !FHash || !FPrint || !FCompare || !FGetKey || !FDestroy) return NULL;
	pHash PointerToHash = (pHash)(malloc(sizeof(Hash)));
	if (!PointerToHash) {
		printf("Error Allocating Memory");
		exit(1);
	}
	pNode* PointerToArray = (pNode*)calloc(HashSize, sizeof(pNode)); // an array of pointers to node
	if (!PointerToArray) {
		printf("Error Allocating Memory");
		exit(1);
	}
	PointerToHash->ElementsArray = PointerToArray;
	PointerToHash->HashSize = HashSize;
	PointerToHash->FHash = FHash;
	PointerToHash->FCompare = FCompare;
	PointerToHash->FDestroy = FDestroy;
	PointerToHash->FGetKey = FGetKey;
	PointerToHash->FPrint = FPrint;
	return PointerToHash; 
}

//* function name: HashAdd
//* Description: This function adds new element to the hash table
//* Parameters: PointerToHash - pointer to the hash table
//*				PointerToElement - pointer to the element we want to add.
//* return value: SUCCES if element was added and FAIL if not
Result HashAdd(pHash PointerToHash, pElement PointerToElement) {
	if (PointerToHash == NULL || PointerToElement == NULL) return FAIL;
	pKey pElemKey;
	pNode newNode;
	int HashIndex = 0;
	pElemKey = PointerToHash->FGetKey(PointerToElement);
	HashIndex = PointerToHash->FHash(pElemKey, PointerToHash->HashSize);
	if (HashFind(PointerToHash, pElemKey)) return FAIL; // make sure the same element is not in the table allready
	newNode = createNode();
	newNode->data = PointerToElement;
	return addNode(newNode, &(PointerToHash->ElementsArray[HashIndex]));
}

//* function name: HashFind
//* Description: This function finds an element from a given key
//* Parameters: P_HASH - pointer to the hash table
//*				P_KEY - pointer to the key of the element we want to find.
//* return value: a pointer to the element that was found
pElement HashFind(pHash P_HASH, pKey P_KEY) {
	if (P_HASH == NULL || P_KEY == NULL) return FAIL; // check parameters
	int location = P_HASH->FHash(P_KEY, P_HASH->HashSize);
	pNode head = P_HASH->ElementsArray[location];
	while (head) { // serching the whole list
		pElement elem2 = head->data;
		pKey KEY2 = P_HASH->FGetKey(elem2);
		if (!P_HASH->FCompare(P_KEY, KEY2)) return elem2;
		head = head->pNext;
	}
	return NULL;
}

//* function name: HashRemove
//* Description: This function removes an elemnt from hash table
//* Parameters: PointerToHash - pointer to the hash table
//*				PointerToElement - pointer to the key of the element we want to remove.
//* return value: SUCCES if element was removed and FAIL if not
Result HashRemove(pHash PointerToHash, pKey key) {
	if (PointerToHash == NULL || key == NULL) return FAIL; //check parameters
	pNode HashToRemove;
	pNode head;
	int headIndex = 0;
	headIndex = PointerToHash->FHash(key, PointerToHash->HashSize);
	head = PointerToHash->ElementsArray[headIndex];
	if (!HashFind(PointerToHash, key)) return FAIL; // in case there is no such element
	if (!head->pNext) { // in case there is only one node
		PointerToHash->FDestroy(head->data); 
		free(PointerToHash->ElementsArray[headIndex]);
		PointerToHash->ElementsArray[headIndex] = NULL;
		return SUCCESS;
	}
	HashToRemove = nodeSearch(PointerToHash, head, key);
	if (HashToRemove == NULL) { // in case its the first node in a filled list
		pNode tmp;
		tmp = head->pNext;
		PointerToHash->FDestroy(head->data);
		free(PointerToHash->ElementsArray[headIndex]);
		PointerToHash->ElementsArray[headIndex] = tmp;
		return SUCCESS;

	}
	PointerToHash->FDestroy(HashToRemove->pNext->data); //free element memory
	return removeNode(HashToRemove);
}

//* function name: HashPrint
//* Description: This function prints the hash table
//* Parameters: PointerToHash - pointer to the hash table
//* return value: SUCCES if hash table was printed and FAIL if not
Result HashPrint(pHash PointerToHash) {
	if (PointerToHash == NULL) return FAIL; // check parameter
	int i = 0;
	pNode current;
	for (i = 0; i < PointerToHash->HashSize; i++) { // running all over the array
		current = PointerToHash->ElementsArray[i];
		while (current) {  // running on all list
			PointerToHash->FPrint(current->data);
			current = current->pNext;
		}
	}
	return SUCCESS;
}

//* function name: HashDestroy
//* Description: This function frees HashTable memory
//* Parameters: PointerToHash - pointer to the hash table
//* return value: SUCCES if hash table was freed and FAIL if not
Result HashDestroy(pHash PointerToHash) {
	if (PointerToHash == NULL) return FAIL;
	int i = 0;
	pNode current;
	for (i = 0; i < PointerToHash->HashSize; i++) {
		current = PointerToHash->ElementsArray[i];
		while (current) {
			if (current->pNext == NULL) { // in case there is only one node left in the list
				PointerToHash->FDestroy(current->data);
				free(PointerToHash->ElementsArray[i]);
				PointerToHash->ElementsArray[i] = NULL;
				break;
			}
			PointerToHash->FDestroy(current->pNext->data); // free element memory
			removeNode(current); // removeNode makes current the head of the list every time it runs.
		}
	}
	free(PointerToHash->ElementsArray); // free HashTable array
	free(PointerToHash); // free HashTable struct memory
	return SUCCESS;
}

//*LINKED LIST FUNCTIONS*//

//* function name: addNode
//* Description: This function adds a new node to the list
//* Parameters: pointerToNewNode - pointer to the node we want to add
//*				PointerToHead - pointer to a pointer to the head of the list.
//* return value: SUCCES if node was added and FAIL if not
Result addNode(pNode pointerToNewNode, pNode* PointerToHead) { //new_node_address is the address of the node being added, p_next is the location new_node is being added
	if (!pointerToNewNode || !PointerToHead) return FAIL;
	pNode tmp = *PointerToHead;
	*PointerToHead = pointerToNewNode;
	pointerToNewNode->pNext = tmp;
	return SUCCESS;
}

//* function name: createNode
//* Description: This function creates a new empty node
//* Parameters: None
//* return value: pointer to the new node the was created
pNode createNode() {
	pNode head; // head is a pointer to an empty node.
	head = (pNode)malloc(sizeof(Node));
	if (head == NULL) {
		printf("Eror Allocating Memory");
		exit(1);
	}
	head->pNext = NULL;
	head->data = NULL;
	return head;
}

//* function name: removeNode
//* Description: This function removes a node from the list
//* Parameters: prevToRemove - pointer to the pre node we want to remove
//* return value: SUCCES if node was removed and FAIL if not
Result removeNode(pNode prevToRemove) {
	if (!prevToRemove) return FAIL;
	pNode tmp = prevToRemove->pNext; //backup for node that we want to remove
	prevToRemove->pNext = tmp->pNext;
	free(tmp);
	return SUCCESS;
}

//* function name: nodeSearch
//* Description: This function searches a node that has given element.
//* Parameters: PointerToHash - pointer to the hash table
//*				head - pointer to the head of the list
//*				key - a pointer to the key of the element
//* return value: pointer to the node that the function found
pNode nodeSearch(pHash PointerToHash, pNode head, pKey key) {
	if (!PointerToHash || !head || !key) return NULL;
	pNode current = head, prevCurrent = NULL;
	pKey keyInNode;
	while (current) {
		keyInNode = PointerToHash->FGetKey(current->data);
		if (!PointerToHash->FCompare(key, keyInNode)) return prevCurrent;
		prevCurrent = current;
		current = current->pNext;
	}
	return NULL;
}







