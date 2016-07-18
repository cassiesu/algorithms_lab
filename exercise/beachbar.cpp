#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    int x,y,z;
};

node a[10010];
int num;
int cord[10010];
int n;

bool comp(const node &u, const node &v) {
    return (u.x>v.x) || (u.x==v.x && u.y<v.y) || (u.x==v.x && u.y==v.y && u.z<v.z);
}

int search(int x, int left, int right) {
    int mid;
    
    if(right-left<=1) {
        if(cord[right]<=x) return right; else return left;
    }
    mid=(left+right)/2;
    if(cord[mid]<=x) return search(x,mid, right); else return search(x,left,mid-1);
}

void testcase() {
    int t;
    int tmp;
    int sign;
    
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> cord[i];
    num=0;
    sort(cord,cord+n);
    for(int i=0;i<n;i++) {
        t = search(cord[i]+200,i,n-1);
        //x the number of parasols
        //y the maximum of reach
        //z x location
        a[num].x=t-i+1;
        a[num].y=(cord[t]-cord[i]+1)/2;
        tmp=cord[t]+cord[i];
        if(tmp<0) {
            tmp=-tmp;
            sign=-1;
        }
        else {
            sign=1;
        }
        a[num].z=sign*(tmp/2);
        num++;
        if(tmp%2) {
            a[num].x=t-i+1;
            a[num].y=(cord[t]-cord[i]+1)/2;
            a[num].z=a[num-1].z+sign;
            num++;
        }
        if(t==n-1) break;
    }
    sort(a,a+num,comp);
    cout << a[0].x << " " << a[0].y << endl;
    cout << a[0].z;
    for(int i=1;i<num;i++) {
        if(a[i].x==a[0].x && a[i].y==a[0].y) {
            cout << " " << a[i].z;
        }
        else break;
    }
    cout << endl;
}

int main() {
    int Z;
    cin >> Z;
    while(Z--) {
        testcase();
    }
    return 0;
}

