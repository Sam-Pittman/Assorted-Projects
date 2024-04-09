#ifndef __PROJ_FOUR_LEVEL_BALANCED_TREE_HPP
#define __PROJ_FOUR_LEVEL_BALANCED_TREE_HPP

#include <string>
#include <vector>

#include "runtimeexcept.hpp"

class ElementNotFoundException : public RuntimeException {
 public:
  ElementNotFoundException(const std::string &err) : RuntimeException(err) {}
};

template <typename Key, typename Value>
struct Node {
  Key key;
  Value value;
  unsigned level;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
};

template <typename Key, typename Value>
class LevelBalancedTree {
 private:
  struct Node<Key, Value> *root;

 public:
  LevelBalancedTree();

  //	LevelBalancedTree(const LevelBalancedTree & st);
  //	LevelBalancedTree & operator=(const LevelBalancedTree & st);

  void deconstructor_helper(Node<Key, Value> root_node);
  // The destructor is required.
  ~LevelBalancedTree();

  // size() returns the number of distinct keys in the tree.
  size_t size() const noexcept;

  // isEmpty() returns true if and only if the tree has no values in it.
  bool isEmpty() const noexcept;

  // contains() returns true if and only if there
  //  is a (key, value) pair in the tree
  //	that has the given key as its key.
  bool contains(const Key &k) const noexcept;

  // find returns the value associated with the given key
  // If !contains(k), this will throw an ElementNotFoundException
  // There needs to be a version for const and non-const LevelBalancedTrees.
  Value &find(const Key &k);
  const Value &find(const Key &k) const;

  // Inserts the given key-value pair into
  // the tree and performs the balancing operation(s) if needed
  // operation, as described in lecture.
  // If the key already exists in the tree,
  // you may do as you please (no test cases in
  // the grading script will deal with this situation)
  void insert(const Key &k, const Value &v);

  // Deletes the given key from the tree
  // and performs the balancing operation(s) if needed.
  // If the key does not exist in the tree,
  // do not modify the tree.
  void remove(const Key &k);

  // The following three functions all return
  // the set of keys in the tree as a standard vector.
  // Each returns them in a different order.
  std::vector<Key> inOrder() const;
  std::vector<Key> preOrder() const;
  std::vector<Key> postOrder() const;
};

template <typename Key, typename Value>
LevelBalancedTree<Key, Value>::LevelBalancedTree() {
  this->root = nullptr;
}

template <typename Key, typename Value>
void LevelBalancedTree<Key, Value>::deconstructor_helper(
    Node<Key, Value> root_node) {
  if (root_node->left != nullptr) {
    deconstructor_helper(root_node->left);
  }
  if (root_node->right != nullptr) {
    deconstructor_helper(root_node->right);
  }
  delete root_node;
}

template <typename Key, typename Value>
LevelBalancedTree<Key, Value>::~LevelBalancedTree() {
  if this->root != nullptr){
        deconstructor_helper(this->root);
    }
}

template <typename Key, typename Value>
size_t LevelBalancedTree<Key, Value>::size_helper(Node<Key, Value> root_node,
                                                  int &counter) {
  counter += 1;
  if (root_node->left != nullptr) {
    size_helper(root_node->left);
  }
  if (root_node->right != nullptr) {
    size_helper(root_node->right);
  }
}

template <typename Key, typename Value>
size_t LevelBalancedTree<Key, Value>::size() const noexcept {
  size_t size = 0;
  if this->root != nullptr){
        return size_helper(this->root, &size);
    }
  return size;
}

template <typename Key, typename Value>
bool LevelBalancedTree<Key, Value>::isEmpty() const noexcept {
  return true;  // stub
}

template <typename Key, typename Value>
bool LevelBalancedTree<Key, Value>::contains(const Key &k) const noexcept {
  struct Node<Key, Value> *current_node = this->root;
  while (current_node->key != k) {
    if (current_node->left == nullptr && current_node->right == nullptr) {
      return false;
    }
    if ((k < current_node->key) && (current_node->left != nullptr)) {
      current_node = current_node->left;
    }
    if ((k ! < current_node->key) && (current_node->right != nullptr)) {
      current_node = current_node->right;
    } else {
      return false;
    }
  }
  if (current_node->key == k) {
    return true;
  }
}

template <typename Key, typename Value>
Value &LevelBalancedTree<Key, Value>::find(const Key &k) {
  struct Node<Key, Value> *current_node = this->root;
  while (current_node->key != k) {
    if (current_node->left == nullptr && current_node->right == nullptr) {
      throw ElementNotFoundException("Element Not Found");
    }
    if ((k < current_node->key) && (current_node->left != nullptr)) {
      current_node = current_node->left;
    }
    if ((k ! < current_node->key) && (current_node->right != nullptr)) {
      current_node = current_node->right;
    } else {
      throw ElementNotFoundException("Element Not Found");
    }
  }
  if (current_node->key == k) {
    return &current_node->value;
  }
}

