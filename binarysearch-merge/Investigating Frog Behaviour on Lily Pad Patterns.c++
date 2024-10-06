#include <stdio.h>
 
#define MAX_LILIES 2000000
#define MAX_FROGS 200000
 
int binarySearch(int A[], int i, int j, int k)
{
    int r = -1, m;
 
    while (i <= j)
    {
        m = (i + j) >> 1; /*m = (i + j) / 2;*/
        if (k == A[m])
        {
            r = m;
            break;
        }
        else
        {
            if (k > A[m])
            {
                i = m + 1;
            }
            else
            {
                j = m - 1;
            }
        }
    }
    if (r == -1)
    {
        r = (-1) * i - 1;
    }
 
    return r;
}
 
int main()
{
    int frogs_count;
    int frog_pos[MAX_FROGS];
 
    // An array of the possible targets for a frog to jump to, sorted in ascending order.
    // Frogs will jump to the closest lily pad ahead that is available.
    int available_lilies[MAX_LILIES];
    int available_lilies_count = 0;
 
    int jump_count;
    int frog_idx;
    int target_lily_idx; // The index of the lily pad that the frog will jump to.
    int aux;
 
    scanf("%d", &frogs_count);
    for (int i = 0; i < frogs_count; i++)
    {
        scanf("%d", &frog_pos[i]);
        frog_pos[i]--;
    }
    for (int i = 0; i <= frog_pos[frogs_count - 1] + 1; i++)
    {
        if (binarySearch(frog_pos, 0, frogs_count - 1, i) < 0)
        {
            available_lilies[available_lilies_count] = i;
            available_lilies_count++;
        }
    }
 
    /*
    for (int i = 0; i < available_lilies_count; i++)
        printf("%d ", available_lilies[i]);
    printf("\n");
    */
 
    scanf("%d", &jump_count);
    for (int i = 0; i < jump_count; i++)
    {
        scanf("%d", &frog_idx);
        frog_idx--;
        target_lily_idx = -binarySearch(available_lilies, 0, available_lilies_count - 1, frog_pos[frog_idx]) - 1;
        printf("%d\n", available_lilies[target_lily_idx] + 1);
        aux = frog_pos[frog_idx];
        frog_pos[frog_idx] = available_lilies[target_lily_idx];
        available_lilies[target_lily_idx] = aux;
        if (target_lily_idx == available_lilies_count - 1)
        {
            // This is the last lily pad, so we need to add a new one ahead for the next frog to jump to.
            available_lilies[available_lilies_count++] = frog_pos[frog_idx] + 1;
        }
    }
}
