
The objective of this assignment is to turn funshield into a message notification panel. It receives messages from the computer (via USB serial link) and displays them on the 7-seg LED display as running text (i.e., text which is scrolling from right to left).

The starter pack can be  [downloaded here](https://recodex.mff.cuni.cz/api/v1/uploaded-files/b69a61fe-abf8-11eb-a1a9-005056ad4f31/download). The  `solution.ino`  already holds constants for individual letter glyphs (`a`-`z`) and a basic function that displays them individually. Please note that we do not distinguish between lowercase and uppercase since we had to mix these two to get recognizable glyphs. All non-letter characters are displayed as empty space (blank position).

The starter pack also contains header file  `input.h`  with  `SerialInputHandler`  structure (class) that encapsulates processing of the serial input. Its  `initialize()`  method must be invoked in  `setup()`  and  `updateInLoop()`  method in every  `loop()`. At the beginning and at the conclusion of scrolling of every message, the  `getMessage()`  will provide you with the next message to be displayed. The structure keeps the last message internally and it will return it until the next message is sent over.

Submit  **only the  `solution.ino`**  file (the name must match exactly) in ReCodEx. File  `input.h`  (on the other hand) must  **not**  be submitted as ReCodEx will provide  `SerialInputHandler`  implementation of its own designed for testing. As usual, do  **not**  use  `delay()`  nor  `delayMicroseconds()`  function and do not block the main loop by other means.

### Displaying the Message

Each message starts its scrolling when the display is empty (showing four empty spaces). The message moves from right to left and the interval between two shifts is exactly  `300 ms`. At the end, the message must entirely leave the display (i.e., as if there are 4 spaces at the end of every message). Thus, the display is rendered empty before the next message starts to scroll.

Please beware, the message may have less then 4 characters or it may be even empty. Nevertheless, it is still displayed using the same algorithm (i.e., empty string will actually cause the display to stay empty for  `1200 ms`).

_Example:_  the intermediate display states for message  `CAKE IS A LIE`  will look like the following (character  `_`  stands for an empty position).

```
___C
__CA
_CAK
CAKE
AKE_
KE_I
E_IS
_IS_
IS_A
S_A_
_A_L
A_LI
_LIE
LIE_
IE__
E___
____

```

Once the scrolling of a message is concluded, the application requests the following message using  `getMessage()`  method and starts displaying it immediately. The empty display is shown as one intermediate state between two (nonempty) messages (i.e., for  `300 ms`). Use time multiplexing you have learned in the previous assignment to display different characters at different positions.

### Testing

You may use  _Serial Monitor_  tool from Arduino IDE (menu  `Tools`  >  `Serial Monitor`), which some of you probably already use for debugging. The monitor allows for bidirectional communication. There is a text input box accompanied with  _Send_  button for sanding text lines over to Arduino device. The  `SerialInputHandler`  remembers only the last received message, so if you input multiple messages in short order, some of them may not be displayed at all.

See  [this video](https://youtu.be/YCbglNdO1Xo), which visualize the reference solution, to get a better idea.
