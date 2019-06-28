#pragma once

#include "ELALogger.h"
#include "ProcessFilter.h"
#include "ResourceUnits.h"
ELALogger *logger;

void GetDiskStat(std::string path,std::string processName)
{
  ProcessFilter pFilter(path, processName);
  std::string fileName = "io";
  while (true)
  {
    std::vector<double> result(6);
    for (std::string &s : pFilter.instances)
    {
      ResourceUnits* unit = new DiskStats(fileName);
      unit->GetStats(s, result);
    }
    for (int i = 0; i < 6; i++)
    {
      logger->info(" %v ", result[i]);
    }
    logger->info("---------------------");
  }
}