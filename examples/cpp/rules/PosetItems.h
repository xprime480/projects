#if ! defined( PosetItems_h )
#define PosetItems_h 1

#include <iosfwd>

/*!
  \brief A group of related function for items in a set with a partial 
         ordering.
*/
template < typename T >
struct PosetItems
{
  /*!
    \brief type of one item in the set
  */
  typedef T PosetItemType;
  
  /*!
    \brief true if there are more points to be generated

    \return the answer
  */
  virtual bool hasMore() const = 0;

  /*!
    \brief return the next point

    \return a point, generated according the the derived class' rules
  */
  virtual PosetItemType next() = 0;

  /*!
    \brief report if one point is less than another
    
    \param a first point
    \param b second point

    \return true iff a < b.
  */
  virtual bool less( PosetItemType const & a, PosetItemType const & b ) const
  {
    return a < b;
  }

  /*!
    \brief process a point

    The derived class may log it, write it to a database, or take some
    other action.

    \param a the point
  */
  virtual void point( PosetItemType const & a ) = 0;

  /*!
    \brief process an edge in the Hasse diagram

    The derived class may log it, write it to a database, or take some
    other action.
    
    \param a the lesser value
    \param b the greater value

  */
  virtual void edge( PosetItemType const & a, PosetItemType const & b ) = 0;

  /*!
    \brief Get an item guaranteed to be less than any other item

    \return the item
  */
  virtual PosetItemType origin() const = 0;

  /*!
    \brief Get an item guaranteed to be greater than any other item

    \return the item
  */
  virtual PosetItemType infinity() const = 0;
};

#endif
