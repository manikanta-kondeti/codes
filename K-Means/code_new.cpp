/* Author: Manikanta -- Objective: (Minimize d = Maximize score) */
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <utility>
#include <algorithm>
using namespace std;
// n= members, x, y array of coords.

#define MAX(a, b) ((a > b) ? a : b) 

class cluster{
	public:
		cluster(){
			length=0;
			centroidX = 0;
			centroidY = 0;
		}
		double dmax;
		int d1;
		int d2;
		double centroidX;
		double centroidY;
		int length;
		int points[201];
		int pointsX[201];
		int pointsY[201];
		void addPoint(int index, int x, int y);
		void removePoint(int index, int x, int y);
		double distFromCentroid(int x,int y);
		void printCluster();
		void computedMax();
		void sort();
		void computeCentroid();
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
	return;
}

double cluster::distFromCentroid(int x, int y){
	return sqrt(((centroidX-x)*(centroidX-x))+((centroidY-y)*(centroidY-y)));
}


double	dist(int x1, int x2, int y1, int y2){
	return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}

void cluster::computedMax(){
	double max3;
	dmax = DBL_MIN;
	for(int i=0;i<length;i++){
		for(int j=i+1;j<length;j++){
			max3 = sqrt(((pointsX[i]-pointsX[j])*(pointsX[i]-pointsX[j]))+((pointsY[i]-pointsY[j])*(pointsY[i]-pointsY[j])));
			if(dmax < max3 ){
				dmax = max3;
				d1=points[i];
				d2=points[j];
			}
		}
	
	}
	if(dmax==DBL_MIN){
		d1=points[0];
		d2=points[0];
		dmax = 0;
	}
	return;
}

void cluster::printCluster(){
	sort();
	printf("%d", length);
	for(int i=0;i<length;i++){
		printf(" %d",points[i]+1);
	}	
	printf("\n");
}
bool comp(cluster c1,cluster c2)
{
        if(c1.dmax<c2.dmax)
                return true;
        return false;
}


int clusterIndexes[210];
int x[210];
int y[210];
double cpointx[220],cpointy[220];




int main(){
	int t;
	cin >> t;
	for(int test=1;test<=t;test++){
		cout << "case " << test <<" Y" <<"\n";
		int n,k;
		cin >> n;
		cin >> k;
		vector<cluster> c(k);
		double cX=0, cY=0;
		double m=DBL_MAX,temp;
		int cIndex=0, zflag=0;
		for(int i=0;i<n;i++){
			cin >> x[i];
			cin >> y[i];
			clusterIndexes[i]=0;
		}
		// Making one cluster intially. 
		// there will be k-1 iterations and in every iteration number of clusters in increased by 1. therefore in the end there will be k clusters.
		// in the available clusters get the max3 distance within clusters and then the farthest point will form the 3rd cluster.
		double max1=DBL_MAX,max2=DBL_MAX, min1=DBL_MIN;
		int rpoint, rpoint1, rpoint2, rindex;
		int apoint, aindex;
		double dist1, dist2,dist3;
		for(int i=0;i<n;i++){
			c[0].addPoint(i, x[i], y[i]);
			clusterIndexes[i]=0;
		}
		c[0].computedMax();
		c[0].computeCentroid();
		cpointx[0]=c[0].centroidX;
		cpointy[0]=c[0].centroidY;
		int clength=1;


		for(int i=1;i<k;i++){
			max1 = DBL_MAX;
			min1 = DBL_MIN;
			max2 = DBL_MAX;
			for(int j=0;j<clength;j++){
				c[j].computedMax();
				//find max3
				if(min1 <  c[j].dmax ){
					min1 = c[j].dmax;
					rpoint1 = c[j].d1;
					rpoint2 = c[j].d2;
					rindex = j;
				}
			}
			dist1 = c[rindex].distFromCentroid(x[rpoint1], y[rpoint1]);
			dist2 = c[rindex].distFromCentroid(x[rpoint2], y[rpoint2]);
			if(dist1>= dist2){
				rpoint = rpoint1;
			}
			else if(dist1 < dist2)
			{
				rpoint = rpoint2;
			}			
			cpointx[i]=double(x[rpoint]);
			cpointy[i]=double(y[rpoint]);
			clusterIndexes[rpoint]=i;
			c[rindex].removePoint(rpoint, x[rpoint], y[rpoint]);
			c[i].addPoint(rpoint, x[rpoint], y[rpoint]);
			clength=i+1;
		
			for(int p=0;p<n;p++){
				max2 = DBL_MAX;
				for(int q=0;q<clength;q++){
					dist3 = sqrt(((cpointx[q]-x[p])*(cpointx[q]-x[p]))+((cpointy[q]-y[p])*(cpointy[q]-y[p])));	
					if(max2 > dist3 ){
						max2 = dist3;
						aindex = q;
					}
				}
				assert(clusterIndexes[p]<clength);
				c[clusterIndexes[p]].removePoint(p,x[p],y[p]);
				c[aindex].addPoint(p,x[p],y[p]);
				clusterIndexes[p] = aindex;
			}
			
			for(int j=0;j<i; j++){
				c[j].computeCentroid();
				cpointx[j] = c[j].centroidX;
				cpointy[j] = c[j].centroidY;
			}
			
		}
	
		for(int i=0;i<k;i++){
			if(c[i].length<2){
				max2 = DBL_MAX;
				for(int j=0;j<n;j++){
					dist1 = sqrt(((x[j]-c[i].centroidX)*(x[j]-c[i].centroidX))+((y[j]-c[i].centroidY)*(y[j]-c[i].centroidY)));
					if(max2 > dist1 && c[clusterIndexes[j]].length>2){
						max2 = dist1;
						apoint = j;
					}
				}
				c[clusterIndexes[apoint]].removePoint(apoint, x[apoint], y[apoint]);
				c[i].addPoint(apoint, x[apoint], y[apoint]);
				clusterIndexes[apoint] = i;
			}
		}

		
		for(int i=0;i<k;i++){
			c[i].printCluster();
		}

	}
	return 0;
}
