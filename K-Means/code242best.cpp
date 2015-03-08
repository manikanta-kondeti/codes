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
        computeCentroid();
        computedMax();
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
        computedMax();
        return;
}


double cluster::distFromCentroid(int x, int y){
        return sqrt(((centroidX-x)*(centroidX-x))+((centroidY-y)*(centroidY-y)));
}




double        dist(int x1, int x2, int y1, int y2){
        return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}


void cluster::computedMax(){
        double max=DBL_MAX;
        dmax = 0;
        d1=points[0];
        d2=points[0];
        for(int i=0;i<length;i++){
                for(int j=i+1;j<length;j++){
                        max = weight[points[i]][points[j]];
                        if(dmax < max ){
                                dmax = max;
                                d1=points[i];
                                d2=points[j];
                        }
                }
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
bool comp(cluster c1,cluster c2)
{
        if(c1.dmax<c2.dmax)
                return true;
        return false;
}
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


                for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                                weight[i][j] = sqrt(((x[i]-x[j])*(x[i]-x[j]))+((y[i]-y[j])*(y[i]-y[j]))); 
                                //        printf("weight[i][j]=%lf ", weight[i][j]);
                        }
                }
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
                        //                        printf("sorted %lf  indexes=%d\n", distPoints[i], initialPoints[i]);
                }




                double m=DBL_MAX,temp;
                int cIndex=0, zflag=0;


                /* Make clusters with including dmax */
                double s=0;
                double tempd=0;
                for(int i=0;i<k;i++){
                        m=DBL_MAX,zflag=0,s=0;
                        for(int j=n-1;j>=0;j--){
                                if(c[i].length==0 && visited[initialPoints[j]]==0){
                                        c[i].addPoint(initialPoints[j], x[initialPoints[j]], y[initialPoints[j]]);
                                        visited[initialPoints[j]] = 1;
                                        clusterIndexes[initialPoints[j]] = i;
                                }
                                else if(c[i].length == 1 && visited[initialPoints[j]]==0){
                                        temp = c[i].distFromCentroid(x[initialPoints[j]],y[initialPoints[j]]);
                                        c[i].addPoint(initialPoints[j], x[initialPoints[j]], y[initialPoints[j]]);
                                        tempd=c[i].dmax;
                                        c[i].removePoint(initialPoints[j], x[initialPoints[j]], y[initialPoints[j]]);
                                        //s = (0.5*temp + 0.5*tempd);
                                //        s= tempd;
                                        s =temp;
                                        if(m > s){
                                                m = s;
                                                cIndex = initialPoints[j];
                                                zflag=1;
                                        }
                                }
                        }
                        if(visited[cIndex]==0 && zflag==1){
                                c[i].addPoint(cIndex,x[cIndex],y[cIndex]);
                                visited[cIndex] = 1;
                                clusterIndexes[cIndex] = i;
                        }
                }
                // Clusters with two nodes done 


                int temp1=0;
                int wctr=25;
                while(wctr--){
                        for(int i=n-1;i>=0;i--){
                                m = DBL_MAX,zflag=0;
                                for(int j=k-1;j>=0;j--){
                                        if(visited[initialPoints[i]]!=1){
                                                //temp = c[j].distFromCentroid(x[initialPoints[i]],y[initialPoints[i]]);
                                                temp1 = c[j].dmax;
                                                c[j].addPoint(initialPoints[i],x[initialPoints[i]],y[initialPoints[i]]);
                                                temp = c[j].dmax;
                                                if(temp <= temp1){
                                                        visited[initialPoints[i]] = 1;
                                                        clusterIndexes[initialPoints[i]] = j;
                                                }
                                                else if(temp > temp1){        
                                                        c[j].removePoint(initialPoints[i],x[initialPoints[i]],y[initialPoints[i]]);
                                                }
                                        }
                                }
                                }
                        }


                        for(int i=0;i<n;i++){
                                m = DBL_MAX,zflag=0;
                                for(int j=k-1;j>=0;j--){
                                        if(visited[initialPoints[i]]!=1){
                                                temp = c[j].distFromCentroid(x[initialPoints[i]],y[initialPoints[i]]);
                                                if(m > temp){
                                                        m = temp;
                                                        cIndex = j;
                                                        zflag=1;
                                                }
                                        }
                                }
                                if(visited[initialPoints[i]]==0 && zflag==1){
                                        c[cIndex].addPoint(initialPoints[i],x[initialPoints[i]],y[initialPoints[i]]);
                                        visited[initialPoints[i]] = 1;
                                        clusterIndexes[initialPoints[i]] = cIndex;
                                }
                        }


                // Clusters filled with n data points. Next step is to try to move data points and decrease 'dmax'


                double val1=0, val2=0,dval1=0,dval2=0;
                int outctr=15;
                while(outctr--){
                        int ctr;
                        int mflag;
                        ctr=12;                        
                        while(ctr--){
                                for(int i=n-1;i>=0;i--){
                                        val1 = c[clusterIndexes[i]].distFromCentroid(x[i],y[i]);
                                        for(int j=0;j<k;j++){                                
                                                val2 = c[j].distFromCentroid(x[i],y[i]);
                                                if(val2 < val1 && c[clusterIndexes[i]].length> 0 && clusterIndexes[i]!=j ){
                                                        c[clusterIndexes[i]].removePoint(i, x[i], y[i]);        
                                                        c[j].addPoint(i,x[i],y[i]);
                                                        clusterIndexes[i] = j;
                                                        break;
                                                }
                                        }
                                }
                        }        
                        mflag=0;
                        for(int i=0;i<k;i++){
                                m=DBL_MAX;
                                mflag=0;
                                if(c[i].length==0){
                                        for(int j=0;j<n;j++){
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
                        int cntr=25;
                        while(cntr--){
                                int i=k-1;
                                if(c[i].length>2){
                                int rcluster[2],acluster[2],rpoint[2];
                                int p1[2];
                                p1[0]=c[i].d1,p1[1]=c[i].d2;
                                int besti;
                                double bestd[2]={DBL_MAX};
                                double tdmax;
                                for(int l=0;l<2;l++){
                                        rcluster[l]=-1;acluster[l]=-1; 
                                        double ndmax;
                                        c[i].removePoint(p1[l],x[p1[l]],y[p1[l]]);
                                        rpoint[l]=p1[l];
                                        rcluster[l]=i;
                                        ndmax=c[i].dmax;
                                        for(int j=0;j<k-1;j++){
                                                c[j].addPoint(p1[l],x[p1[l]],y[p1[l]]);
                                                int aa =clusterIndexes[p1[l]];
                                                clusterIndexes[p1[l]] = j;
                                                tdmax=c[j].dmax;
                                                c[j].removePoint(p1[l],x[p1[l]],y[p1[l]]);
                                                clusterIndexes[p1[l]] = aa;
                                                if(tdmax<=ndmax){
                                                        rpoint[l]=p1[l];
                                                        acluster[l]=j;
                                                        bestd[l]=ndmax;
                                                        break;
                                                }
                                        }
                                        if(acluster[l]==-1)
                                        {
                                                double bdmax=DBL_MAX;
                                                for(int j=0;j<k-1;j++)
                                                {
                                                        tdmax=c[j].dmax;
                                                        if(tdmax<bdmax)
                                                        {
                                                                bdmax=tdmax;
                                                                rpoint[l]=p1[l];
                                                                acluster[l]=j;
                                                        }
                                                }
                                                bestd[l]=bdmax;
                                        }
                                        if(l==1)
                                        {
                                                if(bestd[1]<bestd[0])
                                                        besti=1;
                                                else
                                                        besti=0;
                                        }
                                        c[i].addPoint(p1[l],x[p1[l]],y[p1[l]]);
                                        clusterIndexes[p1[l]] = i;
                                }
                                if(acluster[besti]!=-1){
                                        c[i].removePoint(rpoint[besti],x[rpoint[besti]],y[rpoint[besti]]);
                                        c[acluster[besti]].addPoint(rpoint[besti],x[rpoint[besti]],y[rpoint[besti]]);
                                        clusterIndexes[rpoint[besti]] = acluster[besti];
                                }
                                sort(c.begin(),c.end(),comp);
                                for(int i=0;i<n;i++){
                                        for(int j=0;j<k;j++){
                                                for(int w=0;w<c[j].length;w++){
                                                        if(i==c[j].points[w])
                                                                clusterIndexes[i]=j;
                                                }
                                        }
                                }
                                }
                        }




                //Global gdamx 
                double gdmax=0, gdmaxConverge=0;
                double d=0;
                for(int i=0;i<k;i++){
                        d= MAX(d,c[i].dmax);
                        gdmax=d;
                }
                //Check for Convergence
                val1=0, val2=0,dval1=0,dval2=0;
                outctr=15;
                while(outctr--){
                        int ctr;
                        int mflag;
                        ctr=12;                        
                        while(ctr--){
                                for(int i=n-1;i>=0;i--){
                                        val1 = c[clusterIndexes[i]].distFromCentroid(x[i],y[i]);
                                        for(int j=0;j<k;j++){                                
                                                val2 = c[j].distFromCentroid(x[i],y[i]);
                                                if(val2 < val1 && c[clusterIndexes[i]].length> 0 && clusterIndexes[i]!=j ){
                                                        c[clusterIndexes[i]].removePoint(i, x[i], y[i]);        
                                                        c[j].addPoint(i,x[i],y[i]);
                                                        clusterIndexes[i] = j;
                                                        break;
                                                }
                                        }
                                }
                        }        
                        mflag=0;
                        for(int i=0;i<k;i++){
                                m=DBL_MAX;
                                mflag=0;
                                if(c[i].length==0){
                                        for(int j=0;j<n;j++){
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
                d=0;
                for(int i=0;i<k;i++){
                        assert(c[i].length>=2);
                        d= MAX(d,c[i].dmax);
                        c[i].printCluster();
                }
        }
        return 0;
}
