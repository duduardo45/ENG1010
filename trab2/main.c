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

void display_tree(Node *node, int level) {
    if (node == NULL) {
        return;
    }

    // Exibir as chaves e os ponteiros do nó atual
    printf("Nível %d: ", level);
    printf("Endereço do nó: %p, ", (void*)node);
    printf("key1 = %d, key2 = %d, ", node->key1, node->key2);
    printf("ptr1 = %p, ptr2 = %p, ptr3 = %p\n", 
           (void*)node->ptr1, (void*)node->ptr2, (void*)node->ptr3);

    // Recursivamente exibir os filhos (se existirem)
    if (node->ptr1) {
        display_tree(node->ptr1, level + 1);
    }
    if (node->ptr2) {
        display_tree(node->ptr2, level + 1);
    }
    if (node->ptr3) {
        display_tree(node->ptr3, level + 1);
    }
}

Node *find_parent_node(Node *root, Node *child)
{

    int key = child->key1;

    Node *current_node = root;
    Node *parent_node = NULL;

    // procura até achar o nó e retorna o pai dele
    while (current_node != child)
    {
        parent_node = current_node;
        if (key < current_node->key1)
        {
            current_node = current_node->ptr1;
        }
        else if (key < current_node->key2 || current_node->key2 == -1)
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

Node* insert_key_in_node(Node *node, Node* right_child, int key)
{
    // a função retorna o ponteiro de sobra, se for NULL nn precisa fazer nada
    // insere e shifta o que tiver pra direita
    Node* leftover = NULL;
    if (key < node->key1)
    {
        leftover = node->ptr3;
        node->overflow_key = node->key2;
        node->ptr3 = node->ptr2;
        node->key2 = node->key1;
        node->ptr2 = right_child;
        node->key1 = key;
    }
    else if (node->key2 == -1 || key < node->key2)
    {
        leftover = node->ptr3;
        node->overflow_key = node->key2;
        node->ptr3 = right_child;
        node->key2 = key;
    }
    else
    {
        leftover = right_child;
        node->overflow_key = key;
    }
    return leftover;
}

void fix_inner_nodes(Node **ptree, Node *broken_node, Node* leftover);

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
            else if (key < current_node->key2 || current_node->key2 == -1)
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
            int parent_key = current_node->key2, overflow_key = current_node->overflow_key;
            Node* left_child_node = current_node; 
            Node* right_child_node = create_node(NULL, parent_key, NULL, overflow_key, NULL, -1);
            left_child_node->key2 = -1; 
            left_child_node->overflow_key = -1;

            // testa se a raiz for a unica chave
            if (parent_node == NULL)
            {
                Node *parent_node = create_node(left_child_node, parent_key, right_child_node, -1, NULL, -1);
                *ptree = parent_node;
            }
            else { // senão insere na chave pai
                Node* leftover = insert_key_in_node(parent_node, right_child_node, parent_key);
                if (leftover) fix_inner_nodes(ptree, parent_node, leftover);
                
            }
        }
    }
}

void fix_inner_nodes(Node **ptree, Node *broken_node, Node* leftover) {

    // faz a cisão do nó interno
    int parent_key = broken_node->key2; // a chave a ser subida
    Node* left_child_node = broken_node; 
    Node* right_child_node = create_node(left_child_node->ptr3, left_child_node->overflow_key, leftover, -1, NULL, -1);
    left_child_node->ptr3 = NULL;
    left_child_node->key2 = -1; 
    left_child_node->overflow_key = -1;
    Node* parent_node = find_parent_node(*ptree, broken_node);
    if (parent_node == NULL) {
        // fez cisão na raiz
        Node *parent_node = create_node(left_child_node, parent_key, right_child_node, -1, NULL, -1);
        *ptree = parent_node;
    }
    else {
        Node* leftover = insert_key_in_node(parent_node, right_child_node, parent_key);
        // checa se precisa fazer mais cisão
        if (leftover) fix_inner_nodes(ptree, parent_node, leftover);
    }
}

int find_direction(Node* parent, Node* child) {
    if (parent->ptr1 == child) return 1;
    else if (parent->ptr2 == child) return 2;
    else if (parent->ptr3 == child) return 3;
    return -1;
}

void fix_removal(Node *parent_node) // encontra o filho vazio e resolve pra ele
{
    int direction;
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
    Node *parent_node = find_parent_node(*ptree, node);
    if (node->key1 == key)
    {
        node->key1 = node->key2;
    }
    node->key2 = -1;

    Node *current_node = node;
    while (current_node->key1 == -1)
    {
        Node *next_parent_node = find_parent_node(*ptree, parent_node);
        int direction = find_direction(parent_node, current_node);
        Node *sibling = NULL;
        if (direction == 1) { // Leftmost child
            sibling = parent_node->ptr2;
        } else if (direction == 2) { // Middle child
            sibling = parent_node->ptr1->key2 != -1 ? parent_node->ptr1 : parent_node->ptr3;
        } else if (direction == 3) { // Rightmost child
            sibling = parent_node->ptr2;
        }
        // tenta redistribuicao pra algum lado primeiro
        if (direction == 1) {
            if (parent_node->ptr2->key2 != -1) {
                // redistribui
            } else {
                // concatena
            }
        } else if (direction == 3) {
            if (parent_node->ptr2->key2 != -1) {
                // redistribui
            } else {
                // concatena
            }
        } else if (direction == 2) {
            if (parent_node->ptr3->key2 != -1) {
                // redistribui da direita
            } else if (parent_node->ptr1->key2 != -1) {
                // redistribui da esquerda
            } else {
                // concatena da direita
            }
        }
        current_node = parent_node;
    }
}

int main(void)
{
    Node *tree = NULL;
    insert_key_in_tree(&tree, 10);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 60);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 20);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 25);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 30);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 90);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 40);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 50);
    display_tree(tree, 0);
    printf("\n");
    insert_key_in_tree(&tree, 80);
    display_tree(tree, 0);
    printf("\n");
    
    Node* value = find_node_of_key(tree, 50);

    return 0;
}