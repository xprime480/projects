
f <- function (s = 2) {
  c <- matrix(runif(s*1000), ncol=s)
  cr <- rowSums(c)
  hist(cr)
}

g <- function ( ... ) {
  print(all.names())
}
