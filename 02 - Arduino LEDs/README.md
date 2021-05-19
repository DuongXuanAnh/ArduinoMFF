
Write a program for Arduino UNO with attached Funshield, which will animate the following pattern on the four vertical LEDs. At any given moment, exactly one LED (of four) is turned on (we are starting with the topmost one). In each step of the animation, the active LED moves one slot down. When it hits the bottom, it bounces and moves upwards again, until it reaches top. The animation repeats itself forever.

One step of the animation takes exactly 300ms. Do  **not**  use  `delay()`  nor  `delayMicroseconds()`  function and do not block the main loop by other means. Use  `millis()`  function to measure, how much time actually passed.

See  [this video](https://youtu.be/5-UuEkL5oxI), which visualize the reference solution, to get a better idea.

### Submitting into ReCodEx

Submit  **only the  `solution.ino`**  file (the name must match exactly) in ReCodEx. The skeleton starter pack can be  [downloaded here](https://recodex.mff.cuni.cz/api/v1/uploaded-files/8d4ebc7b-6adc-11eb-a1a9-005056ad4f31/download). Use the supplied  [funshield.h](https://www.ksi.mff.cuni.cz/teaching/nswi170-web/download/Funshield.zip)  library in your solution for the pin identification constants (and related stuff).
