Concurrency 3 Testing Instructions

Run make to compile problem 1 and 2.

Problem 1:
You should see three threads (processes) will begin using a resource. The program will output which of the 10 threads have the resource with a max of three using it at a time. Once there are three processes using the resource, all three will leave before any new processes can begin using it. The program will run until exited and you should see that the mutual exclusion condition is satisfied. I implemented the "I’ll Do It For You" algorithm from https://pdfs.semanticscholar.org/93af/99143f8123032fbcc805656d63617a2268ab.pdf.

Problem2:
For each of the operations of searching, inserting, and deleting there are five threads dedicated. The program's output shows the state of these threads as their functions are ran concurrently. If a delete thread is running, no other thread will be allowed to execute its critical piece. If an insert thread is running, search threads may run; however, no other insert thread will run. Any number of search threads can run as long as we are not deleting.

The program will go on forever using these five threads so "contol+c" after enough output to test the functionality of the program has been printed.
