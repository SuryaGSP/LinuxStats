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
    unit->CaptureData();
    unit->resolveData(result);
  }
};

class CPUStats : public ResourceUnits
{
public:
  CPUStats(std::string &fileNameAlias) : ResourceUnits(fileNameAlias)
  {

  }
  void GetStats(std::string &pid, std::vector<double> &result)
  {
    ResourceUnit* unit = new CPUStat(pid, fileName);
    unit->CaptureData();
    unit->resolveData(result);
  }
};