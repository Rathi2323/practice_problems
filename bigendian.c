#include <stdio.h>
#include <stdint.h>

/*"Big-endian stores the most significant byte at the lowest address, like reading a number left-to-right. 
Little-endian stores the least significant byte at the lowest address, 
which makes casting down to smaller types and hardware-level arithmetic slightly more efficient."*/

uint16_t to_bigendian(uint16_t value)
{
    value = (value&0xFF)<<8 | (value>>8)&0xFF;
    return value;
}
int main() {
    uint16_t value = 0x1234;
    printf("0x%x",to_bigendian(value));
    return 0;
}
/*Look at the two choices when shrinking this to 1 byte (8 bits):
    Option A: Keep the LSB (the right end)You grab 0x05.The value is still 5. Nothing is lost.
    Option B: Keep the MSB (the left end)You grab 0x00.Your number just turned into 0.
What about big numbers like 0x12345678?
If a number is already larger than what 1 byte can hold, data overflow is unavoidable.
$1\text{ byte}$ can only hold values from $0$ to $255$.
0x12345678 is roughly 305 million. It physically cannot fit.
When you force a 305-million number into a container that caps at 255,
mathematics dictates the wrap-around (clock) rule:If a 12-hour clock hits 13:00, you don't say it's 1 o'clock by throwing away the 13—the 
clock wraps around (13 - 12 = 1).
In computers, shrinking an integer is pure modulo math:value mod{256}
0x12345678 divided by 256 leaves a remainder of 0x78.
The Rule in One SentenceTruncation keeps the LSB because that is where the actual values of smaller numbers live;
throwing away the LSB would mean converting every number smaller than 16 million into 0.*/