#include <stdio.h>
#include <bits/stdc++.h>
#define n 4
#define M 10000
#define PINF 1e30   // 無限大
#define NINF -1e30
using namespace std;

int m;        // 不等式數量
int INF = 0; 
int NA = 0;
// max cx   subject to ax <= b, x >= 0
// assume x = 0 is feasible solution
float a[M][n+M], b[M], c[n+M], na[M];
float row_a[M][n+M], row_b[M];

void init()
{
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
    memset(na, 0, sizeof(na));
 	c[0] = 0, c[1] = 0, c[2] = -1, c[3] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j += 2){
            cin >> a[i][j], a[i][j+1] = -a[i][j];
            row_a[i][j] = a[i][j], row_a[i][j+1] = a[i][j+1];
        }
        if((a[i][0] > 0 && a[i][2] > 0) || (a[i][0] < 0 && a[i][2] > 0)) na[i] = 1;
        cin >> b[i];
        row_b[i] = b[i];
    }
    for (int i = 0; i < m; i++)
        a[i][n+i] = 1;
}
 
void pivot(int& row, int& col)
{
    float max = -PINF;
    for (int j = 0; j < n + m; j++)
        if (c[j] > 0)
        {
            float min = PINF;
            int min_row = -1;
            for (int i = 0; i < m; i++)
                if (a[i][j] > 0){
                    if (b[i] / a[i][j] < min)
                    {	
                    	//cout << "a:" << a[i][j] <<endl;
                        min = b[i] / a[i][j];
                        min_row = i;
                    }
                    INF = 0;
                }
            if (max < min * c[j])
            {
                max = min * c[j];
                col = j, row = min_row;
#ifdef BUG
                //cout << "replace col: " << col << " row: " << row << endl;
#endif
            }
        }
    /*for(int i = 0; i < 4; i ++)
        printf("c[%d]:%f ,", i, c[i]);
    cout << "..." << endl;*/
}
 
float eliminate(int row, int col)
{
    float e = a[row][col];
    for (int j = 0; j < n + m; j++)
        a[row][j] /= e;
    b[row] /= e;
 
    for (int i = 0; i < m; i++)
    {
        if (i == row) continue;
        float t = a[i][col];
        for (int j = 0; j < n + m; j++)
            a[i][j] -= t * a[row][j];
        b[i] -= t * b[row];
        na[i] -= t * na[row];
    }
 
    float t = c[col];
    for (int j = 0; j < n + m; j++){
        c[j] -= t * a[row][j];
    	//cout << "c row" << c[j] << endl;
    }
 	//cout << "should be: " << b[row] * t <<endl;
    return b[row] * -t;
}

float simplex(){

    float z = 0;
    while (true)
    {
        int row = -1, col = -1;
        pivot(row, col);
        if (col == -1) break;
        if(row == -1) {
            //cout << "set INF" << endl;
            INF = 1;
            break;
        }
        z += eliminate(row, col);
    }
    //cout << "z: " << z <<endl;
    return z;
}

float reboot(){
    c[0] = 0, c[1] = 0, c[2] = -1, c[3] = 1;//, c[];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j += 2){
            if(j == 0) a[i][j] = row_a[i][j], a[i][j+1] = (-a[i][j]);
            else if(j == 2) a[i][j] = (-row_a[i][j]), a[i][j+1] = (-row_a[i][j+1]);
#ifdef BUG
           //printf("a[%d][%d]:%f , a[%d][%d]:%f \n", i, j, a[i][j], i, j+1, a[i][j+1]);
#endif 
        }
        if((a[i][0] > 0 && a[i][2] > 0) || (a[i][0] < 0 && a[i][2] < 0) ) na[i] = 1;
        else na[i] = 0;
        b[i] = row_b[i];

#ifdef BUG
        //printf("na[%d]:%f\n", i, na[i]);
#endif 

    }
    for (int i = 0; i < m; i++){
        a[i][n+i] = 1;
    }

#ifdef BUG
    cout << "reboot" << endl;
#endif 
    simplex();
}

int DetectNA(){
	for (int i = 0; i < m; i++)
		if((na[i] != 0) && (na[i] != 1)) return 1;
    return 0;
}

int main(){
 	scanf("%d", &m);
    init();
    float result = simplex();

#ifdef BUG
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j += 2){
            printf("a[%d][%d]:%f , a[%d][%d]:%f , ", i, j, a[i][j], i, j+1, a[i][j+1]);
        }
        printf("b[%d]:%f, n[%d]:%f\n", i, b[i] , i, na[i]);
    }
#endif
    //printf("==========%f\n", result);
	if( result > 0) result = -reboot();
    NA = DetectNA();
    int R = round(result);
    //if(NA) printf("NA\n");
	//else if(INF) printf("-INF\n");+
	printf("%d\n", R);

#ifdef BUG
    for(int i = 0; i < 4; i ++)
        printf("c[%d]:%f ,", i, c[i]);
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j += 2){
            printf("a[%d][%d]:%f , a[%d][%d]:%f , ", i, j, a[i][j], i, j+1, a[i][j+1]);
        }
        printf("b[%d]:%f, n[%d]:%f\n", i, b[i] , i, na[i]);
    }
    printf("\n");
#endif

	return 0;
}

//http://140.112.28.213:8080/