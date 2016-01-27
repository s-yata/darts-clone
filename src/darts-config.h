#ifndef DARTS_DARTS_CONFIG_H_
#define DARTS_DARTS_CONFIG_H_

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace Darts {

class DartsConfig {
 public:
  DartsConfig() : command_(NULL), has_values_(false),
      dic_file_name_(NULL), lexicon_file_name_(NULL) {}

  void parse(int argc, char **argv);

  bool has_values() const {
    return has_values_;
  }
  const char *dic_file_name() const {
    return dic_file_name_;
  }
  const char *lexicon_file_name() const {
    return lexicon_file_name_;
  }

  void show_usage() const {
    std::cerr << "\nUsage: " << command_
        << " [Options...] [Dictionary] [Lexicon]\n\n"
        "  -h  display this help\n"
        "  -t  drop tab separated values\n" << std::endl;
  }

 private:
  const char *command_;
  bool has_values_;
  const char *dic_file_name_;
  const char *lexicon_file_name_;

  // Disallows copy and assignment.
  DartsConfig(const DartsConfig &);
  DartsConfig &operator=(const DartsConfig &);
};

inline void DartsConfig::parse(int argc, char **argv) {
  command_ = argv[0];
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      if (dic_file_name_ == NULL) {
        dic_file_name_ = argv[i];
      } else if (lexicon_file_name_ == NULL) {
        lexicon_file_name_ = argv[i];
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
    } else {
      std::cerr << "error: invalid option: " << argv[i] << std::endl;
      show_usage();
      std::exit(1);
    }
  }

  if (dic_file_name_ == NULL) {
    dic_file_name_ = "-";
  }
  if (lexicon_file_name_ == NULL) {
    lexicon_file_name_ = "-";
  }
}

}  // namespace Darts.

#endif  // DARTS_DARTS_CONFIG_H_
