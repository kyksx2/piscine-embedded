Présentation

La Piscine Embarquée est un bootcamp accéléré sur l’embarqué (AVR / ATmega328P).
Objectif : apprendre les bases bas niveau → registres, timers, interruptions, UART, PWM.

J’ai réalisé les modules 00 → 03.

Chaque module comprend des exercices progressifs, du code C
et des tests en conditions réelles sur microcontrôleur.

---------------------------------------------------------------------------------------

Matériel utilisé:

Carte : ATmega328P (type Arduino UNO)
Programmation : AVR-GCC / avrdude
Terminal Série : minicom / screen / cutecom

--------------------------------------------------------------------------------------

Organisation des modules:

| Module |	Sujet principal	|      Concepts      |
--------------------------------------------------
|   00   | setup µC         |	registre DDRx,     |
|        |                  | PORTx, PINx        |
--------------------------------------------------
|   01   |	timers / PWM    | TCCRnA / TCCRnB /  |
|        |                  | OCRnX              |
--------------------------------------------------
|   02   |	UART	          | RX/TX,             |
|        |                  | interruptionsRXCIE0|
--------------------------------------------------
|        |	                | parser #RRGGBB,    |
|   03   | application RGB	| conversion hex,    |
|        |                  | PWM RGB            |
--------------------------------------------------
