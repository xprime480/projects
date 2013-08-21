
#include <iostream>
#include "Form.h"

#if 0

#define EVAL_TO_SELF(form) \
  { \
  Form f(form); \
  std::cout << "*********************************" << std::endl; \
  std::cout << "beginning eval-to-self at " << __FILE__ << ", line " << __LINE__ << std::endl; \
  std::cout << f << std::endl; \
  std::cout << "*********************************" << std::endl; \
  }

#define EVAL_START_1(form) \
  { \
  Form f(form); \
  std::cout << "*********************************" << std::endl; \
  std::cout << "beginning eval at " << __FILE__ << ", line " << __LINE__ << std::endl; \
  std::cout << f << std::endl; \
  std::cout << "*********************************" << std::endl; \
  }

#define EVAL_FINISH(form) \
  { \
  Form f(form); \
  std::cout << "*********************************" << std::endl; \
  std::cout << "ending eval at " << __FILE__ << ", line " << __LINE__ << std::endl; \
  std::cout << f << std::endl; \
  std::cout << "*********************************" << std::endl; \
  }

#define TRACE_HEAD_START(form) \
  { \
  Form f(form); \
  std::cout << "*********************************" << std::endl; \
  std::cout << "getting head at " << __FILE__ << ", line " << __LINE__ << std::endl; \
  std::cout << f << std::endl; \
  std::cout << "*********************************" << std::endl; \
  }

#define TRACE_HEAD_FINISH(form) \
  { \
  Form f(form); \
  std::cout << "*********************************" << std::endl; \
  std::cout << "finished getting head at " << __FILE__ << ", line " << __LINE__ << std::endl; \
  std::cout << f << std::endl; \
  std::cout << "*********************************" << std::endl; \
  }

#else

#define EVAL_TO_SELF(form)
#define EVAL_START_1(form) 
#define EVAL_FINISH(form)
#define TRACE_HEAD_START(form)
#define TRACE_HEAD_FINISH(form)

#endif
