Concurrency 2 testing intructions and solution information

Run make to compile both our concurrency2 program and our test_concurrency2 program which can be run with the test executable.

The test code shows how get and put forks correctly locks and unlocks mutexes . We have each philospher assigned to a number 1-5 and they sit around the table. The first philospher gets forks and the first two mutexes are locked as expected. The fourth philospher gets a fork and the fourth and fifth mutexes are locked. The final statement has them put the forks back and you see that all the mutexes are unlocked again. When you try to get a fork that is already picked up the program halts, which is why philosphers next to each other are never eating at the same time.

Our philosphers are in this order: "Aristotle","Plato","Voltaire","Galileo","Pythagoras"
Since they are sitting in a circle, Aristotle and Pytagoras also cannot eat at the same time.
When you run concurrency2, it may look like only 1 philospher is eating at a time intially, but that is due to being unlucky with thinking and eating times. If you run the program long enough you will see that more than a single philosopher is capable of eating simultaneously and everyone eventually eats.
