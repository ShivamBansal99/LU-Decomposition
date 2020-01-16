#include <bits/stdc++.h>
using namespace std;
#include <omp.h>
int main(int argc, char const *argv[])
{
        int n, t;
        scanf("%d %d", &n, &t);
		vector<vector<double> > a( n , vector<double> (n, 0));
		vector<vector<double> > l( n , vector<double> (n, 0));
		vector<vector<double> > u( n , vector<double> (n, 0));
		vector<vector<double> > a_copy( n , vector<double> (n, 0));
		vector<double> pi( n);
		int start = time(0);
		omp_set_num_threads(t);
		#pragma omp parallel
		{
			#pragma omp for collapse(2)
			for(int i=0; i<n; i++){
				for(int j=0;j<n;j++){
					a[i][j] = drand48();
					a_copy[i][j] = a[i][j];
				}
			}
			#pragma omp for
			for(int i=0;i<n;i++){
				l[i][i]=1.0f;
			}
			#pragma omp for
			for(int i = 0; i < n; i++)
			{
					pi[i] = i;
			}
		}
		// for(int i=0;i<n;i++){
			// for(int j=0;j<n;j++){
				// cout<<a[i][j]<<' ';
			// }
			// cout<<endl;
		// }
		// cout<<endl;
        for(int k = 0; k < n; k++)
        {
                int k_1;
                double temp;
                double max_val = 0.0;


                //Finding the pivot.
				//#pragma omp parallel for reduction(max:max_val) reduction(=:k_1)
				for(int i = k; i < n; i++)
                {
                        if(max_val < abs(a[i][k]))
                        {
                                max_val = abs(a[i][k]);
                                k_1 = i;
                        }
                }
				
                //Singular Matrix handling.
                if(max_val == 0)
                {
                        printf("Error: Singluar Matrix.\n");
                        return 0;
                }
				
                //Swapping pi[k] and pi[k prime]
                temp = pi[k];
                pi[k] = pi[k_1];
                pi[k_1] = temp;
				#pragma omp parallel for
				for(int i=0;i<n;i++){
					double temp1 = a[k][i];
					a[k][i]=a[k_1][i];
					a[k_1][i]=temp1;
				}
				#pragma omp parallel for
				for(int i=0;i<k;i++){
					double temp1 = l[k][i];
					l[k][i]=l[k_1][i];
					l[k_1][i]=temp1;
				}
				u[k][k]=a[k][k];
				#pragma omp parallel for
				for (int i = k+1; i < n; i++)
                {
                        l[i][k] = a[i][k]/u[k][k];
                        u[k][i] = a[k][i];
						//cout<<l[i][k]<<endl;
                }
				#pragma omp parallel for collapse(2)
				for(int i=k+1;i<n;i++){
					for(int j=k+1;j<n;j++){
						a[i][j]-=l[i][k]*u[k][j];
					}
				}
        }
		int stop = time(0);
		cout<<"time taken: "<<stop-start<<endl;
		double res =0.0;
		vector<vector<double> > r( n , vector<double> (n, 0));
		#pragma omp parallel for collapse(2) reduction(+:res)
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				for(int k=0;k<n;k++){
					r[i][j]+=l[i][k]*u[k][j];
				}
				double cache = a_copy[(int)pi[i]][j] - r[i][j];
				res+=cache*cache;
			}
		}
		cout<<res<<endl;
		// for(int i=0;i<n;i++){
			// for(int j=0;j<n;j++){
				// cout<<a_copy[(int)pi[i]][j]<<' ';
			// }
			// cout<<endl;
		// }
		// cout<<endl;
		// for(int i=0;i<n;i++){
			// for(int j=0;j<n;j++){
				// cout<<u[i][j]<<' ';
			// }
			// cout<<endl;
		// }
		// cout<<endl;
		// for(int i=0;i<n;i++){
			// for(int j=0;j<n;j++){
				// cout<<l[i][j]<<' ';
			// }
			// cout<<endl;
		// }
		// cout<<endl;
		// for(int i=0;i<n;i++){
			// for(int j=0;j<n;j++){
				// cout<<r[i][j]<<' ';
			// }
			// cout<<endl;
		// }
		// cout<<endl;
		// for(int i=0;i<n;i++){
				// cout<<pi[i]<<' ';
		// }
        return 0;
}
