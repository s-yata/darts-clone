#include <darts.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./darts-config.h"

namespace {

void darts_search(const Darts::DartsConfig &config,
    const Darts::DoubleArray &dic, std::istream *lexicon) {
  std::vector<Darts::DoubleArray::result_pair_type> result_pairs(1024);

  std::string query;
  while (std::getline(*lexicon, query)) {
    if (config.has_values()) {
      std::string::size_type tab_pos = query.find_last_of('\t');
      if (tab_pos != std::string::npos) {
        query = query.substr(0, tab_pos);
      }
    }

    std::size_t num_results = dic.commonPrefixSearch(
        query.c_str(), &result_pairs[0], result_pairs.size());
    if (num_results > 0) {
      std::cout << query << ": found, num = " << num_results;
      for (std::size_t i = 0; i < num_results; ++i) {
        std::cout << ' ' << result_pairs[i].value
            << ':' << result_pairs[i].length;
      }
      std::cout << std::endl;
    } else {
      std::cout << query << ": not found" << std::endl;
    }
  }
}

}  // namespace

int main(int argc, char **argv) {
  try {
    Darts::DartsConfig config;
    config.parse(argc, argv);

    Darts::DoubleArray dic;
    if (dic.open(config.dic_file_name()) != 0) {
      std::cerr << "error: failed to open dictionary file: "
          << config.dic_file_name() << std::endl;
      std::exit(1);
    }

    if (std::strcmp(config.lexicon_file_name(), "-") != 0) {
      std::ifstream file(config.lexicon_file_name());
      if (!file) {
        std::cerr << "error: failed to open lexicon file: "
            << config.lexicon_file_name() << std::endl;
        std::exit(1);
      }
      darts_search(config, dic, &file);
    } else {
      darts_search(config, dic, &std::cin);
    }
  } catch (const std::exception &ex) {
    std::cerr << "exception: " << ex.what() << std::endl;
    throw ex;
  }

  return 0;
}
