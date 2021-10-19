#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// function here
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void grade_check(int l,int s, int w);


int main(void)
{
    string text = get_string("Text: ");
    int num_letter = count_letters(text);
    int num_word = count_words(text);
    int num_sentence = count_sentences(text);
    grade_check(num_letter, num_sentence, num_word);
}

int count_letters(string text)
{
    int num = 0;
    // it's comma between i and n
    for (int i = 0, n = strlen(text); i < n; i++)
    // single quote!
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            num++;
        }
    }

    // printf("%i",num);
    return num;
}

int count_words(string text)
{
    int num = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            num++;
        }
    }
    // printf("%i", num+1);
    return num + 1;
}

int count_sentences(string text)
{
    int num = 0;
    for (int i = 0, n = strlen(text); i < n;i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            num++;
        }
    }
    // printf("%i", num);
    return num;
}

void grade_check(int l, int s, int w)
{
    float L = l * 100.0 / w;
    float S = s * 100.0 / w;
    int index = round(0.0588 * L - 0.296 * S-15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

