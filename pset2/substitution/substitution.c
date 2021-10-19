#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool validate_len(string key);
bool validate_alpha(string key);
bool validate_unique(string key);
void encipher(string key);


int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Key must contain 26 characters!");
        return 1;
    }
    else{
        string key = argv[1];
        if (validate_len(key) && validate_alpha(key) && validate_unique(key))
        {
            encipher(key);
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }
}

bool validate_len(string key)
{
    if (strlen(key) == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validate_alpha(string key)
{
    for (int i =0; i<26; i++)
    {
        if (isalpha(key[i]) == false)
        {
            return false;
        }

    }
    return true;
}

bool validate_unique(string key)
{
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (key[i] == key[j] || key[i] == toupper(key[j]) || key[i] == tolower(key[j]))
            {
                return false;
            }
        }
    }
    return true;
}




void encipher(string key)
{
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    string ab = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (isalpha(plain[i])== false)
        {
            printf("%c",plain[i]);
        }
        else
        {
            for (int j = 0; j < 26; j++)
            {
                if (plain[i] == ab[j])
                {
                    printf("%c",tolower(key[j]));
                }
                else if (plain[i] == toupper(ab[j]))
                {
                    printf("%c", toupper(key[j]));
                }
            }

        }
    }
    printf("\n");
}