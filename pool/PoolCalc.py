#!/usr/bin/env python3

import os
import unittest

from csvfileio import *

##################################################################
#
class PoolChoice(object) :
    def __init__(self) :
        self.win_pct = 1.0
        self.current = []

    def get_win_pct(self) :
        return self.win_pct

    def get_current_teams(self) :
        return self.current

    def append(self, team, prob) :
        self.win_pct = self.win_pct * prob
        self.current.append(team)

    def clone(self) :
        pc = PoolChoice()
        pc.win_pct = self.win_pct
        pc.current = self.current[:]
        return pc

##################################################################
#
class PoolCalc(object) :

    ############################################################
    #
    def __init__(self) :
        with CsvFileIo('PoolCalc.csv', False) as rdr :
            self.hdrs = rdr.fieldnames
            self.data = {}
            for r in rdr :
                self.insert(r)

    ############################################################
    #
    def insert(self, row) :
        week = int(row[self.hdrs[0]])
        if not self.data.has_key(week) :
            self.data[week] = {}
        weekly = self.data[week]
        team = row[self.hdrs[1]]
        pct  = float(row[self.hdrs[2]])
        weekly[team] = pct

    ############################################################
    #
    def compute(self, depth) :
        self.best_config = self.compute_initial_threshold()
        self.threshold = self.best_config.get_win_pct()
        if depth == 1 :
            return self.best_config

        weeks = sorted(self.data.keys())
        starter = PoolChoice()
        pc_data = [starter]
        
        while pc_data :
            current = pc_data.pop()

            week = weeks[len(current.get_current_teams())]
            all = self.get_all_for_week(week, current)
            for p,t in reversed(all[:depth]) :
                next = current.clone()
                next.append(t, p)
                if next.get_win_pct() > self.threshold :
                    if week == weeks[-1] :
                        self.threshold = next.get_win_pct()
                        self.best_config = next
                    else :
                        pc_data.append(next)

            
        
        return self.best_config.clone()

    ############################################################
    #
    def compute_initial_threshold(self) :
        pc = PoolChoice()

        weeks = sorted(self.data.keys())
        for week in weeks :
            all = self.get_all_for_week(week, pc)
            prob, team = all[0]
            pc.append(team, prob)

        return pc

    ############################################################
    #
    def get_all_for_week(self, week, pc) :
        raw = [(p, t) for t,p in self.data[week].items() if t not in pc.get_current_teams()]
        return sorted(raw, reverse=True)

################################################################
#
if '__main__' == __name__ :
    """Do the computation."""

    pc = PoolCalc()
    ans = pc.compute(2)
    print ans.get_win_pct()
    print zip(range(1,100), ans.get_current_teams())
