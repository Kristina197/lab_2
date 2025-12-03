#include "tree.hpp"
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <vector>

namespace BinaryTree {
    using namespace std;

    FullBinaryTree* createFBT() {
        FullBinaryTree* tree = new FullBinaryTree;
        tree->root = nullptr;
        tree->size = 0;
        return tree;
    }

    void deleteTree(TreeNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void deleteFBT(FullBinaryTree* tree) {
        if (tree != nullptr) {
            deleteTree(tree->root);
            delete tree;
        }
    }

    void clearFBT(FullBinaryTree* tree) {
        if (tree != nullptr) {
            deleteTree(tree->root);
            tree->root = nullptr;
            tree->size = 0;
        }
    }

    bool isEmptyFBT(const FullBinaryTree* tree) {
        return tree == nullptr || tree->root == nullptr;
    }

    TreeNode* insertHelper(TreeNode* node, int value, int& size) {
        if (node == nullptr) {
            size++;
            return new TreeNode(value);
        }
        
        if (value < node->data) {
            node->left = insertHelper(node->left, value, size);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value, size);
        }
        
        return node;
    }

    void insertFBT(FullBinaryTree* tree, int value) {
        if (tree != nullptr) {
            tree->root = insertHelper(tree->root, value, tree->size);
        }
    }

    bool searchHelper(TreeNode* node, int value) {
        if (node == nullptr) {
            return false;
        }
        
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }

    bool searchFBT(FullBinaryTree* tree, int value) {
        if (tree == nullptr || tree->root == nullptr) {
            return false;
        }
        return searchHelper(tree->root, value);
    }

    TreeNode* findMin(TreeNode* node) {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteHelper(TreeNode* node, int value, int& size, bool& found) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (value < node->data) {
            node->left = deleteHelper(node->left, value, size, found);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value, size, found);
        } else {
            found = true;
            size--;
            
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            
            TreeNode* temp = findMin(node->right);
            if (temp != nullptr) {
                node->data = temp->data;
            }
            node->right = deleteHelper(node->right, temp ? temp->data : value, size, found);
            found = false;
        }
        
        return node;
    }

    void deleteNodeFBT(FullBinaryTree* tree, int value) {
        if (tree == nullptr || tree->root == nullptr) {
            return;
        }
        
        bool found = false;
        tree->root = deleteHelper(tree->root, value, tree->size, found);
    }

    int getHeightFBT(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int leftHeight = getHeightFBT(node->left);
        int rightHeight = getHeightFBT(node->right);
        
        return 1 + max(leftHeight, rightHeight);
    }

    bool isBalancedHelper(TreeNode* node) {
        if (node == nullptr) {
            return true;
        }
        
        int leftHeight = getHeightFBT(node->left);
        int rightHeight = getHeightFBT(node->right);
        
        if (abs(leftHeight - rightHeight) > 1) {
            return false;
        }
        
        return isBalancedHelper(node->left) && isBalancedHelper(node->right);
    }

    bool isBalancedFBT(TreeNode* node) {
        return isBalancedHelper(node);
    }

    void extractValuesToArray(TreeNode* node, int* arr, int& index) {
        if (node != nullptr) {
            extractValuesToArray(node->left, arr, index);
            arr[index++] = node->data;
            extractValuesToArray(node->right, arr, index);
        }
    }

    bool isFullHelper(TreeNode* node) {
        if (node == nullptr) {
            return true;
        }
        
        if (node->left == nullptr && node->right == nullptr) {
            return true;
        }
        
        if (node->left != nullptr && node->right != nullptr) {
            return isFullHelper(node->left) && isFullHelper(node->right);
        }
        
        return false;
    }

    bool isFull(FullBinaryTree* tree) {
        if (tree == nullptr || tree->root == nullptr) {
            return true;
        }
        return isFullHelper(tree->root);
    }

    void preOrderTraversal(TreeNode* node) {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void inOrderTraversal(TreeNode* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(TreeNode* node) {
        if (node != nullptr) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            std::cout << node->data << " ";
        }
    }

    void levelOrderTraversal(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        
        queue<TreeNode*> q;
        q.push(node);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            std::cout << current->data << " ";
            
            if (current->left != nullptr) {
                q.push(current->left);
            }
            
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    // Вспомогательная функция для сбора развилок
    void collectForksHelper(TreeNode* node, std::vector<int>& result) {
        if (node != nullptr) {
            collectForksHelper(node->left, result);
            
            if (node->left != nullptr && node->right != nullptr) {
                result.push_back(node->data);
            }
            
            collectForksHelper(node->right, result);
        }
    }

    std::vector<int> getNodesWithTwoChildren(FullBinaryTree* tree) {
        std::vector<int> result;
        if (tree != nullptr && tree->root != nullptr) {
            collectForksHelper(tree->root, result);
        }
        return result;
    }

    void printTreeFBT(FullBinaryTree* tree) {
        if (tree == nullptr || tree->root == nullptr) {
            std::cout << "Дерево пусто" << std::endl;
            return;
        }
        
        std::cout << "Inorder обход: ";
        inOrderTraversal(tree->root);
        std::cout << std::endl;
        
        std::cout << "Preorder обход: ";
        preOrderTraversal(tree->root);
        std::cout << std::endl;
        
        std::cout << "Postorder обход: ";
        postOrderTraversal(tree->root);
        std::cout << std::endl;
        
        std::cout << "Обход в ширину: ";
        levelOrderTraversal(tree->root);
        std::cout << std::endl;
        
        std::cout << "Размер дерева: " << tree->size << std::endl;
        std::cout << "Высота дерева: " << getHeightFBT(tree->root) << std::endl;
        std::cout << "Сбалансировано: " << (isBalancedFBT(tree->root) ? "YES" : "NO") << std::endl;
    }
}