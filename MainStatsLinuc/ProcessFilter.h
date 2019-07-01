#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <dirent.h>
#include "PropertyHandler.h"
template<class T>
void PrintVector(std::vector<T> objects, std::string message)
{
  std::cout << message << ". Size : " << objects.size() << std::endl;
  for (auto &object : objects)
  {
    std::cout << object << std::endl;
  }
  std::cout << std::endl;
}
class ProcessFilter
{
  std::string process, processPath;
  std::vector<int> pids;
  // HQueryProcessor hProcessor;
  void  FilterInstances(std::vector<int>& pids, std::vector <std::string>& thatinstances)
  {
    std::vector<std::string> thisinstances;
    for (int &instance : pids)
    {
      std::string fileName = "/proc/" + std::to_string(instance) + "/exe";
      //File* file = new File(fileName);
      //file->ReadLine(pathName);
      char pathName[101];
      int len;
      if ((len = readlink(fileName.c_str(), pathName, 100)) != -1)
      {
        if (std::string(pathName).find(processPath) != std::string::npos)
        {
          thatinstances.push_back(std::to_string(instance));
        }
      }
    }
  }
  void FilterProcessIDs(std::string thatpath, std::string thatprocess, std::vector<int>& thatpids)
  {
    std::vector<int> thispids;
    for (int pid : thatpids)
    {
      if (pid == 24462)
      {
        std::cout << "";
      }
      std::string fileName = "/proc/" + std::to_string(pid) + "/status";
      File* file = new File(fileName);
      std::string processName;
      file->ReadLine(processName);
      if (processName.find(thatprocess)!=std::string::npos)
      {
        thispids.push_back(pid);
      }
    }
    thatpids = thispids;
  }
  void GetProcessIDs(std::vector<int>& pids)
  {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/proc")) != NULL)
    {
      while ((ent = readdir(dir)) != NULL)
      {
        if (ent->d_name != "." || ent->d_name != "..")
        {
          if (ent->d_type == DT_DIR && atoi(ent->d_name)!=0)
          {
            pids.push_back(atoi(ent->d_name));
          }
        }
      }
      closedir(dir);
    }
  }
public:
  std::vector<std::string> instances;
  ProcessFilter()
  {

  }
  ProcessFilter(std::string &path, std::string &processName)// justTrying &jTrying)
  {
    processPath = path;
    process = processName;
    GetProcessIDs(pids);
    FilterProcessIDs(processPath, process, pids);
    FilterInstances(pids, instances);
  }
}; 