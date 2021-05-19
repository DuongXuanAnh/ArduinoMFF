
Napište počítadlo pro Arduino UNO s připojeným Funshieldem, jehož hodnota se bude zobrazovat na 7-segmentovém displeji tak, že vždy bude vidět jen 1 cifra (tj. neřešte problém multiplexingu).

Počítadlo je celočíselná hodnota 0-9999, která je zobrazována na čtyřciferném 7-segmentovém LED displeji na Funshieldu (standardně dekadicky, jednotky jsou nejvíce vpravo). Na displeji svítí v jednom okamžiku právě jedna cifra (na počátku je to cifra jednotek). Pomocí třetího tlačítka je možné měnit, která cifra (řád) je právě zobrazena a tak si uživatel může přečíst postupně celé zobrazovaná číslo (hodnotu počítadla). Čísla, která mají méně než 4 cifry, zobrazujeme s úvodními nulami (např. číslo 42 chápeme jako  `0042`).

První dvě tlačítka slouží jako inkrement resp. dekrement počítadla (přesněji vybraného řádu - viz dále) v modulární aritmetice (mod 10000). Na počátku (po startu zařízení) má počítadlo hodnotu 0.

Tlačítka fungují následovně:

-   **Třetí**  tlačítko při stisku změní výběr řádu, který je právě zobrazován na displeji. Na počátku je zobrazován řád jednotek, stiskem tlačítka je možné to změnit postupně na desítky, stovky, tisíce a následně zpět na jednotky.
-   **První**  tlačítko provede při stisku inkrement, ale v řádu, který odpovídá cifře právě zobrazované na displeji. Pokud jsou tedy zobrazovány jednotky, přičte se k počítadlu  `+1`, pokud desítky  `+10`  atd.
-   **Druhé**  tlačítko funguje analogicky jako první ale provádí dekrement, tedy dle vybraného řádu provede  `-1`,  `-10`,  `-100`  nebo  `-1000`.

Pro lepší představu se podívejte na  [toto video](https://youtu.be/F9afOP5Jq-8), kde je zachyceno vzorové řešení.

### Odevzdání do ReCodExu

Do ReCodExu  **odevzdávejte pouze soubor  `solution.ino`**  (musí být pojmenovaný přesně takto). Předpřipravený startovací balíček si můžete  [stáhnout zde](https://recodex.mff.cuni.cz/api/v1/uploaded-files/fba912cf-95f6-11eb-a1a9-005056ad4f31/download), naleznete v něm mimo jiné také připravené konstanty pro 7-seg. displej (tedy jak mají vypadat číslice).

Ve vašem řešení, ale  **nesmíte**  používat funkci  `delay()`, ani  `delayMicroseconds()`, ani jinak blokovat hlavní smyčku. K měření uplynulého času použijte funkci  `millis()`. Pro identifikátory pinů (a související věci) nevytvářejte si vlastní konstanty ani nepoužívejte číselné literály, ale výhradně jen konstanty z knihovny  [funshield.h](https://www.ksi.mff.cuni.cz/teaching/nswi170-web/download/Funshield.zip).
