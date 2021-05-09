# ArduinoMFF
Napi�te program pro Arduino UNO s p�ipojen�m Funshieldem, kter� bude animovat n�e popsan� vzor na �ty�ech vertik�ln�ch LED diod�ch. V ka�d�m okam�iku sv�t� pr�v� jedna dioda ze 4, na po��tku je to LED um�st�n� nejv��e. V ka�d�m kroku animace se aktivn� LED posune o jedna n�e. Kdy� doraz� na spodek, odraz� se a vrac� se krok za krokem zp�t nahoru. Naho�e se op�t odraz� a cel� cyklus se opakuje do nekone�na.

Jeden krok animace trv� p�esn� 300ms. Ve va�em �e�en�, ale nesm�te pou��vat funkci delay(), ani delayMicroseconds(), ani jinak blokovat hlavn� smy�ku. K m��en� uplynul�ho �asu pou�ijte funkci millis().

Pro lep�� p�edstavu se pod�vejte na toto video, kde je zachyceno vzorov� �e�en�.

Odevzd�n� do ReCodExu
Do ReCodExu odevzd�vejte pouze soubor solution.ino (mus� b�t pojmenovan� p�esn� takto). P�edp�ipraven� startovac� bal��ek si m��ete st�hnout zde. Ve va�em �e�en� pou�ijte dodanou knihovnu funshield.h. Pro identifik�tory pin� (a souvisej�c� v�ci) nevytv��ejte si vlastn� konstanty ani nepou��vejte ��seln� liter�ly, ale v�hradn� jen konstanty z knihovny funshield.h.