#include "include/logger.h"
#include "include/easylogging++.h"

int configure_logger(el::Level severity_level) {
  el::Configurations defaultConf;
  defaultConf.setToDefault();
  el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
  el::Loggers::setLoggingLevel(severity_level);
  defaultConf.set(el::Level::Global, el::ConfigurationType::Format,
                  "%datetime %level %msg");
  defaultConf.set(el::Level::Global, el::ConfigurationType::ToFile, "false");

  el::Loggers::reconfigureLogger("default", defaultConf);
  return 0;
}
