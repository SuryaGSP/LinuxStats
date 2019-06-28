#include <cstdio>
#include "Stats.h"
#include <thread>
#include <pthread.h>
#include <chrono>
int main()
{
  logger = new ELALogger();
  logger->Start();
  logger->SetLogDir("/opt/surya/");
  logger->SetLogFileName("output.txt");
  std::string path = "/opt/surya/EventLog/";
  std::string name = "java";
  //std::thread t1(GetDiskStat, path, name);
  //t1.join();
  GetDiskStat(path, name);
  return 0;
}