#include <darts.h>

#include <cstdio>
#include <fstream>
#include <iostream>

#include "./benchmark-config.h"
#include "./lexicon.h"
#include "./timer.h"

namespace {

int progress_bar(std::size_t current, std::size_t total) {
  static const char bar[] = "*******************************************";
  static const int scale = sizeof(bar) - 1;

  static int prev = 0;

  int cur_percentage = static_cast<int>(100.0 * current / total);
  int bar_len = static_cast<int>(1.0 * current * scale / total);

  if (prev != cur_percentage) {
    std::fprintf(stderr, "Making double-array: %3d%% |%.*s%*s|",
        cur_percentage, bar_len, bar, scale - bar_len, "");
    if (cur_percentage >= 100) {
      std::fprintf(stderr, "\n");
    } else {
      std::fprintf(stderr, "\r");
    }
    std::fflush(stderr);
  }

  prev = cur_percentage;

  return 1;
};

void benchmark_exact_match_search(const Darts::DoubleArray &dic,
    const Darts::Lexicon &lexicon) {
  Darts::Timer timer;

  std::size_t num_tries = 0;
  do {
    for (std::size_t i = 0; i < lexicon.size(); ++i) {
      Darts::DoubleArray::value_type value;
      dic.exactMatchSearch(lexicon[i], value);
      if (value == -1) {
        std::cerr << "error: failed to find key: "
            << lexicon[i] << std::endl;
        std::exit(1);
      }
    }
    ++num_tries;
  } while (timer.elapsed() < 1.0);

  std::printf(" %6.1fns", 1e+9 * timer.elapsed()
      / (lexicon.size() * num_tries));
  std::fflush(stdout);
}

void benchmark_common_prefix_search(const Darts::DoubleArray &dic,
    const Darts::Lexicon &lexicon) {
  Darts::Timer timer;

  std::size_t num_tries = 0;

  static const std::size_t MAX_NUM_RESULTS = 256;
  Darts::DoubleArray::value_type results[MAX_NUM_RESULTS];
  do {
    for (std::size_t i = 0; i < lexicon.size(); ++i) {
      std::size_t num_matches = dic.commonPrefixSearch(
          lexicon[i], results, MAX_NUM_RESULTS);
      if (num_matches < 1) {
        std::cerr << "error: failed to find prefix keys of: "
            << lexicon[i] << std::endl;
        std::exit(1);
      }
    }
    ++num_tries;
  } while (timer.elapsed() < 1.0);

  std::printf(" %7.1fns", 1e+9 * timer.elapsed()
      / (lexicon.size() * num_tries));
  std::fflush(stdout);
}

void benchmark_traverse(const Darts::DoubleArray &dic,
    const Darts::Lexicon &lexicon) {
  Darts::Timer timer;

  std::size_t num_tries = 0;
  do {
    for (std::size_t i = 0; i < lexicon.size(); ++i) {
      const char *key = lexicon[i];

      std::size_t id = 0;
      std::size_t key_pos = 0;
      Darts::DoubleArray::value_type result = 0;
      for (std::size_t j = 0; key[j] != '\0'; ++j) {
        result = dic.traverse(key, id, key_pos, j + 1);
        if (result == -2) {
          std::cerr << "error: failed to traverse key: "
              << key << std::endl;
          std::exit(1);
        }
      }
      if (result < 0) {
        std::cerr << "error: failed to find key: " << key << std::endl;
        std::exit(1);
      }
    }
    ++num_tries;
  } while (timer.elapsed() < 1.0);

  std::printf(" %6.1fns", 1e+9 * timer.elapsed()
      / (lexicon.size() * num_tries));
  std::fflush(stdout);
}

void benchmark_lexicon(const Darts::BenchmarkConfig &config,
    const Darts::Lexicon &lexicon, Darts::DoubleArray *dic) {
  Darts::Timer timer;

  if (dic->build(lexicon.size(), lexicon.keys(), NULL,
      lexicon.values(), progress_bar) != 0) {
    std::cerr << "error: failed to build dictionary" << std::endl;
    std::exit(1);
  }

  std::printf("+--------+--------+-----------------+-------------------+"
      "-----------------+\n");

  std::printf(" %8s %8s", "size", "build");
  if (config.benchmarks_exact_match_search()) {
    std::printf(" %17s", "exactMatchSearch");
  }
  if (config.benchmarks_common_prefix_search()) {
    std::printf(" %19s", "commonPrefixSearch");
  }
  if (config.benchmarks_traverse()) {
    std::printf(" %17s", "traverse");
  }
  std::printf("\n");

  std::printf(" %8s %8s", "", "");
  if (config.benchmarks_exact_match_search()) {
    std::printf(" %8s %8s", "sorted", "random");
  }
  if (config.benchmarks_common_prefix_search()) {
    std::printf(" %9s %9s", "sorted", "random");
  }
  if (config.benchmarks_traverse()) {
    std::printf(" %8s %8s", "sorted", "random");
  }
  std::printf("\n");

  std::printf("+--------+--------+-----------------+-------------------+"
      "-----------------+\n");

  Darts::Lexicon randomized_lexicon(lexicon);
  randomized_lexicon.randomize();

  std::printf(" %6ukb", static_cast<unsigned int>(dic->total_size() / 1000));
  std::printf(" %6.0fns", 1e+9 * timer.elapsed() / lexicon.size());
  std::fflush(stdout);

  benchmark_exact_match_search(*dic, lexicon);
  benchmark_exact_match_search(*dic, randomized_lexicon);

  benchmark_common_prefix_search(*dic, lexicon);
  benchmark_common_prefix_search(*dic, randomized_lexicon);

  benchmark_traverse(*dic, lexicon);
  benchmark_traverse(*dic, randomized_lexicon);

  std::printf("\n");
  std::printf("+--------+--------+-----------------+-------------------+"
      "-----------------+\n");
}

}  // namespace

int main(int argc, char *argv[]) {
  try {
    Darts::BenchmarkConfig config;
    config.parse(argc, argv);

    Darts::Lexicon lexicon;
    if (std::strcmp(config.lexicon_file_name(), "-") != 0) {
      std::ifstream file(config.lexicon_file_name());
      if (!file) {
        std::cerr << "error: failed to open lexicon file: "
            << config.lexicon_file_name() << std::endl;
        std::exit(1);
      }
      lexicon.read(&file);
    } else {
      lexicon.read(&std::cin);
    }

    // Note that split() of <Darts::Lexicon> may cause a problem if the lexicon
    // contains control characters.
    lexicon.sort();
    if (config.has_values()) {
      lexicon.split();
    }

    Darts::DoubleArray dic;
    benchmark_lexicon(config, lexicon, &dic);
  } catch (const std::exception &ex) {
    std::cerr << "exception: " << ex.what() << std::endl;
    throw ex;
  }

  return 0;
}
