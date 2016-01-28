# Darts-clone Interface

## Abstract

Darts-clone is a header library and it requires only one header file (`darts.h`). Please install Darts-clone and then insert `#include <darts.h>`, or copy the `darts.h` and insert `#include "darts.h"`. That's all. It's ready to use.

The interface of Darts-clone is almost the same as that of Darts. In most applications, Darts can be replaced with Darts-clone by replacing `darts.h`.

## Dictionary Class

`DoubleArrayImpl` is the interface of Darts-clone. Note that other classes should not be accessed from outside. `DoubleArray` is the typical instance of `DoubleArrayImpl`. It uses `int` as the type of values and it is suitable for most cases.

```cpp
namespace Darts {

class DoubleArray {
 public:
  typedef int value_type;
  typedef char key_type;
  typedef value_type result_type;for compatibility.

  struct result_pair_type {
    value_type value;
    std::size_t length;
  };

  DoubleArray();
  ~DoubleArray();

  void set_array(const void *ptr,
                 std::size_t size = 0);
  const void *array() const;

  void clear();

  std::size_t unit_size() const;
  std::size_t size() const;
  std::size_t total_size() const;
  std::size_t nonzero_size() const;

  int build(std::size_t num_keys,
            const key_type * const *keys,
            const std::size_t *lengths = NULL,
            const value_type *values = NULL,
            int (*progress_func)(std::size_t, std::size_t) = NULL);

  int open(const char *file_name,
           const char *mode = "rb",
           std::size_t offset = 0,
           std::size_t size = 0);

  int save(const char *file_name,
           const char *mode = "wb",
           std::size_t offset = 0) const;

  template <class U>
  void exactMatchSearch(const key_type *key,
                        U &result,
                        std::size_t length = 0,
                        std::size_t node_pos = 0) const;
  template <class U>
  U exactMatchSearch(const key_type *key,
                     std::size_t length = 0,
                     std::size_t node_pos = 0) const;

  template <class U>
  std::size_t commonPrefixSearch(const key_type *key,
                                 U *results,
                                 std::size_t max_num_results,
                                 std::size_t length = 0,
                                 std::size_t node_pos = 0) const;

  value_type traverse(const key_type *key,
                      std::size_t &node_pos,
                      std::size_t &key_pos,
                      std::size_t length = 0) const;

 private:
Disallows copy and assignment.
  DoubleArray(const DoubleArray &);
  DoubleArray &operator=(const DoubleArray &);
};

}namespace Darts
```

### Template Arguments

`DoubleArrayImpl` has 4 template arguments but only the 3rd one is used as the type of values. Note that the given `T` is used only from outside, and the internal value type is not changed from `Darts::Details::value_type`. In `build()`, given values are casted from `T` to `Darts::Details::value_type` by using `static_cast`. On the other hand, values are casted from `Darts::Details::value_type` to `T` in searching dictionaries.

### Types

```cpp
struct result_pair_type {
  value_type value;
  std::size_t length;
};

void set_result(value_type *result, value_type value, std::size_t) const;
void set_result(result_pair_type *result,
                value_type value, std::size_t length) const;
```

`DoubleArrayImpl` has 2 kinds of `set_result()`s. The 1st `set_result()` is to set a value to a `value_type`. The 2nd `set_result()` is to set a value and a length to a `result_pair_type`. By using `set_result()`s, search methods can return the 2 kinds of results in the same way.

The 1st `set_result()` takes a length as the 3rd argument but it is not used. If a compiler does a good job, codes for getting the length may be removed.

The 2nd `set_result()` uses both `value` and `length`.

### Methods

#### Constructor and Desctuctor

```cpp
DoubleArray();
```

The constructor initializes member variables with `0` and `NULL`s.

```cpp
~DoubleArray();
```

The destructor frees memory allocated for units and then initializes member variables with `0` and `NULL`s.

#### Set/Get Array

```cpp
void set_array(const void *ptr,
               std::size_t size = 0);
```

`set_array()` calls `clear()` in order to free memory allocated to the old array and then sets a new array. This function is useful to set a memory-mapped array. Note that the array set by `set_array()` is not freed in `clear()` and the destructor of `DoubleArrayImpl`.

`set_array()` can also set the size of the new array but the size is not used in search methods. So it works well even if the 2nd argument is `0` or omitted. Remember that `size()` and `total_size()` returns `0` in such a case.

```cpp
const void *array() const;
```

`array()` returns a pointer to the array of units.

#### Free Memory

```cpp
void clear();
```

`clear()` frees memory allocated to units and then initializes member variables with `0` and `NULL`s. Note that `clear()` does not free memory if the array of units was set by `set_array()`. In such a case, `array_` is not `NULL` and `buf_` is `NULL`.

#### Get Size

```cpp
std::size_t unit_size() const;
std::size_t size() const;
std::size_t total_size() const;
std::size_t nonzero_size() const;
```

`unit_size()` returns the size of each unit. The size must be `4` bytes.

`size()` returns the number of units. It can be `0` if `set_array()` is used.

`total_size()` returns the number of bytes allocated to the array of units. It can be `0` if `set_array()` is used.

`nonzero_size()` exists for compatibility. It always returns the number of units because it takes long time to count the number of non-zero units.

