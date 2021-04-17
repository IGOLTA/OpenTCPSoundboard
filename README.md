# Open TCP Soundboard

## Basic description
Opent TCP Soundboard is a software thas allows you to create your own wireless soundboard. It communicate with the soundboard and let you customize the sounds and effects.

## Communication protocol

Obviously Open TCP Soundboard uses TCP/IP the communication process is made to be the simplest possible so even the smallest wifi controller can handle it.

 1. The software send throught TCP a wake up byte that is 0xDA in hexadecimal.
 2. The soundboard respond with the dimensions of the soundboard in a one byte format that is specified later
 3. Now the communication is etablished to play a sound on the computer the soundboard can send a byte through TCP that represent the sound coordinates on the board in the same specified later format.

## Coordinate format

The format seems a little bit tricky but can fit in 8 bits that is usefull for somes MCUs:

| X  | Y | HEX  | BINARY    | DECIMAL |
|----|---|------|-----------|---------|
| 3  | 7 | 0x37 | 0011 0111 |    55   |
| 1  | 8 | 0x18 | 0001 1000 |    24   |
| A  | 0 | 0xA0 | 1010 0000 |    160  |

In this table the X and Y are in hexadecimal I think it is easyer to understand. In this format the X coordinate is the first digit of the hexadecimal value and the Y coordinate the second. So the hexadecimal version of a point is 0x(X)(Y). In binary cloud say that the most significant quartet(left digits) is the X coordinate and the less significant one(right digits) is the Y coordinate. In decimal this syntax dosent make sense and this column is basicly useless but we can notice that the values goes from 0 to 255 so your soundboard can't contains more than 256 buttons. It's also important to see that even if my soundoard has for size for exemple X:3 Y:30 even if 3 * 30 = 90 that is under 255 you cant have a soundboard like this beacause 30 in hex is 1E and it dosent fit in the one byte format. So the max soundboard size is 16 * 16 (0xFF) if we start counting at 0.
