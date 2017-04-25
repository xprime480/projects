
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

/**
 * \brief Create a vector of iterators where key changes happen.
 *
 * This function takes a collection \a coll and a key function \a kf.  The key
 * function takes a const_iterator of the collection and returns a key value
 * based on the iterator.  partition_by_keys returns a vector consisting of
 * all iterators where the key value changes.  If the caller passes an empty
 * \a coll, the return value is an empty vector.  Otherwise, the return vector
 * always includes, at a minimum, coll.begin() and coll.end() as the first and
 * last elements of the vector.
 *
 * \arg coll any collection which has empty, begin and end
 * \arg kf a callable that takes a iterator of coll and returns a key value
 * 
 */
template <typename Coll, typename KeyFunc>
std::vector<typename Coll::const_iterator>
partition_by_keys(const Coll & coll, KeyFunc kf)
{
    using iter_t = typename Coll::const_iterator;
    std::vector<iter_t> partitions;
    if ( coll.empty() ) {
	return partitions;
    }

    iter_t current = coll.begin();
    partitions.push_back(current);
    auto last_key = kf(current);

    for ( ;; ) {
	++current;
	if ( current == coll.end() ) {
	    partitions.push_back(current);
	    break;
	}

	auto current_key = kf(current);
	if ( last_key != current_key ) {
	    partitions.push_back(current);
	    last_key = current_key;
	}
    }

    return partitions;
}

/**
 * \brief Sample data to run tests of partitioning.
 */
struct TestData
{
    /**
     * \brief Constructor
     *
     * \arg seq major grouping
     * \arg sub minor grouping
     * \arg dat text data
     */ 
    TestData(int seq, int sub, const std::string & dat)
	: Sequence(seq)
	, Subsequence(sub)
	, Data(dat)
    {
    }

    unsigned int Sequence;    //! top level grouping
    unsigned int Subsequence; //! sub grouping
    std::string  Data;        //! text data
};

/**
 * \brief Format a TestData object to an output stream.
 *
 * Output will look like <major>.<minor> text, e.g.
 *
 * 3.1 Random Description goes here.
 *
 * \arg os any output stream
 * \arg td TestData object
 */
std::ostream & operator<<(std::ostream & os, const TestData & td) 
{
    os << td.Sequence << "." << td.Subsequence << " " << td.Data;
    return os;
}

/**
 * \brief Format a pair<> object to an output stream.
 * 
 * Output will will like "{first/second}"
 *
 * \arg os any output stream
 * \arg kv a pair<K,V> where it is assumed that K and V support
 *         streaming to std::ostream
 */
template <typename K, typename V>
std::ostream & operator<<(std::ostream & os, const std::pair<K,V> & kv)
{
    os << "{" << kv.first << "/" << kv.second << "}";
    return os;
}

/**
 * \brief Test driver for partition_by_keys
 */
