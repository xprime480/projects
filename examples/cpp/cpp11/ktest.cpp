
#include <iostream>
#include <vector>
#include <algorithm>

namespace {

  using std::cout;
  using std::endl;
  using std::vector;
  using std::count_if;
  using std::for_each;

  vector<int> test_data = { 1, 3, 5, 7 };

  template <typename T>
  class Ref
  {
  public : 
    Ref(T & _i)
      : i(_i)
    {
    }

    operator T&()
    {
      return i;
    }

  private :
    T & i;
  };

  using IRef = Ref<int>;
  vector<IRef> ref_data;

  void f(int & i)
  {
    ref_data.push_back(IRef(i));
  }

  void g(size_t j)
  {
    ref_data.push_back(IRef(test_data[j]));
  }

  template <typename Data, typename Func>
  void kcommon(const Data & data, Func func)
  {
    for ( auto i : data ) {
      func(i);
      for ( auto j : ref_data ) {
	cout << j << " ";
      }
      cout << endl;
    }
    ref_data.clear();
  }

  void ktest1()
  {
    kcommon(test_data, f);
  }

  void ktest2()
  {
    auto indices = { 0, 1, 2, 3 };
    kcommon(indices, g);
  }

  void ktest3()
  {
    auto f = [] (int & i) { ref_data.push_back(IRef(i)); };
    kcommon(test_data, f);
  }

  void ktest4()
  {
    cout << count_if(test_data.begin(), test_data.end(), [] (int i) { return i < 5; }) << endl;
  }

  void ktest5()
  {
    auto d = { &test_data[0], &test_data[1], &test_data[2], &test_data[3] };
    auto f = [] (int * i) { ref_data.push_back(IRef(*i)); };
    kcommon(d, f);
  }
  
  void ktest6()
  {
    vector<int*> d;
    auto c = [&d] (int & r) { d.push_back(&r); };
    for_each(test_data.begin(), test_data.end(), c);
    auto f = [] (int * i) { ref_data.push_back(IRef(*i)); };
    kcommon(d, f);
  }
}

int ktest(int argc, char ** argv)
{
  auto testlist = { ktest1, ktest2, ktest3, ktest4, ktest5, ktest6 };
  for ( auto t : testlist ) {
    t();
    endl(cout);
  }

  return 0;
}
