#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <sstream>
#include <iostream>

template <typename Type>
struct Node {
  Type item{};
  Node<Type>* left{ nullptr };
  Node<Type>* right{ nullptr };
};

template <typename Type>
class BinaryTree {
public:
  BinaryTree() {}
  BinaryTree(const BinaryTree<Type>& objToCopy);
  BinaryTree<Type>& operator=(const BinaryTree& b);
  ~BinaryTree();
  void insert(Type item);
  void preOrder(std::ostringstream& out);
  void inOrder(std::ostringstream& out);
  void postOrder(std::ostringstream& out);
  int nodeCount();
  Node<Type>* find(Type item);
  Node<Type>* findRightMostNode(Node<Type>* find);
  void remove(Type item);
  int  height();
  int leavesCount();

protected:
  Node<Type>* root{ nullptr };

private:
  void destroy(Node<Type>* curr);
  void insert(Type item, Node<Type>* curr);
  void preOrder(std::ostringstream& out, Node<Type>* curr);
  void postOrder(std::ostringstream& out, Node<Type>* curr);
  void inOrder(std::ostringstream& out, Node<Type>* curr);
  int nodeCount(Node<Type>* curr);
  int leavesCount(Node<Type>* curr);
  Node<Type>* find(Type item, Node<Type>* curr);
  Node<Type>* remove(Type item, Node<Type>* curr);
  int height(int level, Node<Type>* curr);
  Node<Type>* copyTree(Node<Type>* curr);
};

template <typename Type>
BinaryTree<Type>::~BinaryTree() {
  destroy(root);
  root = nullptr;
}

template <typename Type>
Node<Type>* BinaryTree<Type>::copyTree(Node<Type>* curr) {
  if (curr == nullptr) {
    return nullptr;
  }
  Node<Type>* newNode = new Node<Type>;
  newNode->item = curr->item;
  newNode->left = copyTree(curr->left);
  newNode->right = copyTree(curr->right);
  return newNode;
}

template <typename Type>
BinaryTree<Type>::BinaryTree(const BinaryTree<Type>& b) {
  root = copyTree(b.root);
}

template <typename Type>
BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree<Type>& b) {
  if (this != &b) {
    destroy(root);
    root = copyTree(b.root);
  }
  return *this;
}

template <typename Type>
void BinaryTree<Type>::destroy(Node<Type>* curr) {
  if (curr != nullptr) {
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
  }
}

template <typename Type>
void BinaryTree<Type>::insert(Type item) {
  if (root == nullptr) {
    root = new Node<Type>;
    root->item = item;
  } else {
    insert(item, root);
  }
}

template <typename Type>
void BinaryTree<Type>::insert(Type item, Node<Type>* curr) {
  if (item < curr->item) {
    if (curr->left == nullptr) {
      curr->left = new Node<Type>;
      curr->left->item = item;
    } else {
      insert(item, curr->left);
    }
  } else {
    if (curr->right == nullptr) {
      curr->right = new Node<Type>;
      curr->right->item = item;
    } else {
      insert(item, curr->right);
    }
  }
}

template <typename Type>
void BinaryTree<Type>::preOrder(std::ostringstream& out) {
  preOrder(out, root);
}

template <typename Type>
void BinaryTree<Type>::preOrder(std::ostringstream& out, Node<Type>* curr) {
  if (curr != nullptr) {
    if (out.tellp() > 0) {
      out << " ";
    }
    out << curr->item;
    preOrder(out, curr->left);
    preOrder(out, curr->right);
  }
}

template <typename Type>
void BinaryTree<Type>::inOrder(std::ostringstream& out) {
  inOrder(out, root);
}

template <typename Type>
void BinaryTree<Type>::inOrder(std::ostringstream& out, Node<Type>* curr) {
  if (curr != nullptr) {
    inOrder(out, curr->left);
    if (out.tellp() > 0) {
      out << " ";
    }
    out << curr->item;
    inOrder(out, curr->right);
  }
}

template <typename Type>
void BinaryTree<Type>::postOrder(std::ostringstream& out) {
  postOrder(out, root);
}

template <typename Type>
void BinaryTree<Type>::postOrder(std::ostringstream& out, Node<Type>* curr) {
  if (curr != nullptr) {
    postOrder(out, curr->left);
    postOrder(out, curr->right);
    if (out.tellp() > 0) {
      out << " ";
    }
    out << curr->item;
  }
}

template <typename Type>
int BinaryTree<Type>::nodeCount() {
  return nodeCount(root);
}

template <typename Type>
int BinaryTree<Type>::nodeCount(Node<Type>* curr) {
  if (curr == nullptr) {
    return 0;
  }
  return 1 + nodeCount(curr->left) + nodeCount(curr->right);
}

template <typename Type>
int BinaryTree<Type>::leavesCount() {
  return leavesCount(root);
}

template <typename Type>
int BinaryTree<Type>::leavesCount(Node<Type>* curr) {
  if (curr == nullptr) {
    return 0;
  }
  if (curr->left == nullptr && curr->right == nullptr) {
    return 1;
  }
  return leavesCount(curr->left) + leavesCount(curr->right);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::find(Type item) {
  return find(item, root);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::find(Type item, Node<Type>* curr) {
  if (curr == nullptr) {
    return nullptr;
  }
  if (curr->item == item) {
    return curr;
  }
  if (item < curr->item) {
    return find(item, curr->left);
  }
  return find(item, curr->right);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::findRightMostNode(Node<Type>* curr) {
  if (curr == nullptr) {
    return nullptr;
  }
  while (curr->right != nullptr) {
    curr = curr->right;
  }
  return curr;
}

template <typename Type>
void BinaryTree<Type>::remove(Type item) {
  root = remove(item, root);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::remove(Type item, Node<Type>* curr) {
  if (curr == nullptr) {
    return nullptr;
  }

  if (item < curr->item) {
    curr->left = remove(item, curr->left);
  } else if (item > curr->item) {
    curr->right = remove(item, curr->right);
  } else {
    if (curr->left == nullptr) {
      Node<Type>* temp = curr->right;
      delete curr;
      return temp;
    } else if (curr->right == nullptr) {
      Node<Type>* temp = curr->left;
      delete curr;
      return temp;
    } else {
      Node<Type>* rightMost = findRightMostNode(curr->left);
      curr->item = rightMost->item;
      curr->left = remove(rightMost->item, curr->left);
    }
  }
  return curr;
}

template <typename Type>
int BinaryTree<Type>::height() {
  if (root == nullptr) {
    return -1;
  }
  return height(0, root);
}

template <typename Type>
int BinaryTree<Type>::height(int level, Node<Type>* curr) {
  if (curr == nullptr) {
    return level - 1;
  }
  int leftH = height(level + 1, curr->left);
  int rightH = height(level + 1, curr->right);
  if (leftH > rightH) {
    return leftH;
  }
  return rightH;
}


#endif // BINARY_TREE_HPP
