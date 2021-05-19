Navrhněte a naimplementujte stopky na Arudino UNO s připojeným Funshieldem. Stopky musí měřit interně čas s přesností na milisekundy a zobrazovat naměřenou hodnotu na 7-segmentovém displeji s přesností na 0.1s (včetně desetinné tečky, zaokrouhlujeme dolů). K zobrazení používáme dekadický formát obvyklý u nás bez zobrazení úvodních nul (vyjma nuly těsně před desetinnou tečkou). Na počátku jsou stopky vynulované (na displeji se zobrazuje 0.0, první dvě pozice jsou prázdné).

Řízení stopek
Stopky jsou vždy v jednom ze tří logických stavů (stopped, running nebo lapped). Ve stavu stopped je časomíra zastavena a displej zobrazuje poslední naměřený čas (toto je také výchozí stav po spuštění). Ve stavu running probíhá měření času a průběžně se aktualizuje hodnota zobrazovaná na displeji. Ve stavu lapped dále probíhá měření času, ale displej zobrazuje poslední hodnotu, která byla aktuální v okamžik přechodem do stavu lapped. Přechodový diagram vypadá následovně:


![schema.png](https://github.com/DuongXuanAnh/ArduinoMFF/blob/main/05%20-%20Arduino%20Stopwatch/schema.png?raw=true)


Tlačítko 1 provede spuštění resp. zastavení stopek. Ve stavu lapped neprovádí žádnou akci.
Tlačítko 2 zmrazí/obnoví průběžné zobrazování času, pokud stopky běží. Ve stavu stopped neprovádí žádnou akci.
Tlačítko 3 funguje pouze ve stavu stopped a při stisknutí vynuluje časomíru.
Pro lepší představu se podívejte na toto video, kde je zachyceno vzorové řešení.

Upozornění: Pokud se rozhodnete implementovat také filtrování zákmitů tlačítek (což není vyžadováno), mějte na paměti, že tato úloha bude v ReCodExu testována i extrémnějším způsobem, než byt to dokázal člověk s fyzickým zařízením. Nejkratší stisky tlačítek mohou trvat jen 50ms a mezi uvolněním a opětovným stiskem tlačítka může být rovněž pouze 50ms (kratší intervaly nebudou použity).

Displej a multiplexing
Při zobrazování hodnot na displeji je potřeba se vypořádat s faktem, že displej je maticově řízen pomocí posuvného registru (tj. registr může držet pouze jednu číslici v jednom okamžiku). Abychom mohli zobrazovat různé hodnoty na různých pozicích, použijeme časový multiplexing, tedy techniku, kdy každá číslice dostane vyhrazený krátký časový slot ve kterém je zobrazována. Tyto časové sloty se pravidelně střídají v rychlém sledu, aby lidské oko nebylo schopné rozeznat, že dochází k problikávání jednotlivých pozic. Výsledkem je optická iluze, kdy má uživatel dojem, že jednotlivé pozice na displeji zobrazují různé cifry zároveň. Ukázka myšlenky multiplexingu je zachycena na konci tohoto videa.

Příklad: chceme zobrazit číslo 1234. Postupně tedy budeme zobrazovat 1___, _2__, __3_ a ___4 v rychlém sledu stále dokola (_ značí neaktivní pozici). Každá cifra by měla být zobrazována v průměru stejně dlouhou dobu.

V některých situacích by mohlo být možné zobrazovací cyklus optimalizovat. Např. číslo 4254 bychom mohli multiplexovat ve třech časových slotech (4__4, _2__ a __5_), protože maticové řízení umožnuje zobrazení stejné cifry na více pozicích najednou. Tato optimalizace ale není vyžadována a ani ji nedoporučujeme realizovat. Naopak je vhodné věnovat čas správné dekompozici kódu a co nejvíce oddělit logiku zobrazování čísel na displeji od zbytku aplikace tak, abyste mohli tento kód použít u dalších úloh.

Odevzdání do ReCodExu
Do ReCodExu odevzdávejte pouze soubor solution.ino (musí být pojmenovaný přesně takto). Předpřipravený startovací balíček si můžete stáhnout zde, naleznete v něm mimo jiné také připravené konstanty pro 7-seg. displej (tedy jak mají vypadat číslice).

Ve vašem řešení, ale nesmíte používat funkci delay(), ani delayMicroseconds(), ani jinak blokovat hlavní smyčku. K měření uplynulého času použijte funkci millis(). Pro identifikátory pinů (a související věci) nevytvářejte si vlastní konstanty ani nepoužívejte číselné literály, ale výhradně jen konstanty z knihovny funshield.h.
