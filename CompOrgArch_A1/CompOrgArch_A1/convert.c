



#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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


//Assignment 2 functions below

//octal to binary function
void oct_to_bin(const char* oct, char* bin) {
	bin[0] = '\0'; // Initialize output string

	for (size_t i = 0; i < strlen(oct); i++) {
		char oct_digit = oct[i];
		//thros error if not valid octal digit
		if (oct_digit < '0' || oct_digit > '7') {
			strcpy(bin, "Error: Invalid octal digit");
			return;
		}
		int digit = oct_digit - '0';
		char temp[4];
		// Convert octal digit to 3 binary bits
		for (int j = 2; j >= 0; j--) {
			temp[j] = (digit % 2) ? '1' : '0';
			digit /= 2;
		}
		temp[3] = '\0';
		strcat(bin, temp);
	}
	
}

//octal to hex function
void oct_to_hex(const char* oct, char* hex) {
	// Validate input
	if (!oct) {
		strcpy(hex, "Error: Incorrect input");
		return;
	}
	
	size_t olen = strlen(oct);
	if (olen == 0) {
		strcpy(hex, "0");
		return;
	}

	// Binary buff: 3 bits per digit plus NUL
	size_t bin_cap = olen * 3 + 1;
	char *bin = (char*)malloc(bin_cap);
	if (!bin) {
		strcpy(hex, "Error: Allocation failed");
		return;
	}
	bin[0] = '\0';

	// Build binary string (3 bits per digit)
	for (size_t i = 0; i < olen; i++) {
		char oct_digit = oct[i];
		if (oct_digit < '0' || oct_digit > '7') {
			strcpy(hex, "Error: Invalid octal digit");
			free(bin);
			return;
		}
		int digit = oct_digit - '0';
		char temp[4];
		for (int j = 2; j >= 0; j--) {
			temp[j] = (digit & 1) ? '1' : '0';
			digit >>= 1;
		}
		temp[3] = '\0';
		strcat(bin, temp);
	}

	// Trim leading zeros in binary; if all zeros, result is "0"
	char *first_one = strchr(bin, '1');
	if (first_one) {
		memmove(bin, first_one, strlen(first_one) + 1);
	} else {
		strcpy(hex, "0");
		free(bin);
		return;
	}

	size_t bin_len = strlen(bin);
	int pad = (4 - (bin_len % 4)) % 4;
	size_t padded_len = bin_len + pad;

	// Create padded binary string
	char *padded = (char*)malloc(padded_len + 1);
	if (!padded) {
		strcpy(hex, "Error: Allocation failed");
		free(bin);
		return;
	}
	// Fill leading zeros
	for (int i = 0; i < pad; i++) padded[i] = '0';
	strcpy(padded + pad, bin);

	// Convert each 4-bit group to a hex digit
	size_t out_pos = 0;
	for (size_t i = 0; i < padded_len; i += 4) {
		int value = 0;
		for (int b = 0; b < 4; b++) {
			value = (value << 1) + (padded[i + b] - '0');
		}
		hex[out_pos++] = (value < 10) ? ('0' + value) : ('A' + (value - 10));
	}
	hex[out_pos] = '\0';

	// Strip leading zeros but leave at least one digit
	char *h = hex;
	while (*h == '0' && *(h + 1) != '\0') h++;
	if (h != hex) memmove(hex, h, strlen(h) + 1);

	// Clean up
	free(bin);
	free(padded);
}

//hex to binary function
void hex_to_bin(const char* hex, char* out) {
	// Validate input
	if (!hex) {
		strcpy(out, "Error: NULL input");
		return;
	}
	
	size_t len = strlen(hex);
	if (len == 0) {
		strcpy(out, "0");
		return;
	}
	// Convert each hex digit to 4 binary bits
	size_t pos = 0;
	for (size_t i = 0; i < len; ++i) {
		char c = hex[i];
		int val;
		if (c >= '0' && c <= '9') val = c - '0';
		else if (c >= 'A' && c <= 'F') val = 10 + (c - 'A');
		else if (c >= 'a' && c <= 'f') val = 10 + (c - 'a');
		else {
			strcpy(out, "Error: Invalid hex digit");
			return;
		}

		// write 4 bits for this hex digit
		out[pos++] = (val & 8) ? '1' : '0';
		out[pos++] = (val & 4) ? '1' : '0';
		out[pos++] = (val & 2) ? '1' : '0';
		out[pos++] = (val & 1) ? '1' : '0';
	}
	out[pos] = '\0';

}

