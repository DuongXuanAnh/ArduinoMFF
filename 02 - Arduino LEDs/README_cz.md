Napište program pro Arduino UNO s připojeným Funshieldem, který bude animovat níže popsaný vzor na čtyřech vertikálních LED diodách. V každém okamžiku svítí právě jedna dioda ze 4, na počátku je to LED umístěná nejvýše. V každém kroku animace se aktivní LED posune o jedna níže. Když dorazí na spodek, odrazí se a vrací se krok za krokem zpět nahoru. Nahoře se opět odrazí a celý cyklus se opakuje do nekonečna.

Jeden krok animace trvá přesně 300ms. Ve vašem řešení, ale nesmíte používat funkci delay(), ani delayMicroseconds(), ani jinak blokovat hlavní smyčku. K měření uplynulého času použijte funkci millis().

Pro lepší představu se podívejte na toto video, kde je zachyceno vzorové řešení.

Odevzdání do ReCodExu
Do ReCodExu odevzdávejte pouze soubor solution.ino (musí být pojmenovaný přesně takto). Předpřipravený startovací balíček si můžete stáhnout zde. Ve vašem řešení použijte dodanou knihovnu funshield.h. Pro identifikátory pinů (a související věci) nevytvářejte si vlastní konstanty ani nepoužívejte číselné literály, ale výhradně jen konstanty z knihovny funshield.h.
