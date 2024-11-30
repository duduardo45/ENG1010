#include <stdlib.h>
#include <stdio.h>

struct b_plus_node;

typedef struct b_plus_node Node;

struct b_plus_node
{
    Node *ptr1;
    int key1;
    Node *ptr2;
    int key2;
    Node *ptr3;
    int overflow_key;
};

Node *create_node(Node *ptr1, int key1, Node *ptr2, int key2, Node *ptr3, int overflow_key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key1 = key1;
    node->key2 = key2;
    node->overflow_key = overflow_key;
    node->ptr1 = ptr1;
    node->ptr2 = ptr2;
    node->ptr3 = ptr3;
    return node;
}

void insert_key_in_node(Node *node, int key)
{
    if (key < node->key1)
    {
        node->overflow_key = node->key2;
        node->key2 = node->key1;
        node->key1 = key;
    }
    else if (node->key2 == -1 || key < node->key2)
    {
        node->overflow_key = node->key2;
        node->key2 = key;
    }
    else
    {
        node->overflow_key = key;
    }
}

void insert_key_in_tree(Node **ptree, int key)
{
    if (*ptree == NULL)
    {
        Node *root = create_node(NULL, key, NULL, -1, NULL, -1);
        *ptree = root;
    }
    else
    {
        Node *current_node = *ptree;
        while (current_node->ptr1 != NULL)
        {
            if (key < current_node->key1)
            {
                current_node = current_node->ptr1;
            }
            else if (key < current_node->key2)
            {
                current_node = current_node->ptr2;
            }
            else
            {
                current_node = current_node->ptr3;
            }
        }
        insert_key_in_node(current_node, key);
        if (current_node->overflow_key != -1) {
            Node* left_child_node = current_node; 
            Node* right_child_node = create_node(NULL, left_child_node->key2, NULL, left_child_node->overflow_key, NULL, -1);
            // create a new root with the median key (key2)
            Node* parent_node = create_node(left_child_node, left_child_node->key2, right_child_node, -1, NULL, -1);
            left_child_node->key2 = -1;
            left_child_node->overflow_key = -1;
            *ptree = parent_node;
        }
    }
}

int main(void)
{
    Node *tree = NULL;
    insert_key_in_tree(&tree, 40);
    insert_key_in_tree(&tree, 50);
    insert_key_in_tree(&tree, 60);

    return 0;
}