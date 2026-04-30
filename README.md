# Project Design Document: Custom HashMap & LinkedList

## Requirements

Use only the headers and structures provided in the template. Using standard template library (STL) containers like `std::unordered_map`, `std::map`, or `std::list` is strictly prohibited. You must manage raw heap memory manually and prevent memory leaks.

---

### 1. LinkedList Class

The `LinkedList` class serves as the collision chain for your hash map buckets. It must include the following functionalities:

#### Constructors & Destructors (Rule of Five)
* `LinkedList()`: Default constructor initializing an empty list.
* `~LinkedList()`: Destructor that safely deletes all nodes to free memory.
* `LinkedList(const LinkedList &other)`: Copy constructor performing a **deep copy** of all nodes.
* `LinkedList(LinkedList &&other)`: Move constructor transferring ownership of the head pointer.
* `operator=(const LinkedList &other)`: Copy assignment operator (**deep copy**).
* `operator=(LinkedList &&other)`: Move assignment operator.

#### Modifiers
* `insert(key, value)`: Inserts a new key-value pair or updates the value if the key already exists.
* `erase(key)`: Removes the node containing the key and safely frees its memory.
* `clear()`: Deletes all nodes and resets the list to an empty state.

#### Accessors & Utilities
* `at(key)`: Returns a reference (both `const` and non-`const` versions) to the value associated with the key.
* `find(key)`: Returns a pointer to the value if found, or `nullptr` if not.
* `contains(key)`: Returns a boolean indicating if the key exists in the list.
* `size()`: Returns the current number of nodes in the list.

#### Operators
* `operator==` / `operator!=`: Compares two linked lists for exact equality of key-value pairs.

---

### 2. HashFunctor Class

You must implement a function object to generate hash values.

* **Template Specializations**: Implement explicit specializations of `size_t operator()(T Key)` for `int`, `float`, and `std::string`.

---

### 3. HashMap Class

The `HashMap` class manages an array of `LinkedList` buckets of fixed size `N` using Separate Chaining.

#### Constructors & Destructors
* `HashMap()`: Default initialization setting up the empty buckets.
* `~HashMap()`: Cleanup of any resources.
* `operator=(const HashMap &other)` `operator=(HashMap &&other)`: Copy and Move Operator ¯\_(ツ)_/¯

#### Modifiers
* `insert(key, value)`: Hashes the key, finds the correct bucket, and inserts the pair.
* `erase(key)`: Hashes the key and removes it from the corresponding bucket.
* `clear()`: Clears all buckets in the array.

#### Accessors & Utilities
* `at(key)`: Both const and non-const versions which throw error.
* `operator[](key)`: Returns a reference to the value. Should behave similar to `std::unordered_map []`.
* `contains(key)`: Checks if the key exists in the hash map.
* `empty()`: Returns `true` if the hash map contains zero elements.
* `size()`: Returns the total number of elements across all buckets.

#### Operators
* `operator==` / `operator!=`: Compares two hash maps for exact equality.

---

# C++ Learning Resources & Curriculum

> **Note on Learning:** The topics below represent an exhaustive list of core concepts we expect you to learn. However, you are **not limited** to the provided links—these are simply starting points designed to be helpful. Please use any tools and resources at your disposal to master these subjects.

---

## 1. C++ Basics

**Recommended Resources:**
* [C++ Basics](https://progclubiitm.com/pc-1010-1020/) — *Slider of our sessions on basics.*

## 2. Understanding OOP

**Topics Covered:**
* Data as an object with behavior
* Classes & Structs
* Constructors & Destructors
* Member Variables and Functions
* Access Specifiers
* Operator and Function Overloading
* `const` variables and functions

**Recommended Resources:**
* [Object-Oriented Programming in C++](https://www.geeksforgeeks.org/cpp/object-oriented-programming-in-cpp/)
* [Understanding Object-Oriented Programming in C++](https://medium.com/@lokeshbihani99/understanding-object-oriented-programming-in-c-part-1-949cb698eb05)
* [Constructors in C++](https://www.geeksforgeeks.org/cpp/constructors-c/)
* [Operator Overloading in C++](https://www.geeksforgeeks.org/cpp/operator-overloading-cpp/)

---

## 3. Memory Management

**Topics Covered:**
* Heap and Stack
* LValue and RValue references
* The Rule of 5
* Deep vs. Shallow Copy
* Move Semantics (`std::move`)

**Recommended Resources:**
* [Copy Constructor in C++](https://www.geeksforgeeks.org/cpp/copy-constructor-in-cpp/)
* [Move Constructors in C++](https://www.geeksforgeeks.org/cpp/move-constructors-in-c-with-examples/)

---

## 4. C++ Templates

**Topics Covered:**
* Generic Programming Concepts
* Class Templates and Type Parameters (`typename T`)
* Template Specialization

**Recommended Resources:**
* [Templates in C++](https://www.geeksforgeeks.org/cpp/templates-cpp/)
* [Template Specialization in C++](https://www.geeksforgeeks.org/cpp/template-specialization-c/)

---

## 5. Functors

**Topics Covered:**
* Function Pointers
* Functors
* Overloading `operator()`

**Recommended Resources:**
* [Function Pointers](https://www.learncpp.com/cpp-tutorial/function-pointers/)
* [Functors in C++](https://www.geeksforgeeks.org/functors-in-cpp/)

---

## 6. Linked Lists

**Topics Covered:**
* Singly Linked Lists
* Node Structure (Data and `next` pointer)
* Head Pointer Management
* List Traversal and Searching
* Dynamic Insertion
* Safe Deletion and Unlinking Nodes

**Recommended Resources:**
* [Singly Linked List in C++](https://prepinsta.com/cpp-program/singly-linked-list/)

---

## 7. Separately Chained Hash Tables

**Topics Covered:**
* Key-Value Pairs
* Hash Functions & Hash Collisions
* Collision Resolution: Separate Chaining
* `at()` vs `[]`
* `insert()` vs `emplace()`

**Recommended Resources:**
* [Hash Table Implementation using Separate Chaining](https://www.geeksforgeeks.org/dsa/implementation-of-hash-table-in-c-using-separate-chaining/)
* [GeeksforGeeks: `unordered_map` in C++ STL](https://www.geeksforgeeks.org/cpp/unordered_map-in-cpp-stl/)


