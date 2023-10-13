#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED
#include "Movie.h"
#include "User.h"
#include "MovieDatabase.h"
#include "UserDatabase.h"
#include "treemm.h"
#include <string>
#include <vector>
#include <unordered_map>

class UserDatabase;
class MovieDatabase;

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
    struct sortElem{
        sortElem(const std::string& id, const std::string& name, int score, float rating): movie_id(id),movie_name(name),movie_score(score),movie_rating(rating){}
        std::string movie_id;
        std::string movie_name;
        int movie_score;
        float movie_rating;
        static bool cmpr(const sortElem& m1, const sortElem& m2){
            //if the compatability score is higher then it is higher
            if(m1.movie_score > m2.movie_score){
                return true;
            }else if(m1.movie_score < m2.movie_score){
                return false;
            }else if(m1.movie_score == m2.movie_score){//if compatability is the same then judge off 5 star rating
                if(m1.movie_rating > m2.movie_rating){
                    return true;
                }else if(m1.movie_rating < m2.movie_rating){
                    return false;
                }else if(m1.movie_rating == m2.movie_rating){//if 5 star rating is the same then jduge off movies name is alphabetically ascending order A comes before B
                    return m1.movie_name < m2.movie_name;
                }
            }
            return false;
        }
    };
    
    const UserDatabase* userz;
    const MovieDatabase* moviez;
};

#endif // RECOMMENDER_INCLUDED
