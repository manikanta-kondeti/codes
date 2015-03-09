# K-Means clustering 

## Introduction 

This is basically a sample code for K-Means clustering. In this algorithm we try to create K cluster from n data points. The algo follows in this way, take k random points and fill it in the k-clusters. Then fill remaining (n-k) points into K clusters based on eucledian distance. After filling n-points into K-clusters we try to optimize the method by taking each point in every cluster and again trying to fit in the better cluster. 

## Explanation

Each cluster is an object with methods:
  * Methods:
  	* addPoint
	* removePoint 
	* sort 
	* distFromCentroid
	*computeCentroid 
	* printCluster 

## How to run?

chmod +x run.sh
cat results 
  * 'in' file has the input.
  	* First line: test cases 
	* number of data points(n), number of clusters(k)
	* Followed by (x,y) coordinates for n points.
