#include "../src/include/logger.h"
#include <catch2/catch_session.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
  Catch::Session session;

  using namespace Catch::Clara;
  auto cli = session.cli();

  session.cli(cli);

  // Let Catch2 (using Clara) parse the command line
  int returnCode = session.applyCommandLine(argc, argv);
  auto verbosity = session.configData().verbosity;
  if (returnCode != 0)
    return returnCode;

  if ((verbosity == Catch::Verbosity::Normal) |
      (verbosity == Catch::Verbosity::Quiet)) {
    std::cout << "log warning and errors" << std::endl;
    configure_logger(el::Level::Info);
  } else {
    std::cout << "log everything" << std::endl;
    configure_logger(el::Level::Trace);
  }
  return session.run();
}