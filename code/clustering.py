# set up kmeans clustering and lof evaluation using python

from sklearn.cluster import KMeans
from sklearn.neighbors import LocalOutlierFactor
# import numpy as np
import csv

def kmeans(file_name, k=2):
  data = []
  label = []

  with open(file_name,'r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
      data.append([float(row[0]), float(row[1])])
      if(len(row)==3):
          label.append(int(row[2]))

    kmeans = KMeans(n_clusters=k, random_state=0).fit(data)

  with open('py_out_' + file_name[:-4] + '_kmeans.csv', 'w') as csvfile:
    writer = csv.writer(csvfile)
    for i in range(len(data)):
        line = data[i] + [kmeans.labels_[i]]
        writer.writerow(line)

input_files = ["crater.csv", "moon.csv", "square.csv", "three_island.csv", "two_island.csv"]

def lof(file_name, k=4):
  data = []
  label = []

  with open(file_name,'r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
      data.append([float(row[0]), float(row[1])])
      if(len(row)==3):
          label.append(int(row[2]))

  LOF = LocalOutlierFactor(n_neighbors=k)
  LOF.fit_predict(data)
  lofVal = -LOF.negative_outlier_factor_
  
  with open('py_out_' + file_name[:-4] + '_lof.csv', 'w') as csvfile:
    writer = csv.writer(csvfile)
    for i in range(len(data)):
        line = data[i] + [lofVal[i]]
        writer.writerow(line)

for file in input_files:
    k=2
    if(file=="three_island.csv"):
        k=3
    kmeans(file, k)
    lof(file)

