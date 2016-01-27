#ifndef DARTS_MKDARTS_CONFIG_H_
#define DARTS_MKDARTS_CONFIG_H_

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace Darts {

class MkdartsConfig {
 public:
  MkdartsConfig() : command_(NULL), is_sorted_(true), has_values_(false),
      lexicon_file_name_(NULL), dic_file_name_(NULL) {}

  void parse(int argc, char **argv);

  bool is_sorted() const {
    return is_sorted_;
  }
  bool has_values() const {
    return has_values_;
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
        "  -s  sort lexicon before insertion\n"
        "  -t  use tab separated values\n" << std::endl;
  }

 private:
  const char *command_;
  bool is_sorted_;
  bool has_values_;
  const char *lexicon_file_name_;
  const char *dic_file_name_;

  // Disallows copy and assignment.
  MkdartsConfig(const MkdartsConfig &);
  MkdartsConfig &operator=(const MkdartsConfig &);
};

inline void MkdartsConfig::parse(int argc, char **argv) {
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
    } else if (std::strcmp(argv[i], "-s") == 0) {
      is_sorted_ = false;
    } else if (std::strcmp(argv[i], "-t") == 0) {
      has_values_ = true;
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
}

}  // namespace Darts.

#endif  // DARTS_MKDARTS_CONFIG_H_
