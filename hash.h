#ifndef _HASH_H_
#define _HASH_H_

typedef enum { FAIL = 0, SUCCESS } Result;
typedef enum { SAME = 0, DIFFERENT } CompResult;

typedef struct _Hash Hash, * pHash;

typedef void* pElement;
typedef void* pKey;

typedef int (*HashFunc) (pKey key, int size);
typedef Result(*PrintFunc) (pElement element);
typedef CompResult(*CompareFunc) (pKey key1, pKey key2);
typedef pKey(*GetKeyFunc) (pElement element);
typedef void (*DestroyFunc)(pElement element);

//*** ADT declerations ***//

typedef struct _Node* pNode;

//* function name: HashCreate
//* Description: This function creates a new HashTable
//* Parameters: HashSize - the hashtable size
//*				FHah - the hash function adress.
//*				FPrint - the print function adress.
//*				FCompare - the comparation function adress.
//*				FGetKey - the getting key function adress.
//*				FDestroy - the memory cleaning function adress.
//* return value: a Pointer to the new Hash table
pHash HashCreate(int size, HashFunc, PrintFunc, CompareFunc, GetKeyFunc, DestroyFunc);

//* function name: HashAdd
//* Description: This function adds new element to the hash table
//* Parameters: PointerToHash - pointer to the hash table
//*				PointerToElement - pointer to the element we want to add.
//* return value: SUCCES if element was added and FAIL if not
Result HashAdd(pHash, pElement);

//* function name: HashFind
//* Description: This function finds an element from a given key
//* Parameters: P_HASH - pointer to the hash table
//*				P_KEY - pointer to the key of the element we want to find.
//* return value: a pointer to the element that was found
pElement HashFind(pHash, pKey);

//* function name: HashRemove
//* Description: This function removes an elemnt from hash table
//* Parameters: PointerToHash - pointer to the hash table
//*				PointerToElement - pointer to the key of the element we want to remove.
//* return value: SUCCES if element was removed and FAIL if not
Result HashRemove(pHash, pKey);

//* function name: HashPrint
//* Description: This function prints the hash table
//* Parameters: PointerToHash - pointer to the hash table
//* return value: SUCCES if hash table was printed and FAIL if not
Result HashPrint(pHash PointerToHash);

//* function name: HashDestroy
//* Description: This function frees HashTable memory
//* Parameters: PointerToHash - pointer to the hash table
//* return value: SUCCES if hash table was freed and FAIL if not
Result HashDestroy(pHash PointerToHash);


//**** linked list functions ****//

//* function name: addNode
//* Description: This function adds a new node to the list
//* Parameters: pointerToNewNode - pointer to the node we want to add
//*				PointerToHead - pointer to a pointer to the head of the list.
//* return value: SUCCES if node was added and FAIL if not
Result addNode(pNode, pNode*);

//* function name: createNode
//* Description: This function creates a new empty node
//* Parameters: None
//* return value: pointer to the new node the was created
pNode createNode();

//* function name: nodeSearch
//* Description: This function searches a node that has given element.
//* Parameters: PointerToHash - pointer to the hash table
//*				head - pointer to the head of the list
//*				key - a pointer to the key of the element
//* return value: pointer to the node that the function found
pNode nodeSearch(pHash PointerToHash, pNode head, pKey key);

//* function name: removeNode
//* Description: This function removes a node from the list
//* Parameters: prevToRemove - pointer to the pre node we want to remove
//* return value: SUCCES if node was removed and FAIL if not
Result removeNode(pNode);
#endif
