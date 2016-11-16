#!/usr/bin/env python3

import os
import random

from csvfileio import *

################################################################
#
def args() :
    """Parse and return the command line parameters."""

    import argparse
    import sys

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--input",
        help="CSV with weekly probabilities"
    )

    try :
        return parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)

##################################################################
#
class Debugging(Exception) :
    def __init__(self, text) :
        self.text = text

    def get_text(self) :
        return self.text

##################################################################
#
class TeamIndexer(object) :
    def __init__(self) :
        self.indexes = []

    def get_count(self) :
        return len(self.indexes)

    def get_index(self, value) :
        if value not in self.indexes :
            self.indexes.append(value)
        return self.indexes.index(value)

    def get_value(self, index) :
        if 0 <= index < len(self.indexes) :
            return self.indexes[index]
        raise Debugging('No team at index {0}'.format(index))

    def dump(self) :
        print self.indexes

##################################################################
#
class WeeklyManager(object) :
    def __init__(self) :
        self.probs = {}

    def set_team_prob(self, team_index, prob) :
        self.probs[team_index] = prob
            

    def get_team_prob(self, team_index) :
        if self.probs.has_key(team_index) :
            return self.probs[team_index]
        return 0.0

    def dump(self) :
        print self.probs

##################################################################
#
class SeasonManager(object) :
    def __init__(self) :
        self.weeks = [None] * 17
        for idx in range(17) :
            self.weeks[idx] = WeeklyManager()

        self.teams = TeamIndexer()

    def insert(self, week, team, prob) :
        idx = self.teams.get_index(team)
        if 0 < week <= 17 :
            self.weeks[week-1].set_team_prob(idx, prob)
        else :
            raise Debugging('week index ({0} given) out of range'.format(week))

    def get_team_count(self) :
        return self.teams.get_count()

    def get_prob(self, week, team_idx) :
        if 0 <= week < 17 :
            return self.weeks[week].get_team_prob(team_idx)
        raise Debugging('week index ({0} given) out of range'.format(week))

    def decode_team(self, idx) :
        return self.teams.get_value(idx)

    def dump(self) :
        for idx in range(17) :
            print 'Week', idx+1
            self.weeks[idx].dump()
        self.teams.dump()

##################################################################
#

class PoolChoice(object) :
    __util_indexes = range(0)

    def __init__(self, season, parent=None) :
        self.season = season
        if parent :
            self.__create_from(parent)
        else :
            self.__generate()

    def set_team_count(count) :
        PoolChoice.__util_indexes = range(count)

    def get_fitness(self) :
        return self.fitness

    def get_genotype(self) :
        return self.genotype()

    def make_child(self) :
        return PoolChoice(season, self)

    def decode(self) :
        return [self.fitness,
                [(w+1, self.season.decode_team(t)) 
                 for w,t in zip(range(17), self.genotype) ] ]
            
    def __create_from(self, parent) :
        original = parent.genotype[:]
        replacements = [e for e in PoolChoice.__util_indexes if e not in original]
        self.fitness = 0.0
        while self.fitness < 0.00001 :
            idx = random.randrange(0,17)
            new = random.sample(replacements, 1)[0]
            self.genotype = original[:]
            self.genotype[idx] = new
            self.fitness = self.__evaluate()

    def __generate(self) :
        self.fitness = 0.0 
        while self.fitness < .00001 :
            random.shuffle(PoolChoice.__util_indexes)
            self.genotype = PoolChoice.__util_indexes[:17]
            self.fitness = self.__evaluate()

    def __evaluate(self) :
        def product(x,y) :
            return x*y
        augmented = zip(range(17), self.genotype)
        all_ps = [self.season.get_prob(w, t) for w,t in augmented]
        v = reduce(product, all_ps)

        return v

##################################################################
#
class PoolCalc(object) :

    ############################################################
    #
    def __init__(self, config, size) :
        self.size = size
        self.season = SeasonManager()
        self.__read_data(config)
        tmp = PoolChoice(self.season)
        tmp.set_team_count(self.season.get_team_count())
        #self.season.dump()
        pool = self.__init_pool()
        self.pool = self.__sort_pool(pool)
        
    ############################################################
    #
    def iterate(self, count) :
        for _ in range(count) :
            num_to_keep = int(0.1 * self.size)
            pool = self.__evolve_pool(num_to_keep)
            self.pool = self.__sort_pool(pool)

    ############################################################
    #
    def show_pool(self, how_many) :
        for i in range(how_many) :
            print self.pool[i].decode()

    ############################################################
    #
    def __read_data(self, config) :
        
        with CsvFileIo(config.input, False) as rdr :
            hdrs = rdr.fieldnames
            for row in rdr :
                week = int(row[hdrs[0]])
                team = row[hdrs[1]]
                pct  = float(row[hdrs[2]])
                self.season.insert(week, team, pct)


    ############################################################
    #
    def __init_pool(self) :
        pool = [None] * self.size
        for idx in range(self.size) :
            pool[idx] = PoolChoice(self.season)

        return pool

    ############################################################
    #
    def __evolve_pool(self, keepsize) :
        if keepsize < self.size :
            pool = self.pool[:keepsize]
            pool.extend([None] * (self.size - keepsize))
            for idx in range(keepsize, self.size) :
                pool[idx] = PoolChoice(self.season, self.pool[idx%keepsize])
            return pool
        return self.pool[:]

    ############################################################
    #
    def __sort_pool(self, pool) :
        def sorter(x,y) :
            return cmp(x.get_fitness(), y.get_fitness())

        return sorted(pool, cmp=sorter, reverse=True)

################################################################
#
if '__main__' == __name__ :
    """Do the computation."""

    cfg = args()
    try :
        pc = PoolCalc(cfg, 1000)
        pc.iterate(100)
        pc.show_pool(2)
    except Debugging as exc :
        import traceback
        print exc.get_text()
        traceback.print_exc()
