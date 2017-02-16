
library(LaF)
library(ggplot2)
library(dplyr)

m <- detect_dm_csv("../data/panden.csv", sep = ";", dec = ".", header = TRUE)

m$columns$type[m$columns$name == "x"] <- "double"
m$columns$type[m$columns$name == "y"] <- "double"
laf <- laf_open(m)


chunksize <- 1E6
nrow <- nrow(laf)
nchunks <- ceiling(nrow/chunksize)

dta <- vector("list", nchunks)

begin(laf)
for (i in seq_len(nchunks)) {
  dta[[i]] <-  next_block(laf, nrow = chunksize, col = c(7,8)) %>% 
    mutate(x = round(x/25)*25, y = round(y/25)*25) %>% 
    group_by(x, y) %>% summarise(n = n())
  cat(i, "/", nchunks, "\n", sep ="")
}

dta <- dta %>% bind_rows(dta) %>% group_by(x, y) %>% 
  summarise(n = sum(n))


