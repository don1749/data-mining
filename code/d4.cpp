#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#define D_SIZE 200

typedef vector<vector<double> > PointGroup;

void initKCenterPts(PointGroup &data, PointGroup &centerPoints, int k) {
	//pick random k center points from d[] and label them
	srand(time(NULL));
	for(int i=0; i<k; ++i) {
		int randIdx = rand()%D_SIZE;
		centerPoints[i][0] = data[randIdx][0];
		centerPoints[i][1] = data[randIdx][1];
		// cout << centerPoints[i][0] << "," << centerPoints[i][1] << endl;
	}
}

void setLabel(PointGroup &data, PointGroup &centerPts, vector<int> &label) {
	int k = centerPts.size();
	int dSize = data.size();

	for(int i=0; i<dSize; ++i) {
		double x,y;
		x = data[i][0];
		y = data[i][1];
		double minDistSqr = double(1e7);
		
		for(int j=0; j<k; ++j) {
			double distSqr = (x-centerPts[j][0])*(x-centerPts[j][0]) + (y-centerPts[j][1])*(y-centerPts[j][1]);
			if(distSqr-minDistSqr<0) {
				minDistSqr = distSqr;
				label[i] = j;
			}
		}
	}
}

void updateCenter(PointGroup &data, PointGroup &centerPts, vector<int> &label) {
	int k = centerPts.size();
	int dSize = data.size();

	for(int i=0; i<k; ++i) {
		double xSum, ySum;
		int cnt = 0;
		xSum = 0.0;
		ySum = 0.0;

		for(int j=0; j<dSize; ++j) {
			if(label[j] == i) {
				xSum += data[j][0];
				ySum += data[j][1];
				cnt++;
			}
		}

		centerPts[i][0] = xSum/cnt;
		centerPts[i][1] = ySum/cnt;

		cout << centerPts[i][0] << "," << centerPts[i][1] << endl;
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	FILE *fp_in, *fp_out;
	int input;
	int k;
	k=atoi(argv[3]);
	int count = 0;

	PointGroup data(D_SIZE, vector<double>(2,0)); // the number of data is 200
	PointGroup centerPts(k, vector<double>(2,0)); 
	vector<int> label(D_SIZE);
	// flag
	vector<int> curLabel(D_SIZE, k+1); 

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
	
	//k-means//
	initKCenterPts(data, centerPts, k);

	while(!(label == curLabel)) {
		label = curLabel;
		setLabel(data, centerPts, curLabel);
		updateCenter(data, centerPts, curLabel);
	}
	///////////
	
	//Output//
	fp_out = fopen(argv[2],"w");
	if(fp_out==NULL){
		printf("fail: cannot open the output-file. Change the name of output-file.  \n");
		return -1;
	}

	for(int i=0;i<200;i++){
		fprintf(fp_out, "%lf,%lf,%d\n", data[i][0], data[i][1], label[i]);
	}

	return 0;
}