#### Build Dictionary

```cpp
int build(std::size_t num_keys,
          const key_type * const *keys,
          const std::size_t *lengths = NULL,
          const value_type *values = NULL,
          int (*progress_func)(std::size_t, std::size_t) = NULL);
```

`build()` constructs a dictionary from given key-value pairs. If `lengths` is `NULL`, `keys` is handled as an array of zero-terminated strings. If `values` is `NULL`, the index in `keys` is associated with each key, i.e. the `i`th key has `(i - 1)` as its value.

Note that the key-value pairs must be arranged in key order and the values must not be negative. Also, if there are duplicate keys, only the first pair will be stored in the resultant dictionary.

`progress_func` is a pointer to a callback function. If it is not `NULL`, it will be called in `build()` so that the caller can check the progress of dictionary construction. For details, please see the definition of `Darts::Details::progress_func_type`.

The return value of `build()` is `0`, and it indicates the success of the operation. Otherwise, `build()` throws a `Darts::Exception`, which is a derived class of `std::exception`.

`build()` uses another construction algorithm if `values` is not `NULL`. In this case, Darts-clone uses a Directed Acyclic Word Graph (DAWG) instead of a trie because a DAWG is likely to be more compact than a trie.

#### Load Dictionary

```cpp
int open(const char *file_name,
         const char *mode = "rb",
         std::size_t offset = 0,
         std::size_t size = 0);
```

`open()` reads an array of units from the specified file. And if it goes well, the old array will be freed and replaced with the new array read from the file. `offset` specifies the number of bytes to be skipped before reading an array. `size` specifies the number of bytes to be read from the file. If the `size` is `0`, the whole file will be read.

open() returns 0 iff the operation succeeds. Otherwise, it returns a non-zero value or throws a Darts::Exception. The exception is thrown when and only when a memory allocation fails.

#### Save Dictionary

```cpp
int save(const char *file_name,
         const char *mode = "wb",
         std::size_t offset = 0) const;
```

`save()` writes the array of units into the specified file. `offset` specifies the number of bytes to be skipped before writing the array. `open()` returns `0` iff the operation succeeds. Otherwise, it returns a non-zero value.

#### Exact Match Search

```cpp
template <class U>
void exactMatchSearch(const key_type *key,
                      U &result,
                      std::size_t length = 0,
                      std::size_t node_pos = 0) const;
```

The 1st `exactMatchSearch()` tests whether the given key exists or not, and if it exists, its value and length are set to `result`. Otherwise, the value and the length of `result` are set to `-1` and `0` respectively. Note that if `length` is `0`, `key` is handled as a zero-terminated string. `node_pos` specifies the start position of matching. This argument enables the combination of `exactMatchSearch()` and `traverse()`. For example, if you want to test `"xyzA"`, `"xyzBC"`, and `"xyzDE"`, you can use `traverse()` to get the node position corresponding to `"xyz"` and then you can use `exactMatchSearch()` to test `"A"`, `"BC"`, and `"DE"` from that position. Note that the length of `result` indicates the length from the `node_pos`. In the above example, the lengths are `{ 1, 2, 2 }`, not `{ 4, 5, 5 }`.

```cpp
template <class U>
U exactMatchSearch(const key_type *key,
                   std::size_t length = 0,
                   std::size_t node_pos = 0) const;
```

The 2nd `exactMatchSearch()` returns a result instead of updating the 2nd argument. So, the following `exactMatchSearch()` has only 3 arguments.

#### Prefix Search

```cpp
template <class U>
std::size_t commonPrefixSearch(const key_type *key,
                               U *results,
                               std::size_t max_num_results,
                               std::size_t length = 0,
                               std::size_t node_pos = 0) const;
```

`commonPrefixSearch()` searches for keys which match a prefix of the given string. If `length` is `0`, `key` is handled as a zero-terminated string. The values and the lengths of at most `max_num_results` matched keys are stored in `results`. `commonPrefixSearch()` returns the number of matched keys. Note that the return value can be larger than `max_num_results` if there are more than `max_num_results` matches. If you want to get all the results, allocate more spaces and call `commonPrefixSearch()` again. `node_pos` works as well as in `exactMatchSearch()`.

```cpp
value_type traverse(const key_type *key,
                    std::size_t &node_pos,
                    std::size_t &key_pos,
                    std::size_t length = 0) const;
```

In Darts-clone, a dictionary is a deterministic finite-state automaton (DFA) and `traverse()` tests transitions on the DFA. The initial state is `node_pos` and `traverse()` chooses transitions labeled `key[key_pos]`, `key[key_pos + 1]`, ... in order. If there is not a transition labeled `key[key_pos + i]`, `traverse()` terminates the transitions at that state and returns `-2`. Otherwise, `traverse()` ends without a termination and returns `-1` or a nonnegative value, `-1` indicates that the final state was not an accept state. When a nonnegative value is returned, it is the value associated with the final accept state. That is, `traverse()` returns the value associated with the given key if it exists. Note that traverse() updates `node_pos` and `key_pos` after each transition.

#### Copy and Assignment

```cpp
DoubleArray(const DoubleArray &);
DoubleArray &operator=(const DoubleArray &);
```

`DoubleArray`'s copy constructor and assignment operator are disabled.
