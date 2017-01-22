//
// Created by Pawel Burzynski on 22/01/2017.
//

#ifndef APOLLO_STORAGE_FILELOG_H
#define APOLLO_STORAGE_FILELOG_H

#include "log.h"

namespace apollo {

class FileLog : public Log {
 public:
  FileLog(std::string log_file_name);
  ~FileLog();

  void Fatal(std::string message);
  void Info(std::string message);
  void Debug(std::string message);
 private:
  void ToLog(std::string level, std::string message);

  std::string log_file_name;
  FILE *output;
};

}

#endif //APOLLO_STORAGE_FILELOG_H