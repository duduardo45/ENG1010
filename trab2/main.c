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

int is_key_in_node(Node *node, int key)
{ // booleano
    return key == node->key1 || key == node->key2;
}

Node *find_node_of_key(Node *root, int key)
{
    if (root->ptr1 == NULL)
    {
        return is_key_in_node(root, key) ? root : NULL; // se tá no nó, retorna agora, se não tá, é porque não achou na árvore
    }
    if (key < root->key1)
    {
        return find_node_of_key(root->ptr1, key);
    }
    else if (key < root->key2)
    {
        return find_node_of_key(root->ptr2, key);
    }
    else
    {
        return find_node_of_key(root->ptr3, key);
    }
}

Node *find_parent_node(Node **ptree, Node *child)
{

    int key = child->key1;

    Node *current_node = *ptree;
    Node *parent_node = NULL;

    // procura até as folhas e retorna o pai
    while (current_node != child)
    {
        parent_node = current_node;
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
    return parent_node;
}

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

void insert_key_in_node(Node *node, Node *right_child, int key)
{
    // insere e shifta o que tiver pra direita
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

void fix_inner_nodes(Node **ptree, Node *broken_node);

void insert_key_in_tree(Node **ptree, int key)
{
    // cria a raiz se estiver vazia
    if (*ptree == NULL)
    {
        Node *root = create_node(NULL, key, NULL, -1, NULL, -1);
        *ptree = root;
    }

    // insere normal
    else
    {
        Node *current_node = *ptree;
        Node *parent_node = NULL;

        // procura até as folhas e insere na folha
        while (current_node->ptr1 != NULL)
        {
            parent_node = current_node;
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
        insert_key_in_node(current_node, NULL, key);

        // checa por overflow na folha e faz a cisão
        if (current_node->overflow_key != -1)
        {

            // faz a cisão na folha
            int parent_key = current_node->key2;
            Node *left_child_node = current_node;
            Node *right_child_node = create_node(NULL, parent_key, NULL, left_child_node->overflow_key, NULL, -1);
            left_child_node->key2 = -1;
            left_child_node->overflow_key = -1;

            // testa se a raiz for a unica chave
            if (parent_node == NULL)
            {
                Node *parent_node = create_node(left_child_node, parent_key, right_child_node, -1, NULL, -1);
                *ptree = parent_node;
            }
            else
            { // senão insere na chave pai
                insert_key_in_node(parent_node, right_child_node, parent_key);
                if (parent_node->overflow_key != -1)
                    fix_inner_nodes(ptree, parent_node);
            }
        }
    }
}

void fix_inner_nodes(Node **ptree, Node *broken_node)
{

    int parent_key = broken_node->key2;
    Node *left_child_node = broken_node;
    Node *right_child_node = create_node(NULL, left_child_node->overflow_key, NULL, -1, NULL, -1);
    left_child_node->key2 = -1;
    left_child_node->overflow_key = -1;

    Node *current_node = *ptree;
    Node *parent_node = NULL;
    while (current_node != broken_node)
    {
        parent_node = current_node;
        if (parent_key < current_node->key1)
        {
            current_node = current_node->ptr1;
        }
        else if (parent_key < current_node->key2)
        {
            current_node = current_node->ptr2;
        }
        else
        {
            current_node = current_node->ptr3;
        }
    }
}

void fix_removal(Node *parent_node) // encontra o filho vazio e resolve pra ele
{
    if (parent_node == NULL)
    {
    }
    else
    {
        if (direction == 1)
        {
            parent_node->key1 = parent_node->key2;
            parent_node->ptr1 = parent_node->ptr2;
            parent_node->ptr2 = parent_node->ptr3;
            parent_node->ptr3 = NULL;
        }
    }
}
void remove_key(Node **ptree, int key)
{ // parte do pressuposto de que a chave está na árvore
    Node *node = find_node_of_key(*ptree, key);
    Node *parent_node = find_parent_node(ptree, node);
    if (node->key1 == key)
    {
        node->key1 = node->key2;
    }
    else
        node->key2 = -1;

    Node *current_node = node;
    while (current_node->key1 == -1)
    {
        Node *next_parent_node = find_parent_node(ptree, parent_node);
        fix_removal(parent_node);
        current_node = parent_node;
        parent_node = next_parent_node;
    }
}

int main(void)
{
    Node *tree = NULL;
    insert_key_in_tree(&tree, 40);
    insert_key_in_tree(&tree, 50);
    insert_key_in_tree(&tree, 60);
    Node *value = find_node_of_key(tree, 50);

    return 0;
}