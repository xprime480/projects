
plots <- function(data) {
  pdf("water.pdf")

  nf <- layout(matrix(c(2,0,1,3), 2, 2, byrow = TRUE),
               c(2,1),
               c(1,2),
               TRUE)

  psymb <- as.numeric(water$location)
  fm <- mortality ~ hardness
  
  plot(fm, data = water, pch = psymb)
  abline(lm(fm, data = water))
  legend("topright", legend = levels(water$location), pch = c(1,2), bty = "n")

  lab <- "Water hardness (ppm Ca)"
  hist(water$hardness, xlab = lab, main = "")

  boxplot(water$mortality)

  dev.off()
}

tests <- function(data) {
  print(cor.test(~ mortality + hardness, data = data))
}

main <- function() {
  data(water, package = "HSAUR2")
  
  plots(water)
  tests(water)
}


main()
quit("no")
