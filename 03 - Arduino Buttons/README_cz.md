
Napište jednoduché bitové počítadlo pro Arduino UNO s připojeným Funshieldem. Počítadlo je celočíselná hodnota 0-15, která je zobrazována na čtyřech řadových LED na Funshieldu. Nejnižší bit je zobrazen na nejníže položené LED (což je  `led4_pin`, zatímco  `led1_pin`  je nejvýše položená LED). První dvě tlačítka slouží jako inkrement resp. dekrement počítadla v modulární aritmetice (mod 16). Na počátku (po startu zařízení) má počítadlo hodnotu 0.

Hlavní těžiště práce je v implementaci chytrých tlačítek, která se chovají následovně:

-   Při stisknutí prvního tlačítka (v okamžiku, kdy došlo k jeho sepnutí) se provede inkrement počítadla.
-   Pokud je tlačítko dále drženo, po 1000ms proběhne další inkrement počítadla a to se bude dále opakovat každých 300ms až do okamžiku uvolnění tlačítka. Druhé tlačítko funguje analogicky, jen v daných časových okamžicích provádí dekrement místo inkrementu. Tlačítka pracují nezávisle na sobě, pokud jsou držena obě, provádí se inkrementy i dekrementy (v příslušných intervalech).

_Příklad:_  V čase  `T`  dojde ke stisknutí tlačítka a v čase  `T+2000`  (ms) dojde k jeho uvolnění. V takovém případě proběhne inkrementace počítadla v časech  `T`,  `T+1000`,  `T+1300`,  `T+1600`  a  `T+1900`.

Pro lepší představu se podívejte na  [toto video](https://www.youtube.com/watch?v=Nf6J54v5oD4), kde je zachyceno vzorové řešení.

### Odevzdání do ReCodExu

Do ReCodExu  **odevzdávejte pouze soubor  `solution.ino`**  (musí být pojmenovaný přesně takto). Předpřipravený startovací balíček si můžete  [stáhnout zde](https://recodex.mff.cuni.cz/api/v1/uploaded-files/14d5b947-8e40-11eb-a1a9-005056ad4f31/download).

Ve vašem řešení, ale  **nesmíte**  používat funkci  `delay()`, ani  `delayMicroseconds()`, ani jinak blokovat hlavní smyčku. K měření uplynulého času použijte funkci  `millis()`. Pro identifikátory pinů (a související věci) nevytvářejte si vlastní konstanty ani nepoužívejte číselné literály, ale výhradně jen konstanty z knihovny  [funshield.h](https://www.ksi.mff.cuni.cz/teaching/nswi170-web/download/Funshield.zip).
