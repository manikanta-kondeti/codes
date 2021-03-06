// Manikanta -- K-Means
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<math.h>
#include<float.h>
#include<limits.h>
using namespace std;
// n= members, x, y array of coords.

class cluster{
	private:
		void computeCentroid();
		double centroidX;
		double centroidY;
	public:
		cluster(int n){
			length=0;
		}
		int length;
		int points[250];
		int pointsX[250];
		int pointsY[250];
		void addPoint(int index, int x, int y);
		void removePoint(int index, int x, int y);
		double distFromCentroid(int x,int y);
		void printCluster();
		void sort();
		//void Init(int);
		//void FreeMemory();
};
/*
   void cluster::Init(int n){
   points = (int *)malloc(n*sizeof(int));
   pointsX = (int *)malloc(n*sizeof(int));
   pointsY = (int *)malloc(n*sizeof(int));
   }

   void cluster::FreeMemory(){
   free(points);
   free(pointsX);
   free(pointsY);
   }
   */
void cluster::sort(){
	int swap, swapX, swapY;
	for(int i=0;i<length-1;i++){
		for(int j=0;j<length-i-1;j++){
			if(points[j]>points[j+1]){
				//swap;
				swap = points[j];
				points[j] = points[j+1];
				points[j+1] = swap;
				swapX = pointsX[j];
				pointsX[j] = pointsX[j+1];
				pointsX[j+1] = swapX;
				swapY = pointsY[j];
				pointsY[j] = pointsY[j+1];
				pointsY[j+1] = swapY;
			}
		}
	}
	return;
}

void cluster::computeCentroid(){
	centroidX=0;
	centroidY=0;
	for(int i=0;i<length;i++){
		centroidX += pointsX[i];
		centroidY += pointsY[i];
	}
	if(length!=0){
		centroidX /= length;
		centroidY /= length;
	}
	return;
}

void cluster::addPoint(int index, int x,int y){
	points[length]=index;
	pointsX[length]=x;
	pointsY[length]=y;
	length++;
	//	cout << "Added Point " << index << "\n";
	computeCentroid();
	return;
}
void cluster::removePoint(int index, int x, int y){
	int q;
	for(int i=0;i<length;i++){
		if(points[i]==index){
			q=i;
		}
	}
	for(int i=q;i<length-1;i++){
		points[i]=points[i+1];
		pointsX[i]=pointsX[i+1];
		pointsY[i]=pointsY[i+1];
	}
	length--;
	computeCentroid();
	return;
}

double cluster::distFromCentroid(int x, int y){
	sort();
	return sqrt(((centroidX-x)*(centroidX-x))+((centroidY-y)*(centroidY-y)));
}

void cluster::printCluster(){
	printf("%d", length);
	for(int i=0;i<length;i++){
		printf(" %d",points[i]+1);
	}	
	printf("\n");
}
int visited[250];int clusterIndexes[250];
int main(){
	int t;
	cin >> t;
	int x[300];
	int y[300];
	for(int test=1;test<=t;test++){
		cout << "case " << test <<" Y" <<"\n";
		int n,k;

		cin >> n;
		cin >> k;
		vector<cluster> c(k+1, cluster(n));
		for(int i=0;i<n;i++){
			//		c[i].FreeMemory();
			cin >> x[i];
			cin >> y[i];
			visited[i]=0;
			clusterIndexes[i]=0;
		}
		int a=0;
		//Initial Clustering 
		for(int i=0;i<k;i++){
			c[i].addPoint(a, x[a], y[a]);
			c[i].addPoint(a+1, x[a+1], y[a+1]);
			visited[a]=1;
			visited[a+1]=1;
			clusterIndexes[a] = i;
			clusterIndexes[a+1] = i;
			a=a+2;
		}

		double m=DBL_MAX,temp;
		int cIndex=0;
		for(int i=0;i<n;i++){
			m = DBL_MAX;
			for(int j=0;j<k;j++){
				if(visited[i]!=1){
					temp = c[j].distFromCentroid(x[i],y[i]);
					if(m > temp){
						m = temp;
						cIndex = j;
					}
				}
			}
			if(visited[i]==0){
				c[cIndex].addPoint(i,x[i],y[i]);
				visited[i] = 1;
				clusterIndexes[i] = cIndex;
			}
		}


		//End of initial clustering 		
		double val1=0, val2=0;
		int flag_convergence=0;
		//int val1=0, val2=0;
		//Check for Convergence
		int ctr=5;
		while(ctr--){
			flag_convergence=0;
			for(int i=0;i<n;i++){
				val1 = c[clusterIndexes[i]].distFromCentroid(x[i],y[i]);
				for(int j=0;j<k;j++){				
					val2 = c[j].distFromCentroid(x[i],y[i]);
					//		printf("Val1=%d val2=%d\n", val1,val2);				
					if(val2 < val1 && c[clusterIndexes[i]].length>2){
						flag_convergence = 1;
						c[clusterIndexes[i]].removePoint(i, x[i], y[i]);	
						c[j].addPoint(i,x[i],y[i]);
						clusterIndexes[i] = j;
						break;
					}
				}
			}
			if(flag_convergence ==0){
				break;
			}
		}		
		for(int i=0;i<k;i++){
			c[i].printCluster();
			//		c[i].FreeMemory();
		}

	}
	return 0;
}
