#include <stdio.h>
#include <stdint.h>

uint32_t reg_extract_field(uint32_t reg_val, uint8_t start_bit, uint8_t width)
{
    if((width==0U)||(width>32U)||(start_bit>=32U)||((start_bit+width)>32U))
       {
        return 0;
       }
    uint32_t mask = (width==32U) ? (0xFFFFFFFFUL) : ((1UL<<width)-1U);
    return (reg_val>>start_bit) & mask;
}

uint32_t reg_insert_field(uint32_t reg_val, uint8_t start_bit, uint8_t width, uint8_t field_val)
{
    if((width==0U)||(width>32U)||(start_bit>=32U)||((start_bit+width)>32U))
       {
        return 0;
       }
    uint32_t mask = (width==32U) ? (0xFFFFFFFFUL) : ((1UL<<width)-1U);
    uint32_t masked = (reg_val) & ~(mask<<start_bit);
    return (masked | (field_val<<start_bit));
}

int main()
{
    uint32_t reg_val = 0x000000B0, start_bit = 4, width = 4, field_val = 0x5;
    uint32_t extracted = reg_extract_field(reg_val, start_bit, width);
    printf("Extracted bits are 0x%X\n",extracted);
    uint32_t inserted = reg_insert_field(reg_val, start_bit, width, field_val);
    printf("After inserting, the extracted bits are 0x%X\n",inserted);
    return 0;
}