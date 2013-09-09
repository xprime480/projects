#
# create a matrix of normal values representing returns
# each row is one period
# each column is one asset class
#
ts <- function(classes=16,periods=240,mean=1,sd=.03) {
  return (matrix(rnorm(classes * periods,
                       mean = mean,
                       sd=sd),
                 periods,
                 classes))
}

#
# given a matrix of returns, compute the returns with (or without)
# asset class balancing.  When balancing is used, apply the given
# fees per balancing period
#
sim <- function(perf,balance=TRUE,fees=0.0) {
  classes <- length(perf[1,])
  periods <- length(perf[,1])
  values <- rep(10000,classes)
  port <- c(sum(values))
  for ( per in 1:periods ) {
    values <- values * perf[per,]
    if ( balance ) {
      values <- rep(mean(values) - fees, classes)
    }
    port <- c(port, sum(values))
  }

  return (port)
}