//create to_sign_magnitude function
void to_sign_magnitude(int32_t n, char* out) {

	// Determine sign and absolute value
	int is_negative = (n < 0);
	uint32_t abs_val = is_negative ? -n : n;

	char bin[33];
	div_convert(abs_val, 2, bin);

	size_t len = strlen(bin);
	
	
	// absolute-value binary string (no zeros)
	size_t bin_len = strlen(bin);
	 size_t MAG_BITS = 31; // magnitude bits (sign + 31 = 32 total)

	// decide source slice (truncate high bits if magnitude too large)
	const char *mag_src = bin;
	size_t mag_len = bin_len;
	if (bin_len > MAG_BITS) {
    	// keep least-significant MAG_BITS bits (truncate high bits)
    	mag_src = bin + (bin_len - MAG_BITS);
    	mag_len = MAG_BITS;
	}

	size_t pad = MAG_BITS - mag_len; // number of leading '0' to add

	// write sign bit
	out[0] = is_negative ? '1' : '0';

	// fill leading zeros for magnitude then copy magnitude bits
	memset(out + 1, '0', pad);
	memcpy(out + 1 + pad, mag_src, mag_len);

	// terminate string: total chars = 1 + MAG_BITS, plus NUL
	out[1 + MAG_BITS] = '\0';
	
}


//create to_ones_complement function
void to_ones_complement(int32_t n, char* out) {


	int is_negative = (n < 0);
	uint32_t abs_val = is_negative ? -n : n;

	char bin[33];
	div_convert(abs_val, 2, bin);

	size_t len = strlen(bin);
	size_t BITS = 32; // total bits for one's complement representation

	// decide source slice (truncate high bits if too large)
	const char *src = bin;
	size_t src_len = len;
	
	if (len > BITS) {
		// keep least-significant BITS bits (truncate high bits)
		src = bin + (len - BITS);
		src_len = BITS;
	}

	size_t pad = BITS - src_len; // number of leading '0' to add

	// fill leading zeros
	memset(out, '0', pad);

	// copy magnitude bits
	memcpy(out + pad, src, src_len);

	// if negative, flip all bits for one's complement
	if (is_negative) {

		for (size_t i = 0; i < BITS; i++) {
			out[i] = (out[i] == '0') ? '1' : '0';
		}
	}

	// terminate string
	out[BITS] = '\0';
}
void to_twos_complement(int32_t n, char* out) {
	

	int is_negative = (n < 0);
	uint32_t abs_val = is_negative ? -n : n;

	char bin[33];
	//convert absolute value to binary
	div_convert(abs_val, 2, bin);

	size_t len = strlen(bin);
	size_t BITS = 32; // total bits for two's complement representation

	// decide source slice (truncate high bits if too large)
	const char *src = bin;
	size_t src_len = len;

	if (len > BITS) {
		// keep least-significant BITS bits (truncate high bits)
		src = bin + (len - BITS);
		src_len = BITS;
	}

	size_t pad = BITS - src_len; // number of leading '0' to add

	// fill leading zeros
	memset(out, '0', pad);

	// copy magnitude bits
	memcpy(out + pad, src, src_len);

	// if negative, compute two's complement by a adding 1 to one's complement
	if (is_negative) {

		// flip all bits
		for (size_t i = 0; i < BITS; i++) {
			out[i] = (out[i] == '0') ? '1' : '0';
		}

		// add 1 to the one's complement
		int carry = 1;
		for (int i = BITS - 1; i >= 0 && carry; i--) {

			if (out[i] == '1') {
				out[i] = '0'; // 1 + 1 = 0 with carry
			} 
			else {
				out[i] = '1'; // 0 + 1 = 1 no carry
				carry = 0;
			}
		}
	}

	// terminate string
	out[BITS] = '\0';
}

// //main test method for to_sign_magnitude
// int main(void) {
// 	int32_t tests[] = {
// 		5,
// 		1,
// 		255,
// 		-5,
// 		-1,
// 		-255,
// 		0,
// 		2147483647,
// 		-2147483647,
// 	};
// 	size_t ntests = sizeof(tests) / sizeof(tests[0]);

// 	char out[40];

	
// 	for (size_t i = 0; i < ntests; ++i) {
//         int32_t v = tests[i];
//         to_twos_complement(v, out);
//         printf("n = %d -> sign-magnitude = %s\n", v, out);
//     }

// 	return 0;
// }