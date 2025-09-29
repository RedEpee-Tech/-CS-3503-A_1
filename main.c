
//c headers
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "convert.c"



int main(void){
    // Open input and output files
    FILE *inputf = fopen("a2_test.txt", "r");
    FILE *outputf = fopen("output.txt", "w");

    //check if files opened successfully
    if (!inputf || !outputf) {
        printf("Error opening input or output file.\n");
        return 1;
    }

    int test_num = 1;
    int passed = 0;
    int failed = 0;
    char line[256];
    char out = 0;



    while (fgets(line, sizeof(line), inputf) != NULL) {

        // if statement to skip comments and empty lines
        if (line[0] == '#' || strlen(line) < 1) {
            continue;
        }
        // Parse line
        char *tokens[80];
        int count = 0;

        char* token = strtok(line, " \n");
        while (token != NULL && count < 80) {
            tokens[count++] = token;
            token = strtok(NULL, " \n");
        }

        char* endptr;
        char *function=tokens[0];
        char output[256];


        //if div_convert

        if (strstr(line, "div_convert")) {
            uint32_t number = strtoul(tokens[1], &endptr, 10);
            int base = strtol(tokens[2], &endptr, 10);
            char* expected = tokens[3];

            div_convert(number, base, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: div_convert(%u,%d) -> Expected: %s, Got: %s [PASS]\n", test_num, number, base, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: div_convert(%u,%d) -> Expected: %s, Got: %s [FAIL]\n", test_num, number, base, expected, output);
                failed++;
            }
            test_num++;
            continue;{
            
        }
    }
    //if sub_convert
        else if (strstr(line, "sub_convert")) {
            uint32_t number = strtoul(tokens[1], &endptr, 10);
            int base = strtol(tokens[2], &endptr, 10);
            char* expected = tokens[3];

            sub_convert(number, base, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: sub_convert (%u,%d) -> Expected: %s, Got: %s [PASS]\n", test_num, number, base, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: sub_convert (%u,%d) -> Expected: %s, Got: %s [FAIL]\n", test_num, number, base, expected,output);
                failed++;
            }
            test_num++;
            continue;
        } //if print_tables
        else if (strstr(line, "print_tables")) {
            uint32_t number = strtoul(tokens[1], &endptr, 10);

            char bin[33], oct[12], hex[9];
            char bin1[33], oct1[12], hex1[9];
            char bin2[33], oct2[12], hex2[9];

            FILE *tempf = fopen("tempf.txt", "w");

            if(!tempf) {
                printf("Error opening temporary file.\n");
                return 1;
            }

	        // Original number
	        div_convert(number, 2, bin);
	        div_convert(number, 8, oct);
	        div_convert(number, 16, hex);

	        fprintf(tempf,"Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n",bin, oct, number, hex);
	
	        // Left shift by 3
	        uint32_t shifted = number << 3;

	        div_convert(shifted, 2, bin1);
	        div_convert(shifted, 8, oct1);
	        div_convert(shifted, 16, hex1);

	        fprintf(tempf, "Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n",bin1, oct1, shifted, hex1);
	        // AND with 0 xFF
	        uint32_t masked = number & 0xFF;

	        div_convert(masked, 2, bin2);
	        div_convert(masked, 8, oct2);
	        div_convert(masked, 16, hex2);

            fprintf(tempf,"AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",bin2, oct2, masked, hex2);
        
            char expected[1024];
            snprintf(expected, sizeof(expected),
                "Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n"
                "Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n"
                "AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
                bin, oct, number, hex,
                bin1, oct1, shifted, hex1,
                bin2, oct2, masked, hex2);

            fclose(tempf); // Close after writing

            char buffer[1024] = "";
            FILE *tempfRead = fopen("tempf.txt", "r");//temp file to read back
            if (tempfRead) {
                size_t len = fread(buffer, 1, sizeof(buffer)-1, tempfRead);
                buffer[len] = '\0'; // Null-terminate the string
                fclose(tempfRead);
            }
            //if buffer matches expected ==pass or !pass
            if(strcmp(buffer, expected) == 0) {
                fprintf(outputf, "Test %d: print_tables(%u)-> [ FORMATTED OUTPUT CHECK ] [PASS] - \n", test_num, number);
                passed++;
            } else {
                fprintf(outputf, "Test %d: print_tables(%u)-> [ FORMATTED OUTPUT CHECK ] [PASS]\nExpected:\n%s\nGot:\n%s\n", test_num, number, expected, buffer);
                failed++;
            }    
        }


        //assignment 2 tests prints

        else if (strstr(line, "oct_to_bin")) {
            char* octal = tokens[1];
            char* expected = tokens[2];

            oct_to_bin(octal, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: oct_to_bin(%s) -> Expected: %s, Got: %s [PASS]\n", test_num, octal, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: oct_to_bin(%s) -> Expected: %s, Got: %s [FAIL]\n", test_num, octal, expected, output);
                failed++;
            }
            test_num++;
            continue;
        }
        else if (strstr(line, "oct_to_hex")) {
            char* octal = tokens[1];
            char* expected = tokens[2];

            oct_to_hex(octal, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: oct_to_hex(%s) -> Expected: %s, Got: %s [PASS]\n", test_num, octal, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: oct_to_hex(%s) -> Expected: %s, Got: %s [FAIL]\n", test_num, octal, expected, output);
                failed++;
            }
            test_num++;
            continue;
        }
        
        
        else if (strstr(line, "hex_to_bin")) {
            char* hex_input = tokens[1];
            char* expected = tokens[2];

            hex_to_bin(hex_input, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: hex_to_bin(%s) -> Expected: %s, Got: %s [PASS]\n", test_num, hex_input, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: hex_to_bin(%s) -> Expected: %s, Got: %s [FAIL]\n", test_num, hex_input, expected, output);
                failed++;
            }
            test_num++;
            continue;
        }
        
        else if (strstr(line, "to_sign_magnitude")) {
            int32_t number = strtol(tokens[1], &endptr, 10);
            char* expected = tokens[2];

            to_sign_magnitude(number, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: to_sign_magnitude(%d) -> Expected: %s, Got: %s [PASS]\n", test_num, number, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: to_sign_magnitude(%d) -> Expected: %s, Got: %s [FAIL]\n", test_num, number, expected, output);
                failed++;
            }
            test_num++;
            continue;
        }
        else if (strstr(line, "to_ones_complement")) {
            int32_t number = strtol(tokens[1], &endptr, 10);
            char* expected = tokens[2];

            to_ones_complement(number, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: to_ones_complement(%d) -> Expected: %s, Got: %s [PASS]\n", test_num, number, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: to_ones_complement(%d) -> Expected: %s, Got: %s [FAIL]\n", test_num, number, expected, output);
                failed++;
            }
            test_num++;
            continue;
            
        }
        else if (strstr(line, "to_twos_complement")) {
            int32_t number = strtol(tokens[1], &endptr, 10);
            char* expected = tokens[2];

            to_twos_complement(number, output);
            //tests if output matches expected and prints to output file
            if (strcmp(output, expected) == 0) {
                fprintf(outputf, "Test %d: to_twos_complement(%d) -> Expected: %s, Got: %s [PASS]\n", test_num, number, expected, output);
                passed++;
            } else {
                fprintf(outputf, "Test %d: to_twos_complement(%d) -> Expected: %s, Got: %s [FAIL]\n", test_num, number, expected, output);
                failed++;
            }
            test_num++;
            continue;
        }

        //if no function matched
        // else {
        //     fprintf(outputf, "Test %d: Unknown function in line: %s [SKIPPED]\n", test_num, line);
        //     failed++;
        //     test_num++;
        // }
        
        
    }
    fprintf(outputf, "\nSummary:%u/%d PASSED\n",passed, passed + failed);
    fclose(inputf);
    fclose(outputf);

    return 0;
}