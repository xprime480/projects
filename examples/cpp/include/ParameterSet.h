// $Id: /home/I809989/test/cpp/ParameterSet.h#1 $
// $DateTime: Tue Apr 12 11:01:00 2011 $

#if ! defined(ParameterSet_h)
#define ParameterSet_h 1

#include <vector>
#include <string>

class ParameterSet;

/**
 * Parameters
 *
 * Class to encapsulate a set of parameters specified in a
 * ParameterSet.
 */
class Parameters
{
public:
  /**
   * constructor
   *
   * Create an instance of named parameter values
   *
   * @param ps the names of the parameters
   */
  Parameters(ParameterSet const & ps);

  /**
   * set
   *
   * Set the value associated with a name, if it exists
   *
   * @param name  the name of the parameter
   * @param value the updated value
   *
   * @throws runtime_error if @a name is not in the set.
   */
  void set(std::string const & name, double value);

  /**
   * get
   *
   * Look up the current value associated with a name, if it exists.
   *
   * @param name  the name of the parameter
   *
   * @return the current value
   *
   * @throws runtime_error if @a name is not in the set.
   */
  double get(std::string const & name);

protected:

private:
  /**
   * The names of the parameters in this instance
   */
  ParameterSet const & names;

  /**
   * The values of the parameters
   */
  std::vector<double> values;
};

/**
 * ParameterSet
 *
 * Class to encapsulate a set of parameter names, each of which is
 * unique in the set, and each of which is mapped to an index from
 * [0, #parms).  The indices are fixed as each parameter is added, and
 * parameters may not be removed once added.
 */
class ParameterSet 
{
public:
  /**
   * constructor
   *
   * Construct a set with no parameters.
   */
  ParameterSet();

  /**
   * constructor
   *
   * Construct a set with the passed range as the initial set of
   * parameters. 
   *
   * @param from the beginning of the range
   * @param to   the end of the range (not included)
   */
  template <typename IT>
  ParameterSet(IT from, IT to)
    : locked(false)
  {
    while ( from != to ) {
      append(*from++);
    }
  }

  /**
   * append
   *
   * Add a parameter name to the end of the range unless the same name
   * is already present.
   *
   * @param name the name of the new parameter.
   *
   * @return true iff the new name does not already exist in the set.
   */
  bool append(std::string const & name);

  /**
   * index
   *
   * Get the index of the parameter in the set
   *
   * @param name the name of the parameter
   *
   * @return a value from 0..n representing the index of the parameter
   *         in the set
   * 
   * @throws runtime_error if @a name is not in the set.
   */
  size_t index(std::string const & name) const;

  /**
   * count
   *
   * Get the number of parameters in the set
   *
   * @return the current parameters set size
   */
  size_t count() const;

  /**
   * at
   *
   * Get the name of the parameter at a given position
   *
   * @param pos the index to look at
   *
   * @throws std::out_of_range if @pos is not an index in the range
   *          [0, parms.size)
   */
  std::string at(size_t pos) const;

  /**
   * instance
   *
   * Create an instance of parameters with the names and ordering
   * given by this object.  After calling this function, no more
   * parameters may be added to the set.
   *
   * *** IMPORTANT ***
   *
   * The lifetime of the Parameters object returned by this function
   * must be bounded by the lifetime of the ParameterSet object whose
   * instance() method is called to create it.  If the ParameterSet
   * goes out of scope, the result of using the Parameters is
   * undefined.
   *
   * @return such an instance
   */
  Parameters instance();
  
protected:

private:

  /**
   * parameter type
   */
  typedef std::vector<std::string> parm_t;
  /**
   * iterator on the paramter type
   */
  typedef parm_t::const_iterator iter;

  /**
   * parameters
   */
  parm_t parms;

  /**
   * true when the user explicitly locks the set or an instance is
   * created. 
   */
  bool locked;

  /**
   * find
   *
   * Get an iterator to the named parameter
   *
   * @param name the name of the parameter to seek
   *
   * @return an iterator, possibly to the end of the container
   */
  iter find(std::string const & name) const;

  /**
   * begin
   *
   * Get the iterator to the start of the parameter list
   *
   * @return the iterator
   */
  iter begin() const;

  /**
   * end
   * 
   * Get the iterator to the end of the parameter list
   *
   * @return the iterator
   */
  iter end() const;
};

#endif // not defined ParameterSet_h
