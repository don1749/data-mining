import matplotlib.pyplot as plt
import csv
  
x = []
y = []
label = []

file_name = input("Input file name: ")

with open(file_name,'r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        x.append(float(row[0]))
        y.append(float(row[1]))
        label.append(int(row[2]))
  
plt.scatter(x,y,c=label)
# plt.xticks(rotation = 25)
# plt.xlabel('Names')
# plt.ylabel('Values')
# plt.title('Patients Blood Pressure Report', fontsize = 20)
  
plt.show()