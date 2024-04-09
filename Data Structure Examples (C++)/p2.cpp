template <typename Key, typename Value>
struct Node {
  Key key;
  Value value;
  bool pos_neg_node = false;
  struct Node<Key, Value> *next;
  struct Node<Key, Value> *up;
  struct Node<Key, Value> *down;
  struct Node<Key, Value> *left;
};
template <typename Key, typename Value>
class SkipList {
 private:
  struct Node<Key, Value> *head;
  struct Node<Key, Value> *top_neg_inf;
  struct Node<Key, Value> *top_pos_inf;
  struct Node<Key, Value> *bottom_neg_inf;
  struct Node<Key, Value> *bottom_pos_inf;

 public:
  SkipList();

  // You DO NOT need to implement a copy constructor or an assignment operator.

  ~SkipList();

  // How many distinct keys are in the skip list?
  size_t size() const noexcept;

  // Does the Skip List contain zero keys?
  bool isEmpty() const noexcept;

  // How many layers are in the skip list?
  // Note that an empty Skip List has two layers by default,
  // the "base" layer S_0 and the top layer S_1.
  //
  // [S_1: Top layer]    -inf ------> inf
  // [S_0: Bottom layer] -inf ------> inf
  //
  // This "empty" Skip List has two layers and a height of one.
  unsigned numLayers() const noexcept;

  // What is the height of this key, assuming the "base" layer S_0
  // contains keys with a height of 1?
  // For example, "0" has a height of 1 in the following skip list.
  //
  // [S_1]  -inf --------> inf
  // [S_0]  -inf --> 0 --> inf
  //
  // Throw an exception if this key is not in the Skip List.
  unsigned height(const Key &k) const;

  // If this key is in the SkipList and there is a next largest key
  // return the next largest key.
  // This function should throw a RuntimeException if either the key doesn't
  // exist or there is no subsequent key. A consequence of this is that this
  // function will throw a RuntimeException if *k* is the *largest* key in the
  // Skip List.
  Key nextKey(const Key &k) const;

  // If this key is in the SkipList and a next smallest key exists,
  // return the next smallest key.
  // This function should throw a RuntimeException if either the key doesn't
  // exist or there is no previous key. A consequence of this is that this
  // function will throw a RuntimeException if *k* is the *smallest* key in the
  // Skip List.
  Key previousKey(const Key &k) const;

  // These return the value associated with the given key.
  // Throw a RuntimeException if the key does not exist.
  Value &find(const Key &k);
  const Value &find(Key k) const;

  void node_insertion_new_layer(Node<Key, Value> *main_node,
                                Node<Key, Value> *left_node,
                                Node<Key, Value> *right_node);

  void node_insertion_existing_layer(Node<Key, Value> *main_node,
                                     Node<Key, Value> *left_node,
                                     Node<Key, Value> *right_node);

  void bottom_node_insertion(Node<Key, Value> *main_node,
                             Node<Key, Value> *left_node,
                             Node<Key, Value> *right_node, int skip_list_size);

  // Return true if this key/value pair is successfully inserted, false
  // otherwise. See the project write-up for conditions under which the key
  // should be "bubbled up" to the next layer. If the key already exists, do not
  // insert one -- return false.
  bool insert(const Key &k, const Value &v);

  // Return a vector containing all inserted keys in increasing order.
  std::vector<Key> allKeysInOrder() const;

  // Is this the smallest key in the SkipList? Throw a RuntimeException
  // if the key *k* does not exist in the Skip List.
  bool isSmallestKey(const Key &k) const;

  // Is this the largest key in the SkipList? Throw a RuntimeException
  // if the key *k* does not exist in the Skip List.
  bool isLargestKey(const Key &k) const;

  // I am not requiring you to implement remove.
};

