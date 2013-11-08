trailing.nonzero <- function(x) {
  len = length(x)
  for ( t in 1:len ) {
    if ( x[t] != 0 ) {
      return (x[t:len])
    }
  }

  x[c()]
}
