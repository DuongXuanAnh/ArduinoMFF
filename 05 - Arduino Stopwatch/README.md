
Design and implement a Stopwatch based on Arduino UNO with attached Funshield. The stopwatch must measure the time internally in milliseconds and display the measured values on the 7-segment LED display with 0.1s precision (including the decimal dot, rounding down). The number should be displayed in regular decadic format used in Czech Republic (no leading zeros except one right before the decimal dot). The stopwatch is zeroed at the beginning (i.e., displaying only  `0.0`  aligned right).

### Stopwatch Controls

The stopwatch is always in one of three logical states (`stopped`,  `running`, or  `lapped`). In the  `stopped`  state, internal clock are not advanced and the display is showing the last measured value (this state is also the initial state after boot). In the  `running`  state, the internal clock is measuring passed time and the value on the display is updated continuously. In the  `lapped`  state, the stopwatch is still running (collecting time), but the display is frozen -- showing the value which was actual when the lapped state was initiated. The transition diagram looks as follows:

-   **Button 1**  performs the start/stop function. It has no bearing in the  `lapped`  state.
-   **Button 2**  freezes/unfreezes (laps/un-laps) the time. It has no bearing in the  `stopped`  state.
-   **Button 3**  works only in the  `stopped`  state and it resets the stopwatch (sets internal time counter to 0).

See  [this video](https://youtu.be/wT15zxqQthM), which visualize the reference solution, to get a better idea.

**Warning:**  If you decide to implement button debouncing as well (not explicitly required here), please bear in mind that this assignment is tested beyond human capabilities in ReCodEx. Namely, we are using rather extreme timing for button actions. However, you can rely on the fact that the shortest button downtime or uptime (i.e., time between two subsequent button events) would be at least  `50ms`.

### Multiplexing the Display

We need to solve the matrix-control issue of the 7-seg LED display, so we can display arbitrary numbers on it. The problem is that the shift register can hold only one glyph at a time, but we might need to display different digits at individual positions. For this purpose we employ technique called  _time multiplexing_. Each position will be given a short time slot when its value is being displayed and these slots are alternating in rapid order. If the frequency is high enough, the human eye would not be able to recognize the slot changes and would be convinced that all positions are active simultaneously. The main idea is captured at the end of  [this video](https://youtu.be/Nwst00RFC58).

_Example:_  we would like to display  `1234`. Hence, we will be displaying a sequence  `1___`,  `_2__`,  `__3_`, and  `___4`  in a loop (`_`  denotes blank position). To achieve best result, each slot should take the same time on average.

In some situations, it might be possible to optimize the algorithm. For instance, number  `4254`  can be displayed using only three slots (`4__4`,  `_2__`, and  `__5_`) since the shift registers can allow the same digit to be visible at multiple positions simultaneously. However, this optimization  **is not required no recommended**. We would encourage you to divert your effort and attention to the  **correct code decomposition**  so you separate the display management and the stopwatch application (and the buttons handling) as much as possible. That way you could re-use some parts of your code in the future assignments.

### Submitting into ReCodEx

Submit  **only the  `solution.ino`**  file (the name must match exactly) in ReCodEx. The skeleton starter pack can be  [downloaded here](https://recodex.mff.cuni.cz/api/v1/uploaded-files/fba912cf-95f6-11eb-a1a9-005056ad4f31/download). It also includes necessary constants for controlling 7-seg. display, namely how the numbers should look like on the display.

Do  **not**  use  `delay()`  nor  `delayMicroseconds()`  function and do not block the main loop by other means. Use  `millis()`  function to measure, how much time actually passed. Use the supplied  [funshield.h](https://www.ksi.mff.cuni.cz/teaching/nswi170-web/download/Funshield.zip)  library in your solution for the pin identification constants (and related stuff).
