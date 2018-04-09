#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
using namespace std;
 
// Maximum string length
#define N 102
 
int L[N][N];
int LCS_LEN = 0, LCS_NUM = 0;
int idx = 0;

string X, Y;
string tmp;
vector <string> s;
/*bool compare(void const *data1, void const *data2){
	return strcmp(( *) data1, (char *)data2);
}
*/
void findLCS(int m, int n, int len){
	if(L[m][n] == 0){
		if(len == -1){
            tmp = tmp.assign(tmp, 0, LCS_LEN);
			s.push_back(tmp);
			LCS_NUM++; 
		}
	}
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			if(X[i-1] == Y[j-1] && L[m][n] == L[i][j]){
				//cout << "len: " << len;
				tmp[len] = X[i-1];
				//cout << "tmp: " << tmp << endl; 
				findLCS(i-1, j-1, len-1);
			}
		}
	}
	return;
}

int LCS(int m, int n){

    // Build L[m+1][n+1] in bottom up fashion
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    return L[m][n];
}
/* Driver program to test above function */
int main(){

    cin >> X;
    cin >> Y;
    int m = X.length();
    int n = Y.length();
    
    LCS_LEN = LCS(m, n);
 	tmp.resize(200);
    findLCS(m, n, LCS_LEN-1);
    cout <<  LCS_LEN <<" " << LCS_NUM << endl;
    sort(s.begin(), s.end());
    /*for(int i = 0; i < s.size(); j++){
        for(int j = 0; j <= LCS_NUM; j++){

        }
    }*/
    vector<string>::iterator itr;
   	for (itr = s.begin(); itr != s.end(); itr++){
        cout << *itr << endl;
   	}
    return 0;
}