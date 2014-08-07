#!/usr/bin/env python3

import random

import NcaaConf

ConfCount   = 10
TeamPerConf = 10

def make_conf(conf) :
    conference = NcaaConf.NcaaConf(conf)
    for team in range(1, 1+TeamPerConf) :
        conference.new_team(team)
    return conference

def make_teams() :
    return [make_conf(conf) for conf in range(1, 1+ConfCount)]

def make_schedule(all_teams, game_count) :
    conf_games     = 2 * (TeamPerConf-1)
    non_conf_games = game_count - conf_games

    season = []

    for game_id in range(1, 1+non_conf_games) :
        while True :
            games = schedule_one_week(all_teams)
            if games :
                season.append(games)
                for t1,t2 in games :
                    t1.add_game(game_id, t2)
                    t2.add_game(game_id, t1)
                break

    conf_sched = [[] for i in range(conf_games)]
    for conf in all_teams :
        sched = schedule_conf(conf)
        for i in range(conf_games) :
            conf_sched[i].extend(sched[i])
    
    season.extend(conf_sched)

    return season


def schedule_one_week(all_teams) :
    games = []
    unscheduled = []
    for conf in all_teams :
        unscheduled.extend(conf.get_teams()[:])

    while True :
        left = len(unscheduled)
        rescheduled = []

        while unscheduled :
            team1,team2 = tuple(random.sample(unscheduled, 2))
            unscheduled.remove(team1)
            unscheduled.remove(team2)

            if team1 in team2.get_opponents() :
                rescheduled.append(team1)
                rescheduled.append(team2)
            else :
                games.append((team1, team2))

            if len(games) > (ConfCount * TeamPerConf / 2) :
                print ("Internal Error: Too Many Games")
                print (games)
                print (unscheduled)
                raise Exception("Internal Error: Too Many Games")

        unscheduled = rescheduled[:]
        if not unscheduled :
            return games

        if len(unscheduled) == left :
            # not making any progress here, start all over
            return []


def schedule_conf(conf) :
    teams     = conf.get_teams()
    num_teams = len(teams)
    teamx = range(1,num_teams)

    sched = []

    for x in range(num_teams-1) :
        games = []

        tempx = [None, 0] + list(teamx[x:]) + list(teamx[:x])
        for x in range(1, 1+int(num_teams/2)) :
            team1 = teams[tempx[ x]]
            team2 = teams[tempx[-x]]
            games.append((team1,team2))
        sched.append(games)

    t = sched[:]
    t.reverse()

    for w in t :
        games = []
        for t1, t2 in w :
            games.append((t2,t1))
        sched.append(games)

    return sched

def play(sched) :
    weeks = len(sched)
    for x in range(weeks) :
        print ("Games for week %d" % (x+1))
        games = sched[x]
        for g in games :
            t1 = g[0]
            t2 = g[1]
            s1 = t1.score()
            s2 = t2.score()
            ot = 0
            while s1 == s2 :
                ot += 1
                s1 += t1.ot_score()
                s2 += t2.ot_score()
            if ot :
                xtra = '(%dOT)' % ot
            else :
                xtra = ''
            print ("%s (%d) at %s (%d) %s" % (t1, s1, t2, s2, xtra))

def main() :
    all_teams = make_teams()
    sched     = make_schedule(all_teams, 30)
    play(sched)

if __name__ == '__main__' :
    main()
