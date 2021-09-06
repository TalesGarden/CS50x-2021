#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


bool testArg(int argc1, string argv1[]);
bool isChar(char letter);
int positionLetter(char letter);
char changePosition(char letter, string key);
void ciphertext(string plaintext, string key);


int main(int argc, string argv[])
{
    //test the argument of the program
    if (!testArg(argc, argv))
    {
        return 1;
    }

    string plaintext = get_string("\nplaintext: ");
    ciphertext(plaintext, argv[1]);

    return 0;
}

bool testArg(int argc1, string argv1[])
{

    //check number of parameters
    if (argc1 != 2)
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    if (strlen(argv1[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; argv1[1][i] != '\0'; ++i)
    {
        if (!isChar(argv1[1][i]))
        {
            printf("The key must contain only characters\n");
            return false;
        }
    }
    //check duplicate


    for (int i = 0; argv1[1][i] != '\0'; ++i)
    {
        for (int j = i + 1; argv1[1][j] != '\0' ; ++j)
        {
            if (argv1[1][i] == argv1[1][j])
            {
                return false;
            }
        }
    }

    return true;
}
//verify if a character is a letter of the alphabet
bool isChar(char letter)
{
    if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122))
    {
        return true;
    }
    return false;
}
//gets the position of a letter in the alphabet
int positionLetter(char letter)
{
    int position = 0;
    if (letter >= 65  && letter <= 90)
    {
        for (int i = 65; i <= 90; ++i)
        {
            if (letter == i)
            {
                return position;
            }
            ++position;
        }
    }
    else if (letter >= 97  && letter <= 122)
    {
        for (int i = 97; i <= 122; ++i)
        {
            if (letter == i)
            {
                return position;
            }
            ++position;
        }
    }
    return 1;  // a wrong return
}

char changePosition(char letter, string key)
{
    int position = positionLetter(letter);
    char letter_key = toupper(key[position]);

    if (letter >= 97 && letter <= 122)
    {
        letter = letter_key + 32;
        return letter;
    }

    letter = letter_key;
    return letter;
}

void ciphertext(string plaintext, string key)
{
    printf("\nciphertext: ");
    char letter_changed;
    for (int i = 0; plaintext[i]; ++i)
    {
        if (!isChar(plaintext[i]))
        {
            printf("%c", plaintext[i]);
            continue;
        }
        letter_changed = changePosition(plaintext[i], key);
        printf("%c", letter_changed);
    }
    printf("\n");
}