#include<iostream>
using namespace std;


struct BST {

	int key;

	BST *parent = NULL, *left = NULL, *right = NULL;

};

void InorderTreeWalk(BST * root)
{
	cout << "Wypisuje wartosci drzewa BST metoda inorder" << endl;
	if (root != NULL)
	{
		InorderTreeWalk(root->left);
		cout << root->key << ", ";
		InorderTreeWalk(root->right);
	}
	cout << endl;

}

BST *Search(BST *root, int key)
{
	if (root == NULL || root->key == key)
		return root;
	else if (root->key < key)
		return Search(root->right, key);
	else return Search(root->left, key);
}

BST *minimum(BST *root)
{
	while (root->left != NULL)		root = root->left;

	return root;
}

BST *maximum(BST *root)
{
	while (root->right != NULL)		root = root->right;

	return root;
}

BST *successor(BST *node)
{
	if(node->right != NULL)		return minimum(node->right);
	
	BST *p = node->parent;

	while (p != NULL && p->right == node)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

BST *predecessor(BST *node)
{
	if (node->left != NULL)		return maximum(node->left);

	BST *p = node->parent;

	while (p != NULL && p->left == node)
	{
		node = p;
		p = p->parent;
	}

	return p;
}

void TreeInsert(BST **root, BST *element)
{
	BST *y = NULL;

	while (*root != NULL)
	{
		y = *root;
		if (element->key < (*root)->key)
			*root = (*root)->left;
		else *root = (*root)->right;
	}

	element->parent = y;
	if (y == NULL)	*root = element;
	else if (y->key < element->key)		y->right = element;
	else	y->left = element;

}

/*void Transplant(BST *node, BST *y)
{
	y->parent->left = y->right;
	if (y->right != NULL) 
		y->right->parent = y->parent;


	y->parent = node->parent;
	y->left = node->left;
	y->right = node->right;
}

void NodeDelete(BST *node, BST **head)
{
	
		if (node->parent != NULL)
		{
			if (node->left == NULL && node->right == NULL)
			{
				if (node == *head) *head = NULL;
				else if (node->parent->left == node)  node->parent->left = NULL;
				else node->parent->right = NULL;
			}

			else if (node->left == NULL && node->right != NULL)
			{
				if (node->parent->left == node)
					node->parent->left = node->right;

				else
					node->parent->right = node->right;

				node->right->parent = node->parent;
			}

			else if (node->left != NULL && node->right == NULL)
			{
				if (node->parent->left == node)
					node->parent->left = node->left;

				else
					node->parent->right == node->left;

				node->left->parent = node->parent;

			}

			else
			{
				BST *y = minimum(node->right);
				if (y == node->right)
				{
					y->parent = node->parent;
					y->left = node->left;

				}
				else
					Transplant(node, y);
			}

		}
	
	

} */



void transplant(BST **root, BST *node, BST* y)
{
	if (node->parent == NULL)
		*root = y;
	else if (node == node->parent->left)
		node->parent->left = y;
	else node->parent->right = y;

	if (y != NULL)
		y->parent = node->parent;
}

void Delete(BST **root, BST *node)
{
	if (node->left == NULL)
		transplant(root, node, node->right);
	else if (node->right == NULL)
		transplant(root, node, node->left);
	else
	{
		BST *y = minimum(node->right);
		if (y->parent != node)
		{
			transplant(root, y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}
		transplant(root, node, y);
		y->left = node->left;
		y->left->parent = y;
	}
}