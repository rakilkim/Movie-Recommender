#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>

#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
    :udb(user_database), mdb(movie_database)
{
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    unordered_map<string, int> mov;     //store movie id and compatibility score
    unordered_map<string, int> dir;     //store director and how much each will increase the score
    unordered_map<string, int> act;     //store actor and how much each will increase the score
    unordered_map<string, int> gen;     //store genre and how much each will increase the score
    vector<string> h = udb.get_user_from_email(user_email)->get_watch_history();
    for (vector<string>::iterator it = h.begin(); it != h.end(); it++) {    //give -1 score to movies already watched
        mov[*it] = -1;
    }
    vector<MovieAndRank> mar;

    for (vector<string>::iterator it = h.begin(); it != h.end(); it++) {    //for every movie's director, actor, and genre, add how much each will increase the score
        vector<string> d = mdb.get_movie_from_id(*it)->get_directors();
        for (vector<string>::iterator q = d.begin(); q != d.end(); q++) {
            dir[*q] += 20;
        }
        d = mdb.get_movie_from_id(*it)->get_actors();
        for (vector<string>::iterator q = d.begin(); q != d.end(); q++) {
            act[*q] += 30;
        }
        d = mdb.get_movie_from_id(*it)->get_genres();
        for (vector<string>::iterator q = d.begin(); q != d.end(); q++) {
            gen[*q] += 1;
        }
    }

    unordered_map <string, int>::iterator iter = dir.begin();   
    for (iter; iter != dir.end(); iter++) {
        vector<Movie*> m = mdb.get_movies_with_director(iter->first);
        for (vector<Movie*>::iterator i = m.begin(); i != m.end(); i++) {   //for every movie not on watch history add to hash table
            if (mov[(*i)->get_id()] != -1)
                mov[(*i)->get_id()] += iter->second;
        }
    }
    iter = act.begin();
    for (iter; iter != act.end(); iter++) {
        vector<Movie*> m = mdb.get_movies_with_actor(iter->first);
        for (vector<Movie*>::iterator i = m.begin(); i != m.end(); i++) {
            if (mov[(*i)->get_id()] != -1)
                mov[(*i)->get_id()] += iter->second;
        }
    }
    iter = gen.begin();
    for (iter; iter != gen.end(); iter++) {
        vector<Movie*> m = mdb.get_movies_with_genre(iter->first);
        for (vector<Movie*>::iterator i = m.begin(); i != m.end(); i++) {
            if (mov[(*i)->get_id()] != -1)
                mov[(*i)->get_id()] += iter->second;
        }
    }
    vector<cmp> c;

    for (unordered_map<string, int>::iterator it = mov.begin(); it != mov.end(); it++) {    
        Movie* m = mdb.get_movie_from_id(it->first);
        if (it->second != -1) {
            c.push_back(cmp(it->second, m->get_rating(), m->get_title(), it->first));   //add to vector of struct that holds elements necessary to rank the rankings
        }
    }

    sort(c.begin(), c.end(), &comp);        

    for (vector<cmp>::iterator i = c.begin(); i != c.end(); i++) {      
        if (movie_count == 0)
            return mar;
        mar.push_back(MovieAndRank(i->id, i->score));   
        movie_count--;
    }
    return mar;
}
