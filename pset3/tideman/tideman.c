#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int n);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }

        }

        record_preferences(ranks);

    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int i;
    for (i = 0; i < candidate_count; i++)
    {
        if (strcmp (name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;

}

// Update preferences given one、 voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j< candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            // printf("%i\n",preferences[ranks[i]][ranks[j]]);
        }

    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j< candidate_count; j++)
        {
            // 没看懂题目
            if (preferences[i][j]>0 && preferences[i][j]> preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory


void sort_pairs(void)
{
    for (int i = 0; i < pair_count-1; i++)
    {
        int max_index = i;
        int j;
        for (j = i+1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[max_index].winner][pairs[max_index].loser])
            {
                max_index = j;
            }
        }
// don't use a function; 
        pair temp = pairs[max_index];
        pairs[max_index] = pairs[i];
        pairs[i] = temp;
    }

    for (int k = 0; k < pair_count; k++)
    {
        printf("the pair is %i,%i,%i;\n",pairs[k].winner,pairs[k].loser, preferences[pairs[k].winner][pairs[k].loser]);
    }

}

bool check_cycle(int n)
{
    for (int i = n-1; i >0; i--)
    {
        if (pairs[n].winner == pairs[i].loser)
        {
            if (pairs[n].loser == pairs[i].winner)
            {
                // printf("There is a cycle here");
                return true;
            }
            else
            {
                check_cycle(i);
            }
        }
    }
    return false;
}



struct Node
{
    int key;
    struct Node* next;
};


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    list array[MAX]
    array[0].prev=-1;
    array[0].key=pairs[0].winner;
    array[0].next = pairs[0].loser
        
        
    }
        
        
    {
        for (int j = i - 1; j > 0; j--)
        {
            if locked[pairs[i].winner] == locked[pairs[j].loser]
        }
        locked[pairs[i].winner
        
        if (check_cycle(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        printf("Locked: %i\n", locked[pairs[i].winner][pairs[i].loser]);
    }
}


// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j != pairs[i].loser && locked[pairs[i].loser][j] == false)
            {
                printf("%s\n",candidates[j]);
            }
        }
    }
}

