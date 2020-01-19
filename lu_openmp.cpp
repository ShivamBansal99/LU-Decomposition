#include <bits/stdc++.h>
using namespace std;
#include <omp.h>
int change_index(int i,int j,int n){
	return j+i*n;
}
int main(int argc, char const *argv[])
{
        int n, t;
        scanf("%d %d", &n, &t);
		double** a = (double **)malloc(n*sizeof(double*));
		vector<double> l( n*n ,0);
		double** u = (double **)malloc(n*sizeof(double*));
		vector<vector<double> > a_copy( n , vector<double> (n, 0));
		vector<double> pi( n);
		//double start = time(0);
		auto start = chrono::high_resolution_clock::now();
		omp_set_num_threads(t);
		#pragma omp parallel
		{
			//#pragma omp for collapse(2)
			for(int i=0; i<n; i++){
				a[i] = (double *)malloc(n*sizeof(double));
				u[i] = (double *)malloc(n*sizeof(double));
				for(int j=0;j<n;j++){
					u[i][j]=0;
					a[i][j] = drand48();
					a_copy[i][j] = a[i][j];
				}
			}
			#pragma omp for
			for(int i=0;i<n;i++){
				l[change_index(i,i,n)]=1.0f;
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
					double temp1 = l[change_index(k,i,n)];
					l[change_index(k,i,n)]=l[change_index(k_1,i,n)];
					l[change_index(k_1,i,n)]=temp1;
				}
				u[k][k]=a[k][k];
				#pragma omp parallel for
				for (int i = k+1; i < n; i++)
                {
                        l[change_index(i,k,n)] = a[i][k]/u[k][k];
                        u[k][i] = a[k][i];
						//cout<<l[i][k]<<endl;
                }
				//int k1 = k*n;
				#pragma omp distribute parallel for	simd
				for(int i=k+1;i<n;i++){
					// int i1= i*n;
					register double temp1 = l[i*n+k];
					for(int j=k+1;j<n;j++){
						a[i][j]-=temp1*u[k][j];
					}
				}
        }
		//double stop = time(0);
		auto stop = chrono::high_resolution_clock::now();
		cout<<"time taken: "<<(double)(chrono::duration_cast<chrono::milliseconds>(stop-start).count())/1000<<endl;
		// double res =0.0;
		// vector<vector<double> > r( n , vector<double> (n, 0));
		// #pragma omp parallel for collapse(2) reduction(+:res)
		// for(int i=0;i<n;i++){
			// for(int j=0;j<n;j++){
				// for(int k=0;k<n;k++){
					// r[i][j]+=l[change_index(i,k,n)]*u[k][j];
				// }
				// double cache = a_copy[(int)pi[i]][j] - r[i][j];
				// res+=cache*cache;
			// }
		// }
		// cout<<res<<endl;
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
