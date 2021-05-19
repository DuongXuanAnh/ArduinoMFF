
V této úloze je cílem vytvořit zobrazovací panel pro textové zprávy, které jsou zadávány přes sériové rozhraní (USB) z připojeného počítače. Zprávy jsou zobrazovány na 7-seg. LED displeji jako běžící text (text, který se posouvá zprava doleva).

Předpřipravený startovací balíček si můžete  [stáhnout zde](https://recodex.mff.cuni.cz/api/v1/uploaded-files/b69a61fe-abf8-11eb-a1a9-005056ad4f31/download). V souboru  `solution.ino`  naleznete připravené konstanty pro jednotlivá písmena (`a`-`z`) pro 7-seg. displej a základní funkci, která je zobrazuje. Všimněte si, že nerozlišujeme malá a velká písmena (pro účely zobrazování jsme museli je namíchat aby bylo vůbec možné je smysluplně zobrazit) a znaky, které nejsou písmena, zobrazujeme jako mezeru (prázdnou pozici).

Dále je ve startovacím balíčku hlavičkový soubor  `input.h`  se strukturou  `SerialInputHandler`, která zapouzdřuje práci se sériovým vstupem. Metodu  `initialize()`  musíte zavolat v  `setup()`  a metodu  `updateInLoop()`  v každém volání  `loop()`. Po spuštění a po zobrazení každé zprávy si novou zprávu vyžádáte voláním  `getMessage()`. Struktura si drží poslední načtenou zprávu, takže ta se opakuje stále dokola dokud uživatel nepošle další.

Do ReCodExu  **odevzdávejte pouze soubor  `solution.ino`**  (musí být pojmenovaný přesně takto). Soubor  `input.h`  naopak  **odevzdat nesmíte**, ReCodEx si doplní vlastní se speciální implementací  `SerialInputHandler`  určenou pro testování. Jako obvykle ve vašem řešení  **nesmíte**  používat funkci  `delay()`, ani  `delayMicroseconds()`, ani jinak blokovat hlavní smyčku.

### Zobrazení zprávy

Na počátku zobrazení každé zprávy je displej prázdný. Zpráva se posouvá postupně zprava doleva, přičemž mezi dvěma posuny musí být  `300 ms`. Na konci se musí zpráva zcela odsunout z displeje -- tedy jako by za zprávou následovaly 4 prázdné znaky. Tím se docílí toho, že je displej prázdný a tedy připravený zobrazit další zprávu.

Nezapomeňte, že zpráva může být kratší než 4 znaky, nebo dokonce prázdný řetězec. V takovém případě se stále zobrazuje podle stejného algoritmu (tj. prázdný řetězec de facto odpovídá zobrazení prázdného displeje po dobu  `1200 ms`).

_Příklad:_  takto budou vypadat jednotlivé mezistavy displeje při zobrazení zprávy  `CAKE IS A LIE`  (znak  `_`  zde reprezentuje prázdnou pozici).

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

Jakmile je zobrazení zprávy ukončeno, váš kód si vyžádá voláním  `getMessage()`  následující zprávu a okamžitě započne s jejím zobrazováním. Mezi dvěma následujícími (neprázdnými) zprávami je prázdný displej zobrazován jako jeden mezistav (tedy právě  `300 ms`). Při zobrazování používejte časový multiplexing, stejně jako v minulé úloze.

### Testování

Pro testování můžete použít nástroj  _Serial Monitor_  z Arduino IDE (v menu  `Tools`  >  `Serial Monitor`), který pravděpodobně řada z vás již používá pro ladění. Monitor umožňuje obousměrnou komunikaci, v horní částí můžete napsat zprávu a tlačítkem  _Send_  ji odeslat.  `SerialInputHandler`  si pamatuje pouze poslední zadanou zprávu, takže pokud jich zadáte více rychle za sebou, zobrazí se pouze poslední z nich.

Pro lepší představu se podívejte na  [toto video](https://youtu.be/YCbglNdO1Xo), kde je zachyceno vzorové řešení.
