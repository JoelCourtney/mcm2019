require(ggplot2)

control = read.csv("data/control.csv",header=FALSE,sep=",")
control$time = control$V1

ggplot(control, aes(x=time)) +
  geom_histogram(binwidth=100) +
  xlab("Time Taken (ticks)") +
  ylab("Number of Occurrences (out of 250)") +
  ggtitle("Histogram of Simulation Times for Control") +
  xlim(2500, 11000)

vspeople = read.csv("data/vspeople.csv",header=FALSE,sep=",")
vspeople$time = vspeople$V1
vspeople$people = c(seq(from=1000, to=20000, by=50), seq(from=20400,to=100000,by=400))

ggplot(vspeople, aes(x=people,y=time)) +
  geom_point(size=0.5) +
  ggtitle("Simulation Time vs Initial Number of People") +
  xlab("Initial People (people") +
  ylab("Simulation Time (ticks)")
