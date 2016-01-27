#ifndef DARTS_LEXICON_H_
#define DARTS_LEXICON_H_

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <limits>
#include <vector>

#include "./mersenne-twister.h"

namespace Darts {

class Lexicon {
 private:
  class KeyComparer {
   public:
    bool operator()(const char *lhs, const char *rhs) const {
      while (*lhs != '\0' && *lhs == *rhs) {
        ++lhs, ++rhs;
      }
      return static_cast<unsigned char>(*lhs) <
          static_cast<unsigned char>(*rhs);
    }
  };

 public:
  Lexicon() : keys_(), values_(), chunks_(), total_(0) {}
  Lexicon(const Lexicon &lexicon) : keys_(lexicon.keys_),
    values_(), chunks_(), total_(lexicon.total_) {}
  ~Lexicon() { clear(); }

  void read(std::istream *in);

  const char *operator[](std::size_t id) const {
    return keys_[id];
  }

  const char * const *keys() const {
    return keys_.empty() ? NULL : &keys_[0];
  }
  const int *values() const {
    return values_.empty() ? NULL : &values_[0];
  }

  std::size_t size() const {
    return keys_.size();
  }
  std::size_t total() const {
    return total_;
  }

  // sort() arranges keys in order. Values are not affected.
  void sort() {
    std::stable_sort(keys_.begin(), keys_.end(), KeyComparer());
  }
  // randomize() shuffles keys. Values are not affected.
  void randomize() {
    Darts::MersenneTwister mt(
        static_cast<Darts::MersenneTwister::int_type>(std::time(NULL)));
    std::random_shuffle(keys_.begin(), keys_.end(), mt);
  }

  void split();

  void clear();

 private:
  enum { CHUNK_SIZE = 1 << 12 };

  std::vector<char *> keys_;
  std::vector<int> values_;
  std::vector<char *> chunks_;
  std::size_t total_;

  // Disallows assignment.
  Lexicon &operator=(const Lexicon &);
};

inline void Lexicon::read(std::istream *in) {
  clear();

  std::size_t begin = 0;
  std::size_t avail = 0;
  while (*in) {
    chunks_.push_back(NULL);
    char *chunk = chunks_.back() = new char[CHUNK_SIZE];

    if (avail == CHUNK_SIZE) {
      std::cerr << "failed to read key: too long line" << std::endl;
      std::exit(1);
    }

    if (avail > 0) {
      std::memcpy(chunk, chunks_[chunks_.size() - 2] + begin, avail);
    }
    std::size_t pos = avail;

    in->read(chunk + avail, CHUNK_SIZE - avail);
    begin = 0;
    avail += in->gcount();

    while (pos < avail) {
      if (chunk[pos] == '\r' || chunk[pos] == '\n') {
        std::size_t length = pos - begin;
        if (length > 0) {
          keys_.push_back(chunk + begin);
        }
        begin += length + 1;
        chunk[pos] = '\0';
        total_ += length;
      }
      ++pos;
    }
    avail -= begin;
  }
}

inline void Lexicon::split() {
  if (!values_.empty()) {
    return;
  }

  values_.resize(keys_.size(), 0);
  for (std::size_t i = 0; i < keys_.size(); ++i) {
    char *tab = NULL;
    char *ptr = keys_[i];
    while (*ptr != '\0') {
      if (*ptr == '\t') {
        tab = ptr;
      }
      ++ptr;
    }
    if (tab == NULL) {
      continue;
    }

    total_ -= ptr - tab;
    *tab++ = '\0';
    if (*tab == '\0') {
      std::cerr << "error: failed to split keys: no value" << std::endl;
      std::exit(1);
    }

    char *value_end;
    long value = std::strtol(tab, &value_end, 10);
    if (*value_end != '\0') {
      std::cerr << "error: failed to split keys: invalid characters: \""
          << tab << "\" (" << value << ')' << std::endl;
      std::exit(1);
    } else if (value < 0) {
      std::cerr << "error: failed to split keys: negative value: \""
          << tab << "\" (" << value << ')' << std::endl;
      std::exit(1);
    } else if (value > std::numeric_limits<int>::max()) {
      std::cerr << "error: failed to split keys: too large value: \""
          << tab << "\" (" << value << ')' << std::endl;
      std::exit(1);
    }
    values_[i] = static_cast<int>(value);
  }
}

inline void Lexicon::clear() {
  keys_.clear();
  values_.clear();
  for (std::size_t i = 0; i < chunks_.size(); ++i) {
    if (chunks_[i] != NULL) {
      delete[] chunks_[i];
      chunks_[i] = NULL;
    }
  }
  chunks_.clear();
  total_ = 0;
}

}  // namespace Darts

#endif  // DARTS_LEXICON_H_
