Concurrency 3 Testing Instructions

Run make to compile problem 1 and 2.

Problem 1:
You should see three threads (processes) will begin using a resource. The program will output which of the 10 threads have the resource with a max of three using it at a time. Once there are three processes using the resource, all three will leave before any new processes can begin using it. The program will run until exited and you should see that the mutual exclusion condition is satisfied. I implemented the "I’ll Do It For You" algorithm from https://pdfs.semanticscholar.org/93af/99143f8123032fbcc805656d63617a2268ab.pdf.

Problem2:

