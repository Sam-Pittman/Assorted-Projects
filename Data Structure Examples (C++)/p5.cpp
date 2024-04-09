template <typename Object>
void MyPriorityQueue<Object>::insert(const Object &elem) {
  // this code snippet comes from one I found on stack overflow
  // https://stackoverflow.com/questions/33059706/adding-to-dynamic-array
  this->heap_size += 1;

  Object *temporary_array = new Object[this->heap_size];
  for (int i = 0; i < this->heap_size - 1; i++) {
    temporary_array[i] = this->que_array[i];
  }
  temporary_array[this->heap_size - 1] = elem;
  delete[] this->que_array;
  this->que_array = temporary_array;
  int start_index = this->heap_size - 1;
  Object start_value = this->que_array[start_index];
  int parent_index = floor((this->heap_size - 2) / 2);
  Object parent_value = this->que_array[parent_index];
  while (start_value < parent_value) {
    this->que_array[start_index] = parent_value;
    this->que_array[parent_index] = start_value;
    start_index = parent_index;
    parent_index = floor((start_index - 2) / 2);
  }
}

template <typename Object>
void MyPriorityQueue<Object>::extractMin() {
  if (this->heap_size == 0) {
    throw PriorityQueueEmptyException("cannot extract from empty stack");
  } else if (this->heap_size == 1) {
    delete[] this->que_array;
    this->que_array = new Object[0];
    this->heap_size = 0;
  } else {
    this->que_array[0] = this->que_array[-1];
    Object *temporary_array = new Object[this->heap_size];
    for (int i = 0; i < this->heap_size - 1; i++) {
      temporary_array[i] = this->que_array[i];
    }
    delete[] this->que_array;
    this->que_array = temporary_array;
    this->heap_size -= 1;
    int start_index = 0;
    Object start_value = this->que_array[start_index];
    int child_index = -1;
    if (this->que_array[(2 * start_index) + 1] <
        this->que_array[(2 * start_index) + 2]) {
      Object child_value = this->que_array[(2 * start_index) + 1];
      int child_index = (2 * start_index) + 1;
    } else if (!(this->que_array[(2 * start_index) + 1] <
                 this->que_array[(2 * start_index) + 2])) {
      Object child_value = this->que_array[(2 * start_index) + 2];
      int child_index = (2 * start_index) + 2;
    }
    while (child_value < start_value) {
      this->que_array[start_index] = child_value;
      this->que_array[child_index] = start_value;
      start_index = child_index;
      if ((2 * child_index + 2) <= (this->heap_size - 1)) {
        if (this->que_array[(2 * start_index) + 1] <
            this->que_array[(2 * start_index) + 2]) {
          Object child_value = this->que_array[(2 * start_index) + 1];
          int child_index = (2 * start_index) + 1;
        } else if (!(this->que_array[(2 * start_index) + 1] <
                     this->que_array[(2 * start_index) + 2])) {
          Object child_value = this->que_array[(2 * start_index) + 2];
          int child_index = (2 * start_index) + 2;
        }
      } else if (((2 * child_index + 1) < (this->heap_size - 1)) &&
                 ((2 * child_index + 2) > (this->heap_size - 1))) {
        Object child_value = this->que_array[(2 * start_index) + 1];
        int child_index = (2 * start_index) + 1;
      } else {
        break;
      }
    }
  }
}

TEST(SAM, size_check1) {
  MyPriorityQueue<int> mpq;
  EXPECT_EQ(mpq.size(), 0);
  mpq.insert(3);
  EXPECT_EQ(mpq.size(), 1);
  mpq.insert(5);
  mpq.insert(2);
  mpq.insert(11);
  mpq.extractMin();
  EXPECT_EQ(mpq.size(), 3);
}

TEST(SAM, empty_check1) {
  MyPriorityQueue<int> mpq;
  EXPECT_TRUE(mpq.isEmpty());
  mpq.insert(3);
  EXPECT_FALSE(mpq.isEmpty());
  mpq.insert(5);
  mpq.insert(2);
  mpq.insert(11);
  mpq.extractMin();
  EXPECT_FALSE(mpq.isEmpty());
}

TEST(SAM, empty_size_check1) {
  MyPriorityQueue<int> mpq;
  mpq.insert(3);
  mpq.extractMin();
  EXPECT_TRUE(mpq.isEmpty());
  EXPECT_EQ(mpq.size(), 0);
}

TEST(SAM, extracting_min1) {
  MyPriorityQueue<int> mpq;
  mpq.insert(1);
  mpq.insert(3);
  EXPECT_EQ(mpq.min(), 1);
  mpq.extractMin();
  EXPECT_EQ(mpq.min(), 3);
}

TEST(SAM, extracting_min2) {
  MyPriorityQueue<int> mpq;
  mpq.insert(3);
  mpq.insert(1);
  EXPECT_EQ(mpq.min(), 1);
  mpq.extractMin();
  EXPECT_EQ(mpq.min(), 3);
}

TEST(SAM, extracting_min3) {
  MyPriorityQueue<int> mpq;
  mpq.insert(1);
  mpq.insert(3);
  mpq.insert(5);
  mpq.insert(7);
  mpq.insert(9);
  mpq.insert(11);
  EXPECT_EQ(mpq.min(), 1);
  mpq.extractMin();
  EXPECT_EQ(mpq.min(), 3);
}

struct que_object {
  int placement;
  std::string value;
  bool operator<(que_object other) {
    if (placement < other.placement) {
      return true;
    } else {
      return false;
    }
  }
}

std::vector<std::string>
convert(const std::string &s1, const std::string &s2,
        const std::unordered_set<std::string> &words) {
  std::vector<std::string> l_c_vec;
  std::unordered_map<std::string, std::string> dict;
  MyPriorityQueue<que_object> this_pq;
  int letters_away_start = 0;
  for (int i = 0; i < s1.length(); i++) {
    if (s1[i] != s2[i]) {
      letters_away_start += 1;
    }
  }
  int final_value = letters_away_start;
  struct que_object to_insert {
    final_value, s1
  };
  this_pq.insert(to_insert);
  while (this_pq.isEmpty() == false) {
    std::string current_word = (this_pq.min()).value;
    this_pq.extractMin();
    for (int i = 0; i < current_word.length(); i++) {
      int current_char_val = current_word[i];
      std::string s1_copy = current_word;
      for (int j = 97; j <= 122; j++) {
        if (j == current_char_val) {
          continue;
        }
        s1_copy[i] = j;
        if (words.find(s1_copy) != words.end()) {
          dict[s1_copy] = current_word;
          int letters_away = 0;
          int l_c_d = 0;
          for (int i = 0; i < current_word.length(); i++) {
            if (s1_copy[i] != s2[i]) {
              letters_away += 1;
            }
            if (s1_copy[i] != s1[i]) {
              l_c_d += 1;
            }
          }
          int final_value = letters_away + l_c_d;
          struct que_object to_insert {
            final_value, s1_copy
          };
          this_pq.insert(to_insert);
        }
        if (s1_copy == s2) {
          break;
        }
      }
    }
  }
  if (dict.find(s2) != dict.end()) {
    std::string current_word = s2;
    while (current_word != s1) {
      l_c_vec.push(current_word);
      current_word = dict[current_word];
    }
    l_c_vec.push(s1);
    reverse(l_c_vec.begin(), l_c_vec.end());
  }
  return l_c_vec;
}
