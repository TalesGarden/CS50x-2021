#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int countLetters(string text);
int countWords(string text);
int countPhrases(string text);
int colemanLiauindex(int letters, int words, int phrases);

int main()
{
    string text = get_string("Text :");

    int numberLetters = countLetters(text);
    int numberWords = countWords(text);
    int numberPhrases = countPhrases(text);

    int grade = colemanLiauindex(numberLetters, numberWords, numberPhrases);

    if (grade > 16)
    {
        printf(" Grade 16+\n");
        return 0;
    }

    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    printf("Grade %d\n", grade);
    return 0;
}

int colemanLiauindex(int letters, int words, int phrases)
{
    float average_l = 100 * letters / (float)words;
    float average_s = 100 * phrases / (float)words;

    float index = 0.0588 * average_l - 0.296 * average_s - 15.8;
    int index_round = round(index);
    return index_round;
}


//this function count the number of letter on the text
int countLetters(string text)
{
    int counter = 0;
    int i = 0;
    while (text[i])
    {
        if ((text[i] >= 64 && text[i] <= 90)  || (text[i] >= 97 && text[i] <= 122))
        {
            ++counter;
        }
        ++i;
    }
    return counter;
}

//this function count the number of words on the text
int countWords(string text)
{
    int i = 0;
    int counter = 1;    // to count the last word
    while (text[i])
    {
        if (text[i] == 32)
        {
            ++counter;
        }
        ++i;
    }
    return counter;
}

//this function count the number of phrases on the text
int countPhrases(string text)
{
    int i = 0;
    int counter = 0;
    while (text[i])
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            ++counter;
        }
        ++i;
    }

    return counter;
}