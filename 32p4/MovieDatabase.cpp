#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

MovieDatabase::MovieDatabase()
    :called(false)
{
}

bool MovieDatabase::load(const string& filename)
{
    if (!called) {
        string id = "";
        string title = "";
        string year = "";
        vector<string> directors;
        vector<string> actors;
        vector<string> genres;
        float rating;
        ifstream infile(filename);
        if (!infile)
            return false;
        int line = 1;
        std::string s;
        while (getline(infile, s))
        {
            if (line == 1) {
                id = s;
                line++;
            }
            else if (line == 2) {
                title = s;
                line++;
            }
            else if (line == 3) {
                year = s;
                line++;
            }
            else if (line == 4) {
                string director = "";
                for (int i = 0; i < s.size(); i++) {    //go through each character and add when ',' is hit
                    if (s.at(i) == ',') {
                        directors.push_back(director);
                        director = "";
                    }
                    else
                        director += s.at(i);
                }
                directors.push_back(director);  //last one doesn't end with ',' so just add
                line++;
            }
            else if (line == 5) {
                string actor = "";
                for (int i = 0; i < s.size(); i++) {
                    if (s.at(i) == ',') {
                        actors.push_back(actor);
                        actor = "";
                    }
                    else
                        actor += s.at(i);
                }
                actors.push_back(actor);
                line++;
            }
            else if (line == 6) {
                string genre = "";
                for (int i = 0; i < s.size(); i++) {
                    if (s.at(i) == ',') {
                        genres.push_back(genre);
                        genre = "";
                    }
                    else
                        genre += s.at(i);
                }
                genres.push_back(genre);
                line++;
            }
            else if (line == 7) {
                rating = stof(s);     //change string to float
                line++;
            }
            else {
                string lower_id = "";
                for (int i = 0; i < id.size(); i++)     //need to add all lowercase for key for case insensitive search
                    lower_id += tolower(id.at(i));
                m_id.insert(lower_id, Movie(id, title, year, directors, actors, genres, rating));

                for (int i = 0; i < directors.size(); i++) {
                    string lower_director = "";
                    for (int j = 0; j < directors[i].size(); j++)
                        lower_director += tolower(directors[i].at(j));
                    m_director.insert(lower_director, Movie(id, title, year, directors, actors, genres, rating));
                }
                for (int i = 0; i < actors.size(); i++) {
                    string lower_actor = "";
                    for (int j = 0; j < actors[i].size(); j++)
                        lower_actor += tolower(actors[i].at(j));
                    m_actor.insert(lower_actor, Movie(id, title, year, directors, actors, genres, rating));
                }
                for (int i = 0; i < genres.size(); i++) {
                    string lower_genre = "";
                    for (int j = 0; j < genres[i].size(); j++)
                        lower_genre += tolower(genres[i].at(j));
                    m_genre.insert(lower_genre, Movie(id, title, year, directors, actors, genres, rating));
                }

                for (vector<string>::iterator i = directors.begin(); i != directors.end();)     //reset all vectors to get ready for new movie
                    i = directors.erase(i);
                for (vector<string>::iterator i = actors.begin(); i != actors.end();)
                    i = actors.erase(i);
                for (vector<string>::iterator i = genres.begin(); i != genres.end();)
                    i = genres.erase(i);
                line = 1;
            }
        }
        if (line != 1) {        //if file doesn't end with empty line
            string lower_id = "";
            for (int i = 0; i < id.size(); i++)
                lower_id += tolower(id.at(i));
            m_id.insert(lower_id, Movie(id, title, year, directors, actors, genres, rating));

            for (int i = 0; i < directors.size(); i++) {
                string lower_director = "";
                for (int j = 0; j < directors[i].size(); j++)
                    lower_director += tolower(directors[i].at(j));
                m_director.insert(lower_director, Movie(id, title, year, directors, actors, genres, rating));
            }
            for (int i = 0; i < actors.size(); i++) {
                string lower_actor = "";
                for (int j = 0; j < actors[i].size(); j++)
                    lower_actor += tolower(actors[i].at(j));
                m_actor.insert(lower_actor, Movie(id, title, year, directors, actors, genres, rating));
            }
            for (int i = 0; i < genres.size(); i++) {
                string lower_genre = "";
                for (int j = 0; j < genres[i].size(); j++)
                    lower_genre += tolower(genres[i].at(j));
                m_genre.insert(lower_genre, Movie(id, title, year, directors, actors, genres, rating));
            }
        }
            
    }
    else
        return false;
    called = true;
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string lower_id = "";       //case insensitive search
    for (int i = 0; i < id.size(); i++)
        lower_id += tolower(id.at(i));
    if (!m_id.find(lower_id).is_valid()) {
        return nullptr;
    }
    return &m_id.find(lower_id).get_value();

}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string lower = "";
    for (int i = 0; i < director.size(); i++)
        lower += tolower(director.at(i));
    TreeMultimap<string, Movie>::Iterator it = m_director.find(lower);
    if (!it.is_valid()) {
        return vector<Movie*>();
    }
    vector<Movie*> movies;
    while (it.is_valid()) {
        movies.push_back(&it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string lower = "";
    for (int i = 0; i < actor.size(); i++)
        lower += tolower(actor.at(i));
    TreeMultimap<string, Movie>::Iterator it = m_actor.find(lower);
    if (!it.is_valid()) {
        return vector<Movie*>();
    }
    vector<Movie*> movies;
    while (it.is_valid()) {
        movies.push_back(&it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string lower = "";
    for (int i = 0; i < genre.size(); i++)
        lower += tolower(genre.at(i));
    TreeMultimap<string, Movie>::Iterator it = m_genre.find(lower);
    if (!it.is_valid()) {
        return vector<Movie*>();
    }
    vector<Movie*> movies;
    while (it.is_valid()) {
        movies.push_back(&it.get_value());
        it.advance();
    }
    return movies;
}
