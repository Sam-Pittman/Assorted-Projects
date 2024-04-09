WordSet::resize() {
  unsigned size_holder = this->array_capacity * 2;
  bool found_prime = false;
  while (found_prime == false) {
    for (int i = 2; i <= ceil(sqrt(size_holder)); i++) {
      if (array_size % i == 0) {
        size_holder += 1;
        break;
      }
    }
  }
  string *copy_of_table1 = this->table1;
  string *copy_of_table2 = this->table2;
  this->table1 = new string[size_holder];
  this->table2 = new string[size_holder];

  for (int i = 0; i < this->array_capacity; i++) {
    if (copy_of_table1[i].length() != 0) {
      insert(copy_of_table1[i]);
    }
  }
  for (int i = 0; i < this->array_capacity; i++) {
    if (copy_of_table1[i].length() != 0) {
      insert(copy_of_table1[i]);
    }
  }
  this->array_capacity = size_holder;
}

TEST(RequiredPart1, SAM_COUNTEMPTY) {
  WordSet ws(11);
  EXPECT_TRUE(ws.getCount(), 0);
}

TEST(RequiredPart1, SAM_COUNTONE) {
  WordSet ws(11);
  ws.insert("ab");
  EXPECT_TRUE(ws.getCount(), 1);
}

TEST(SAM2, level_balanced_tree) {
  LevelBalancedTree<int, std::string> tree;
  tree.insert(20, "five");
  tree.insert(19, "three");
  tree.insert(18, "ten");
  std::vector<int> trav = tree.preOrder();
  std::vector<int> expected = {19, 18, 20};
  EXPECT_EQ(trav, expected);
}
if (this->root->right != nullptr && this->root->left != nullptr) {
  std::cout << "\nROOT LEVEL " << this->root->level << " LEFT LEVEL "
            << this->root->left->level << " RIGHT LEVEL"
            << this->root->right->level;
  std::cout << "\nROOT VALUE " << this->root->key << " LEFT VALUE "
            << this->root->left->key << " RIGHT VALUE"
            << this->root->right->key;
}

if (node2->parent == nullptr) {
  node1->parent = nullptr;
} else if (node2->parent != nullptr) {
  node1->parent = node2->parent;
  if (node2 == node2->parent->right) {
    node1->parent->right = node1;
  } else if (node2 == node2->parent->right) {
    node1->parent->left = node1;
  }
}
std::cout << "OPTION 1\n";
tree.insert(12, "twelve");
tree.insert(9, "nine");
tree.insert(17, "seventeen");
tree.insert(7, "seven");
tree.insert(5, "five");
tree.insert(13, "thirteen");
tree.insert(15, "fifteen");
tree.insert(6, "six");
tree.insert(16, "sixteen");
tree.insert(15, "fifteen");
tree.insert(14, "fourteen");

std::cout << "Node 1 Level " << node1->level << " Node 2 Level " << node2->level
          << "\n";
<< " Current " << current_node->key;
std::cout << "\nROOT " << this->root;
void LevelBalancedTree<Key, Value>::balance_left(Node<Key, Value> node1,
                                                 Node<Key, Value> node2) const {
  if (child_distance(node2, "right") == 1) {
    node2->level += 1;
    if (node1 == this->root || node2 == this->root) {
      this->root = node2;
    }
  } else if (child_distance(node2, "right") == 2) {
    node2->level -= 1;
    if (node1 == this->root || node2 == this->root) {
      this->root = node1;
    }
  }
}

for (int i = 0; i < s1.length(); i++) {
  string current_char = s1[i];
  int current_char_val = s1[i];
  string s1_copy = s1;
  for (int j = 97; j <= 122 : j++) {
    if (j = current_char_val) {
      j++;
    }
    s1_copy[i] = j;
    if (words.contains(s1_copy) == true) {
    }
  }
}

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
        }
        node2->parent = node1->left;
        if (node1->left->left == nullptr && node1->left->right != nullptr) {
          node1->left = node1->left->right;
        } else if (node1->left->left != nullptr &&
                   node1->left->right == nullptr) {
          node1->left = node1->left->left;
        } else if (node1->left->left == nullptr &&
                   node1->left->right == nullptr) {
          node1->left = nullptr;
        }
        node1->parent->left = node2;
        node1->parent->right = node1;
        carry_on = false;
        break;

      } else if (child_distance(node1, "left") == 1 && carry_on == true) {
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
        }
        node2->parent = node1->right;
        if (node1->right->left == nullptr && node1->right->right != nullptr) {
          node1->right = node1->right->right;
        } else if (node1->right->left != nullptr &&
                   node1->right->right == nullptr) {
          node1->right = node1->right->left;
        } else if (node1->right->left == nullptr &&
                   node1->right->right == nullptr) {
          node1->right = nullptr;
        }
        node1->parent->right = node2;
        node1->parent->left = node1;
        carry_on = false;
        break;

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
tree.insert(33, "thirty three");
tree.insert(25, "twenty five");
tree.insert(23, "twenty three");
tree.insert(32, "thirty two");
tree.insert(24, "twenty four");

