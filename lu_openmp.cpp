#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
        int n, t;
        scanf("%d %d", &n, &t);
        double a[n][n], pi[n];
		double l[n][n] = {0.0f};
		double u[n][n] = {0.0f};
		double a_copy[n][n];
		
		srand((unsigned)0); 	
		for(int i=0; i<n; i++){
			for(int j=0;j<n;j++){
				a[i][j] = drand48();
				a_copy[i][j] = a[i][j];
				l[i][j]=0.0f;
				u[i][j]=0.0f;
			}
		}
		
		for(int i=0;i<n;i++){
			l[i][i]=1.0f;
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<u[i][j]<<' ';
			}
			cout<<endl;
		}
		cout<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<l[i][j]<<' ';
			}
			cout<<endl;
		}
		cout<<endl;
        for(int i = 0; i < n; i++)
        {
                pi[i] = i;
        }

        for(int k = 0; k < n; k++)
        {
                int k_1;
                double temp;
                double max = 0.0;

                //Finding the pivot.
                for(int i = k; i < n; i++)
                {
                        if(max < abs(a[i][k]))
                        {
                                max = abs(a[i][k]);
                                k_1 = i;
                        }
                }
				
                //Singular Matrix handling.
                if(max == 0)
                {
                        printf("Error: Singluar Matrix.\n");
                        return 0;
                }

                //Swapping pi[k] and pi[k prime]
                temp = pi[k];
                pi[k] = pi[k_1];
                pi[k_1] = temp;
				
				for(int i=0;i<n;i++){
					temp = a[k][i];
					a[k][i]=a[k_1][i];
					a[k_1][i]=temp;
				}
				for(int i=0;i<k;i++){
					temp = l[k][i];
					l[k][i]=l[k_1][i];
					l[k_1][i]=temp;
				}
				u[k][k]=a[k][k];
				
				for (int i = k+1; i < n; i++)
                {
                        l[i][k] = a[i][k]/u[k][k];
                        u[k][i] = a[k][i];
						//cout<<l[i][k]<<endl;
                }
				
				for(int i=k+1;i<n;i++){
					for(int j=k+1;j<n;j++){
						a[i][j]=a[i][j]-l[i][k]*u[k][j];
					}
				}
        }
		double res =0.0;
		double r[n][n];
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				r[i][j] =0;
				for(int k=0;k<n;k++){
					r[i][j]+=l[i][k]*u[k][j];
				}
				double cache = a_copy[(int)pi[i]][j] - r[i][j];
				res+=cache*cache;
			}
		}
		cout<<res<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<a_copy[(int)pi[i]][j]<<' ';
			}
			cout<<endl;
		}
		cout<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<u[i][j]<<' ';
			}
			cout<<endl;
		}
		cout<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<l[i][j]<<' ';
			}
			cout<<endl;
		}
		cout<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<r[i][j]<<' ';
			}
			cout<<endl;
		}
		cout<<endl;
		for(int i=0;i<n;i++){
				cout<<pi[i]<<' ';
		}
        return 0;
}
