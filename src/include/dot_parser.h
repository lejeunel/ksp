#ifndef DOT_PARSER_H_
#define DOT_PARSER_H_

#include "common.h"
#include "parsers.h"
#include <expected>
#include <string>
#include <tuple>

class DotFileParser {
public:
  DotFileParser(FileParser const &a_file_parser,
                RegexpSearcher const &a_dag_block_matcher,
                RegexpMatcherGroups const &a_edge_matcher,
                LineSplitter const &a_line_splitter)
      : file_parser(a_file_parser), dag_block_matcher(a_dag_block_matcher),
        edge_matcher(a_edge_matcher), line_splitter(a_line_splitter) {}

  std::expected<DiGraphEdges, std::string> parse(std::string const &path) {
    auto str = file_parser.parse(path);
    if (!str) {
      return std::unexpected{str.error()};
    }

    auto body = dag_block_matcher.search(str.value());

    if (!body) {
      return std::unexpected{body.error()};
    }

    StringList edge_lines = line_splitter.split(body.value());

    DiGraphEdges edges;
    for (auto l : edge_lines) {
      auto e = edge_matcher.parse(l);
      if (!e.empty()) {

        edges.push_back(
            DiGraphEdge(std::stoi(e[1]), std::stoi(e[2]), std::stof(e[3])));
      }
    }
    return edges;
  }

private:
  FileParser file_parser;
  RegexpSearcher dag_block_matcher;
  RegexpMatcherGroups edge_matcher;
  LineSplitter line_splitter;
};

#endif // DOT_PARSER_H_
