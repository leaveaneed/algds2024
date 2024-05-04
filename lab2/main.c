#include <stdio.h>
#include <stdlib.h>

// Структура узла дерева
struct Node {
    int data;
    struct Node *left, *right, *parent;
};

// Функция для создания нового узла
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

// Функция для добавления узла в скошенное дерево
struct Node* insert(struct Node* root, int data) {
    struct Node *curr = root, *prev = NULL;
    
    // Находим место для вставки нового узла
    while (curr != NULL) {
        prev = curr;
        if (data < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    // Создаем новый узел
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->parent = prev;
    
    // Обновляем ссылки предков и потомков
    if (prev == NULL)
        root = newNode;
    else if (data < prev->data)
        prev->left = newNode;
    else
        prev->right = newNode;
    
    return root;
}

// Функция для поиска узла в скошенном дереве
struct Node* search(struct Node* root, int key) {
    struct Node* curr = root;
    while (curr != NULL && curr->data != key) {
        if (key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr;
}

// Функция для удаления узла из скошенного дерева
struct Node* deleteNode(struct Node* root, int key) {
    struct Node *curr = search(root, key);
    if (curr == NULL) return root;
    
    // Удаление узла с одним или без потомков
    if (curr->left == NULL) {
        if (curr->right != NULL)
            curr->right->parent = curr->parent;
        if (curr->parent == NULL)
            root = curr->right;
        else if (curr == curr->parent->left)
            curr->parent->left = curr->right;
        else
            curr->parent->right = curr->right;
        free(curr);
    } else if (curr->right == NULL) {
        if (curr->left != NULL)
            curr->left->parent = curr->parent;
        if (curr->parent == NULL)
            root = curr->left;
        else if (curr == curr->parent->left)
            curr->parent->left = curr->left;
        else
            curr->parent->right = curr->left;
        free(curr);
    } else { // Удаление узла с двумя потомками
        struct Node* successor = curr->right;
        while (successor->left != NULL)
            successor = successor->left;
        curr->data = successor->data;
        curr->right = deleteNode(curr->right, successor->data); // Исправление
    }
    
    return root;
}



// Функция для вывода дерева в порядке инфиксного обхода
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Дерево в порядке инфиксного обхода: ");
    inorderTraversal(root);
    printf("\n");

    root = deleteNode(root, 20);
    printf("Удаление узла 20: ");
    inorderTraversal(root);
    printf("\n");

    root = deleteNode(root, 30);
    printf("Удаление узла 30: ");
    inorderTraversal(root);
    printf("\n");

    root = deleteNode(root, 50);
    printf("Удаление узла 50: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
