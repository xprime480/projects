

main <- function () {
  v1 <- 1:25
  v2 <- seq(0,1,length.out=200)
  layout(matrix(v1, nrow=5, ncol=5, byrow=TRUE))

  for ( n in v1 ) {
    plot(dbeta(v2, shape1=25, shape2=n),
         main=paste(25, ", ", n),
         xlab="",
         ylab="",
         lwt=1)
  }
}

main()








