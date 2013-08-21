
#include "PerfTest_PA.h"
#include "PerfTest_PV.h"
#include "PerfTest_AOFS.h"
#include "PerfTest_VOFS.h"
#include "PerfTest_AOFLS.h"
#include "PerfTest_VOFLS.h"

#include "ThinData.h"
#include "FatData.h"
#include "VeryFatData.h"
#include "PerfTest_AOS.h"
#include "PerfTest_VOS.h"

template<typename T>
int run(int argc, char ** argv)
{
  T p;
  return p.run(argc, argv);
}

int main(int argc, char ** argv) 
{
//  (void) run<Test::PerfTest_PA>(argc, argv);
//  (void) run<Test::PerfTest_PV>(argc, argv);
//  (void) run<Test::PerfTest_AOFS>(argc, argv);
//  (void) run<Test::PerfTest_VOFS>(argc, argv);
//  (void) run<Test::PerfTest_AOFLS>(argc, argv);
//  (void) run<Test::PerfTest_VOFLS>(argc, argv);

  (void) run<Test::PerfTest_AOS<Test::ThinData> >(argc, argv);
  (void) run<Test::PerfTest_AOS<Test::FatData> >(argc, argv);
  (void) run<Test::PerfTest_AOS<Test::VeryFatData> >(argc, argv);
  (void) run<Test::PerfTest_VOS<Test::ThinData> >(argc, argv);
  (void) run<Test::PerfTest_VOS<Test::FatData> >(argc, argv);
  (void) run<Test::PerfTest_VOS<Test::VeryFatData> >(argc, argv);
  

  return 0;
}

