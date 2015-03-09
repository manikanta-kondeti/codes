# K-Means clustering 

## Introduction 

This is basically a sample implementation on K-Means clustering. In this algorithm we try to create K clusters from N data points. The algorithm follows in this way. Take 'K' random points and fill it in the k-clusters. Then fill remaining (n-k) points into K clusters based on eucledian distance of that point and centroid of that cluster. After filling N-points into K-clusters we try to optimize the method by taking each point in every cluster and again trying to fit in the better cluster. 

## Explanation

Each cluster is an object with methods:
  * Methods:
  	* addPoint
	* removePoint 
	* sort 
	* distFromCentroid
	* computeCentroid 
	* printCluster 

## How to run?
* git clone https://github.com/manikanta-kondeti/codes
* cd codes/K-Means 
* chmod +x run.sh
* cat results 
  * 'in' file has the input.
  	* First line: test cases 
	* number of data points(n), number of clusters(k)
	* Followed by (x,y) coordinates for n points.

## License 
Released under MIT-X license. Feel free to get in touch with me if you have any doubts or want to give me some suggestions.
