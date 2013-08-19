#if ! defined(AnonSeqBase_h)
#define AnonSeqBase_h 1

#include "RepeatSeq.h"

/**
 * AnonSeqBase
 *
 * This class always returns the sequence (1 1).
 */
template <typename T = int>
class AnonSeqBase : public RepeatSeq<T>
{
public:
  /**
   * constructor
   */
  AnonSeqBase()
    : RepeatSeq<T>(1, 2)
  {
  }

private:
};


#endif // not defined AnonSeqBase_h
