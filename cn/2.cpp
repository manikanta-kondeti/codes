#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<map>
using namespace std;
long long int m[1100][1100];
long long int cm[1100][1100];
long long int cm1[1100];
int count_k=0;
int subArraySum(long long int arr[], int n, long long int sum)
{
	map<long long int,int> map1;
	long long int var=0;
	long long int var11=0;
	map<long long int,int>::iterator it; 
	for(int i=0;i<n;i++){
			var = var+arr[i];
			it=map1.find(var);
			var11 = var-sum;
			if(it != map1.end() ){
				map1[var]=1;
			}
			else {
				map1[var]+=1;
			}
			if (map1.find(var11) != map1.end()){
				count_k+=map1[var-sum];
			}
			if (arr[i]==sum){
				count_k+=1;}
	}
	return 0;
}
int main(){
	int n;
	scanf("%d",&n);
	int a[1100];
	count_k=0;
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	long long int k;
	scanf("%lld",&k);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			m[i][j]=a[i]*a[j];
		}
	}
	for(int i=0;i<n;i++){
		cm[0][i]=m[0][i];
	}

	for(int j=0;j<n;j++){
		for(int i=1;i<n;i++){
			cm[i][j] += cm[i-1][j]+m[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			for(int z=0;z<n;z++){
				if((i-1)== -1){
					cm1[z]=cm[j][z];		
				}
				else{
					cm1[z]=cm[j][z]-cm[i-1][z];		
				}
			}
			subArraySum(cm1,n,k);
		}
	}
	printf("%d\n", count_k);
	return 0;
}
