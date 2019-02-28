require(ggplot2)

control = read.csv("data/control.csv",header=FALSE,sep=",")
control$time = control$V1

mean(control$time)
sd(control$time)

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
mod = lm(vspeople$time ~ vspeople$people^2)
summary(mod)

vswait = read.csv("data/vswait.csv",header=FALSE,sep=",")
vswait$time = vswait$V1
vswait$wait = rep(seq(from=1,to=59,by=1),each=3)
ggplot(vswait, aes(x=wait,y=time)) +
  geom_point(size=0.5) +
  ggtitle("Simulation Time vs Stair Traversal Time") +
  xlab("Stair Traversal Time (ticks)") +
  ylab("Simulation Time (ticks)")

vsbias = read.csv("data/vsbias.csv",header=FALSE,sep=",")
vsbias$time = vsbias$V1
vsbias$bias = rep(seq(from=15,to=1,by=-1),each=5)
ggplot(vsbias, aes(x=bias,y=time)) +
  geom_point(size=0.5) +
  geom_smooth() +
  ggtitle("Simulation Time vs Room Distribution Bias") +
  xlab("Room Distribution Bias (unitless)") +
  ylab("Simulation Time (ticks)") +
  ylim(4000,8000)
