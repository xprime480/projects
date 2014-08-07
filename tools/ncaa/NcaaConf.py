#!/usr/bin/env python3

import random

import NcaaTeam

class NcaaConf(object) :
    def __init__(self, conf) :
        self.conf  = conf
        self.teams = []

    def new_team(self, team_id) :
        rating = random.gauss(5, 1)
        team   = NcaaTeam.NcaaTeam(self.conf, team_id, rating)
        self.teams.append(team)

    def get_teams(self) :
        return self.teams[:]

    def __repr__(self) :
        return str(self.teams)
