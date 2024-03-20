# 8-bit-computer-and-IR-programmer

## Welcome 

Below is the write up of my 8 bit breadboard CPU which was based on the project uploaded on youtube by Ben Eater. This was a long and fascinating project that is excellent for people who are curious about low level electronics, a skill that seems to be all but lost in modern times. 

![IMG_0314_resize](https://github.com/scassar/8-bit-computer-and-IR-programmer/assets/2356898/5e4438e9-adc0-441e-8aff-2bd17cbc77e7)

As Ben's initial solution has programs loaded into memory by dip switches, I decided to improve this by adding an Arduino Nano alongside an IR reciever (details and images below) - to allow programs to be loaded remotely. Some of the functions of the IR programmer are: 

- Take control of the 8 bit CPU bus, and perform a number of operations to set up the computers programs
- Load sample programs (such as a program that counts up by 1 forever) by the simple press of 1 button
- Manually load a program using a "set" control button, followed by the sequences of binary 1's and 0's to set the command.
- Manually select a memory address to store the above set command
- Give back control of the bus for program execution

For years I had always wanted to build my own CPU. You can only imagine my excitement when I found out that someone on the internet provided an intuitive and great starting point. It was also nice that Ben packaged up many of the components, to avoid needing to source these myself. Its a little more difficult I found to source some components here in Australia.

## IR Reciever 

Below is some images of the IR reciever setup on the board, and the controller. The parts list that I used can also be noted below:

### Parts
- https://core-electronics.com.au/nano-v3-0-board.html?gad_source=1&gclid=CjwKCAjwkuqvBhAQEiwA65XxQJpYXAXOwPKtn18qe0lsqy8vpYezDvSV7x51v7jYjVpsFrxEQm39GxoCtZUQAvD_BwE
- https://www.jaycar.com.au/duinotech-arduino-compatible-infrared-receiver-module/p/XC4427
- https://www.jaycar.com.au/ir-remote-control-for-arduino/p/XC3718

![IMG_0306](https://github.com/scassar/8-bit-computer-and-IR-programmer/assets/2356898/01ce9b51-98b1-435b-93e5-3f2553715e89)
![IMG_0310(1)](https://github.com/scassar/8-bit-computer-and-IR-programmer/assets/2356898/a3868ed0-3cfa-432f-9d02-99b176bf259e)


## Challenges

Unfortunately (and fortunately) Ben Eaters build came not without its issues. There were a number of aspects that seemed to work within Bens videos that I found myself debugging for hours and needed to be addressed. Some of these include: 

1) Consistent power distrubiton across the boards
2) Monostable clock bouncing (Solution discussed here. https://www.reddit.com/r/beneater/comments/edp1ls/noise_issue_in_monostable_mode_of_ben_eaters/)
3) Faulty 74LS00 Quad NAND GATE (Nothing is worse than failing IC's)
4) Many others!

## Future plans for the build

While I have now moved onto other projects, some of the things I would still like to do include the following: 

1) Drill a power connector into the side of the display case, to deliver power to the board whilst on display
2) Use Arduino to kick switch between monostable and astable clock. Ideally, monostable pulse can be initiated using the arduino IR controller.
3) Ability to reset the computer remotely.

Most of these enhacements are just around allowing the computer to be interacted with remotely in its display box, and will not control any of the actual CPU functionality.

## Links: 
eater.net/8bit - Ben Eater's homepage