template <typename Key, typename Value>
void LevelBalancedTree<Key, Value>::balance_up(struct Node<Key, Value> *node) {
  bool satisfied = false;
  while (satisfied == false)
    if (node->right == nullptr && node->left == nullptr) {
      node->level = 1;
      if (node->parent == nullptr) {
        satisfied = true;
      } else {
        node = node->parent;
      }
    } else {
      else if (child_distance(node, "right") == 2 &&
               child_distance(node, "left") == 2) {
      }
      else if (child_distance(node, "right") == 1 &&
               child_distance(node, "left") == 2) {
      }
      else if (child_distance(node, "right") == 2 &&
               child_distance(node, "left") == 1) {
      }

    }
}

template <typename Key, typename Value>
void LevelBalancedTree<Key, Value>::remove(const Key &k) {
  struct Node<Key, Value> *current_node = this->root;
  while (!(current_node->key == k)) {
    if (current_node->left == nullptr && current_node->right == nullptr) {
      throw ElementNotFoundException("Element Not Found");
    } else if ((k < current_node->key) && (current_node->left != nullptr)) {
      current_node = current_node->left;
    } else if (!(k < current_node->key) && (current_node->right != nullptr)) {
      current_node = current_node->right;
    } else {
      throw ElementNotFoundException("Element Not Found");
    }
  }
  if (current_node->key == k) {
    if (current_node->left == nullptr && current_node->right == nullptr) {
      if (current_node == current_node->parent->right) {
        current_node->parent->right = nullptr;
        if (current_node->parent->left == nullptr) {
          current_node->parent->level = 1;
        }
      }
      if (current_node == current_node->parent->left) {
        current_node->parent->left = nullptr;
        if (current_node->parent->right == nullptr) {
          current_node->parent->level = 1;
        }
      }
      struct Node<Key, Value> *parent_node = current_node->parent;
      delete current_node;
      this->tree_size -= 1;
    } else if (current_node->left != nullptr &&
               current_node->right == nullptr) {
      // Find predecessor
      // put pred in cur node place
      // balance from where predecssor used to be up
      delete current_node;
    } else if (current_node->left == nullptr &&
               current_node->right != nullptr) {
      // Find successor
      // put suc in cur node place
      // balance from where successor used to be up
      delete current_node;
    } else if (current_node->left != nullptr &&
               current_node->right != nullptr) {
      // Find predecessor or sucessor
      // place pred suc
      /// balance from where successor or pred used to be up
      delete current_node;
    }
    balance_up(parent_node);
  }
}

TEST(SAM4, balance_this_hard_removal)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(44, "fourty four");
	tree.insert(17, "seventeen");
	tree.insert(78, "seventy eight");
	tree.insert(32, "thirty two");
	tree.insert(87, "eighty seven");
  tree.insert(50, "fifty");
	tree.insert(48, "fourty eight");
  tree.insert(62, "sixty two");

	
	std::vector<int> trav = tree.preOrder();
	std::vector<int> tray = tree.postOrder();
	
	std::vector<int> expected1 = {44, 17, 32, 78, 50, 48, 62, 87};
	std::vector<int> expected2 = {32, 17, 48, 62, 50, 87, 78, 44};
	EXPECT_EQ( trav, expected1 );
	EXPECT_EQ( tray, expected2 );
  tree.remove(48);
  trav = tree.preOrder();
	tray = tree.postOrder();
	
	std::vector<int> expected1 = {44, 17, 32, 78, 50, 62, 87};
	std::vector<int> expected2 = {32, 17, 62, 50, 87, 78, 44};
  EXPECT_EQ( trav, expected1 );
	EXPECT_EQ( tray, expected2 );
	
}
// numbers44, 17, 78, 32, 87, 50, 48, 62
// preorder 44, 17, 32, 78, 50, 48, 62, 87
// postorder 32, 17, 48, 62, 50, 87, 78, 44


  template <typename Key, typename Value>
  void printBT(const std::string& prefix, const struct Node<Key, Value> *node, bool isLeft)
	{
		if( node != nullptr )
		{
			std::cout << prefix;

			std::cout << (isLeft ? "├──" : "└──" );

			// print the value of the node
			std::cout << node->key << std::endl;

			// enter the next tree level - left and right branch
			printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
			printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
		}
	}
	template <typename Key, typename Value>
	void printBT(const struct Node<Key, Value>* node)
	{
		printBT("", node, false);    
	}