#include "include/dot_parser.h"

DotFileParser make_dotfile_parser(std::string const &digraph_rex,
                                  std::string const &edge_rex) {
  return DotFileParser(
      FileParser(),
      RegexpSearcher("digraph block",
                     std::regex(digraph_rex, std::regex::extended)),
      RegexpMatcherGroups("edge", std::regex(edge_rex, std::regex::extended)),
      LineSplitter(';'));
}
