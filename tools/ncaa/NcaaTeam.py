#!/usr/bin/env python3

import random

class NcaaTeam(object) :
    def __init__(self, conf, team, rating) :
        self.conf     = conf
        self.team     = team
        self.rating   = rating
        self.record   = []
        self.schedule = []

    def get_opponents(self) :
        return [x[1] for x in self.schedule]

    def add_game(self, id, opp) :
        self.schedule.append((id, opp))

    def score(self) :
        return max(0, int(random.gauss(15*self.rating, 10)))

    def ot_score(self) :
        return max(0, int(random.gauss(2*self.rating, 4)))

    def __repr__(self) :
        return str('{%d / %d}' % (self.conf, self.team))

