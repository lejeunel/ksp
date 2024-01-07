#include "../src/include/directed_graph.h"
#include "include/argparse.hpp"
#include "include/dot_parser.h"
#include "include/ksp.h"
#include "include/logger.h"
#include <iostream>
#include <string>

INITIALIZE_EASYLOGGINGPP

DotFileParser make_parser(std::string const &digraph_rex,
                          std::string const &edge_rex) {
  return DotFileParser(
      FileParser(),
      RegexpSearcher("digraph block",
                     std::regex(digraph_rex, std::regex::extended)),
      RegexpMatcherGroups("edge", std::regex(edge_rex, std::regex::extended)),
      LineSplitter(';'));
}

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program("edksp");

  program.add_argument("dot-file").help("path to dot file");
  program.add_argument("source-id").help("node id of source").scan<'i', int>();
  program.add_argument("sink-id").help("node id of sink").scan<'i', int>();
  program.add_argument("k").help("number of paths").scan<'i', int>();

  int verbosity = 0;
  program.add_argument("-v", "--verbose")
      .action([&](const auto &) { ++verbosity; })
      .append()
      .default_value(false)
      .implicit_value(true)
      .nargs(0);

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  if (verbosity == 1)
    configure_logger(el::Level::Error);
  else if (verbosity == 2)
    configure_logger(el::Level::Debug);
  else
    configure_logger(el::Level::Unknown);

  auto path = program.get<std::string>("dot-file");
  auto source_id = program.get<int>("source-id");
  auto sink_id = program.get<int>("sink-id");
  auto k = program.get<int>("k");

  std::cout << "Parsing file: " << path << std::endl;

  auto parser = make_parser(R"(digraph.*\{(.*)}.*)",
                            R"(([0-9]*) -> ([0-9]*)\[weight=\"(.*)\"])");
  auto parser_result = parser.parse(path);

  if (!parser_result.has_value()) {
    std::cout << parser_result.error() << std::endl;
    return 1;
  }

  auto graph = std::make_shared<DirectedGraph>(parser_result.value());
  auto ksp = KSP(graph, source_id, sink_id);
  auto result = ksp.run(k);

  if (!result.has_value()) {
    std::cout << result.error() << std::endl;
    return 1;
  }

  auto paths = result.value();
  for (auto p : paths) {
    std::cout << p->to_str() << std::endl;
  }

  return 0;
}
