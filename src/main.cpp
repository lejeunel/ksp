#include "include/argparse.hpp"
#include "include/directed_graph.h"
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
  argparse::ArgumentParser program("edksp", "0.1");

  program.add_argument("dot-file").help("path to dot file");
  program.add_argument("source-id").help("node id of source").scan<'i', int>();
  program.add_argument("sink-id").help("node id of sink").scan<'i', int>();
  program.add_argument("k").help("number of paths").scan<'i', int>();

  int verbosity = 0;
  program.add_argument("-V")
      .action([&](const auto &) { ++verbosity; })
      .append()
      .default_value(false)
      .implicit_value(true)
      .help("verbosity level")
      .nargs(0);

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  configure_logger(el::Level::Error);
  if (verbosity == 1)
    configure_logger(el::Level::Debug);
  else if (verbosity > 1)
    configure_logger(el::Level::Trace);

  auto path = program.get<std::string>("dot-file");
  auto source_id = program.get<int>("source-id");
  auto sink_id = program.get<int>("sink-id");
  auto k = program.get<int>("k");

  LOG(DEBUG) << "Parsing file: " << path;

  auto parser = make_parser(R"(digraph.*\{(.*)}.*)",
                            R"(([0-9]*) -> ([0-9]*)\[weight=\"(.*)\"])");
  auto parser_result = parser.parse(path);

  if (!parser_result) {
    LOG(ERROR) << parser_result.error();
    return 1;
  }

  auto graph = std::make_unique<DirectedGraph>(parser_result.value());
  auto ksp = KSP(std::move(graph), source_id, sink_id);
  auto result = ksp.run(k);

  if (!result) {
    LOG(ERROR) << result.error();
    return 1;
  }

  auto paths = ksp.get_paths();
  LOG(INFO) << "Found " << paths.size() << " paths:";
  for (auto p : paths) {
    LOG(INFO) << p;
  }

  return 0;
}
