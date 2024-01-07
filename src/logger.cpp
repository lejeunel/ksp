#include "include/logger.h"
#include "include/easylogging++.h"

int configure_logger(el::Level severity_level) {
  el::Configurations defaultConf;
  defaultConf.setToDefault();
  el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
  el::Loggers::setLoggingLevel(severity_level);
  defaultConf.set(el::Level::Info, el::ConfigurationType::Format,
                  "%datetime %level %msg");
  defaultConf.set(el::Level::Debug, el::ConfigurationType::Format,
                  "%datetime %level %msg");
  defaultConf.set(el::Level::Trace, el::ConfigurationType::Format,
                  "%datetime %level %msg");

  el::Loggers::reconfigureLogger("default", defaultConf);
  return 0;
}
