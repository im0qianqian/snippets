# TCO 2018 Round 1A 500

## **Problem Statement**

> The Resistance is a multiplayer board game. During the game each player belongs into one of two groups: some are resistance members, others are spies. In this problem there are P players, and exactly S of them are spies. The players are numbered 0 through P-1.
>
> The game is played in rounds. In each round of the game a subset of all players goes on a mission. Each player who goes on the mission casts a secret vote on whether they want it to succeed or to fail. Resistance members always vote for the mission to succeed, and spies may cast either vote. (Sometimes a spy will vote for a mission to succeed in order to gain trust of the other players.) If at least one player on a mission voted for it to fail, the mission fails. If everybody voted for the mission to succeed, it succeeds.
>
> You are given the ints P and S. You are also given the vector `<string>` missions: data on all the missions that already took place. Each mission is described by a string. The first character of that string is 'F' for a failed mission or 'S' for a successful one. The next P characters describe which players went on the mission: for each valid i, character (i+1) is '1' if player i went on the misson and '0' otherwise.
>
> Verify whether the mission history is valid. If there is no assignment of roles (spies / resistance members) to players that would be consistent with the given mission history, return an empty vector `<double>`.
>
> If the mission history is valid, assume that each of the matching assignments of roles to players is equally likely. Return a vector `<double>` containing P elements. For each i, the i-th element of the return value should be the probability that player i is a spy, given the above assumption.



## **Examples**

    4
    1
    {"S0110",
     "F1100",
     "S0011"}
    Returns: {0.5, 0.5, 0.0, 0.0}



## **题意**

在 Resistance 这款游戏中，存在 resistance members 与 spies 这两种玩家，已知 resistance members 一定想让任务成功，而 spies 则不一定，所有失败的任务一定是因为 spies 的支持所导致的，求每个人是 spies 的概率。



## **思路**

因为总人数 P 很小，于是我们枚举所有可能性（必须包含 S 个间谍），我们首先判断当前所选择的方案是否合法，因为这 S 个间谍的支持导致出现了失败的任务，也就是说若某个失败的任务没有得到任何当前方案里的间谍支持，则该方案是不合法的。

对于每一个合法的方案，这 S 个人成为间谍的概率是等可能的，因此统计他们所出现的次数，最终将 $S \times 1.0$ 的概率值按权分配到每一个人身上即他们是间谍的概率。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;

class Resistance {
public:
    bitset<32> sk;
    bool judgeX(int P, vector<string> &missions) {
        unordered_set<int> vis;
        for (int i = 0; i < P; i++) {
            if (sk[i]) {
                for (int k = 0; k < (int)missions.size(); k++) {
                    if (missions[k][i + 1] == '1') {
                        vis.insert(k);
                    }
                }
            }
        }
        for (int i = 0; i < (int)missions.size(); i++) {
            if (missions[i][0] == 'F') {
                if (!vis.count(i))
                    return false;
            }
        }
        return true;
    }

    vector<double> spyProbability(int P, int S, vector<string> missions) {
        int num[20] = {0};
        for (int i = 0; i < (1 << P); i++) {
            sk = i;
            if (sk.count() != S || !judgeX(P, missions))
                continue;
            for (int i = 0; i < P; i++) {
                if (sk[i]) {
                    num[i]++;
                }
            }
        }
        int cut = 0;
        for (int i = 0; i < P; i++) {
            cut += num[i];
        }
        if (cut == 0)
            return vector<double>();
        double mis = S * 1.0 / cut;
        vector<double> ans;
        for (int i = 0; i < P; i++) {
            ans.push_back(num[i] * mis);
        }
        return ans;
    }

};
```

