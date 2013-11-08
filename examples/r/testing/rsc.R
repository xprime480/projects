

rsc <- function(sequence, count) {
  s <- sample(sequence, count, TRUE)
  s.augmented <- append(s, sequence)
  t <- table(s.augmented) - 1
  t.augmented <- append(t,0:count)
  tt <- table(t.augmented) - 1
  b <- rev(as.vector(tt))
  b
}
