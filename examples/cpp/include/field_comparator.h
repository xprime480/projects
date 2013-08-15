#if ! defined(field_comparator_h)
#define field_comparator_h 1

/*
 * base case, no fields, the objects are not meaningfully different
 */
inline bool field_comparator()
{
  return false;
}

/*
 * one field, if it compares different, return comparison of the
 * field, otherwise recurse
 */
template<typename T, typename V1>
inline bool field_comparator(T const & t1, T const & t2, V1 T::*pmv1)
{
  V1 const & v1 = t1.*pmv1;
  V1 const & v2 = t2.*pmv1;

  if (v1 != v2) {
    return v1 < v2;
  }

  return field_comparator();
}

/*
 * two fields, if first compares different, return comparison of that
 * field, otherwise recurse
 */
template<typename T, typename V1, typename V2>
inline bool field_comparator(T const & t1, T const & t2, V1 T::*pmv1, V2 T::*pmv2)
{
  V1 const & v1 = t1.*pmv1;
  V1 const & v2 = t2.*pmv1;

  if (v1 != v2) {
    return v1 < v2;
  }

  return field_comparator(t1, t2, pmv2);
}

/*
 * three fields, if first compares different, return comparison of that
 * field, otherwise recurse
 */
template<typename T, typename V1, typename V2, typename V3>
inline bool field_comparator(T const & t1, T const & t2, V1 T::*pmv1, V2 T::*pmv2, V3 T::*pmv3)
{
  V1 const & v1 = t1.*pmv1;
  V1 const & v2 = t2.*pmv1;

  if (v1 != v2) {
    return v1 < v2;
  }

  return field_comparator(t1, t2, pmv2, pmv3);
}


#endif
