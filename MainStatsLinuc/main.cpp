#include <cstdio>
#include "Stats.h"
int main()
{
  logger = new ELALogger();
  logger->Start();
  logger->SetLogDir("/opt/surya/");
  logger->SetLogFileName("output.txt");
  std::string path = "/opt/surya/EventLog/";
  std::string name = "java";
  //std::string path = "";
  //std::string name = "gnome-system-mo";
  GetCPUStats(path, name);
  return 0;
}