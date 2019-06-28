#pragma once
#include "ELALogger.h"
#include "PropertyHandler.h"
#include <string>
extern ELALogger *logger;
class ResourceUnit
{
  
protected:
  std::deque<std::string> fileData;
  std::string pid, fileName;
public:
  ResourceUnit(std::string &pidAlias,std::string &filePathAlias)
  {
    pid = pidAlias;
    fileName = filePathAlias;
  }
  void CaptureData()
  {
    File* file = new File("/proc/" + pid + "/" + fileName);   
    fileData = file->ReadAllLines();
  }
  virtual void resolveData(std::vector<double> &result)
  {
    int i = 0;
    for (std::string &s : fileData)
    {
      std::cout << s;
      result.at(i) = atoi(s.substr(s.find(" ")).c_str());
      i++;
    }
    fileData.clear();
  }
};

class DiskStat : public ResourceUnit
{
public:
  DiskStat(std::string &pidAlias, std::string filePathAlias) : ResourceUnit(pidAlias, filePathAlias)
  {

  }

  void resolveData(std::vector<double> &result)
  {
    result.at(0) = atoi(fileData.front().substr(fileData.front().find(" ")).c_str())/1024;
    fileData.pop_front();
    result.at(1) = atoi(fileData.front().substr(fileData.front().find(" ")).c_str())/1024;
    fileData.pop_front();
    result.at(2) = atoi(fileData.front().substr(fileData.front().find(" ")).c_str());
    fileData.pop_front();
    result.at(3) = atoi(fileData.front().substr(fileData.front().find(" ")).c_str());
    fileData.pop_front();
    result.at(4) = atoi(fileData.front().substr(fileData.front().find(" ")).c_str())/1024;
    fileData.pop_front();
    result.at(5) = atoi(fileData.front().substr(fileData.front().find(" ")).c_str())/1024;
    fileData.pop_front();
    fileData.clear();
  }
};