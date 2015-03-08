/* Author: Manikanta -- Objective: (Minimize d = Maximize score) */
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

#define MAX(a, b) ((a > b) ? a : b) 

double weight[210][210];
class cluster{
	private:
		void computeCentroid();
		double centroidX;
		double centroidY;
	public:
		cluster(){
			length=0;
		}
		double dmax;
		int d1;
		int d2;
		int length;
		int points[250];
		int pointsX[250];
		int pointsY[250];
		void addPoint(int index, int x, int y);
		void removePoint(int index, int x, int y);
		double distFromCentroid(int x,int y);
		void printCluster();
		void computedMax();
		void sort();
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
	double max=DBL_MIN;
	dmax = 0;
	d1=points[0];
	d2=points[0];
	for(int i=0;i<length;i++){
		for(int j=i+1;j<length;j++){
			dmax = weight[points[i]][points[j]];
			if(dmax > max ){
				max = dmax;
				d1=points[i];
				d2=points[j];
			}
		}
		dmax = max;
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

int visited[250];int clusterIndexes[250];
int x[300];
int y[300];
int initialPoints[300];
double distPoints[300];

struct Node{
	int p1;
	int p2;
	double val;
};

bool comp(cluster c1,cluster c2)
{
	if(c1.dmax<c2.dmax)
		return true;
	return false;
}
bool compStruct(Node c1,Node c2)
{
	if(c1.val<c2.val)
		return true;
	return false;
}

double getdmax(vector<cluster> c, int k){
	double maxdmax=0.0,d=DBL_MIN;
	for(int i=0;i<k;i++){
		maxdmax=c[i].dmax;
		if(d<maxdmax){
			d=maxdmax;
		}
	}
	return d;
}

Node node[40001];

int main(){
	int t;
	cin >> t;
	double score = 0;
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
			visited[i]=0;
			clusterIndexes[i]=0;
		}

		int nodeCount=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				weight[i][j] = sqrt(((x[i]-x[j])*(x[i]-x[j]))+((y[i]-y[j])*(y[i]-y[j]))); 
				//	printf("weight[i][j]=%lf ", weight[i][j]);
				if(i!=j && i<j){
					node[nodeCount].p1 = i;
					node[nodeCount].p2 = j;
					node[nodeCount].val = weight[i][j];
					nodeCount++;
				}
			}
		}

		sort(node, node+nodeCount, compStruct);


		//First  fill clusters with 2points each 
		for(int i=0;i<k;i++){
			for(int j=0;j<nodeCount;j++){
				if(visited[node[j].p1] ==0 && visited[node[j].p2]==0){
					c[i].addPoint(node[j].p1, x[node[j].p1], y[node[j].p1]);
					c[i].addPoint(node[j].p2, x[node[j].p2], y[node[j].p2]);
					visited[node[j].p1]=1;
					visited[node[j].p2]=1;
					clusterIndexes[node[j].p1]=i;
					clusterIndexes[node[j].p2]=i;
					break;
				}
			}
		}


		double befored, afterd, max=DBL_MAX, maxval=DBL_MAX, val;
		for(int i=0;i<n;i++){
			if(visited[i]!=1){
				max = DBL_MAX;
				for(int j=0;j<k;j++){
					c[j].computedMax();
					befored = c[j].dmax;
					c[j].addPoint(i, x[i], y[i]);
					c[j].computedMax();
					afterd = c[j].dmax;
					c[j].removePoint(i, x[i], y[i]);
					if(befored == afterd){		
							cIndex = j;
					}
					else if(befored < afterd)
					{
						if(max > afterd ){
							max = afterd;
							cIndex = j;
						}
					}
				}
				c[cIndex].addPoint(i, x[i], y[i]);
				visited[i]=1;
				clusterIndexes[i]=cIndex;
			}
		}



		//Global gdamx 


	 	double check = getdmax(c, k);
		// Clusters filled with n data points. Next step is to try to move data points and decrease 'dmax'


					sort(c.begin(),c.end(),comp);
					for(int i=0;i<n;i++){
						for(int j=0;j<k;j++){
							for(int w=0;w<c[j].length;w++){
								if(i==c[j].points[w])
									clusterIndexes[i]=j;
							}
					}
				}


					// New Code --- Optimizing dmax
					double initdmax, finaldmax,max1,max2;
					int checkflag = 0;

		int cntr=30;
		while(cntr--){
			int i=k-1;
			initdmax= c[k-1].dmax;	
			max1=DBL_MAX, max2=DBL_MAX;
			checkflag=0;
				int mflag;
					int rcluster[2],acluster[2],rpoint[2];
					int p1[2];
					p1[0]=c[i].d1,p1[1]=c[i].d2;
					int besti;
					double bestd[2];
					bestd[0]=DBL_MAX, bestd[1]=DBL_MAX;
					double tdmax1,tdmax2,middledmax;

					//Check for Convergence
					for(int l=0;l<2;l++){
					max1=DBL_MAX, max2=DBL_MAX;
					checkflag=0;
						acluster[l]=-1; 
						double ndmax;
						c[i].removePoint(p1[l],x[p1[l]],y[p1[l]]);
						rpoint[l]=p1[l];
						rcluster[l]=i;
						for(int j=0;j<k-1;j++){
							c[j].computedMax();
							tdmax1=c[j].dmax;
							c[j].addPoint(p1[l],x[p1[l]],y[p1[l]]);
							c[j].computedMax();
							tdmax2=c[j].dmax;
							middledmax = getdmax(c,k);
							c[j].removePoint(p1[l],x[p1[l]],y[p1[l]]);
							if(tdmax1 == tdmax2){
								if(max1 > middledmax){
									max1=middledmax;
									rpoint[l] = p1[l];
									acluster[l] = j;
									rcluster[l] = i;
									checkflag = 1;
								}
							}
							else if (tdmax2 > tdmax1 && (checkflag==0 || checkflag==2)){
								if(initdmax >= middledmax){
								if(max2 > middledmax){
									max2=middledmax;
									rpoint[l] = p1[l];
									acluster[l]= j;
									rcluster[l] = i;
									checkflag = 2;
								}
							}
								else if(initdmax < middledmax && (checkflag!=2)){
									acluster[l]= i;
								}
						}
						bestd[l] = MAX(bestd[l],middledmax);
					}
						c[i].addPoint(p1[l],x[p1[l]],y[p1[l]]);
				}
					if(bestd[0] > bestd[1])
						besti=1;
					else if(bestd[0] <= bestd[1])
						besti=0;
					if(acluster[besti]!=-1){
						c[i].removePoint(rpoint[besti],x[rpoint[besti]],y[rpoint[besti]]);
						c[acluster[besti]].addPoint(rpoint[besti],x[rpoint[besti]],y[rpoint[besti]]);
						clusterIndexes[rpoint[besti]] = acluster[besti];
					}

					sort(c.begin(),c.end(),comp);
					for(int i=0;i<n;i++){
						for(int j=0;j<k;j++){
							c[j].computedMax();
							for(int w=0;w<c[j].length;w++){
								if(i==c[j].points[w])
									clusterIndexes[i]=j;
							}
					}
			}
		}


		for(int i=0;i<k;i++){
			assert(c[i].length>=2);
			c[i].printCluster();
		}
	//	cout << "Finaldmax = " << finaldmax << endl;
	}
	return 0;
}
