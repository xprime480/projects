#if ! defined( PosetItems_2D_h )
#define PosetItems_2D_h 1

#include <iosfwd>
#include <fstream>

#include "Point.h"
#include "PosetItems.h"

/*!
  \brief number of dimensions in the point type
*/
static size_t const NDIMS = 2;

/*!
  \brief the point type
*/
typedef Point< NDIMS > Point_2D;

/*!
  \brief an interface to manage a poset consisting of points with 2
  indexes.

  This class serves as a base class for two further implementation
  classes defined below.
*/
struct PosetItems_2D : public PosetItems< Point_2D >
{
  /*!
    \brief type of one item in the set
  */
  typedef PosetItems< Point_2D >::PosetItemType PosetItemType;

  /*!
    \brief process a point

    This version writes out some commands for a TCL file
    
    \param a the point
  */
  virtual void point( PosetItemType const & a );

  /*!
    \brief process an edge in the Hasse diagram

    This version writes out some commands for a TCL file
    
    \param a the lesser value
    \param b the greater value

  */
  virtual void edge( PosetItemType const & a, PosetItemType const & b );
};

/*!
  \brief randomly generated 2D points
*/
struct PosetItems_2D_Random : public PosetItems_2D
{
  /*!
    \brief type of one item in the set
  */
  typedef PosetItems_2D::PosetItemType PosetItemType;

  /*!
    \brief constructor
    
    \param c count of items
    \param max largest value of a single coordinate.
  */
  PosetItems_2D_Random( size_t count, size_t max = 10 );
  
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
  size_t max_dim;
};

/*!
  \brief 2D points read from a file
*/
struct PosetItems_2D_File : public PosetItems_2D
{
  /*!
    \brief type of one item in the set
  */
  typedef PosetItems< Point_2D >::PosetItemType PosetItemType;

  /*!
    \brief constructor
    
    \param data_file file name to read data from
  */
  PosetItems_2D_File( char const * data_file );
  
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
    \brief stream
  */
  std::ifstream data;

  bool     filled;
  Point_2D cache;
};




#endif