template <typename Key, typename Value>
SkipList<Key, Value>::SkipList() {
  this->head = nullptr;
  struct Node<Key, Value> *neg_inf_top_node = new Node<Key, Value>();
  struct Node<Key, Value> *pos_inf_top_node = new Node<Key, Value>();
  struct Node<Key, Value> *neg_inf_bottom_node = new Node<Key, Value>();
  struct Node<Key, Value> *pos_inf_bottom_node = new Node<Key, Value>();
  // make sure all 4 of these nodes are declared as a positive or negative node
  neg_inf_top_node->pos_neg_node = true;
  pos_inf_top_node->pos_neg_node = true;
  neg_inf_bottom_node->pos_neg_node = true;
  pos_inf_bottom_node->pos_neg_node = true;
  // make it so the top nodes point to one another and the bottom nodes point to
  // one another
  neg_inf_top_node->next = pos_inf_top_node;
  pos_inf_top_node->left = neg_inf_top_node;
  neg_inf_bottom_node->next = pos_inf_bottom_node;
  pos_inf_bottom_node->left = neg_inf_bottom_node;
  // make it so the top nodes point down and the bottom nodes point up
  neg_inf_top_node->down = neg_inf_bottom_node;
  neg_inf_top_node->up = nullptr;
  pos_inf_bottom_node->down = nullptr;
  neg_inf_bottom_node->down = nullptr;
  pos_inf_top_node->down = pos_inf_bottom_node;
  pos_inf_top_node->up = nullptr;
  neg_inf_bottom_node->up = neg_inf_top_node;
  pos_inf_bottom_node->up = pos_inf_top_node;
  // set the SkipList's pointers equal to these nodes
  this->top_neg_inf = neg_inf_top_node;
  this->top_pos_inf = pos_inf_top_node;
  this->bottom_neg_inf = neg_inf_bottom_node;
  this->bottom_pos_inf = pos_inf_bottom_node;
}

template <typename Key, typename Value>
SkipList<Key, Value>::~SkipList() {
  struct Node<Key, Value> *current = this->head;
  while (current->next != nullptr) {
    struct Node<Key, Value> *currently = current->next;
    while (current->up != nullptr) {
      struct Node<Key, Value> *place_holder = current->up;
      delete current;
      current = place_holder;
    }
    if (current->up == nullptr) {
      delete current;
    }
    current = currently;
  }
}

template <typename Key, typename Value>
size_t SkipList<Key, Value>::size() const noexcept {
  struct Node<Key, Value> *current = this->head;
  size_t size = 0;
  while (current != nullptr) {
    size += 1;
    current = current->next;
  }
  return size;
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::isEmpty() const noexcept {
  if (this->head != nullptr) {
    return false;
  }
  return true;
}

template <typename Key, typename Value>
unsigned SkipList<Key, Value>::numLayers() const noexcept {
  unsigned max = 2;
  struct Node<Key, Value> *current = this->bottom_neg_inf;
  if (current->next == this->bottom_pos_inf){
      return max;
  }
  max = 1;
  while (current->up != nullptr){
      max += 1;
  }
//   while (current->next->pos_neg_node != true) {
//     unsigned layers = 1;
//     struct Node<Key, Value> *currently = current->next;
//     while (current->up != nullptr) {
//       layers += 1;
//       current = current->up;
//     }
//     if (layers > max) {
//       max = layers;
//     }
//     current = currently;
//   }
//   return max;
}

template <typename Key, typename Value>
unsigned SkipList<Key, Value>::height(const Key &k) const {
  struct Node<Key, Value> *current = this->head;
  while (current != nullptr) {
    if (!(current->key < k || k < current->key)) {
      unsigned k_size = 0;
      while (current != nullptr) {
        k_size += 1;
        current = current->up;
      }
      break;
    }
    current = current->next;
  }
  if (current == nullptr) {
    throw RuntimeException("value not found in list");
  }
}

template <typename Key, typename Value>
Key SkipList<Key, Value>::nextKey(const Key &k) const {
  struct Node<Key, Value> *current = this->head;
  while (current->pos_neg_node != true) {
    if (!(current->key < k || k < current->key)) {
      if (current->next->pos_neg_node != true) {
        return current->next->key;
      } else {
        throw RuntimeException("value is the biggest key");
      }
    }
    current = current->next;
  }
  if (current->pos_neg_node == true){
        throw RuntimeException("value not found");
    }
  return k;
}

template <typename Key, typename Value>
Key SkipList<Key, Value>::previousKey(const Key &k) const {
  struct Node<Key, Value> *current = this->head;
  if (current->value == k) {
    throw RuntimeException("value is the smallest key");
  }
  while (current->pos_neg_node != true) {
    if (current->next->pos_neg_node != true)
      if (!(current->next->key < k || k < current->next->key)) {
        return current->key;
      }
      current = current->next;
    }
    if (current->pos_neg_node == true){
        throw RuntimeException("value not found");
    }
  }
  return k;
}
std::vector<int> expected = {};
EXPECT_EQ(tree.inOrder(), expected);
EXPECT_EQ(tree.preOrder(), expected);
EXPECT_EQ(tree.postOrder(), expected);
EXPECT_EQ(tree.size(), 0)
template <typename Key, typename Value>
const Value &SkipList<Key, Value>::find(Key k) const {
  struct Node<Key, Value> *current = this->top_neg_inf->down->next;
  while (current->pos_neg_node == false) {
    if (current->key < k) {
      if (current->next->pos_neg_node == true) {
        if (current->down != nullptr) {
          current = current->down;
        } else {
          current = current->next;
        }
        continue;
      } else {
        current = current->next;
        continue;
      }
    } else if (current->key > k) {
      if (current->left->pos_neg_node == true) {
        if (current->down != nullptr) {
          current = current->down;
        } else {
          current = current->left;
        }
        continue;
      } else {
        current = current->left;
        continue;
      }
    } else if (current->key == k) {
      return current->value;
    }
  }
  if (current->pos_neg_node == true) {
    throw RuntimeException("value not found");
  }
  Value object;
  return 
}

