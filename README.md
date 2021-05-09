# ArduinoMFF
Napište program pro Arduino UNO s pøipojeným Funshieldem, který bude animovat níže popsaný vzor na ètyøech vertikálních LED diodách. V každém okamžiku svítí právì jedna dioda ze 4, na poèátku je to LED umístìná nejvýše. V každém kroku animace se aktivní LED posune o jedna níže. Když dorazí na spodek, odrazí se a vrací se krok za krokem zpìt nahoru. Nahoøe se opìt odrazí a celý cyklus se opakuje do nekoneèna.

Jeden krok animace trvá pøesnì 300ms. Ve vašem øešení, ale nesmíte používat funkci delay(), ani delayMicroseconds(), ani jinak blokovat hlavní smyèku. K mìøení uplynulého èasu použijte funkci millis().

Pro lepší pøedstavu se podívejte na toto video, kde je zachyceno vzorové øešení.

Odevzdání do ReCodExu
Do ReCodExu odevzdávejte pouze soubor solution.ino (musí být pojmenovaný pøesnì takto). Pøedpøipravený startovací balíèek si mùžete stáhnout zde. Ve vašem øešení použijte dodanou knihovnu funshield.h. Pro identifikátory pinù (a související vìci) nevytváøejte si vlastní konstanty ani nepoužívejte èíselné literály, ale výhradnì jen konstanty z knihovny funshield.h.