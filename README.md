# 8 Bit Breadboard CPU & IR Programmer

## Background 

My 8 bit breadboard CPU which is based on the project done by Ben Eater. 

I built this project a year or two ago, and decided it was time to do a short upload up of my build, along with the custom infrared (IR) programmer code that I wrote to extend the ease-of-use for this CPU. 

Overall, this was a long and fascinating project that is excellent for people who are curious about low level electronics, a skill that seems to be all but lost in modern times!

![IMG_0307_final](https://github.com/scassar/8-bit-computer-and-IR-programmer/assets/2356898/472b002d-fa68-478e-a859-dd355f245c4f)

As Ben's initial solution has programs loaded into memory via dip switches, I decided to improve this by adding an Arduino Nano alongside an IR reciever (details and images below) - to allow programs to be loaded remotely. Some of the functions of the IR programmer are: 

- Take control of the 8 bit CPU bus, and perform a number of operations to set up the computers programs
- Load pre-defined sample programs (such as a program that counts up by 1 indefinitely) by the simple press of a button
- Manually load a program using a "set" control button, followed by the sequences of binary 1's and 0's to set the command
- Manually select a memory address to store the above set command
- Give back control of the bus for program execution

For years, I had always wanted to build my own CPU. You can only imagine my excitement when I found out that someone on the internet provided an intuitive and great starting point. It was also nice that Ben packaged up many of the components with his kits, to avoid needing to source these myself. Its a little more difficult I found to source some components here in Australia.

## IR Reciever 

Below is some images of the IR reciever setup on the board, and the controller. The parts list that I used can also be noted below:

The IR reciever is connected to the 8 bit bus, along with the clock pin distributed across the board. Its also required to connect the Arduino to the memory in control signal.

### Parts
- https://core-electronics.com.au/nano-v3-0-board.html?gad_source=1&gclid=CjwKCAjwkuqvBhAQEiwA65XxQJpYXAXOwPKtn18qe0lsqy8vpYezDvSV7x51v7jYjVpsFrxEQm39GxoCtZUQAvD_BwE
- https://www.jaycar.com.au/duinotech-arduino-compatible-infrared-receiver-module/p/XC4427
- https://www.jaycar.com.au/ir-remote-control-for-arduino/p/XC3718

![IMG_0306_final](https://github.com/scassar/8-bit-computer-and-IR-programmer/assets/2356898/01f6855e-f359-455b-bf5d-0f73cf9204d9)
![IMG_0310(1)_res](https://github.com/scassar/8-bit-computer-and-IR-programmer/assets/2356898/6569df7d-8dbc-4f28-9ad9-584304de99b7)


## Challenges

Unfortunately (and fortunately because it was a great learning experience) Ben's build came not without its issues. There were a number of aspects that seemed to work within Ben's videos that I found myself debugging for hours and needed to be addressed. Some of these include: 

1) Consistent power distribution across the boards. Had to solve this with numerous capacitors and more stable power adapter. Spliced into a USB cable and used an trusty Apple phone brick.
2) Monostable clock bouncing (solution discussed here. https://www.reddit.com/r/beneater/comments/edp1ls/noise_issue_in_monostable_mode_of_ben_eaters/)
3) Faulty 74LS00 Quad NAND GATE (nothing is worse than failing IC's)
4) Many others!

## Future plans for the build

While for now I have moved onto other projects, some of the things I would still like to do include the following: 

1) Drill a home and feed a power connector into the side of the display case, to deliver power to the board whilst on display
2) Use Arduino to kick switch between monostable and astable clock. Ideally, monostable pulse can be initiated using the arduino IR controller
3) Ability to reset the computer remotely

Most of these enhacements are just around allowing the computer to be interacted with remotely in its display box, and will not control any of the actual CPU functionality. I might look at expanding the CPU further after I have completed my 6502 project.

## Links: 
eater.net/8bit - Ben Eater's homepage
https://www.reddit.com/r/beneater/ - Helpful insights into similar builds






