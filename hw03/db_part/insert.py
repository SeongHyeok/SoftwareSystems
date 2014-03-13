# -*- coding: utf-8 -*-
"""
Created on Mon Mar  3 21:37:39 2014

@author: sim
"""

import sys

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
    data = f.read()
    f.close()
    print "# End reading - %s" % (file_path)

    data = data[data.find("MOVIES LIST"): ]
    lines = data.splitlines()
    # set of (movie, year)
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
                print "Error occured"
                print "Line:", line
                sys.exit(1)
    print "# End parsing"
    return movies

############################################################################
# Functions for actor and actress
############################################################################

"""
Irregular examples for parenthesis...
			Mark(s) (2006)  [Hariff]
$, Steve		E.R. Sluts (2003) (V)  <12>
"""
def extract_actor_line(l):
    """
    """
    actor = ""
    movie = ""
    year = ""
    word = ""
    pos = 1
    try:
        actor = l[0]
        while True:
            if l[pos] != '':
                break
            pos += 1
        word = l[pos]

        pos = 0
        start = 0
        while True:
            pos = word.find('(', start)
            if pos == -1:
                sys.exit(1)
            year = word[pos + 1: pos + 5]
            if year.isdigit() or year == "????":
                movie = word[: pos].strip()
                break
            start += pos + 1
    except:
        print "l    -->", l
        print "word -->", word
        print "pos  -->", pos
        print "actor-->", actor
        print "movie-->", movie
        print "year -->", year
        # print to error log
        return "", "", ""
    return actor, movie, year

"""
$, Claw			"OnCreativity" (2012)  [Himself]

$, Homo			Nykytaiteen museo (1986)  [Himself]  <25>
			Suuri illusioni (1985)  [Guests]  <22>

$, Steve		E.R. Sluts (2003) (V)  <12>

['$, Claw', '', '', '"OnCreativity" (2012)  [Himself]']
['']
['$, Homo', '', '', 'Nykytaiteen museo (1986)  [Himself]  <25>']
['', '', '', 'Suuri illusioni (1985)  [Guests]  <22>']
['']
['$, Steve', '', 'E.R. Sluts (2003) (V)  <12>']
['']
"""

def read_actors_and_movies(file_path, need_cut):
    print "# Start reading - %s" % (file_path)
    f = file(file_path, "rt")
    #data = f.read(15000)
    #data = f.read(300000)
    #data = f.read(3000000)
    #data = f.read(30000000)
    data = f.read()
    f.close()
    print "# End reading - %s / size: %d" % (file_path, len(data))

    if need_cut:
        key = '----			------'
        data = data[data.find(key, 0, 15000) + len(key):]
    print "# Start splitting"
    lines = data.splitlines()
    print "# End splitting"
    # set of (actor, movie, year)

    result = set()

    print "# Start parsing"
    l = len(lines)
    i = 0
    prev_actor = ""

    for i in range(l):
        if i == l: break
        print "Parsing - [%d%% %d/%d]" % ((float(i) / l) * 100, i + 1, l)
        #sys.exit()
        line = lines[i]
        sl = line.split('\t')
        if len(sl) > 1 and ''.join(sl) != '':
            actor, movie, year = extract_actor_line(sl)
            if actor == "":
                if movie == "" and year == "":
                    continue
                actor = prev_actor
            else:
                prev_actor = actor

            """if movie[0] == "\"":
                print "Movie: [%s]" % (movie)
                print "Year: [%s]" % (year)
                print "Line:", line
                print "Splited List: ", sl
                sys.exit(1)"""
            if len(year) != 4:
                print "Error occured"
                print "Year: [%s]" % (year)
                print "Line:", line
                print "Splited List: ", sl
                sys.exit(1)
            result.add((actor, movie, year))
    print "# End parsing"

    #print result
    return result

############################################################################
# Functions for DB
############################################################################

import MySQLdb

db = MySQLdb.connect(host="localhost",
                     user="root",
                     passwd="sim",
                     db="softsys")
cur = db.cursor()

def execute_query(q):
    try:
        cur.execute(q)
    except:
        print "Query -->", q
        sys.exit(1)

def insert_actors_and_movies(data_set):import pygame
from pygame.locals import *
import random
import math
import time
    q = "INSERT INTO `actor_tbl` (actor_name, movie_name, year) VALUES ('%s', '%s', '%s')"
    print "# Start querying"
    data = list(data_set)
    l = len(data)
    try:
        for i in range(l):
            print "Querying - [%d / %d]" % (i + 1, l)
            actor, movie, year = data[i]
            sql = q % (MySQLdb.escape_string(actor),
                       MySQLdb.escape_string(movie),
                       MySQLdb.escape_string(year))
            execute_query(sql)
    except:
        db.rollback()
    db.commit()
    print "# End querying"

if __name__ == "__main__":
    # movie_set is a set of (movie, year)
    #movie_set = read_movies("./raw_data_from_imdb/movies.list")

    # actor_set is a set of (actor, movie, year)
    # I split original list file into several ones because of memory error.

    #actor_set = read_actors_and_movies("./raw_data_from_imdb/actors.list.1", True)
    #insert_actors_and_movies(actor_set)
    #actor_set = read_actors_and_movies("./raw_data_from_imdb/actors.list.2", False)
    #insert_actors_and_movies(actor_set)
    #actor_set = read_actors_and_movies("./raw_data_from_imdb/actors.list.3", False)
    #insert_actors_and_movies(actor_set)
    actor_set = read_actors_and_movies("./raw_data_from_imdb/actors.list.4", False)
    insert_actors_and_movies(actor_set)
    actor_set = read_actors_and_movies("./raw_data_from_imdb/actors.list.5", False)
    insert_actors_and_movies(actor_set)

    actress_set = read_actors_and_movies("./raw_data_from_imdb/actresses.list.1", True)
    insert_actors_and_movies(actress_set)
    actress_set = read_actors_and_movies("./raw_data_from_imdb/actresses.list.2", False)
    insert_actors_and_movies(actress_set)
    actress_set = read_actors_and_movies("./raw_data_from_imdb/actresses.list.3", False)
    insert_actors_and_movies(actress_set)

    db.close()