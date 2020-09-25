# A9 free
## What is the A9
The A9 is based on a system-on-a-chip namely RDA8955, made by RDA Technologies.
It is a very powerful and versatile GSM/GPRS-capable microcontroller that
was definitely conceived for mobile use, and probably used by various mobile
phone manufacturers during the 2000's (personal opinion). A GPS-enabled version
is also available, called A9G.

## What is this project
The A9 currently depends on a set of proprietary tools and firmware blobs that
have been left unmantained since 2018 by its manufacturer, Ai-Thinker.
Therefore, this project aims to maintain the A9 and A9G by creating a free
(as in freedom) version developed by the community. The A9 and A9G have great
potential as IoT devices or even to build low-spec smartphones entirely based
in free software.

## What has been developed so far
Currently, no free firmware has been developed yet. The project is on a very
initial phase where we need to know as much as possible about the system
(e.g.: reverse-engineering) so we can start developing free software for it.
`doc/notes.txt` contains a growing amount of information about what has been
found so far and what still needs to be studied in further detail.

This is a list of ToDo things for this project:

 - [x] De-compile firmware blobs using an automated tool e.g.: Ghidra.
 - [ ] Understand how the flashing process works.
 - [ ] Write minimal working example that runs on the hardware.
 - [ ] Write sample applications that interact with the hardware peripherals.
 - [ ] Port newlib and FreeRTOS to replace existing custom implementations.
 - [ ] Write a free bootloader that allows uploading application code.
 - [ ] Implement a free GSM/GPRS stack.
 - [ ] Implement a free GPS stack.

## How to contribute
This is a very ambitious project that definitely takes a lot of time and
resources. I am currently alone at this, and it is impossible to achieve all
these targets without your support. So I encourage anyone interested in this
project to join and help the project to become a reality. I think the A9 has
a lot of potential that the community can benefit from.

So please review `doc/notes.txt`, give your feedback, provide new information
and help development that allows us to use the A9 with free software only.
Despite being based on closed-source binaries, the repositores provided by
Ai-Thinker already include lots of documentation that will surely help us in
knowing about the inner details on the A9 and the binaries themselves.
