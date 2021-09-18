#include <stdio.h>

struct linkedList
{
    int count;
    // char _char;
    int prev;
    int next;
};

int main()  {
    int i, j;
    int start = 0;
    struct linkedList ll[26];

    char string[20] = "ajdkskkjjwmkqkkklaal";

    for (i = 0; i < 20; i++) {
        ll[i].count = 0;
        ll[i].prev = i-1;
        ll[i].next = i+1;
    }

    for (i = 0; i < 20; i++) {
        j = string[i] - 'a';
        printf("i: %d, string[i]: %c, string[i] - 'a': %d\n", i, string[i], (string[i] - 'a'));
        if (ll[j].count == 0) {
            ll[j].count = 1;
        } else {
            if (start == j) {
                start = ll[j].next;
            } else {
                ll[ll[j].prev].next = ll[j].next;
            }
        }
    }

    printf("Index: %d, char: %c\n", start, 'a' + start);

    return 0;
}
