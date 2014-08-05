//POJ 1200 一个字符串中最多出现NC种字符
//求有多少个不重复的长度为N的子串
#include <iostream>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAX_LEN = 16000010;

char s[MAX_LEN];
bool exist[MAX_LEN];

int main() {
    int n, nc;
    scanf("%d%d", &n, &nc);
    scanf("%s", s);

    int nCnt = 0;
    map<char, int> mapping;
    for (int i = 0; s[i] != 0; ++ i) {
        if (mapping.find(s[i]) == mapping.end()) {
            mapping[s[i]] = nCnt ++;
            if (nCnt == nc) break;
        }
    }

    int mod = nc, hc = 0;
    for (int i = 0; i < n - 1; ++ i) {
        mod = mod * nc;
        hc = hc * nc + mapping[s[i]];
    }

    int ans = 0, len = strlen(s);
    for (int i = n - 1; i < len; ++ i) {
        hc = (hc * nc + mapping[s[i]]) % mod;
        if (!exist[hc]) {
            ans ++;
            exist[hc] = true;
        }
    }
    printf("%d\n", ans);
}
