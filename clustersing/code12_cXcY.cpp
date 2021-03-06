//Author:::  Manikanta -- K-Means, Try-9 ..Initial Clustering with best shortest pairs. 
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <utility>
#include <algorithm>
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


double	dist(int x1, int x2, int y1, int y2){
	return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}

void cluster::printCluster(){
	printf("%d", length);
	for(int i=0;i<length;i++){
		printf(" %d",points[i]+1);
	}	
	printf("\n");
}

int visited[250];int clusterIndexes[250];
double weight[210][210];
int x[300];
int y[300];
int initialPoints[210];
double distPoints[210];
int main(){
	int t;
	cin >> t;
	for(int test=1;test<=t;test++){
		cout << "case " << test <<" Y" <<"\n";
		int n,k;
		cin >> n;
		cin >> k;
		double cX=0, cY=0;
		vector<cluster> c(k+1, cluster(n));
		for(int i=0;i<n;i++){
			cin >> x[i];
			cin >> y[i];
			cX += x[i];
			cY += y[i];
			visited[i]=0;
			clusterIndexes[i]=0;
		}
		cX /= n;
		cY /= n;

		
		double val1=0, val2=0;
		int flag_convergence=0;
		int outctr=14;
		double m=DBL_MAX,temp;
		int cIndex=0;


		/*
		// Method-4: Divide into K sets based on sorted distances values.
		for(int i=0;i<n;i++){
			distPoints[i] = sqrt(((cX-x[i])*(cX-x[i]))+((cY-y[i])*(cY-y[i])));
			initialPoints[i]=i;
		}

		
		double s2;
		int s1;
		for(int i=0;i<n-1;i++){
			for(int j=0;j<n-i-1;j++){
				if(distPoints[j]>distPoints[j+1]){
					//swap;
					s2 = distPoints[j];
					distPoints[j] = distPoints[j+1];
					distPoints[j+1] = s2;
					s1 = initialPoints[j];
					initialPoints[j] = initialPoints[j+1];
					initialPoints[j+1] = s1;
				}
			}
		}
		

		for(int i=0;i<n;i++){
//			printf("Points=%d  dist=%lf cX=%lf  cY=%lf\n", initialPoints[i],distPoints[i],cX, cY);
		}
		int itrFlag=0,q=0;
		for(int i=0;i<k;i++){
			for(int j=0;j<n/k;j++){
				c[i].addPoint(initialPoints[itrFlag], x[initialPoints[itrFlag]], y[initialPoints[itrFlag]]);
				visited[initialPoints[itrFlag]] = 1;
				clusterIndexes[initialPoints[itrFlag]] = i;
				itrFlag++;
			}
		}
		for(int i=itrFlag;i<n;i++){
				c[k-1].addPoint(initialPoints[itrFlag], x[initialPoints[itrFlag]], y[initialPoints[itrFlag]]);
				visited[initialPoints[itrFlag]] = 1;
				clusterIndexes[initialPoints[itrFlag]] = k-1;
				itrFlag++;
		}
		*/

		/*
		//Distance Matrix
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i!=j){
					weight[i][j]=dist(x[i],y[i],x[j],y[j]);
				}
				else if(i==j){
					weight[i][j]=0;
				}
			}
		}
		*/

		/*
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
		*/
		
		

		//Initial Clustering Algo-2:  Take best solutions
		for(int i=0;i<k;i++){
			m=DBL_MAX;
			for(int j=n-1;j>=0;j--){
				if(c[i].length==0 && visited[initialPoints[j]]==0){
					c[i].addPoint(initialPoints[j], x[initialPoints[j]], y[initialPoints[j]]);
					visited[initialPoints[j]] = 1;
					clusterIndexes[initialPoints[j]] = i;
				}
				else if(c[i].length == 1 && visited[initialPoints[j]]==0){
					temp = c[i].distFromCentroid(x[initialPoints[j]],y[initialPoints[j]]);
					if(m > temp){
						m = temp;
						cIndex = initialPoints[j];
					}
				}
			}
			if(visited[cIndex]==0){
				c[i].addPoint(cIndex,x[cIndex],y[cIndex]);
				visited[cIndex] = 1;
				clusterIndexes[cIndex] = i;
			}
		}
		

		// Taking best pairs from distance matrix
		/*
		   int a1,a2;
		   for(int i=0;i<k;i++){
		   for(int j=0;j<v_count;j++){
		   a1 = V[j].pairs.first;
		   a2 = V[j].pairs.second;
		   if(visited[a1]!=1 && visited[a2]!=1 ){
		   c[i].addPoint(a1, x[a1], y[a1]);
		   c[i].addPoint(a2, x[a2], y[a2]);
		   visited[a1]=1;
		   visited[a2]=1;
		   clusterIndexes[a1] = i;
		   clusterIndexes[a2] = i;
		   break;
		   }
		   }
		   }*/

		
		for(int i=n-1;i>=0;i--){
			m = DBL_MAX;
			for(int j=k-1;j>=0;j--){
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
		



		//Check for Convergence

		int ctr;
		outctr=14;
		while(outctr--){
		ctr=10;
		while(ctr--){
			for(int i=0;i<n;i++){
				val1 = c[clusterIndexes[i]].distFromCentroid(x[i],y[i]);
				for(int j=0;j<k;j++){				
					val2 = c[j].distFromCentroid(x[i],y[i]);
					//		printf("Val1=%d val2=%d\n", val1,val2);				
					if(val2 < val1 && c[clusterIndexes[i]].length>0){
						flag_convergence = 1;
						c[clusterIndexes[i]].removePoint(i, x[i], y[i]);	
						c[j].addPoint(i,x[i],y[i]);
						clusterIndexes[i] = j;
						break;
					}
				}
			}
		}
		int mflag;
		mflag=0;
		for(int i=0;i<k;i++){
			m=DBL_MAX;
			mflag=0;
			if(c[i].length==0){
				for(int j=n-1;j>=0;j--){
					if(i!=clusterIndexes[j] &&c[clusterIndexes[j]].length>2){
						temp = c[i].distFromCentroid(x[j],y[j]);
						if(m > temp){
							m = temp;
							mflag=1;
							cIndex = j;
						}
					}
				}
				if(mflag==1){
				c[clusterIndexes[cIndex]].removePoint(cIndex,x[cIndex],y[cIndex]);
				c[i].addPoint(cIndex,x[cIndex],y[cIndex]);
				clusterIndexes[cIndex] = i;
				}
			}
			mflag=0;
			m=DBL_MAX;
			 if(c[i].length==1){
				for(int j=n-1;j>=0;j--){
					if(i!=clusterIndexes[j] &&c[clusterIndexes[j]].length>2){
						temp = c[i].distFromCentroid(x[j],y[j]);
						if(m > temp){
							m = temp;
							mflag=1;
							cIndex = j;
						}
					}
				}
				if(mflag==1){
				c[clusterIndexes[cIndex]].removePoint(cIndex,x[cIndex],y[cIndex]);
				c[i].addPoint(cIndex,x[cIndex],y[cIndex]);
				clusterIndexes[cIndex] = i;
				}
			}
		}

		}

		for(int i=0;i<k;i++){
			assert(c[i].length>=2);
			c[i].printCluster();
		}

	}
	return 0;
}
