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
typedef vector<vector<int> > Neighbors;

double dist(PointGroup &data, int i, int j) {
  // Return the distance between the two points ith and jth in data
  return sqrt((data[i][0]-data[j][0])*(data[i][0]-data[j][0]) + (data[i][1]-data[j][1])*(data[i][1]-data[j][1]));
}

vector<int> regionQuery(PointGroup &data, int i, double eps) {
  vector<int> neighbors;
  for(int j = 0; j < data.size(); ++j) {
    if(dist(data, i, j) <= eps) neighbors.push_back(j);
  }

  return neighbors;
}

void expandCluster(PointGroup &data, int i, Neighbors &neighbors, vector<int> &label, vector<bool> &visited, int C, double eps, int minPts) {
  label[i] = C;
  for(int j=0; j < neighbors[i].size(); ++j) {
    int q = neighbors[i][j];
    if(!visited[q]) {
      visited[q] = true;
      vector<int> newNeighbors = regionQuery(data, q, eps);

      if(newNeighbors.size() >= minPts)
        neighbors[i].insert(neighbors[i].end(), newNeighbors.begin(), newNeighbors.end());
    }

    if(label[q] == -1) label[q] = C;
  }
}

void DBSCAN(PointGroup &data, Neighbors &neighbors, vector<int> &label, vector<bool> &visited, double eps, int minPts) {
  int C = 0; // cluster count
  for(int i = 0; i < data.size(); ++i) {
    if(visited[i]) continue;
    
    visited[i] = true;
    neighbors[i] = regionQuery(data, i, eps);

    if (neighbors[i].size() < minPts) label[i] = 0; //noise
    else {
      C++;
      expandCluster(data, i, neighbors, label, visited, C, eps, minPts);
    }
  }
}

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);

	FILE *fp_in, *fp_out;
	int input;
  double eps = 1.5;
  int minPts = 4;
	int count = 0;

	PointGroup data(D_SIZE, vector<double>(2,0)); // the number of data is 200
  Neighbors neighbors(D_SIZE);
	vector<int> label(D_SIZE,-1);
  vector<bool> visited(D_SIZE, false);

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
	
	//DBSCAN//
  DBSCAN(data, neighbors, label, visited, eps, minPts);
	///////////
	
	//Output//
	fp_out = fopen(argv[2],"w");
	if(fp_out==NULL){
		printf("fail: cannot open the output-file. Change the name of output-file.  \n");
		return -1;
	}

	for(int i=0;i<D_SIZE;i++){
		fprintf(fp_out, "%lf,%lf,%d\n", data[i][0], data[i][1], label[i]);
	}

	return 0;
}
