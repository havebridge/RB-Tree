#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct node_s
{
	struct node_s* left;
	struct node_s* right;
	struct node_s* parent;
	unsigned char color;
	size_t key;
};

typedef struct node_s* node_t;


struct tree
{
	node_t root;
};


struct tree* create_tree()
{
	struct tree* tree = malloc(sizeof(struct tree));
	tree->root = NULL;
	return tree;
}


void print_inorder(node_t root)
{
	if (root != NULL)
	{
		print_inorder(root->left);
		printf("key: %d color:", root->key);
		if (root->color == 1) printf(" Red\n");
		else printf(" Black\n");
		print_inorder(root->right);
	}
}


void left_rotate(struct tree* tree, node_t x)
{
	node_t y = x->right;
	x->right = y->left;
	if (y->left != NULL)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL)
	{
		tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}


void right_rotate(struct tree* tree, node_t x)
{
	node_t y = x->left;
	x->left = y->right;
	if (y->right != NULL)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL)
	{
		tree->root = y;
	}
	else if (x == x->parent->right)
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}


void fix_insert(struct tree* tree, node_t node)
{
	node_t u;
	while (node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->right)
		{
			u = node->parent->parent->left;

			if (u->color == RED)
			{
				u->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					right_rotate(tree, node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				left_rotate(tree, node->parent->parent);
			}
		}
		else
		{
			u = node->parent->parent->right;

			if (u->color == RED)
			{
				u->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					left_rotate(tree, node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				right_rotate(tree, node->parent->parent);
			}
		}
		if (node == tree->root)
		{
			break;
		}
	}
	tree->root->color = BLACK;
}

void insert(struct tree* tree, unsigned int key)
{
	node_t node = malloc(sizeof(struct node_s));
	node->key = key;
	node->left = node->right = node->parent = NULL;
	node->color = RED;

	node_t y = NULL;
	node_t x = tree->root;
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y == NULL)
	{
		tree->root = node;
		tree->root->color = BLACK;
		return;
	}
	else if (node->key < y->key)
		y->left = node;
	else
		y->right = node;

	fix_insert(tree, node);
}

int main()
{
	struct tree* tree = create_tree();

	insert(tree, 5);
	insert(tree, 1);
	insert(tree, 6);
	insert(tree, 3);
	insert(tree, 8);

	print_inorder(tree->root);
	return 0;
}