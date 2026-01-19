// T9 search for contacts 
// made in 2024 - by
// xblizna00

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//----------DATA OF PERSON FROM TEXT FILE (including name and phone number)-----------------------//
typedef struct
{
    char name_name[101];                                                               // Array of names
    char name_number[101];                                                             // Array of phone numbers
} person;
//----------DECLARED FUNCTIONS--------------------------------------------------------------------//
bool argument_overflow(int argc);
bool name_compare(char *argv, person *data, int *converter, bool *contact_found);
bool number_compare(char *argv, person *data, bool *contact_found);
bool number_only(char *argv);
bool all_contacts(int charcheck_2, int distance_index, int line);
bool last_line_printer(char *argv, bool is_name, int distance_index, 
person *data, int *converter, bool *contact_found);
//----------MAIN FUNCTION-------------------------------------------------------------------------//
int main(int argc, char *argv[])
{
    if (argc > 1 && !number_only(argv[1]))                                             // Checking if there is entered argument (number) and if the argument
    {                                                                                  // contain only numbers
        return 1;
    }
    if (!argument_overflow(argc))                                                      // Checking if there is entered only one argument (number)
    {
        return 1;
    }
//----------VARIABLES-----------------------------------------------------------------------------//
    person data;                                                                       // Structure of every person storing (name and number)
    char charcheck;                                                                    // Variable for characters
    int charcheck_2 = 0;                                                               // Checker for entered characters for function 'all_contacts'
    int distance_index = 0;                                                            // Line chracter counter
    int line = 0;                                                                      // Total line counter 
    int converter[27] =
        {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};// Converter for switching entered numbers to letters
    bool is_name = true;                                                               // Switcher for name and number
    bool contact_found = false;                                                        // Checker for matched numbers or letter (argument and contact)
//----------ALL LINES PRINTER---------------------------------------------------------------------//
    if (argc < 2)
    {                                                                                  // to print all contacts
        contact_found = true;                                                          // If there is not entered argument (number)... call function and switch 
        if(all_contacts(charcheck_2, distance_index, line) == 1){                      // contact as found
            return 1;                                       
        }                                                   
    }               

    while (argument_overflow(argc))                                                    // If there is not more than one argument (numbers) 
    {
        int breaker = getchar();                                                       // Taking character to variable

        if (breaker == EOF)                                                            // If there is end of file... the loop will stop...
        {                                                                              
            break;
        }

        charcheck = (char)breaker;                                                     // ...if not variable charcheck will be assigned as breaker

        if (charcheck == '\n')                                                         // Looking of no line
        {
            if (is_name)                                                               // First and every second line in input representing name
            {                                                                          // so is_name is set as true
                data.name_name[distance_index] = '\0';                                 // End of chain
            }
            else                                                                       // Second and every second line in input representing number
            {                                                                          // so is_name is set as false
                data.name_number[distance_index] = '\0';                               // End of chain
                if (name_compare(argv[1], &data, converter, &contact_found)            // Check if entered argument representing name or number 
                || number_compare(argv[1], &data, &contact_found))                     // from input
                {
                    printf("%s, %s\n", data.name_name, data.name_number);              // It will be printed on output
                }
            }
            distance_index = 0;                                                        // Reset counter for a new line
            is_name = !is_name;                                                        // Switch between name and number
        }
        else
        {
//----------DATA WRITER (name and phone number)---------------------------------------------------------//
            if (is_name)                                                               // Adding characters to name 
            {
                if (distance_index < 100)                                              // Checking if there is not character overflow in line
                {                                                                      // otherwise print ERROR
                    data.name_name[distance_index++] = charcheck;
                }
                else
                {
                    fprintf(stderr, "ERROR: Line too long\n");                         
                    return 1;
                }
            }
            else                                                                       // Adding characters to number
            {
                if (distance_index < 100)                                              // Checking if there is not character overflow in line
                {                                                                      // otherwise print ERROR
                    data.name_number[distance_index++] = charcheck;
                }
                else
                {
                    fprintf(stderr, "ERROR: Line too long\n");                         
                    return 1;
                }
            }
        }
    }
//----------PRINTER FOR THE LAST LINE-------------------------------------------------------------//
    if (distance_index > 0)                                                            // Adding last line (number) to data
    {
        last_line_printer(argv[1], is_name, distance_index, &data, converter, &contact_found); 
    }
//----------NOT FOUND ANY CONTACTS----------------------------------------------------------------//
    if (!contact_found)                                          
    {
        printf("Not found\n");
    }
    return 0;
}
//----------FUNCTIONS-----------------------------------------------------------------------------//
//----------CROWDED NUMBER OF ARGUMENTS-----------------------------------------------------------//
bool argument_overflow(int search)                                                     // Checking if there was entered allowed amount of arguments
{                                                                                      
    if (search > 2)
    {
        fprintf(stderr, "ERROR: You have entered more than one argument\n");
        return false;
    }
    return true;
}

