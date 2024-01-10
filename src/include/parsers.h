#ifndef STRUTILS_H_
#define STRUTILS_H_
#include <expected>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::string> StringList;

class RegexpMatcherGroups {
public:
  RegexpMatcherGroups(std::string const &a_name, std::regex a_regexp)
      : regexp(a_regexp), name(a_name) {}
  StringList parse(std::string input) {

    StringList result;
    std::regex_search(input, match, regexp);
    for (auto m : match) {
      result.push_back(m);
    }

    return result;
  }

private:
  std::regex regexp;
  std::smatch match;
  std::string name;
};

class RegexpSearcher {
public:
  RegexpSearcher(std::string const &a_name, std::regex a_regexp)
      : regexp(a_regexp), name(a_name) {}

public:
  std::expected<std::string, std::string> search(std::string const &input) {

    if (!std::regex_search(input.begin(), input.end(), match, regexp)) {
      return std::unexpected{"[" + name + "]" + " parsing error"};
    } else {
      return match[1];
    }
  }

private:
  std::regex regexp;
  std::smatch match;
  std::string name;
};

class FileParser {
public:
  std::expected<std::string, std::string> parse(std::string path) {

    std::ifstream file(path);

    if (!file.is_open()) {
      // show message:
      return std::unexpected{"Could not open file " + path};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }

private:
  std::string content;
};

class LineSplitter {
public:
  LineSplitter(char a_delim) : delim(a_delim) {}

  StringList split(std::string str) {

    StringList lines;
    std::string line;
    std::stringstream line_stream(str);

    while (std::getline(line_stream, line, delim)) {
      lines.push_back(line);
    }
    return lines;
  }

private:
  char delim;
};

#endif // STRUTILS_H_
