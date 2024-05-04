#include <gtest/gtest.h>
#include "main.c" // Замените это на имя вашего заголовочного файла

// Тест для функции newNode
TEST(NewNodeTest, BasicAssertions) {
    struct Node* node = newNode(10);
    ASSERT_EQ(node->data, 10);
    ASSERT_EQ(node->left, nullptr);
    ASSERT_EQ(node->right, nullptr);
    ASSERT_EQ(node->parent, nullptr);
    free(node); // Не забудьте освободить память
}

// Тест для функции insert
TEST(InsertTest, BasicAssertions) {
    struct Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->data, 50);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->left->data, 30);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->left->parent, root);
    free(root); // Не забудьте освободить память
}

// Тест для функции search
TEST(SearchTest, BasicAssertions) {
    struct Node* root = newNode(50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);
    ASSERT_EQ(search(root, 20)->data, 20);
    ASSERT_EQ(search(root, 60)->data, 60);
    ASSERT_EQ(search(root, 100), nullptr);
    free(root); // Не забудьте освободить память
}

// Тест для функции deleteNode
TEST(DeleteNodeTest, BasicAssertions) {
    struct Node* root = newNode(50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);
    root = deleteNode(root, 20);
    ASSERT_EQ(search(root, 20), nullptr);
    root = deleteNode(root, 30);
    ASSERT_EQ(search(root, 30), nullptr);
    root = deleteNode(root, 50);
    ASSERT_EQ(search(root, 50), nullptr);
    free(root); // Не забудьте освободить память
}

// Запуск тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
