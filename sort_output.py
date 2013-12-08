#code to sort output

def readfile(filename):
    from operator import itemgetter
    try:
        f = open(filename)
        content = []
        for line in f:
            temp = line.strip().split(",")
            temp = (temp[0], float(temp[1]))
            content.append(tuple(temp))
        content.sort(key=itemgetter(1), reverse=True)
        f.close()
        return content
    except IOError as e:
        print "Unable to open " + filename
    

def sort_all_files(in_directory, out_directory):
    import os
    for root, dirs, files in os.walk(in_directory):
        for file in files:
            content = readfile(in_directory+"/"+file)
            print out_directory+file
            f = open(out_directory+file, "w")
            for line in content:
                temp = line[0] + "," + str(line[1]) +"\n"
                f.write(temp)
            f.close()

if __name__ == "__main__":
    in_directory = "./data/output/"
    out_directory = "./data/output/sorted/"
    
    sort_all_files(in_directory, out_directory)

    
    
