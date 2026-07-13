#include <darts.h>

#include <cassert>
#include <cstddef>
#include <iostream>

// Exercises the helpers adapted from google/sentencepiece commit d685ef31:
// DoubleArray::validate() and DoubleArray::copy_array().
int main() {
  Darts::DoubleArray array;
  const char *keys[] = {
    "a",
    "ab",
    "b",
  };
  const int values[] = {
    0,
    1,
    2,
  };

  assert(array.build(3, keys, NULL, values) == 0);

  // validate() accepts a well-formed array. With max_value_limit = 3 every
  // leaf value (0, 1, 2) is in bounds, but with a limit of 2 the value 2 is
  // out of bounds and validation must fail.
  assert(array.validate(3));
  assert(!array.validate(2));
  std::cout << "validate(): ok" << std::endl;

  Darts::DoubleArray::result_pair_type result;
  array.exactMatchSearch("ab", result);
  assert(result.value == 1 && result.length == 2);

  // copy_array() takes ownership of a private copy of the serialized units, so
  // the copy searches identically and does not alias the source array.
  Darts::DoubleArray copied;
  copied.copy_array(array.array(), array.total_size());
  assert(copied.validate(3));
  assert(copied.array() != array.array());

  copied.exactMatchSearch("ab", result);
  assert(result.value == 1 && result.length == 2);
  std::cout << "copy_array() with array(): ok" << std::endl;

  // copy_array() rounds the byte count up to a whole number of units, so five
  // bytes are padded out to two units.
  const char raw_bytes[] = {0, 0, 0, 0, 0};
  Darts::DoubleArray padded_copy;
  padded_copy.copy_array(raw_bytes, sizeof(raw_bytes));
  assert(padded_copy.size() == 2);
  std::cout << "copy_array() padding: ok" << std::endl;

  return 0;
}
