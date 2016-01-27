#ifndef DARTS_BENCHMARK_CONFIG_H_
#define DARTS_BENCHMARK_CONFIG_H_

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace Darts {

class BenchmarkConfig {
 public:
  BenchmarkConfig() : command_(NULL), has_values_(false),
      benchmarks_exact_match_search_(false),
      benchmarks_common_prefix_search_(false), benchmarks_traverse_(false),
      lexicon_file_name_(NULL), dic_file_name_(NULL) {}

  void parse(int argc, char **argv);

  bool has_values() const {
    return has_values_;
  }

  bool benchmarks_exact_match_search() const {
    return benchmarks_exact_match_search_;
  }
  bool benchmarks_common_prefix_search() const {
    return benchmarks_common_prefix_search_;
  }
  bool benchmarks_traverse() const {
    return benchmarks_traverse_;
  }

  const char *lexicon_file_name() const {
    return lexicon_file_name_;
  }
  const char *dic_file_name() const {
    return dic_file_name_;
  }

  void show_usage() const {
    std::cerr << "\nUsage: " << command_
        << " [Options...] [Lexicon] [Dictionary]\n\n"
        "  -h  display this help\n"
        "  -t  use tab separated values\n"
        "  -E  benchmark exactMatchSearch()\n"
        "  -C  benchmark commonPrefixSearch()\n"
        "  -T  benchmark traverse()\n" << std::endl;
  }

 private:
  const char *command_;
  bool has_values_;
  bool benchmarks_exact_match_search_;
  bool benchmarks_common_prefix_search_;
  bool benchmarks_traverse_;
  const char *lexicon_file_name_;
  const char *dic_file_name_;

  // Disallows copy and assignment.
  BenchmarkConfig(const BenchmarkConfig &);
  BenchmarkConfig &operator=(const BenchmarkConfig &);
};

inline void BenchmarkConfig::parse(int argc, char **argv) {
  command_ = argv[0];
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      if (lexicon_file_name_ == NULL) {
        lexicon_file_name_ = argv[i];
      } else if (dic_file_name_ == NULL) {
        dic_file_name_ = argv[i];
      } else {
        std::cerr << "error: too many arguments" << std::endl;
        show_usage();
        std::exit(1);
      }
    } else if (std::strcmp(argv[i], "-h") == 0) {
      show_usage();
      std::exit(0);
    } else if (std::strcmp(argv[i], "-t") == 0) {
      has_values_ = true;
    } else if (std::strcmp(argv[i], "-E") == 0) {
      benchmarks_exact_match_search_ = true;
    } else if (std::strcmp(argv[i], "-C") == 0) {
      benchmarks_common_prefix_search_ = true;
    } else if (std::strcmp(argv[i], "-T") == 0) {
      benchmarks_traverse_ = true;
    } else {
      std::cerr << "error: invalid option: " << argv[i] << std::endl;
      show_usage();
      std::exit(1);
    }
  }

  if (lexicon_file_name_ == NULL) {
    lexicon_file_name_ = "-";
  }
  if (dic_file_name_ == NULL) {
    dic_file_name_ = "-";
  }

  if (!benchmarks_exact_match_search_ &&
      !benchmarks_common_prefix_search_ && !benchmarks_traverse_) {
    benchmarks_exact_match_search_ = true;
    benchmarks_common_prefix_search_ = true;
    benchmarks_traverse_ = true;
  }
}

}  // namespace Darts.

#endif  // DARTS_BENCHMARK_CONFIG_H_
