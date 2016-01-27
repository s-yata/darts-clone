#ifndef DARTS_MERRSENNE_TWISTER_H_
#define DARTS_MERRSENNE_TWISTER_H_

namespace Darts {

class MersenneTwister {
 public:
  typedef unsigned int int_type;

  explicit MersenneTwister(int_type seed = 0) : mti_(0) {
    init(seed);
  }

  void init(int_type seed) {
    mt_[0]= seed;
    for (mti_ = 1; mti_ < N; ++mti_) {
      mt_[mti_] = 1812433253U * (mt_[mti_ - 1] ^ (mt_[mti_ - 1] >> 30)) + mti_;
    }
  }

  int_type gen();
  int_type operator()(int_type limit) {
    return gen() % limit;
  }

 private:
  enum { N = 624, M = 397 };

  int_type mt_[N];
  int mti_;

  static int_type mag01(int_type id) {
    static const int_type mag01[] = { 0, 0x9908B0DFU };
    return mag01[id & 1];
  }
  static int_type to_upper(int_type value) {
    return value & 0x80000000U;
  }
  static int_type to_lower(int_type value) {
    return value & 0x7FFFFFFFU;
  }

  // Disallows copy and assignment.
  MersenneTwister(const MersenneTwister &);
  MersenneTwister &operator=(const MersenneTwister &);
};

inline MersenneTwister::int_type MersenneTwister::gen() {
  int_type y;
  if (mti_ >= N) {
    int i = 0;
    for (i = 0; i < N - M; i++) {
      y = to_upper(mt_[i]) | to_lower(mt_[i + 1]);
      mt_[i] = mt_[i + M] ^ (y >> 1) ^ mag01(y);
    }
    for (; i < N - 1; i++) {
      y = to_upper(mt_[i]) | to_lower(mt_[i + 1]);
      mt_[i] = mt_[i + (M - N)] ^ (y >> 1) ^ mag01(y);
    }
    y = to_upper(mt_[N - 1]) | to_lower(mt_[0]);
    mt_[N - 1] = mt_[M - 1] ^ (y >> 1) ^ mag01(y);

    mti_ = 0;
  }

  y = mt_[mti_++];

  y ^= (y >> 11);
  y ^= (y << 7) & 0x9D2C5680UL;
  y ^= (y << 15) & 0xEFC60000UL;
  y ^= (y >> 18);
  return y;
}

}  // namespace Darts

#endif  // DARTS_MERRSENNE_TWISTER_H_
