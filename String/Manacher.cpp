//HDU 3068
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 221000;

char s[MAXN];
int p[MAXN];

void init(char *s) {
    int len = strlen(s);
    for (int i = len; i >= 0; -- i) {
         s[2 * i + 1] = '#';
         s[2 * i + 2] = s[i];
    }
    s[0] = '$';
}

int manacher(char *s) {
    int id;
    int mx = 0;
    for (int i = 1; s[i] != 0; ++ i) {
        if (mx > i)
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1;
        while (s[i + p[i]] == s[i - p[i]])
            p[i] ++;
        if (p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
    }

    int ans = 0;
    for (int i = 1; s[i] != 0; ++ i) {
        if (p[i] - 1 > ans) ans = p[i] - 1;
    }
    return ans;
}

int main() {
    while (scanf("%s", s) != EOF) {
        init(s);
        printf("%d\n", manacher(s));
    }
    return 0;
}