template <typename Key, typename Value>
Value &SkipList<Key, Value>::find(const Key &k) {
  struct Node<Key, Value> *current = this->top_neg_inf->down->next;
  while (current->pos_neg_node == false) {
    if (current->key < k) {
      if (current->next->pos_neg_node == true) {
        if (current->down != nullptr) {
          current = current->down;
        } else {
          current = current->next;
        }
        continue;
      } else {
        current = current->next;
        continue;
      }
    } else if (current->key > k) {
      if (current->left->pos_neg_node == true) {
        if (current->down != nullptr) {
          current = current->down;
        } else {
          current = current->left;
        }
        continue;
      } else {
        current = current->left;
        continue;
      }
    } else if (current->key == k) {
      Value &returned_value = current->value;
      return returned_value;
    }
  }
  if (current->pos_neg_node == true) {
    throw RuntimeException("value not found");
  }
}

template <typename Key, typename Value>
void SkipList<Key, Value>::node_insertion_new_layer(
    Node<Key, Value> *main_node, Node<Key, Value> *left_node,
    Node<Key, Value> *right_node) {
  struct Node<Key, Value> *new_left = new Node<Key, Value>();
  struct Node<Key, Value> *new_right = new Node<Key, Value>();
  new_left->pos_neg_node = true;
  new_right->pos_neg_node = true;
  left_node->up->down = new_left;
  new_left->up = left_node->up;
  right_node->up->down = new_right;
  new_right->up = right_node->up;
  left_node->up = new_left;
  right_node->up = new_right;
  new_left->down = left_node;
  new_right->down = right_node;
  main_node->left = new_left;
  main_node->next = new_right;
  new_right->left = main_node;
  new_left->next = main_node;
}

template <typename Key, typename Value>
void SkipList<Key, Value>::node_insertion_existing_layer(
    Node<Key, Value> *main_node, Node<Key, Value> *left_node,
    Node<Key, Value> *right_node) {
  main_node->left = left_node;
  main_node->next = right_node;
  right_node->left = main_node;
  left_node->next = main_node;
}