template <typename Key, typename Value>
const Value &LevelBalancedTree<Key, Value>::find(const Key &k) const {
  struct Node<Key, Value> *current_node = this->root;
  while (current_node->key != k) {
    if (current_node->left == nullptr && current_node->right == nullptr) {
      throw ElementNotFoundException("Element Not Found");
    }
    if ((k < current_node->key) && (current_node->left != nullptr)) {
      current_node = current_node->left;
    }
    if ((k ! < current_node->key) && (current_node->right != nullptr)) {
      current_node = current_node->right;
    } else {
      throw ElementNotFoundException("Element Not Found");
    }
  }
  if (current_node->key == k) {
    return const & current_node->value;
  }
}

template <typename Key, typename Value>
void LevelBalancedTree<Key, Value>::insert(const Key &k, const Value &v) {
  struct Node<Key, Value> *to_be_inserted = new Node<Key, Value>();
  to_be_inserted.key = k;
  to_be_inserted.value = v;
  to_be_inserted.left = nullptr;
  to_be_inserted.right = nullptr;
  if (this->root == nullptr) {
    to_be_inserted.level = 1;
    to_be_inserted.parent = nullptr;
    this->root = to_be_inserted;
  } else {
    current_node = this->root;
    bool placed == false;
    while (placed == false) {
      if (k < current_node->key) {
        if (current_node->left == nullptr) {
          current_node->left = to_be_inserted;
          to_be_inserted->parent = current_node;
          placed = true;
        } else {
          current_node = current_node->left;
        }
      }
      if (k ! < current_node->key) {
        if (current_node->right == nullptr) {
          current_node->right = to_be_inserted;
          to_be_inserted->parent = current_node;
          placed = true;
        } else {
          current_node = current_node->right;
        }
      }
    }
  }
}

template <typename Key, typename Value>
void LevelBalancedTree<Key, Value>::remove(const Key &k) {
  struct Node<Key, Value> *current_node = this->root;
  while (current_node->key != k) {
    if (current_node->left == nullptr && current_node->right == nullptr) {
      throw ElementNotFoundException("Element Not Found");
    }
    if ((k < current_node->key) && (current_node->left != nullptr)) {
      current_node = current_node->left;
    }
    if ((k ! < current_node->key) && (current_node->right != nullptr)) {
      current_node = current_node->right;
    } else {
      throw ElementNotFoundException("Element Not Found");
    }
  }
  if (current_node->key == k) {
    if (current_node->left == nullptr && current_node->right == nullptr) {
      if (current_node = current_node->parent->right) {
        current_node->parent->right == nullptr;
        delete current_node;
      }
      if (current_node = current_node->parent->left) {
        current_node->parent->left == nullptr;
        delete current_node;
      }
    }
  }
}

template <typename Key, typename Value>
LevelBalancedTree<Key, Value>::inOrder_helper(Node<Key, Value> root,
                                              std::vector &this_vector) {
  if (root == nullptr) {
    return;
  }
  inOrder_helper(root->left);
  push_back(root.key);
  inOrder_helper(root->right);
}

template <typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::inOrder() const {
  std::vector<Key> foo;
  std::vector<Key> *foo_pointer;
  inOrder_helper(this->root, foo_pointer);
  return foo;
}

template <typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::preOrder() const {
  std::vector<Key> foo;
  return foo;
}

template <typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::postOrder() const {
  std::vector<Key> foo;
  return foo;
}

#endif

