# Open TCP Soundboard

## Basic description
Opent TCP Soundboard is a software thas allows you to create your own wireless soundboard. It communicate with the soundboard and let you customize the sounds and effects.

## Communication protocol

Obviously Open TCP Soundboard uses TCP/IP the communication process is made to be the simplest possible so even the smallest wifi controller can handle it.

 1. The software send throught TCP a wake up byte that is 0xDA in hexadecimal.
 2. The soundboard respond with the dimensions of the soundboard in a one byte format that is specified later
 3. Now the communication is etablished to play a sound on the computer the soundboard can send a byte through TCP that represent the sound coordinates on the board in the same specified later format.

## Coorfdinate format
