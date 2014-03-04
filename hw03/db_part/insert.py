# -*- coding: utf-8 -*-
"""
Created on Mon Mar  3 21:37:39 2014

@author: sim
"""

def read_movies(file_path):
    data = []
    print "# Start reading - %s" % (file_path)
    f = file(file_path, "rt")
    #data = f.read()
    data = f.read(40960)
    f.close()
    print "# End reading - %s" % (file_path)

    data = data[data.find("MOVIES LIST"): ]
    lines = data.splitlines()
    movies = set()
    for line in lines:
        l = line.split(")")
        if len(l) > 1:
            l = l[0].split('"')
            movie = l[1]
            year = l[2][l[2].find('(') + 1: ]
            movies.add((movie, year))
    print movies

if __name__ == "__main__":
    read_movies("./raw_data_from_imdb/movies.list")