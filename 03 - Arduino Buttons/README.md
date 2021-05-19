
Write a simple counter application for Arduino UNO with attached Funshield. The counter is an integer in 0-15 range, which is being displayed continuously on the four-LEDs stipe on the shield. Lowest bit is displayed at bottom LED (note that is  `led4_pin`, whilst  `led1_pin`  is topmost). The first two buttons act as increment and decrement for the counter in modular arithmetic (mod 16). The counter is set to 0 at the beginning (when the device boots).

The main objective is to implement a smart behavior of the buttons as follows:

-   When the first button is pressed (changes state from being up to being down), it increments the counter.
-   If the button is being held down, the application waits for 1000ms and then perform another increment. After that the increments will repeat periodically every 300ms until the button is released. The second button works analogically, but it decrements the counter instead. The buttons work independently. If they are both held, the counter is being both incremented and decremented (in due intervals).

_Example:_  The first button is pressed at time  `T`  and at  `T+2000`  (ms) it is released again. In this situation, the counter will be incremented at times  `T`,  `T+1000`,  `T+1300`,  `T+1600`, and  `T+1900`.

See  [this video](https://www.youtube.com/watch?v=Nf6J54v5oD4), which visualize the reference solution, to get a better idea.

### Submitting into ReCodEx

Submit  **only the  `solution.ino`**  file (the name must match exactly) in ReCodEx. The skeleton starter pack can be  [downloaded here](https://recodex.mff.cuni.cz/api/v1/uploaded-files/14d5b947-8e40-11eb-a1a9-005056ad4f31/download).

Do  **not**  use  `delay()`  nor  `delayMicroseconds()`  function and do not block the main loop by other means. Use  `millis()`  function to measure, how much time actually passed. Use the supplied  [funshield.h](https://www.ksi.mff.cuni.cz/teaching/nswi170-web/download/Funshield.zip)  library in your solution for the pin identification constants (and related stuff).
