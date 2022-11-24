#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <cmath>
using namespace std;

#define D_SIZE 200

typedef vector<vector<double> > PointGroup;
typedef vector<vector<pair<double, int> > > Neighbors;

double dist(PointGroup &data, int i, int j) {
  // Return the distance between the two points ith and jth in data
  return sqrt((data[i][0]-data[j][0])*(data[i][0]-data[j][0]) + (data[i][1]-data[j][1])*(data[i][1]-data[j][1]));
}

double reach_dist(PointGroup &data, Neighbors &neighbors, int i, int j) {
  double d = dist(data, i, j);
  int k = neighbors[j].size();
  return (d > neighbors[j][k-1].first ? d : neighbors[j][k-1].first);
}

double lrd(PointGroup &data, Neighbors &neighbors, int i) {
  double sum = 0;
  int k = neighbors[i].size();

  for(int j=0; j<k; ++j) {
    sum += reach_dist(data, neighbors, i, neighbors[i][j].second);
  }

  return k/sum;
}

double LOF(PointGroup &data, Neighbors &neighbors, int i) {
  double sum = 0;
  int k = neighbors[i].size();

  for(int j=0; j<k; ++j) {
    sum += lrd(data, neighbors, neighbors[i][j].second) / k;
  }

  return sum / lrd(data, neighbors, i);
}

Neighbors KNN(PointGroup &data, int k) {
  int dSize = data.size();
  Neighbors neighbors(dSize);

  for (int i = 0; i < dSize; ++i) {
    priority_queue<pair<double, int> > knn;

    for (int j = 0; j < dSize; ++j) {
      if(i==j) continue;

      double d = dist(data, i, j);
      if(knn.size() <= k) knn.push(make_pair(d,j));
      else {
        if(knn.top().first > d) {
          knn.pop();
          knn.push(make_pair(d,j));
        }
      }
    }

    while (!knn.empty()) {
      neighbors[i].insert(neighbors[i].begin(), knn.top());
      knn.pop();
    }
  }

  return neighbors;
}

int main(int argc, char *argv[]) {
  FILE *fp_in, *fp_out;
	int input;
	int k;
	k= argc==4 ? atoi(argv[3]) : 3;
	int count = 0;

	PointGroup data(D_SIZE, vector<double>(2,0)); // the number of data is 200
  Neighbors neighbors(D_SIZE); // containing the indices of k neighbors and distances to them
  vector<double> lofVal(D_SIZE); // output vector

	//Input//
	fp_in = fopen(argv[1],"r");
	if(fp_in==NULL){
		printf("fail: cannot open the input-file. Change the name of input-file. \n");
		return -1;
	}
	
	while( (input=fscanf(fp_in, "%lf,%lf", &data[count][0], &data[count][1])) != EOF){
		//printf("%lf %lf\n", data[count][0], data[count][1]);
		count++;
	}

  // LOF //////////////////////////////////
  neighbors = KNN(data, k);
  for(int i = 0; i < D_SIZE; ++i) {
    lofVal[i] = LOF(data, neighbors, i);
  }

  //Output//
  fp_out = fopen(argv[2],"w");
	if(fp_out==NULL){
		printf("fail: cannot open the output-file. Change the name of output-file.  \n");
		return -1;
	}

	for(int i=0; i<D_SIZE; ++i){
		fprintf(fp_out, "%lf,%lf,%lf\n", data[i][0], data[i][1], lofVal[i]);
	}

	return 0;
}