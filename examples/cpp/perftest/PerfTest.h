#if ! defined(PerfTest_h)
#define PerfTest_h

namespace Test {
  /*!
   * Framework for the performance tests
   */
  class PerfTest
  {
  public:

    PerfTest();
    virtual ~PerfTest();
  
    int run(int argc, char ** argv);

  protected:
    static unsigned int const ARRSIZE = 1 * 1000;

    virtual void setX(int i, double v) = 0;
    virtual void setY(int i, double v) = 0;
    virtual void setZ(int i, double v) = 0;
    virtual double getX(int i) = 0;
    virtual double getY(int i) = 0;
    virtual double getZ(int i) = 0;

    virtual char const * identify() = 0;

  private:
  
    static void initRNG();

    void populate();
    void compute();
    void report();
  };
}

#endif
