#include <cstddef>
#include <iostream>

class TestClass{
private:
    int* value = nullptr;

public:
    TestClass() {
        std::cout << "nullptr :Created\n";
    }

    TestClass(int v): value(new int(v)) {
        std::cout << v << " :Created\n";
    }

    ~TestClass() {
        clear();
    }

    TestClass(const TestClass &other){
        if(other.value){
            value = new int(*other.value);
            std::cout << *value << ": Copied\n";
        } else {
            value = nullptr;
            std::cout << "nullptr: Copied\n";
        }
    }

    TestClass(TestClass &&other) noexcept : value(other.value) { 
        if(value)
            std::cout << *value << ": Moved\n";
        else
            std::cout << "nullptr: Moved\n";

        other.value = nullptr;
    }

    TestClass& operator=(const TestClass &other){
        if(this != &other){
            clear();
            if(other.value){
                value = new int(*other.value);
                std::cout << *value << ": Copied\n";
            } else {
                value = nullptr;
                std::cout << "nullptr: Copied\n";
            }
        }
        return *this;
    }

    TestClass& operator=(TestClass&& other) noexcept{
        if (this != &other){
            clear();

            if(other.value)
                std::cout << *other.value << ": Moved\n";
            else
                std::cout << "nullptr: Moved\n";

            value = other.value;
            other.value = nullptr;
        }
        return *this;
    }
    
    int get_val() const { 
        return value ? *value : 0;   // safe fallback
    }

private:
    void clear(){
        if(value){
            std::cout << *value << ": Deleted\n";
            delete value;
            value = nullptr;   // CRITICAL
        } else {
            std::cout << "nullptr: Deleted\n";
        }
    }
};




///-------------------------------- DO NOT LOOK ABOVE THIS LINE, IT'S FOR TESTING --------------------------------///
///------------------ IF YOU DO SO MEDUSA WILL COME TO YOU IN YOUR DREAMS AND TURN TO STONE :D ------------------///



/// THE 3 CLASSES BELOW IS THE TEMPLATE DECLARATION OF THE CLASSES, FUNCTORS WE EXPECT YOU TO IMPLEMENT
/// READ UPON THE RESOURCES PROVIDED AND DO THE IMPLEMENTATION

template <typename KeyType, typename ValueType>
class LinkedList{
public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList &other);
    LinkedList(LinkedList &&other) noexcept;
    LinkedList &operator=(const LinkedList &other);
    LinkedList &operator=(LinkedList &&other) noexcept;

    void insert(const KeyType &key, const ValueType &value);
    void erase(const KeyType &key);
    void clear();

    const ValueType &at(const KeyType &key) const;
    ValueType &at(const KeyType &key);
    ValueType *find(const KeyType &key);

    bool operator==(const LinkedList &other) const;
    bool operator!=(const LinkedList &other) const;

    [[nodiscard]] bool contains(const KeyType &key) const;
    [[nodiscard]] size_t size() const;

private:
    struct Node{
        KeyType key;
        ValueType value;
        Node *next;
    };
    Node *head = nullptr;
    size_t n = 0;
};

template <size_t N, typename KeyType, typename ValueType, typename HashFunc>
class HashMap{
public:
    HashMap();
    ~HashMap();

    HashMap &operator=(const HashMap &other);
    HashMap &operator=(HashMap &&other) noexcept;

    void insert(const KeyType &key, const ValueType &value);
    void erase(const KeyType &key);
    void clear();

    const ValueType &at(const KeyType &key) const;
    ValueType &at(const KeyType &key);
    ValueType &operator[](const KeyType &key);

    bool operator==(const HashMap &other) const;
    bool operator!=(const HashMap &other) const;

    [[nodiscard]] bool contains(const KeyType &key) const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;

private:
    HashFunc hash;
    using Bucket = LinkedList<KeyType, ValueType>;
    Bucket buckets[N];
};

// IMPLEMENT HASH FUNCTIONS FOR INT, FLOAT AND STRING
template<typename T>
class HashFunctor{
public:
    size_t operator()(T Key);
};


///---------------------- DO NOT TOUCH/MODIFY ABOVE THIS LINE, IT'S FOR YOUR REFERENCE ----------------------///
///------------------ IF YOU DO SO THE CURSE OF KING MIDUS WILL TURN IT INTO BROKEN CODE :P------------------///

// WRITE THE IMPLEMENTATION OF THE CLASSES HERE





// ---------- UnComment the features as you finish implementing them, this allows partial submisions without crashing ----------///

//Obviously some functions are interlinked

// // ---------- LINKED LIST ----------

// // constructors / destructors
// #define LL_CTOR_DEFAULT
// #define LL_DTOR
// #define LL_CTOR_COPY
// #define LL_CTOR_MOVE
// #define LL_ASSIGN_COPY
// #define LL_ASSIGN_MOVE

// // modifiers
// #define LL_INSERT
// #define LL_ERASE
// #define LL_CLEAR

// // access
// #define LL_AT_CONST
// #define LL_AT
// #define LL_FIND

// // utilities
// #define LL_CONTAINS
// #define LL_SIZE

// // operators
// #define LL_EQ
// #define LL_NEQ


// // ---------- HASH FUNCTOR ----------
// #define FUNCTOR_INT
// #define FUNCTOR_FLOAT
// #define FUNCTOR_STRING


// // ---------- HASH MAP ----------

