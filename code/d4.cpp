#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#define D_SIZE 200

typedef vector<vector<double>> PointGroup;

void FindKCenterPts(int k, PointGroup &d, PointGroup &cP) {
	//pick random k center points from d[] and label them
	srand(time(NULL));
	for(int i=0; i<k; ++i) {
		int randIdx = rand()%D_SIZE;
		cP[i][0] = d[randIdx][0];
		cP[i][1] = d[randIdx][1];
		cP[i][2] = i;
	}
}

// void findLabel(int k, double centerPts[][], double d[][], int x, int y) {

// }

// void findCenter(int k, int l[], double **d, double **centerPts) {
// 	double res[2];
// 	res[0] = 0.0;
// 	res[1] = 0.0;
// 	int cnt = 0;

// 	for(int i=0; i<k; i++) {
// 		if(l[i]==k) {
// 			cnt ++;
// 			res[0] += d[i][0];
// 			res[1] += d[i][1];
// 		}
// 	}
// 	res[0] /= cnt;
// 	res[1] /= cnt;
	
// 	centerPts[k][0] = res[0];
// 	centerPts[k][1] = res[1];
// }

int main(int argc, char *argv[])
{
	FILE *fp_in, *fp_out;
	int input;
	int k;
	k=atoi(argv[3]);
	int count = 0;
	PointGroup data(D_SIZE, vector<double>(2,0));// the number of data is 200
	PointGroup centerPts(k, vector<double>(3,0));
	int label[D_SIZE];
	int i=0;

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
	//Init label array
	for (int i=0; i<D_SIZE; i++) {
		label[i] = k+1;
	}

	FindKCenterPts(k, data, centerPts);
	for (int i=0; i<D_SIZE; i++) {
		for (int j=0; j<k; j++) {
			if (data[i][0] == centerPts[j][0] && data[i][1] == centerPts[j][1]) {
				label[i] = centerPts[j][2];
				break;
			}
		}
	}
	
	///////////
	
	//Output//
	fp_out = fopen(argv[2],"w");
	if(fp_out==NULL){
		printf("fail: cannot open the output-file. Change the name of output-file.  \n");
		return -1;
	}


	for(i=0;i<200;i++){
		fprintf(fp_out, "%lf,%lf,%d\n", data[i][0], data[i][1], label[i]);
	}

	for (int i=0; i<k; i++) {
		cout << centerPts[i][0] << centerPts[i][1] << ' ' << centerPts[i][2] << endl;
	}

	return 0;
}
