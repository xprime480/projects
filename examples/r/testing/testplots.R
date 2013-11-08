
relative.weights <- function (weights) {
  weights / sum(weights)
}

random.norm <- function (points) {
  mu = runif(1, 0, 4)
  sigma = runif(1, 0.5, 2.5)
  dnorm(points, mean=mu, sd=sigma)
}

composite.norm <- function (ncurves=3, npoints=201) {

  points <- seq(-4, 8, length.out = npoints)
  
  weights <- relative.weights(runif(ncurves))
  ds = matrix(0, nrow=npoints, ncol=ncurves)
  for ( x in 1:ncurves ) {
    ds[,x] = random.norm(points) * weights[x]
  }

  d <- rowSums(ds)
  
  ymin <- min(ds, d) 
  ymax <- max(ds, d)
  
  plot(points, d, type="l", ylim=c(ymin, ymax), lwd=3)
  
  colors = sample(c("red", "blue", "green", "orange"), ncurves)
  for ( x in 1:ncurves ) {
    lines(points, ds[,x], col=colors[x])
  }
}


for ( x in 1:10 ) {
  composite.norm(4)
}
