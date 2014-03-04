# -*- coding: utf-8 -*-
"""
Created on Mon Mar  3 21:37:39 2014

@author: sim
"""

############################################################################
# Functions for movie
############################################################################

def check_movie_line(line):
    if line.count('"') == 2 and line.count('(') >= 1 and line.count(')') >= 1:
        return True
    return False
def extract_movie_line(line):
    l = line.split('"')
    movie = l[1]
    year = l[2].split('(')[1][:4]
    return movie, year

def read_movies(file_path):
    print "# Start reading - %s" % (file_path)
    f = file(file_path, "rt")
    #data = f.read()
    data = f.read()
    f.close()
    print "# End reading - %s" % (file_path)

    data = data[data.find("MOVIES LIST"): ]
    lines = data.splitlines()
    movies = set()
    print "# Start parsing"
    for line in lines:
        """
        "$40 a Day" (2002) {Cooperstown (#1.17)}		2002
        """
        if check_movie_line(line):
            movie, year = extract_movie_line(line)
            movies.add((movie, year))
            if len(year) != 4:
                print line
    print "# End parsing"
    return movies

if __name__ == "__main__":
    read_movies("./raw_data_from_imdb/movies.list")