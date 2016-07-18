#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

int n,c;
int a,b;
int num;
int prime[500];

int find(int x) {
    if(x==1) return 1;
    for(int i=1;i<=num;i++)
        if(x%prime[i]==0) return prime[i];
    return x;
}

int testcase(int a,int b) {
    if(a==b) return 0;
    if(a<b) return 1+testcase(a,b/find(b));
    else return 1+testcase(a/find(a),b);
}

int main() {
    int T;
    bool flag;
    ios::sync_with_stdio(false);
    num=0;
    for(int i=2;i<=sqrt(10000000);i++) {
        flag = 1;
        for(int j=1;j<=num;j++) {
            if(i%prime[j]==0) {
                flag = 0;
                break;
            }
        }
        if(flag) {
            num++;
            prime[num]=i;
        }
    }
    cin >> T;
    while(T--) {
        cin >> n >> c;
        for(int i=0;i<c;i++) {
            cin >> a >> b;
            cout << testcase(a,b) << endl;
        } 
    }
    return 0;
}
