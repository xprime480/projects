#
# Demonstrate how to create a data frame from a frequency table, elminiating zeros
#
foo <- as.data.frame(rpois(10, 2))
names(foo) <- c('x')
foo$y <- rpois(10, 1.5)
bar <- as.data.frame(table(foo))
baz <- bar[bar$Freq>0,]
row.names(baz) <- NULL

rm(foo,bar)
