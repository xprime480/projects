
stats <- function(data, convert) {
  print("Quartiles by measurment unit", quote = FALSE)
  print(tapply(data$width * convert, data$unit, summary))
  print("Standard deviation by measurment unit", quote = FALSE)
  print(tapply(data$width * convert, data$unit, sd))
}


plots <- function(data, convert) {
  pdf("roomwidth.pdf")

  layout(matrix(c(1,2,1,3),
                nrow = 2,
                ncol = 2,
                byrow = FALSE))

  boxplot(I(width * convert) ~ unit,
          data = data,
          ylab = "Estimated width (feet)",
          varwidth = TRUE,
          names = c("Estimates in feet",
                    "Estimates in meters (converted to feet)"))

  feet <- data$unit == "feet"

  qqplot <- function(data, label) {
    qqnorm(data, ylab = label)
    qqline(data)
  }

  qqplot(data$width[feet] , "Estimated width (feet)")
  qqplot(data$width[!feet], "Estimated width (meters)")

  dev.off()
}

tests <- function(data, convert) {
  fm <- I(width * convert) ~ unit

  print(t.test(fm,
               data = roomwidth,
               var.equal = TRUE))
  print(t.test(fm,
               data = roomwidth,
               var.equal = FALSE))
  print(wilcox.test(fm,
                    data = roomwidth,
                    conf.int = TRUE))
}

main <- function() {
  data(roomwidth, package = "HSAUR2")
  convert <- ifelse(roomwidth$unit == "feet", 1, 3.28)

  stats(roomwidth, convert)
  plots(roomwidth, convert)
  tests(roomwidth, convert)
}

main()
quit("no")
