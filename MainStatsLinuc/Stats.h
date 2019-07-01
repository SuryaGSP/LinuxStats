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

void GetCPUStats(std::string path, std::string processName)
{
  ProcessFilter pFilter(path, processName);
  std::string fileName = "stat";
  while (true)
  {
    std::vector<double> result(6);
    std::vector<std::vector<double>> previousCPUTimeByProcess(pFilter.instances.size(), std::vector<double>(2, 0));
    std::vector<std::vector<double>> currentCPUTimeByProcess(pFilter.instances.size(), std::vector<double>(2, 0));
    std::vector<double> previousTotalCpuUsedTime(pFilter.instances.size());
    std::vector<double> currentTotalCpuUsedTime(pFilter.instances.size());
    std::vector<ResourceUnits*> resourceUnitsArray;
    File* file;
     int i = 0;
    for (std::string &s : pFilter.instances)
    {
      std::string CPUData;
      ResourceUnits* unit = new CPUStats(fileName);
      unit->GetStats(s, previousCPUTimeByProcess[i]);
      file = new File("/proc/stat");
      file->ReadLine(CPUData);
      CPUData.replace(0, CPUData.find(" ") + 1, "");
      while(CPUData != "")
      {
        previousTotalCpuUsedTime[i] += atof(CPUData.c_str());
        CPUData.replace(0, CPUData.find(" ") + 1, "");
        if (CPUData.find(" ") > CPUData.length())
        {
          break;
        }
      }
      previousTotalCpuUsedTime[i] += atof(CPUData.c_str());
      resourceUnitsArray.push_back(unit);
      i++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    i = 0;
    for (std::string &s : pFilter.instances)
    {
      resourceUnitsArray[i]->GetStats(s, currentCPUTimeByProcess[i]);
      file = new File("/proc/stat");
      std::string CPUData;
      file->ReadLine(CPUData);
      CPUData.replace(0, CPUData.find(" ") + 1, "");
      while (CPUData != "")
      {
        currentTotalCpuUsedTime[i] += atof(CPUData.c_str());
        CPUData.replace(0, CPUData.find(" ") + 1, "");
        if (CPUData.find(" ") > CPUData.length())
        {
          break;
        }
      }
      currentTotalCpuUsedTime[i] += atof(CPUData.c_str());
      i++;
    }
    double previousCPU = 0.0, currentCPU = 0.0, totalCPUPercentage = 0.0;
    for (int j = 0; j < pFilter.instances.size(); j++)
    {
      previousCPU += previousCPUTimeByProcess[j][0] + previousCPUTimeByProcess[j][1];
      currentCPU += currentCPUTimeByProcess[j][0] + currentCPUTimeByProcess[j][1];
      totalCPUPercentage += (100 * (currentCPU - previousCPU) / (currentTotalCpuUsedTime[j] - previousTotalCpuUsedTime[j]));
    }
    logger->info("%v",totalCPUPercentage);
  }
}
