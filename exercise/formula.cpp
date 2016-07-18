#include<iostream>

using namespace std;

int N,T;
int a[100010];
int ans;

void mergesort(int A[], int lft, int rgt)
{
    int B[100010];
    int x,mid,p1,p2;

    if(lft==rgt) return;
    mid = (lft+rgt)/2;
    mergesort(A,lft,mid);
    mergesort(A,mid+1,rgt);
    p1 = lft;
    p2 = mid+1;
    x=0;
    while( p1 <= mid && p2 <= rgt)
    {
        x++;
        if(A[p1] < A[p2])
        {
            B[x]=A[p1];
            p1++;
        }
        else
        {
            B[x]=A[p2];
            p2 ++;
            ans = (ans+(mid-p1+1))%10000;
            //cout << lft << " " << rgt << " " << mid << endl;
        }
    }
    while(p1<=mid)
    {
        x++;
        B[x]=A[p1];
        p1++;
    }
    while(p2<=rgt)
    {
        x++;
        B[x]=A[p2];
        p2++;
    }
    for(int i=lft;i<=rgt;i++)
    {
        A[i]=B[i-lft+1];
    }
}

int main()
{
    cin >> T;
    while(T--)
    {
        cin >> N;
        for(int i=1;i<=N;i++)
            cin >> a[i];
        ans = 0;
        mergesort(a,1,N);
        cout << ans << endl;
    }
    return 0;
}

