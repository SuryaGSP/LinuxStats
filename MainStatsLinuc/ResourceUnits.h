#pragma once
#include "ProcessFilter.h"
#include "ResourceUnit.h"
#include <thread>
#include <chrono>
class ResourceUnits
{
  ProcessFilter pFilter;
protected:
  std::string fileName;
public:
  ResourceUnits(std::string &fileNameAlias) 
  {
    fileName = fileNameAlias;
  }
  virtual void GetStats(std::string &pid, std::vector<double> &result)
  {

  }

};
class CPUUnits : public ResourceUnits
{
public:
  CPUUnits(std::string &fileNameAlias) : ResourceUnits(fileNameAlias)
  {

  }
};

class RAMUnits : public ResourceUnits
{
public:
  RAMUnits(std::string &fileNameAlias) : ResourceUnits(fileNameAlias)
  {
  }
};

class DiskStats : public ResourceUnits
{
public:
  DiskStats(std::string &fileNameAlias) : ResourceUnits(fileNameAlias)
  {

  }
  void GetStats(std::string &pid,std::vector<double> &result)
  {
    ResourceUnit* unit = new DiskStat(pid,fileName);
    std::vector<double> current(6);
    std::vector<double> previous(6);
    unit->CaptureData();
    unit->resolveData(previous);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    unit->CaptureData();
    unit->resolveData(current);
    for (int i = 0; i < 6; i++)
    {
      result[i] += current[i] - previous[i];
    }
  }
};