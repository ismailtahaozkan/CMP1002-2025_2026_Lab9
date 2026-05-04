# Dynamic Memory Management & Static Classes

## 1. Concept Overview

In C++, **dynamic memory** allows you to allocate memory on the heap at runtime using `new` and release it using `delete`. Unlike stack variables (which are automatically managed), heap memory persists until you explicitly free it. This is essential when the size of your data is not known at compile time.

When a class manages dynamic memory through a pointer, the default copy behavior (shallow copy) only copies the pointer value — not the data it points to. This means two objects end up sharing the same memory, leading to **double-free** bugs. To fix this, you implement a **copy constructor** and **copy assignment operator** that perform **deep copies**.

**Static class members** belong to the class rather than to any specific instance. They are useful for tracking class-wide information, such as counting how many objects currently exist.

## 2. Key Concepts

- **`new` and `delete`**: Allocate and free single objects on the heap
- **`new[]` and `delete[]`**: Allocate and free arrays on the heap
- **Destructor (`~ClassName`)**: Automatically called when an object goes out of scope; use it to free dynamic memory
- **Shallow copy**: Copies the pointer, not the pointed-to data (default behavior — dangerous with dynamic memory)
- **Deep copy**: Allocates new memory and copies the actual data element by element
- **Copy constructor**: `ClassName(const ClassName& other)` — called when a new object is created from an existing one
- **Copy assignment operator**: `ClassName& operator=(const ClassName& other)` — called when an existing object is overwritten
- **Self-assignment check**: In `operator=`, always check `if (this != &other)` before deleting old data
- **Static member variable**: Declared with `static` inside the class, defined once outside it
- **Static member function**: Can be called without an object; can only access static members
- **RAII (Resource Acquisition Is Initialization)**: A pattern where resources are tied to object lifetime — acquire in the constructor, release in the destructor

## 3. Important Keywords

| Keyword | Explanation |
|---|---|
| `new` | Allocates memory on the heap; returns a pointer |
| `delete` | Frees memory allocated with `new` |
| `new[]` | Allocates an array on the heap |
| `delete[]` | Frees an array allocated with `new[]` |
| `static` | Makes a member belong to the class, not to instances |
| `const` | In copy constructor parameter, prevents modifying the source |
| `&` (reference) | Copy constructor takes a reference to avoid infinite recursion |
| `this` | Pointer to the current object; used in self-assignment check |

## 4. Common Mistakes

1. **Using `delete` instead of `delete[]` for arrays**
   - `new int[10]` must be freed with `delete[]`, not `delete`
   - Wrong: `delete data;` → undefined behavior
   - Right: `delete[] data;`

2. **Forgetting the deep copy**
   - If you don't write a copy constructor, the compiler generates a shallow one
   - Two objects then share the same pointer → crash when both destructors run

3. **No self-assignment check in `operator=`**
   ```cpp
   // BAD: if a = a, this deletes a's own data first!
   IntArray& operator=(const IntArray& other) {
       delete[] data;          // oops, just deleted our own data
       data = new int[other.capacity];
       // ... copying from destroyed memory!
   }
   ```

4. **Forgetting to define static members outside the class**
   ```cpp
   class Tracker {
       static int count; // declaration only
   };
   // Without this line → linker error:
   int Tracker::count = 0;
   ```

5. **Calling `Tracker::objectCreated()` in copy assignment**
   - Copy assignment overwrites an existing object — the object already exists
   - Only constructors (including copy constructor) should call `objectCreated()`

## 5. Mini Examples

### Dynamic Allocation
```cpp
int* arr = new int[5];     // allocate 5 ints on heap
for (int i = 0; i < 5; i++)
    arr[i] = i * 10;
delete[] arr;               // free the memory
arr = nullptr;              // good practice
```

### Deep Copy in Copy Constructor
```cpp
IntArray::IntArray(const IntArray& other) {
    capacity = other.capacity;
    count = other.count;
    data = new int[capacity];           // allocate NEW memory
    for (int i = 0; i < count; i++)
        data[i] = other.data[i];        // copy each element
}
```

### Copy Assignment with Self-Assignment Check
```cpp
IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {               // self-assignment guard
        delete[] data;                  // free old memory
        capacity = other.capacity;
        count = other.count;
        data = new int[capacity];       // allocate new memory
        for (int i = 0; i < count; i++)
            data[i] = other.data[i];
    }
    return *this;
}
```

### Static Class
```cpp
class Counter {
    static int total;
public:
    static void increment() { total++; }
    static int getTotal() { return total; }
};
int Counter::total = 0;  // definition

// Usage (no object needed):
Counter::increment();
cout << Counter::getTotal();  // prints 1
```

## 6. When to Use This

- **Dynamic arrays**: When the size of your data depends on user input or runtime conditions
- **Resource-managing classes**: Any class that owns a file handle, network socket, or heap memory needs a destructor, copy constructor, and copy assignment operator (the **Rule of Three**)
- **Object counting / tracking**: Static members are ideal for tracking how many objects of a class are alive
- **Singleton pattern**: Static members are the foundation of the Singleton design pattern
- **Factory counters**: Tracking total allocations, logging, or generating unique IDs across all instances