//----------COMPARE OF SEARCHED NUMBER AND NAME CONVERTED TO NUMBER------------------------------//
bool name_compare(char *argv, person *data, int *converter, bool *contact_found)
{
    char converted_number[101];                                                        // New array for numbers switched from letters
    for (int index = 0; index < 101; index++)                                          
    { 
        if (data->name_name[index] == '+')                                             // Going trough whole name by every character.. if there is match with '+'
        {
            converted_number[index] = '0';                                             // Write it in the same position in new array created above as '0'  
        }
        else                                                                           // Otherwise 
        {
            char small_letter = tolower(data->name_name[index]);                       // Changing all latter (name of the person from data struct) to lower case
            converted_number[index] = small_letter;                                    // Adding those letter to created array
            int converting_number = (converted_number[index] - 'a');                   // Creating new variable (getting character of small letter - 'a' 
            if (converting_number < 0 || converting_number > 25)                       // (example 'p' - 'a' = 112 - 97 = 15))
            {                                                                          // Checking if the values are representing only values from converter
                converted_number[index] = '.';
            }
            else
            {
                converted_number[index] = converter[converting_number] + '0';          // Taking numbers from converter + '0' and writing them to array of converted numbers
            }                                                                          // For example ('p' - 'a' = 15, converter[15] = 7, decimal 7 in ASCII table + decimal 
        }                                                                              // of '0' is 48 so 7 + 48 = 55 and decimal 55 representing number 7
    }    
    converted_number[100] = '\0';                                                      // Adding nullbite at the end of array of converter values
    if (strstr(converted_number, argv) != NULL)
    {                                                                                  // Checking if entered argument belong to any contact
        (*contact_found) = true;
    }
    return strstr(converted_number, argv) != NULL;                                     // Searching entered argument (number) in new array 
}
//----------COMPARE OF SEARCHED NUMBER AND NUMBER FROM TEXT FILE--------------------------------//
bool number_compare(char *argv, person *data, bool *contact_found)
{   
    char help_number[101];                                                             // New array for numbers switched from numbers or sign '+'
    for (int index = 0; index < 101; index++){
        help_number[index] = data->name_number[index];                                 // Going trough whole name by every character.. if there is match with '+'
        if (help_number[index] == '+')
        {                                                                              
            help_number[index] = '0';                                                  // Write it in the same position in new array created above as '0'
        }
    }
    help_number[100] = '\0';                                                           // Adding nullbite at the end of array of converter values
    if (strstr(help_number, argv) != NULL)
    {                                                                                  // Checking if entered argument belong to any contact
        (*contact_found) = true;
    }
    return strstr(help_number, argv) != NULL;                                          // Searching entered argument (number) in new array 
}
//----------CHECKING IF THE ARGUMENT IS A NUMBER------------------------------------------------//
bool number_only(char *argv)
{ 
    int distance_argv = strlen(argv);                                                  // New variable of lenght of argument
    for (int index = 0; index < distance_argv; index++)                                
    {
        if (isdigit(argv[index]) == 0)                                                 // Checking if every character of entered argument representing only number...
        {                                                                              // If there is not a number, '0' is represented as false 
            fprintf(stderr, "ERROR: You have entered unallowed characters\n");
            return false;
        }
    }
    return true;
}
//----------PRINTING ALL CONTACTS---------------------------------------------------------------//
bool all_contacts(int charcheck_2, int distance_index, int line){
    while ((charcheck_2 = getchar()) != EOF)                                           // Printing for all lines until end of line
    {
        distance_index++;                                                              
        if (distance_index > 100)                                                      // Checking a distance of line
        {
            fprintf(stderr, "ERORR: Line too long\n");
            return 1;
        }
        else if (charcheck_2 == '\n')                                                  // If there is and end of line, we will increas value of line
        {                                                                              // and check if line value can be devided by 2 without leftovers
            line++;                                                                    // if not, we are adding comma because 1st line represent name and
            distance_index = 0;                                                        // second line represent number
            if (line % 2 != 0)                                                         // if yes, we are adding new line
            {
                printf(", ");
            }
            else
            {
                printf("\n");
            }
        }
        else                                                                           // Otherwise we are printing characters of (charcheck_2)
        {
            putchar(charcheck_2);
        }
    }
    return 0;
}
//----------PRINTER FOR THE LAST LINE-----------------------------------------------------------//
bool last_line_printer(char *argv, bool is_name, int distance_index,                   // Printing only last line 
person *data, int *converter, bool *contact_found){
    if (is_name)
    {
        data->name_name[distance_index] = '\0';                                        // End of chain
    }
    else
    {
        data->name_number[distance_index] = '\0';                                      // End of chain
        if (name_compare(argv, data, converter, contact_found) ||                      // Check if entered argument representing name or number
            number_compare(argv, data, contact_found))                                 // from input
        {
            printf("%s, %s\n", data->name_name, data->name_number);                    // It will be printed on output
        }
    }
    return 0;
}