// // constructors / destructors
// #define HM_CTOR
// #define HM_DTOR
// #define HM_ASSIGN_COPY
// #define HM_ASSIGN_MOVE

// // modifiers
// #define HM_INSERT
// #define HM_ERASE
// #define HM_CLEAR

// // access
// #define HM_AT_CONST
// #define HM_AT
// #define HM_BRACKET   // operator[]
// #define HM_CONTAINS

// // utilities
// #define HM_EMPTY
// #define HM_SIZE

// // operators
// #define HM_EQ
// #define HM_NEQ

int main(){

#if defined(HM_CTOR) && defined(FUNCTOR_INT)
    HashMap<5,int,int,HashFunctor<int>> h;
#endif

#ifdef LL_CTOR_DEFAULT
    LinkedList<int,int> l;
#endif

    int q; 
    if (!(std::cin >> q)) return 0;

    while(q--){
        std::string type, op;
        std::cin >> type >> op;

        // ==========================================
        // ---------- LINKED LIST QUERIES -----------
        // ==========================================
        if(type == "LL"){

            if(op == "insert"){
                int k, v; 
                std::cin >> k >> v; // Always consume input
#if defined(LL_CTOR_DEFAULT) && defined(LL_INSERT)
                l.insert(k, v);
#else
                std::cout << "LL insert not enabled\n";
#endif
            }

            else if(op == "erase"){
                int k; 
                std::cin >> k; // Always consume input
#if defined(LL_CTOR_DEFAULT) && defined(LL_ERASE)
                l.erase(k);
#else
                std::cout << "LL erase not enabled\n";
#endif
            }

            else if(op == "clear"){
#if defined(LL_CTOR_DEFAULT) && defined(LL_CLEAR)
                l.clear();
#else
                std::cout << "LL clear not enabled\n";
#endif
            }

            else if(op == "at"){
                int k; 
                std::cin >> k; // Always consume input
#if defined(LL_CTOR_DEFAULT) && defined(LL_AT)
                std::cout << l.at(k) << "\n";
#else
                std::cout << "LL at not enabled\n";
#endif
            }

            else if(op == "find"){
                int k; 
                std::cin >> k; // Always consume input
#if defined(LL_CTOR_DEFAULT) && defined(LL_FIND)
                auto p = l.find(k);
                if(p) std::cout << *p << "\n";
                else std::cout << "NOT FOUND\n";
#else
                std::cout << "LL find not enabled\n";
#endif
            }

            else if(op == "contains"){
                int k; 
                std::cin >> k; // Always consume input
#if defined(LL_CTOR_DEFAULT) && defined(LL_CONTAINS)
                std::cout << (l.contains(k) ? "YES\n" : "NO\n");
#else
                std::cout << "LL contains not enabled\n";
#endif
            }

            else if(op == "size"){
#if defined(LL_CTOR_DEFAULT) && defined(LL_SIZE)
                std::cout << l.size() << "\n";
#else
                std::cout << "LL size not enabled\n";
#endif
            }

            else if(op == "compare"){
#if defined(LL_CTOR_DEFAULT) && defined(LL_EQ) && defined(LL_CTOR_COPY)
                LinkedList<int,int> other = l;
                std::cout << (l == other ? "YES\n" : "NO\n");
#else
                std::cout << "LL compare/copy not enabled\n";
#endif
            }
        }

        // ==========================================
        // ------------ HASH MAP QUERIES ------------
        // ==========================================
        else if(type == "HM"){

            if(op == "insert"){
                int k, v; 
                std::cin >> k >> v; // Always consume input
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_INSERT)
                h.insert(k, v);
#else
                std::cout << "HM insert not enabled\n";
#endif
            }

            else if(op == "erase"){
                int k; 
                std::cin >> k; // Always consume input
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_ERASE)
                h.erase(k);
#else
                std::cout << "HM erase not enabled\n";
#endif
            }

            else if(op == "clear"){
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_CLEAR)
                h.clear();
#else
                std::cout << "HM clear not enabled\n";
#endif
            }

            else if(op == "at"){
                int k; 
                std::cin >> k; // Always consume input
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_AT)
                std::cout << h.at(k) << "\n";
#else
                std::cout << "HM at not enabled\n";
#endif
            }
            
            else if(op == "bracket"){
                int k, v; 
                std::cin >> k >> v; // Always consume input
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_BRACKET)
                h[k] = v;
#else
                std::cout << "HM bracket not enabled\n";
#endif
            }

            else if(op == "contains"){
                int k; 
                std::cin >> k; // Always consume input
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_CONTAINS)
                std::cout << (h.contains(k) ? "YES\n" : "NO\n");
#else
                std::cout << "HM contains not enabled\n";
#endif
            }

            else if(op == "empty"){
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_EMPTY)
                std::cout << (h.empty() ? "YES\n" : "NO\n");
#else
                std::cout << "HM empty not enabled\n";
#endif
            }

            else if(op == "size"){
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_SIZE)
                std::cout << h.size() << "\n";
#else
                std::cout << "HM size not enabled\n";
#endif
            }

            else if(op == "compare"){
#if defined(HM_CTOR) && defined(FUNCTOR_INT) && defined(HM_EQ) && defined(HM_ASSIGN_COPY)
                HashMap<5,int,int,HashFunctor<int>> other = h;
                std::cout << (h == other ? "YES\n" : "NO\n");
#else
                std::cout << "HM compare/copy not enabled\n";
#endif
            }
        }
    }
    return 0;
}