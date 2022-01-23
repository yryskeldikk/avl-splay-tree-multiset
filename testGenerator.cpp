#include <iostream>
#include <algorithm>
#include <ctime>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

const int N = 100000;
const int value = 100000;

inline int randopt() {
    return rand() % 6 + 1;
}

inline int randval() {
    int sign = rand() % 2;
    if (sign == 0)
        sign = -1;
    else
        sign = 1;
    return (rand() % value) * sign;
}

inline int randOrder(int m) {
    return rand() % m;
}

int main() {
    vector<int> v;
    ofstream myTest;
    myTest.open("test.txt");
    srand(time(NULL));

    myTest << N << endl;

    for (int i = 1; i <= N; i++) {
        int opt = randopt();
        if (1 <= i && i <= 5000) {
            opt = 1;
        }
        if (opt == 1) {
            int randVal = randval();
            myTest << opt << " " << randVal << endl;
            v.push_back(randVal);
        }
        else if (opt == 2) {
            int randorder = randOrder(v.size());
            int val = v[randorder];
            myTest << opt << " " << val << endl;
            v.erase(v.begin() + randorder);
        }
        else if (opt == 3) {
            int randorder = randOrder(v.size());
            int val = v[randorder];
            myTest << opt << " " << val << endl;
        }
        else if (opt == 4) {
            int randorder = randOrder(v.size());
            myTest << opt << " " << randorder << endl;
        }
        else if (opt == 5) {
            sort(v.begin(), v.end());
            int randorder = randOrder(v.size() - 4);
            randorder += 2;
            int val = v[randorder];
            myTest << opt << " " << val << endl;
        }
        else if (opt == 6) {
            sort(v.begin(), v.end());
            int randorder = randOrder(v.size() - 4);
            randorder += 2;
            int val = v[randorder];
            myTest << opt << " " << val << endl;
        }
    }
    myTest.close();
    return 0;
}