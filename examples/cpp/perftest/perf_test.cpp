
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

using namespace Test;

int main(int argc, char ** argv) 
{
//  (void) run<PerfTest_PA>(argc, argv);
//  (void) run<PerfTest_PV>(argc, argv);
//  (void) run<PerfTest_AOFS>(argc, argv);
//  (void) run<PerfTest_VOFS>(argc, argv);
//  (void) run<PerfTest_AOFLS>(argc, argv);
//  (void) run<PerfTest_VOFLS>(argc, argv);

  (void) run<PerfTest_AOS<ThinData> >(argc, argv);
  (void) run<PerfTest_AOS<FatData> >(argc, argv);
  (void) run<PerfTest_AOS<VeryFatData> >(argc, argv);
  (void) run<PerfTest_VOS<ThinData> >(argc, argv);
  (void) run<PerfTest_VOS<FatData> >(argc, argv);
  (void) run<PerfTest_VOS<VeryFatData> >(argc, argv);
  

  return 0;
}

