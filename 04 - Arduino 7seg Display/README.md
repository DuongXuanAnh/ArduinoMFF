
Write a counter application for Arduino UNO with attached Funshield. The value of the counter will be projected on 7-segment LED display so that exactly one digit is visible at any given time (i.e., we are not going to use multiplexing to show multiple digits).

The counter holds value in 0-9999 range which should be displayed on the four-digit 7-segment LED display in standard decadic format (units are the rightmost digits). Exactly one digit (one order) is lit at any given time, the order of units is selected at the beginning. The third button alternates, which digit is shown (i.e., which order is selected) so the user can read the whole number digit per digit. Values which do not have 4 digits (lesser than  `1000`) are displayed with leading zeroes (e.g., value 42 is displayed as  `0042`).

The first two buttons work as increment and decrement respectively modifying the counter according to the selected order (as explained in the following text). The counter is modified in modular arithmetic (mod 10,000). When the device is started, the counter is set to 0.

The operations of individual buttons are:

-   **Button #3**  selects the displayed digit (order). At the beginning, the order of units is selected (the rightmost digit). Clicking the button changes the the order to tens, hundreds, thousands, and then back to units.
-   **Button #1**  increments the currently selected digit when pressed (when the button goes down). In other words, if the order of units is selected,  `+1`  is added to the counter. If order of tens is selected,  `+10`  is added and so on.
-   **Button #2**  works in the same way as button #1, but it decrements the value (i.e., adds  `-1`,  `-10`,  `-100`, or  `-1000`  to the counter depending on currently selected order).

See  [this video](https://youtu.be/F9afOP5Jq-8), which visualize the reference solution, to get a better idea.

### Submitting into ReCodEx

Submit  **only the  `solution.ino`**  file (the name must match exactly) in ReCodEx. The skeleton starter pack can be  [downloaded here](https://recodex.mff.cuni.cz/api/v1/uploaded-files/fba912cf-95f6-11eb-a1a9-005056ad4f31/download). It also includes necessary constants for controlling 7-seg. display, namely how the numbers should look like on the display.

Do  **not**  use  `delay()`  nor  `delayMicroseconds()`  function and do not block the main loop by other means. Use  `millis()`  function to measure, how much time actually passed. Use the supplied  [funshield.h](https://www.ksi.mff.cuni.cz/teaching/nswi170-web/download/Funshield.zip)  library in your solution for the pin identification constants (and related stuff).
