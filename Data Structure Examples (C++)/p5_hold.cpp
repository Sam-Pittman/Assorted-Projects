
template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{
	this->heap_size = 0;
	this->que_array = new Object[this->heap_size];
}


template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
	delete[] this->que_array;
}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return this->heap_size;
}



template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	if (this->heap_size == 0){
		return true;
	}
	return false;
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
	// this code snippet comes from one I found on stack overflow
	// https://stackoverflow.com/questions/33059706/adding-to-dynamic-array
	this->heap_size += 1;
	Object *temporary_array = new Object[this->heap_size];
    for (int i = 0 ; i < this->heap_size - 1 ; i++){
        temporary_array[i] = this->que_array[i];
    }
    temporary_array[this->heap_size - 1] = elem;
    delete[] this->que_array;
    this->que_array = temporary_array;
	if (this->heap_size > 1){
		int start_index = this->heap_size - 1;
		Object start_value = this->que_array[start_index];
		int parent_index = floor((this->heap_size - 2)/2);
		Object parent_value = this->que_array[parent_index];
		while (start_value < parent_value){
			this->que_array[start_index] = parent_value;
			this->que_array[parent_index] = start_value;
			start_index = parent_index;
			parent_index = floor((start_index - 2)/2);
			start_value = this->que_array[start_index];
			parent_value = this->que_array[parent_index];
		}
	}
}




template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	return this->que_array[0];
}



template <typename Object>
void MyPriorityQueue<Object>::extractMin() {
	// for (int i = 0; i < this->heap_size; i++) {
    //     std::cout << this->que_array[i];
    // }
	if (this->heap_size == 0) {
    throw PriorityQueueEmptyException("cannot extract from empty stack");
	} else if (this->heap_size == 1) {
      delete[] this->que_array;
      this->que_array = new Object[0];
      this->heap_size = 0;

    } else if (this->heap_size == 2){
      Object value = this->que_array[this->heap_size - 1];
      delete[] this->que_array;
      this->que_array = new Object[1]{value};
      this->heap_size -= 1;
    } else {
		//            std::cout << "ARRAY -1 " << this->que_array[this->heap_size - 1] << "\n";
      this->que_array[0] = this->que_array[this->heap_size - 1];
      Object *temporary_array = new Object[this->heap_size - 1];
      for (int i = 0; i < this->heap_size - 1; i++) {
        temporary_array[i] = this->que_array[i];
      }
      delete[] this->que_array;
      this->que_array = temporary_array;
      this->heap_size -= 1;
	//   for (int i = 0; i < this->heap_size; i++) {
    //     std::cout << this->que_array[i];
    // 	}
      int start_index = 0;
      Object start_value = this->que_array[start_index];
      int child_index = -1;
	  Object child_value = this->que_array[child_index];
    //   if (this->que_array[(2 * start_index) + 1] <
    //       this->que_array[(2 * start_index) + 2]) {
    //     Object child_value = this->que_array[(2 * start_index) + 1];
    //     int child_index = (2 * start_index) + 1;
    //   } else if(!(this->que_array[(2 * start_index) + 1] <
    //       this->que_array[(2 * start_index) + 2])) {
    //       Object child_value = this->que_array[(2 * start_index) + 2];
    //       int child_index = (2 * start_index) + 2;
    //     }
	// 	bool flagged = true;
      while (child_value < start_value) {
        if ((2 * child_index + 2) <= (this->heap_size - 1)) {
          if (this->que_array[(2 * start_index) + 1] <
              this->que_array[(2 * start_index) + 2]) {
            child_value = this->que_array[(2 * start_index) + 1];
            child_index = (2 * start_index) + 1;
          } else if
            (!(this->que_array[(2 * start_index) + 1] <
              this->que_array[(2 * start_index) + 2])) {
              child_value = this->que_array[(2 * start_index) + 2];
              child_index = (2 * start_index) + 2;
            }
        } else if (((2 * child_index + 1) < (this->heap_size - 1)) &&
                   ((2 * child_index + 2) > (this->heap_size - 1))) {
          child_value = this->que_array[(2 * start_index) + 1];
          child_index = (2 * start_index) + 1;
        } else {
          break;
        }
		this->que_array[start_index] = child_value;
        this->que_array[child_index] = start_value;
        start_index = child_index;
      }
    }
  }

#endif 