template <typename Coll, typename KeyFunc, typename PrintFunc>
void
test_partition_by_keys(const Coll & coll, KeyFunc kf, PrintFunc pf)
{
    auto partition = partition_by_keys(coll, kf);
    while ( partition.size() >= 2 ) {
	auto s = partition[0];
	auto e = partition[1];
	partition.erase(partition.begin());
	for ( ; s != e ; ++s ) {
	    pf(s);
	}
	std::cout << "######################" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

void test1()
{
    using data_t = std::vector<TestData>;
    using iter_t = data_t::const_iterator;

    data_t testData {
	{ 0, 0, "Rabbit" },
	{ 0, 1, "Bunny" },
	{ 1, 0, "Cow"},
	{ 2, 0, "Horse" },
	{ 2, 1, "Pony" }
    };
    auto kf = [](iter_t i) -> decltype(i->Sequence) {
	return i->Sequence;
    };
    auto pf = [&testData, &kf](iter_t i) -> void {
	if ( i != testData.end() ) {
	    std::cout << kf(i) << "..." << (*i) << std::endl;
	}
    };

    test_partition_by_keys(testData, kf, pf);
}

void test2()
{
    using data_t = std::map<int, std::string>;
    using iter_t = data_t::const_iterator;

    data_t testData {
	{ 0, "Rabbit" },
	{ 0, "Bunny" },
	{ 1, "Cow"},
	{ 2, "Horse" },
	{ 2, "Pony" }
    };
    auto kf = [](iter_t i) -> bool {
	return i->first < 2;
    };
    auto pf = [&testData, &kf](iter_t i) -> void {
	if ( i != testData.end() ) {
	    std::cout << kf(i) << "..." << (i->second) << std::endl;
	}
    };

    test_partition_by_keys(testData, kf, pf);
}

void test3()
{
    using data_t = std::map<int, std::string>;
    using iter_t = data_t::const_iterator;

    data_t testData {
	{ 0, "Rabbit" },
	{ 0, "Bunny" },
	{ 1, "Cow"},
	{ 2, "Horse" },
	{ 2, "Pony" }
    };
    auto kf = [](iter_t i) -> bool {
	return i->first % 2;
    };
    auto pf = [&](iter_t i) -> void {
	if ( i != testData.end() ) {
	    std::cout << kf(i) << "..." << (i->second) << std::endl;
	}
    };

    test_partition_by_keys(testData, kf, pf);
}

template <typename Coll, typename Ret, typename Arg>
class PartitionMap
{
private:
    using key_t         = Ret;

    using KeySetType    = typename std::set<key_t>;

    using item_t        = Arg;
    using KeyDataType   = typename std::vector<item_t>;
    using PartitionType = typename std::map<key_t, KeyDataType>;

    using KeyFunc       = typename std::function<Ret(Arg)>;

public:

    PartitionMap(const Coll & coll, KeyFunc kf)
    {
	for ( const auto item : coll ) {
	    partition[kf(item)].push_back(item);
	}
    }
    
    PartitionMap(const PartitionMap & that) = default;
    PartitionMap & operator=(const PartitionMap & that) = default;

    KeySetType getKeySet() const 
    {
	KeySetType rv;
	for ( auto kv : partition ) {
	    rv.insert(kv.first);
	}
	return rv;
    }

    const KeyDataType & getValuesForKey(const key_t & key) const
    {
	auto iter = partition.find(key);
	if ( iter == partition.end() ) {
	    static KeyDataType emptyKeyData;
	    return emptyKeyData;
	}

	return iter->second;
    }

private:
    PartitionType partition;
};

template <typename Coll, typename R, typename Arg, typename PrintFunc>
void
test_partition_map(const Coll & coll, std::function<R(Arg)> kf, PrintFunc pf)
{
    const PartitionMap<Coll, R, Arg> pm(coll, kf);

    auto keys = pm.getKeySet();
    for ( const auto k : keys ) {
	std::cout << "key = " << k << std::endl;
	auto values = pm.getValuesForKey(k);
	for ( const auto v : values ) {
	    pf(v);
	}
	std::cout << "######################" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

template <typename Coll, typename R, typename Arg>
void
test_partition_map(const Coll & coll, std::function<R(Arg)> kf)
{
    auto pf = [&kf](const Arg & td) -> void {
	std::cout << td << std::endl;
    };
    test_partition_map(coll, kf, pf);
}

void test4()
{
    std::cout << "Test 4" << std::endl;

    using data_t = std::vector<TestData>;

    data_t testData {
	{ 0, 0, "Rabbit" },
	{ 2, 0, "Horse" },
	{ 0, 1, "Bunny" },
	{ 1, 0, "Cow"},
	{ 2, 1, "Pony" }
    };

    using kf_t = std::function<decltype(TestData::Sequence)(const TestData)>;
    kf_t kf = [](const TestData & td) -> decltype(td.Sequence) {
	return td.Sequence;
    };

    test_partition_map(testData, kf);
}

void test5()
{
    std::cout << "Test 5" << std::endl;

    using item_t = std::shared_ptr<TestData>;
    using data_t = std::vector<item_t>;

    data_t testData {
	std::make_shared<TestData>(0, 0, "Rabbit"),
	std::make_shared<TestData>(2, 0, "Horse" ),
	std::make_shared<TestData>(0, 1, "Bunny" ),
	std::make_shared<TestData>(1, 0, "Cow"),
	std::make_shared<TestData>(2, 1, "Pony" )
    };

    using kf_t = std::function<int(item_t)>;
    kf_t kf = [](const item_t & td) -> decltype(td->Sequence) {
	return td->Sequence;
    };
    auto pf = [&kf](const item_t & td) -> void {
	std::cout << (*td) << std::endl;
    };

    testData.front()->Subsequence = 7;
    std::for_each(testData.begin(), testData.end(), [](std::shared_ptr<TestData> i){ i->Subsequence *= 2; i->Data += "!"; });

    test_partition_map(testData, kf, pf);
}

void test6()
{
    std::cout << "Test 6" << std::endl;

    using data_t = std::map<int, std::string>;
    using iter_t = data_t::value_type;

    std::cout << std::boolalpha;

    data_t testData {
	{ 0, "Rabbit" },
	{ 0, "Bunny" },
	{ 1, "Cow"},
	{ 2, "Horse" },
	{ 2, "Pony" },
	{ 734, "Xenomorph" },
    };

    using kf_t = std::function<bool(iter_t)>;
    kf_t kf = [](iter_t i) -> bool {
	return i.first < 2;
    };
    test_partition_map(testData, kf);
}

int main(int argc, char ** argv)
{
#if false
    test1();
    test2();
    test3();
#endif

    test4();
    test5();
    test6();

    return 0;
}
