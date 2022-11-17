import matplotlib.pyplot as plt
import csv

def visualization(file_name, prefix):
    x = []
    y = []
    label = []

    with open(file_name,'r') as csvfile:
        lines = csv.reader(csvfile, delimiter=',')
        for row in lines:
            x.append(float(row[0]))
            y.append(float(row[1]))
            if(len(row)==3):
                label.append(int(row[2]))
    
    plt.Figure()
    if(len(label)==0):
        plt.scatter(x,y)
    else:
        plt.scatter(x,y,c=label)
    plt.xticks(rotation = 25)
    # plt.xlabel('Names')
    # plt.ylabel('Values')
    plt.title(prefix + file_name)
    plt.savefig(file_name[:-4] + '.png')
    plt.show()
    plt.close()

input_files = ["crater.csv", "moon.csv", "square.csv", "three_island.csv", "two_island.csv"]
output_files = ["cpp_out_crater_kmeans.csv", "cpp_out_moon_kmeans.csv", "cpp_out_square_kmeans.csv", "cpp_out_three_island_kmeans.csv", "cpp_out_two_island_kmeans.csv"]

for file in output_files:
    visualization(file, "")
