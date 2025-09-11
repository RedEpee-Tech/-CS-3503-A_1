



#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "convert.h"


//div convert function uint32= input number, base=numberator
void div_convert(uint32_t n, int base, char* out) {
	char temp[65]; // Temporary buffer
	int pos = 0;
	 // Handle zero case
	if (n == 0) {
		strcpy(out, "0");
		return;
	}
	// Extract digits from right to left
	while (n > 0) {
		int remainder = n % base;
		n = n / base;
		
		 // Convert digit to character
		 if (remainder < 10){
			 temp[pos++] = '0' + remainder;
		 }
		else{
			 temp[pos++] = 'A' + (remainder - 10);
		 }
	}
	//my code add temp to out in reverse order
	for (int i=0; i < pos; i++)
	{
		out[i] = temp[pos - i - 1];
	}
		out[pos] = '\0'; // Null-terminate the string

	
}


void sub_convert(uint32_t n, int base, char* out) {
	char temp[1000]; // Temporary buffer
	int pos = 0;
	if (n == 0) {
		strcpy(out, "0");
		return;
	}

	uint32_t power = 1;
	
	//find the largest power of base less than or equal to n
	while(power <= n / base) {

		power*=base;
	}
	// Extract digits from left to right
	while (power > 0)
	{
		int digit = n / power;
		n= n - digit * power;
		 if (digit < 10){
			 temp[pos++]= '0' + digit;
		 }
		else{
			 temp[pos++]= 'A' + (digit - 10);
		 }

		power /= base;
	}
	//add temp to out in same order
	for (int i=0; i < pos; i++)
	{

		out[i] = temp[i];
	}
	out[pos] = '\0'; // Null-terminate the string
	

}


void print_tables(uint32_t n) {
	char bin[33], oct[12], hex[9];

	// Original number
	div_convert(n, 2, bin);

	div_convert(n, 8, oct);

	div_convert(n, 16, hex);

	printf(" Original : Binary =%s Octal =%s Decimal =%u Hex =%s\n",bin, oct, n, hex);
	
	// Left shift by 3
	uint32_t shifted = n << 3;

	div_convert(shifted, 2, bin);

	div_convert(shifted, 8, oct);

	div_convert(shifted, 16, hex);

	printf(" Left Shift by 3: Binary =%s Octal =%s Decimal =%u Hex =%s\n",bin, oct, shifted, hex);
	// AND with 0 xFF
	uint32_t masked = n & 0xFF;
	// ... similar pattern

	div_convert(masked, 2, bin);

	div_convert(masked, 8, oct);

	div_convert(masked, 16, hex);

	printf(" And with 0xFF: Binary =%s Octal =%s Decimal =%u Hex =%s\n",bin, oct, masked, hex);

}