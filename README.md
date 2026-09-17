# Project 1

- Name: Amanda Tuttle
- Email: amandatuttle631@u.boisestate.edu
- Class: CS525

## Known Bugs or Issues

The only issue I know of is that the program does not currently use stdin to get the body of the message, but -b "message here" works in all tests.

## Experience

When I started this project, I spent quite a bit of time reading over the assignment and SMTP documentation, and while I understood the protocol and the end goal of what I was supposed to implement I did struggle quite a bit with turning the idea into structured C code. I would honestly say this was the hardest part of the project for me, though it was not the only difficulty I encountered along the way.

An error that was very difficult to figure out for me was that even though I had included <netdb.h> to be able to use addrinfo and getaddrinfo(), vscode was angrily underlining addrinfo in my lab.h declarations, but then if I erased struct and rewrote it the underline would go away. Then when I wrote getaddrinfo() in lab.c it was also not able to find the declaration. It turns out that some Linux systems control which declarations are visible from system headers and I had to manually expose the version of POSIX containing these definitions (and here I was using Linux because it was supposed to have the least problems!). 

I also had an issue when I was first starting writing tests, where the first test for parseArgs was running perfectly, the next test was failing, and some number of tests later was causing a very angry dramatic segmentation fault. I decided to figure out why the test was simply failing first because in that moment I wanted the seg fault to be a problem for later me, and after putting a debug point on just about every line of parseArgs I found out that optind wasn't being reset to 0 between tests and all I had to do was add one single line to lab-test setUp saying optind = 0 and it magically fixed all of my problems. 

While I was working towards 100% code coverage, I discovered that one of my test was failing successfully, but for the wrong reason. test_parseArgs_missing_from was set up so that -f had no argument and -t did, but it was simply interpreting -t as the argument for -f and failing because *to == NULL, and wasn't hitting the branch where -f had no argument. I fixed this by adding a test that only contained myapp -f as the input which successfully hit the branch.

Not an actual issue, but for the amusement of who reads this, I had commented out the first few RUN_TEST functions to make debugging easier while I was working on code coverage, but forgot to uncomment those lines before running make report again, and was deeply confused as to how I'd managed to make the coverage go *down*.

Overall, even though I did face quite a few struggles during this project, I did enjoy the debugging process and feel like I ended up with a good project.

## Design
While my functions are not strictly separated into three layers, the functionality within them is. All of the unit tests run locally without touching a live mail server by creating local socket pairs.

Protocol helpers: 
- parseArgs parses the command line input and checks its validity. In the case of the unit tests, a char array is passed into the function and parsed. 
- sendMessage builds the message to be sent after DATA is acknowledged and dot stuffs the body. In the unit tests, the message is sent using one local socket and received using the another.
- getResponse parses the reply line and decides whether a reply line is the final one. This is done in the unit tests by sending a char array from one local socket and getting the response with the other. 

The session: 
- getResponse reads a line, reads a whole reply, and checks the received code against the expected code. This is done in unit tests using local socket pairs. 
- sendCommand writes and sends one command. This is done in the unit test using local socket pairs.

The socket transport: 
- resolveAddr uses the name or address of the server and calls getaddrinfo. This is unit tested by resolving the address of localhost, 127.0.0.1, and a fake server (which should fail, and does).
- serverConnect uses the results from resolveAddr and calls connect to establish connection to the server. This is unit tested by establishing connection to localhost.
- getResponse uses recv to get a response from the server. This is unit tested using local socket pairs. 
- sendCommand uses send to send commands to the server. This is unit tested using local socket pairs.
- sendMessage uses send to send the message (body) to the server. This is unit tested using local socket pairs. 




