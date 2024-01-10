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
      : dag_block_matcher(a_dag_block_matcher), edge_matcher(a_edge_matcher),
        line_splitter(a_line_splitter), file_parser(a_file_parser) {}

  std::expected<DiGraphEdges, std::string> parse(std::string const &path) {
    auto str = file_parser.parse(path);
    auto body = dag_block_matcher.search(str);

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
  LineSplitter line_splitter;
  RegexpMatcherGroups edge_matcher;
};

#endif // DOT_PARSER_H_
