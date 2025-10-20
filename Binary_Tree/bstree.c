#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "bstree.h"

BSTree NewBSTree()
{
	// New empty tree
	BSTree newTree = (BSTree)malloc(sizeof(Node));
	newTree->word = NULL;
	newTree->left = NULL;
	newTree->right = NULL;

	return newTree;
}

void AddNode(BSTree *bst, char *word)
{
	// Recursively searching for a word inside the tree, if found it's not added 
	
	if (*bst == NULL || (*bst)->word == NULL) { 
		(*bst) = NewBSTree();
		(*bst)->word = strdup(word);
	}

	else if (strcmp((*bst)->word, word) > 0) {
		AddNode(&(*bst)->left, word);
	
	}
	else if (strcmp((*bst)->word, word) < 0) {
		AddNode(&(*bst)->right, word);
	
	}

	return;
}

int BSTHeight(BSTree bst)
{
	// Recursively going throught whole tree to find longest branch aka tree height
	if (bst == NULL)
		return 0;

	int m = BSTHeight(bst->left) + 1;
	int n = BSTHeight(bst->right) + 1;

	return (m < n) ? n : m;
}

void PrintBSTree(BSTree bst)
{
	// Writes the words in the tree on the screen in alphabetical order. 
	// In-order tree walk (left child, knot, right child)
	
	if (bst != NULL) {
		PrintBSTree(bst->left);
		printf("%s\n", bst->word);
		PrintBSTree(bst->right);
	}

}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Records word by word from the tree to a text file.
	// The words are separated by a space. 
	// Pre-order tree walk (current knot then children)
	if (bst == NULL)
		return;

	SaveBSTree(bst->left, fd);
	fprintf(fd, "%s\n", bst->word);
	SaveBSTree(bst->right, fd);
}

void DeleteBSTree(BSTree bst)
{
	// Deletes the tree (string word and the node itself) from memory. 
	// Post-order tree walk (first the children, then the current knot)
	if (bst == NULL)
		return;
	
	if (bst->left == NULL && bst->right == NULL) {
		free(bst->word);
		free(bst);
		return NULL;
	}
	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	return;
	

}

BSTree LoadBSTree(FILE *fd)
{
	// Reads word by word from a text file and adds them to the tree via 
	// the AddNode() function. Duplicate the word with strdup().
	char buffer[1024];
	BSTree bst;

	bst = NewBSTree();

	while (1) {
		if (fscanf(fd, "%s", buffer) == EOF) {
			return bst;
		}

		buffer[strlen(buffer)] = '\0';
		AddNode(&bst, strdup(buffer));
	}
}