template <typename Key, typename Value>
void LevelBalancedTree<Key, Value>::balance_right(
    struct Node<Key, Value> *node1, struct Node<Key, Value> *node2) {
  while (node1->level == node2->level) {
    if (node2->left == node1) {
      balance_left(node1, node2);
      break;
    }
    std::cout << "\nRIGHT Node1 Level " << node1->level << " Node2 Level "
              << node2->level << "\n";
    std::cout << "\nNODE1 " << node1->key << " NODE2 " << node2->key;
    bool carry_on = true;
    //EQUAL TO HERE
    if (child_distance(node2, "left") == 1) {
      node2->level += 1;
      carry_on = false;
      if (node2->parent != nullptr) {
        if (node2->level == node2->parent->level) {
          node1 = node2;
          node2 = node1->parent;
        }
      }
    } else if (child_distance(node2, "left") == 2 && carry_on == true) {
      if (child_distance(node1, "right") == 2 &&
          child_distance(node1, "left") == 1) {
        node1->left->level += 1;
        node1->level -= 1;
        node2->level -= 1;
        node1->parent = node1->left;
        if (node1->key == this->root->key || node2->key == this->root->key) {
          this->root = node1->parent;
          node1->parent->parent = nullptr;
        } else {
          node1->parent->parent = node2->parent;
          node1->parent->parent->left = node1->parent;
        }
        node2->parent = node1->left;
        if (node1->left->left == nullptr && node1->left->right != nullptr) {
          node1->left = node1->left->right;
          node1->left->parent = node1;
        } else if (node1->left->left != nullptr &&
                   node1->left->right == nullptr) {
          node1->left = node1->left->left;
          node1->left->parent = node1;
        } else if (node1->left->left == nullptr &&
                   node1->left->right == nullptr) {
          node1->left = nullptr;
        }
        node1->parent->left = node2;
        node1->parent->right = node1;
        node2->parent = node1->parent;
        carry_on = false;
        node2->right = nullptr;
        break;
        //EQUAL TO HERE
      } else if (child_distance(node1, "right") == 1 && carry_on == true) {
        node2->level -= 1;
        if (node2->parent == nullptr) {
          node1->parent = nullptr;
        } else if (node2->parent != nullptr) {
          node1->parent = node2->parent;
          if (node2 == node2->parent->right) {
            node1->parent->right = node1;
          } else if (node2 == node2->parent->left) {
            node1->parent->left = node1;
          }
        }
        if (node1->left != nullptr) {
          node2->right = node1->left;
        } else {
          node2->right = nullptr;
        }
        node1->left = node2;
        node2->parent = node1;
        if (node1->key == this->root->key || node2->key == this->root->key) {
          this->root = node2;
        }
        if (node2->parent != nullptr) {
          if (node2->level == node2->parent->level) {
            node1 = node2;
            node2 = node1->parent;
          }
        }
      }
    }
  }
}

template <typename Key, typename Value>
void LevelBalancedTree<Key, Value>::balance_left(
    struct Node<Key, Value> *node1, struct Node<Key, Value> *node2) {
  while (node1->level == node2->level) {
    if (node2->right == node1) {
      balance_right(node1, node2);
      break;
    }
    std::cout << "\nLEFT Node1 Level " << node1->level << " Node2 Level "
              << node2->level << "\n";
    bool carry_on = true;
    //EQUAL TO HERE
    if (child_distance(node2, "right") == 1) {
      std::cout << "OPTION 1\n";
      node2->level += 1;
      carry_on = false;
      if (node2->parent != nullptr) {
        if (node2->level == node2->parent->level) {
          node1 = node2;
          node2 = node1->parent;
        }
      }
    } else if (child_distance(node2, "right") == 2 && carry_on == true) {
      std::cout << "OPTION 2\n";
      if (child_distance(node1, "left") == 2 &&
          child_distance(node1, "right") == 1) {
        std::cout << "OPTION 2.1\n";
        node1->right->level += 1;
        node1->level -= 1;
        node2->level -= 1;
        node1->parent = node1->right;
        if (node1->key == this->root->key || node2->key == this->root->key) {
          this->root = node1->parent;
          node1->parent->parent = nullptr;
        } else {
          node1->parent->parent = node2->parent;
          node1->parent->parent->right = node1->parent;
        }
        node2->parent = node1->right;
        if (node1->right->left == nullptr && node1->right->right != nullptr) {
          node1->right = node1->right->right;
          node1->right->parent = node1;
        } else if (node1->right->left != nullptr &&
                   node1->right->right == nullptr) {
          node1->right = node1->right->left;
          node1->right->parent = node1;
        } else if (node1->right->left == nullptr &&
                   node1->right->right == nullptr) {
          node1->right = nullptr;
        }
        node1->parent->right = node2;
        node1->parent->left = node1;
        node2->parent = node1->parent;
        carry_on = false;
        node2->left = nullptr;
        break;
        //EQUAL TO HERE
      } else if (child_distance(node1, "left") == 1 && carry_on == true) {
        std::cout << "OPTION 2.2\n";
        node2->level -= 1;
        if (node2->parent == nullptr) {
          node1->parent = nullptr;
        } else if (node2->parent != nullptr) {
          node1->parent = node2->parent;
          if (node2 == node2->parent->right) {
            node1->parent->right = node1;
          } else if (node2 == node2->parent->left) {
            node1->parent->left = node1;
          }
        }
        if (node1->right != nullptr) {
          node2->left = node1->right;
        } else {
          node2->left = nullptr;
        }

        node1->right = node2;
        node2->parent = node1;
        if (node1->key == this->root->key || node2->key == this->root->key) {
          this->root = node1;
        }
        if (node2->parent != nullptr) {
          if (node2->level == node2->parent->level) {
            node1 = node2;
            node2 = node1->parent;
          }
        }
      }
    }
  }
}