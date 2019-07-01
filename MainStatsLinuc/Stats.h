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
    std::vector<std::vector<double>> previous(pFilter.instances.size(),std::vector<double>(6,0));
    std::vector<std::vector<double>> current(pFilter.instances.size(),std::vector<double>(6,0));
    std::vector<ResourceUnits*> resourceUnitsArray;
    int i = 0; 
    for (std::string &s : pFilter.instances)
    {
      ResourceUnits* unit = new DiskStats(fileName);
      unit->GetStats(s, previous[i]);
      resourceUnitsArray.push_back(unit);
      i++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    i = 0;
    for (std::string &s : pFilter.instances)
    {
      resourceUnitsArray[i]->GetStats(s, current[i]);
      i++;
    }
      for (int j = 0; j < pFilter.instances.size(); j++)
      {
        for (int i = 0; i < 6; i++)
        {
          result[i] += current[j][i] - previous[j][i];
        }
      }
      for(int i=0;i<6;i++)
      {
        logger->info(" %v ", result[i]);
      }
    logger->info("---------------------");
  }
}