template <typename Key, typename Value>
void SkipList<Key, Value>::bottom_node_insertion(Node<Key, Value> *main_node,
                                                  Node<Key, Value> *left_node,
                                                  Node<Key, Value> *right_node,
                                                  int skip_list_size) {
  main_node->left = left_node;
  left_node->next = main_node;
  main_node->next = right_node;
  right_node->left = main_node;
  main_node->down = nullptr;
  struct Node<Key, Value> *to_be_inserted = new Node<Key, Value>();
  to_be_inserted->key = main_node->key;
  to_be_inserted->value = main_node->value;
  struct Node<Key, Value> *find_left = main_node->left;
  struct Node<Key, Value> *find_right = main_node->next;
  struct Node<Key, Value> *new_top_node_right;
  struct Node<Key, Value> *new_top_node_left;

  main_node->up = to_be_inserted;
  to_be_inserted->down = main_node;
  while (find_left->pos_neg_node == false) {
    if (find_left->up != nullptr) {
      new_top_node_left = find_left->up;
      break;
    }
    find_left = find_left->left;
  }
  while (find_right->pos_neg_node == false) {
    if (find_right->up != nullptr) {
      new_top_node_right = find_right->up;
      break;
    }
    find_right = find_right->next;
  }
  if (skip_list_size <= 16) {
    unsigned flip_counter_max = 11;
    unsigned flip_counter = 0;
    while (flip_counter <= flip_counter_max) {
      if (flipCoin(main_node->key, flip_counter) == true) {
        if (find_left->pos_neg_node == true &&
            find_right->pos_neg_node == true) {
          node_insertion_new_layer(to_be_inserted, find_left, find_right);
        } else {
          node_insertion_existing_layer(to_be_inserted, new_top_node_left,
                                        new_top_node_right);
        }
        main_node = to_be_inserted;
        flip_counter += 1;
      } else {
        break;
      }
    }
  } else if (skip_list_size > 16) {
    unsigned flip_counter_max = 3 * ceil(log2(skip_list_size));
    unsigned flip_counter = 0;
    while (flip_counter <= flip_counter_max) {
      if (flipCoin(main_node->key, flip_counter) == true) {
        if (find_left->pos_neg_node == true &&
            find_right->pos_neg_node == true) {
          node_insertion_new_layer(to_be_inserted, find_left, find_right);
        } else {
          node_insertion_existing_layer(to_be_inserted, new_top_node_left,
                                        new_top_node_right);
        }
        main_node = to_be_inserted;
        flip_counter += 1;
      } else {
        break;
      }
    }
  }
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::insert(const Key &k, const Value &v) {
  struct Node<Key, Value> *to_be_inserted = new Node<Key, Value>();
  to_be_inserted->key = k;
  to_be_inserted->value = v;
  if (this->head == nullptr) {
    bottom_node_insertion(to_be_inserted, this->bottom_neg_inf,
                          this->bottom_pos_inf, 1);
    this->head = to_be_inserted;
    return true;
  } else {
    struct Node<Key, Value> *current_node = this->top_neg_inf->down->next;
    while (current_node->pos_neg_node == false) {
      if (current_node->key == k) {
        return false;
      }
      if (current_node->key < k) {
        if (current_node->next->pos_neg_node == true) {
          if (current_node->down != nullptr) {
            current_node = current_node->down;
            continue;
          } else {
            bottom_node_insertion(to_be_inserted, this->bottom_neg_inf,
                          this->bottom_pos_inf, size());
						  return true;
          }
        } else {
          current_node = current_node->next;
          continue;
        }
      } else if (current_node->key > k) {
        if (current_node->left->pos_neg_node == true) {
          if (current_node->down != nullptr) {
            current_node = current_node->down;
            continue;
          } else {
            bottom_node_insertion(to_be_inserted, this->bottom_neg_inf,
                          this->bottom_pos_inf, size());
						  this->head = to_be_inserted;
						  return true;
          }
        } else {
          if (current_node->left->key < k) {
            if (current_node->down != nullptr) {
              current_node = current_node->down;
              continue;
            } else {
              bottom_node_insertion(to_be_inserted, this->bottom_neg_inf,
                          this->bottom_pos_inf, size());
			return true;
            }
          } else if (current_node->left->key >= k) {
            current_node = current_node->left;
            continue;
          }
        }
      }
    }
  }
  return false;
}


template <typename Key, typename Value>
std::vector<Key> SkipList<Key, Value>::allKeysInOrder() const {
  std::vector<Key> returned_vector;
  struct Node<Key, Value> *current = this->head;
  while (current != nullptr) {
    returned_vector.push_back(current->key);
    current = current->next;
  }
  return returned_vector;
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::isSmallestKey(const Key &k) const {
  struct Node<Key, Value> *current = this->head;
  if (!(current->key < k || k < current->key)) {
    return true;
  }
  while (current != nullptr) {
    if (!(current->key < k || k < current->key)) {
      return false;
    }
    current = current->next;
  }
  if (current == nullptr) {
    throw RuntimeException("value not found");
  }
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::isLargestKey(const Key &k) const {
  struct Node<Key, Value> *current = this->head;
  while (current != nullptr) {
    if (!(current->key < k || k < current->key)) {
      if (current->next == nullptr) {
        return true;
      }
      return false;
    }
    current = current->next;
  }
  if (current == nullptr) {
    throw RuntimeException("value not found");
  }
}