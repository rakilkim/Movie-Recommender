#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>

class UserDatabase;
class MovieDatabase;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
      struct cmp {
          cmp(int s, double r, std::string n, std::string i)
              :score(s), rate(r), name(n), id(i)
          {}
          int score;
          double rate;
          std::string name;
          std::string id;
      };
      const UserDatabase& udb;
      const MovieDatabase& mdb;
      static bool comp(const cmp& i, const cmp& j) {
          if (i.score != j.score)
              return i.score > j.score;
          if (i.rate != j.rate)
              return i.rate > j.rate;
          return i.name < j.name;
      }
};

#endif // RECOMMENDER_INCLUDED
