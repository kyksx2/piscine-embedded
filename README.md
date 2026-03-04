## Présentation

La Piscine Embarquée est un bootcamp accéléré sur l’embarqué (AVR / ATmega328P).
Objectif : apprendre les bases bas niveau → registres, timers, interruptions, UART, PWM.

J’ai réalisé les modules 00 → 03.

Chaque module comprend des exercices progressifs, du code C
et des tests en conditions réelles sur microcontrôleur.

## Matériel utilisé:

Carte : ATmega328P (type Arduino UNO)

Programmation : AVR-GCC / avrdude

Terminal Série : minicom / screen / cutecom


## Organisation des modules:

module 0:
* sujet principal: setup µC
* conecpt: registre DDRx / PORTx, PINx

module 01:
* sujet principal: timers / PWM
* concept: TCCRnA / TCCRnB / OCRnX

module 02:
* sujet principal: UART
* concept: RX/TX / interruptionsRXCIE0|

module 03:
* sujet principal: application RGB
* concept: conversion hex / PWM RGB / parser #RRGGBB
