plots <- function(data) {
  pdf("pistonrings.pdf")

  assoc(data)

  dev.off()
}

tests <- function(data) {
  chisq <- chisq.test(data)
  print(chisq)
  print(chisq$residuals)
}

main <- function() {
  data(pistonrings, package = "HSAUR2")
  
  plots(pistonrings)
  tests(pistonrings)
}

library("vcd")
main()
