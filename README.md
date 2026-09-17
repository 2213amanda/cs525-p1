# Project 1

- Name: Amanda Tuttle
- Email: amandatuttle631@u.boisestate.edu
- Class: CS525

## Known Bugs or Issues

The only issue I know about is that the program does not currently use stdin to get the body of the message, but -b "message here" works in all tests.

## Experience

When I started this project, I spent quite a bit of time reading over the assignment and SMTP documentation, and while I understood the protocol
and the end goal of what I was supposed to implement I did struggle quite a bit with turning the idea into structured C code. I would honestly say this was the hardest part of the project for me, though it was not the only difficulty I encountered along the way.

An error that was very difficult to figure out for me was that even though I had included <netdb.h> to be able to use addrinfo and 
getaddrinfo(), vscode was angrily underlining addrinfo in my lab.h declarations, but then if I erased struct and rewrote it the underline would
go away. Then when I wrote getaddrinfo() in lab.c it was also not able to find the declaration. It turns out that some Linux systems control
which declarations are visible from system headers and I had to manually expose the version of POSIX containing these definitions (and here I
was using Linux because it was supposed to have the least problems!). 

I also had an issue when I was first starting writing tests, where the first test for parseArgs was running perfectly, the next test was failing, and some number of tests later was causing a very angry dramatic segmentation fault. I decided to figure out why the test was simply failing first because in that moment I wanted the seg fault to be a problem for later me, and after putting a debug point on just about every line of parseArgs I found out that optind wasn't being reset to 0 between tests and all I had to do was add one single line to lab-test setUp saying optind = 0 and it magically fixed all of my problems. 

While I was working towards 100% code coverage, I discovered that one of my test was failing successfully, but for the wrong reason. 
test_parseArgs_missing_from was set up so that -f had no argument and -t did, but it was simply interpreting -t as the argument for -f and failing 
because *to == NULL, and wasn't hitting the branch where -f had no argument. I fixed this by adding a test that only contained myapp -f as the input which successfully hit the branch.

Not an actual issue, but for the amusement of who reads this, I had commented out the first few RUN_TEST functions to make debugging easier while
I was working on code coverage, but forgot to uncomment those lines before running make report again, and was deeply confused as to how I'd managed
to make the coverage go *down*.

Overall, even though I did face quite a few struggles during this project, I did enjoy the debugging process and feel like I ended up with a good project.

## Design
Your Design section should explain the three layer split from Task 2 and why it is there.


