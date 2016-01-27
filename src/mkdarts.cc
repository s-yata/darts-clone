#include <darts.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

#include "./lexicon.h"
#include "./mkdarts-config.h"

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
}

}  // namespace

int main(int argc, char **argv) {
  try {
    Darts::MkdartsConfig config;
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

    if (!config.is_sorted()) {
      lexicon.sort();
    }

    // Note that split() of <Darts::Lexicon> may cause a problem if the lexicon
    // contains control characters.
    if (config.has_values()) {
      lexicon.split();
    }

    std::cerr << "keys: " << lexicon.size() << std::endl;
    std::cerr << "total: " << lexicon.total() << std::endl;

    Darts::DoubleArray dic;
    if (dic.build(lexicon.size(), lexicon.keys(), NULL,
        lexicon.values(), progress_bar) != 0) {
      std::cerr << "error: failed to build dictionary" << std::endl;
      std::exit(1);
    }

    if (std::strcmp(config.dic_file_name(), "-") != 0) {
      std::ofstream file(config.dic_file_name(), std::ios::binary);
      if (!file) {
        std::cerr << "error: failed to open dictionary file: "
            << config.dic_file_name() << std::endl;
        std::exit(1);
      }
      file.close();
      dic.save(config.dic_file_name());
    } else {
      std::cout.write(static_cast<const char *>(dic.array()),
          dic.total_size());
    }

    std::cerr << "size: " << dic.size() << std::endl;
    std::cerr << "total_size: " << dic.total_size() << std::endl;
  } catch (const std::exception &ex) {
    std::cerr << "exception: " << ex.what() << std::endl;
    throw ex;
  }

  return 0;
}
