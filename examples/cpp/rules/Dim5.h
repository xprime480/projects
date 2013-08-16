#if ! defined( Dim5_h ) 
#define Dim5_h 1

#include <iosfwd>

#include "Point.h"
#include "PosetItems.h"

/*!
  \brief an interface to manage a poset consisting of points with 5
  indexes.

  The points are generated randomly according to the spec given by the
  creator. 
*/
struct Dim5 : public PosetItems< Point< 5 > >
{
  /*!
    \brief type of our base class
  */
  typedef PosetItems< Point< 5 > > Base;

  /*!
    \brief type of one item in the set
  */
  typedef Base::PosetItemType PosetItemType;

  /*!
    \brief constructor
    
    \param c count of items
    \param max largest value of a single coordinate.
  */
  Dim5( size_t c, int max );

  /*!
    \brief true if there are more points to be generated

    \return the answer
  */
  virtual bool hasMore() const;

  /*!
    \brief return a random point

    \return a point, even if \a hasMore returns false
  */
  virtual PosetItemType next();

  /*!
    \brief process a point

    This overload does nothing
    
    \param a the point
  */
  virtual void point( PosetItemType const & a );

  /*!
    \brief process an edge in the Hasse diagram

    This overload logs to stdout
    
    \param a the lesser value
    \param b the greater value

  */
  virtual void edge( PosetItemType const & a, PosetItemType const & b );

  /*!
    \brief Get an item guaranteed to be less than any other item

    \return the item
  */
  virtual PosetItemType origin() const;

  /*!
    \brief Get an item guaranteed to be greater than any other item

    \return the item
  */
  virtual PosetItemType infinity() const;

private:
  /*!
    \brief number of points to create
  */
  size_t max_count;

  /*!
    \brief number of points created so far
  */
  size_t current;

  /*!
    \brief maximum value for a point
  */
  int    max_val;
};

#endif
