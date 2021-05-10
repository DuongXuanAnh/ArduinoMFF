
Write a program for Arduino UNO with attached Funshield, which will animate the following pattern on the four vertical LEDs. At any given moment, exactly one LED (of four) is turned on (we are starting with the topmost one). In each step of the animation, the active LED moves one slot down. When it hits the bottom, it bounces and moves upwards again, until it reaches top. The animation repeats itself forever.

One step of the animation takes exactly 300ms. Do  **not**  use  `delay()`  nor  `delayMicroseconds()`  function and do not block the main loop by other means. Use  `millis()`  function to measure, how much time actually passed

------------------------------------------------------------------------------------

Napište program pro Arduino UNO s připojeným Funshieldem, který bude animovat níže popsaný vzor na čtyřech vertikálních LED diodách. V každém okamžiku svítí právě jedna dioda ze 4, na počátku je to LED umístěná nejvýše. V každém kroku animace se aktivní LED posune o jedna níže. Když dorazí na spodek, odrazí se a vrací se krok za krokem zpět nahoru. Nahoře se opět odrazí a celý cyklus se opakuje do nekonečna.

Jeden krok animace trvá přesně 300ms. Ve vašem řešení, ale  **nesmíte**  používat funkci  `delay()`, ani  `delayMicroseconds()`, ani jinak blokovat hlavní smyčku. K měření uplynulého času použijte funkci  `millis()`.
