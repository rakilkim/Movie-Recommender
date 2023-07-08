#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

void findMatches(const Recommender& r,
	const MovieDatabase& md,
	const string& user_email,
	int num_recommendations) {
	// get up to ten movie recommendations for the user
	vector<MovieAndRank> recommendations =
		r.recommend_movies(user_email, num_recommendations);
	if (recommendations.empty())
		cout << "We found no movies to recommend :(.\n";
	else {
		for (int i = 0; i < recommendations.size(); i++) {
			const MovieAndRank& mr = recommendations[i];
			Movie* m = md.get_movie_from_id(mr.movie_id);
			cout << i + 1 << ". " << m->get_title() << " ("
				<< m->get_release_year() << ")\n Rating: "
				<< m->get_rating() << "\n Compatibility Score: "
				<< mr.compatibility_score << "\n";
		}
	}
}

int main()
{
	MovieDatabase mdb;
	UserDatabase udb;
	if (!udb.load(USER_DATAFILE) || !mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
	/*
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
			cout << "Found " << u->get_full_name() << endl;
	} */
	Recommender r = Recommender(udb, mdb);
	for (;;)
	{ 
		cout << "Enter email: ";
		string email;
		getline(cin, email);
		cout << "Enter count: ";
		string count;
		getline(cin, count);
		findMatches(r, mdb, email, stoi(count)); 
		/*
		cout << "Enter movie id, director, actor, or genre (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		
		Movie* m = mdb.get_movie_from_id(email);
		vector<Movie*> mm = mdb.get_movies_with_director(email);
		vector<Movie*> mm1 = mdb.get_movies_with_actor(email);
		vector<Movie*> mm2 = mdb.get_movies_with_genre(email);
		if (mm != vector<Movie*>()) {
			for (int i = 0; i < mm.size(); i++)
				cout << (mm)[i]->get_title() << endl;
			for (int i = 0; i < mm.size(); i++)
				cout << (mm)[i]->get_id() << endl;
			for (int i = 0; i < mm.size(); i++)
				cout << (mm)[i]->get_release_year() << endl;
			for (int i = 0; i < mm.size(); i++)
				cout << (mm)[i]->get_rating() << endl;
			for (int i = 0; i < mm.size(); i++) {
				for (int j = 0; j < mm[i]->get_directors().size(); j++)
					cout << (mm)[i]->get_directors()[j] << endl;
			}
			for (int i = 0; i < mm.size(); i++) {
				for (int j = 0; j < mm[i]->get_actors().size(); j++)
					cout << (mm)[i]->get_actors()[j] << endl;
			}
			for (int i = 0; i < mm.size(); i++) {
				for (int j = 0; j < mm[i]->get_genres().size(); j++)
					cout << (mm)[i]->get_genres()[j] << endl;
			}
		}
		else if (mm1 != vector<Movie*>()) {
			for (int i = 0; i < mm1.size(); i++)
				cout << (mm1)[i]->get_title() << endl;
			for (int i = 0; i < mm1.size(); i++)
				cout << (mm1)[i]->get_id() << endl;
			for (int i = 0; i < mm1.size(); i++)
				cout << (mm1)[i]->get_release_year() << endl;
			for (int i = 0; i < mm1.size(); i++)
				cout << (mm1)[i]->get_rating() << endl;
			for (int i = 0; i < mm1.size(); i++) {
				for (int j = 0; j < mm1[i]->get_directors().size(); j++)
					cout << (mm1)[i]->get_directors()[j] << endl;
			}
			for (int i = 0; i < mm1.size(); i++) {
				for (int j = 0; j < mm1[i]->get_actors().size(); j++)
					cout << (mm1)[i]->get_actors()[j] << endl;
			}
			for (int i = 0; i < mm1.size(); i++) {
				for (int j = 0; j < mm1[i]->get_genres().size(); j++)
					cout << (mm1)[i]->get_genres()[j] << endl;
			}
		}
		else if (mm2 != vector<Movie*>()) {
			for (int i = 0; i < mm2.size(); i++)
				cout << (mm2)[i]->get_title() << endl;
			for (int i = 0; i < mm2.size(); i++)
				cout << (mm2)[i]->get_id() << endl;
			for (int i = 0; i < mm2.size(); i++)
				cout << (mm2)[i]->get_release_year() << endl;
			for (int i = 0; i < mm2.size(); i++)
				cout << (mm2)[i]->get_rating() << endl;
			for (int i = 0; i < mm2.size(); i++) {
				for (int j = 0; j < mm2[i]->get_directors().size(); j++)
					cout << (mm2)[i]->get_directors()[j] << endl;
			}
			for (int i = 0; i < mm2.size(); i++) {
				for (int j = 0; j < mm2[i]->get_actors().size(); j++)
					cout << (mm2)[i]->get_actors()[j] << endl;
			}
			for (int i = 0; i < mm2.size(); i++) {
				for (int j = 0; j < mm2[i]->get_genres().size(); j++)
					cout << (mm2)[i]->get_genres()[j] << endl;
			}
		}
		else
			cout << "null";
		if (m == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
			cout << "Found " << m->get_id() << m->get_directors()[0] << endl; */
	}
}
