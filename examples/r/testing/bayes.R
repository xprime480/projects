p.to.decibels <- function(p) { -10 * log10((1-p)/p) }
decibels.to.p <- function(d) { 1 / (1+10^(-d/10)) }
bayes <- function(prior, true.positive, false.positive) {
  (prior * true.positive) / ((prior * true.positive) + ((1-prior) * false.positive))
}
