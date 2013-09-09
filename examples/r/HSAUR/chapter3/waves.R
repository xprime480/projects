
plots <- function(data) {
  pdf("waves.pdf")

  lab <- "Differences (Newon meters)"

  layout(matrix(1:2, ncol = 2))

  boxplot(data,
          ylab = lab,
          main = "Boxplot")
  abline(h = 0, lty = 2)

  qqplot <- function(data, label) {
    qqnorm(data, ylab = label)
    qqline(data)
  }

  qqplot(data , lab)

  dev.off()
}

tests <- function(data) {
  print(t.test(data))
  print(wilcox.test(data))
}

main <- function() {
  data(waves, package = "HSAUR2")
  mooringdiff <- waves$method1 - waves$method2

  plots(mooringdiff)
  tests(mooringdiff)
}


main()
quit("no")
