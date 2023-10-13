#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database):userz(&user_database),moviez(&movie_database){}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    std::unordered_map<std::string,int> uom;
    if(movie_count<0){
        return vector<MovieAndRank>();
    }
    User* currUser = userz->get_user_from_email(user_email);
    if(currUser == nullptr){
        vector<MovieAndRank> failHolder;
        cout<<"User not found"<<endl;
        return failHolder;
    }
    vector<string> hist = currUser->get_watch_history();
    unordered_set<string> setHist;
    setHist.insert(hist.begin(), hist.end());
    for(string ID: currUser->get_watch_history()){
        Movie* currMovie = moviez->get_movie_from_id(ID);
        vector<string> dirList = currMovie->get_directors();
        vector<string> actList = currMovie->get_actors();
        vector<string> genList = currMovie->get_genres();
        for(string dir: dirList){
            vector<Movie*> moviesWithDirector = moviez->get_movies_with_director(dir);
            for(Movie* m: moviesWithDirector){//for every movie that has the director
                unordered_set<string>::iterator it = setHist.find(m->get_id()); //see if the person has already watched the movie
                if(it == setHist.end()){ //if the user hasn't watched yet
                    uom[m->get_id()] += 20;
                }
                //else then insert it to the map and add 20 points to the score
            }
        }
        for(string act: actList){
            vector<Movie*> moviesWithActor = moviez->get_movies_with_actor(act);
            for(Movie* m: moviesWithActor){
                unordered_set<string>::iterator it = setHist.find(m->get_id());
                if(it == setHist.end()){
                    uom[m->get_id()] += 30;
                    
                }
            }
            
        }
        for(string gen: genList){
            vector<Movie*> moviesWithGenre = moviez->get_movies_with_genre(gen);
            for(Movie* m: moviesWithGenre){
                unordered_set<string>::iterator it = setHist.find(m->get_id());
                if(it == setHist.end()){
                    uom[m->get_id()] += 1;
                }
            }
        }
    }
    vector<sortElem> tobeSorted;
    unordered_map<string,int>::iterator it = uom.begin();
    while(it!=uom.end()){
        string id = it->first;
        string name = (moviez->get_movie_from_id(id))->get_title();
        int score = it->second;
        float rating = (moviez->get_movie_from_id(id))->get_rating();
        sortElem curr(id,name,score,rating);
        tobeSorted.push_back(curr);
        it++;
    }
    
    sort(tobeSorted.begin(),tobeSorted.end(),sortElem::cmpr);
    vector<MovieAndRank> reccs;
    for(int i = 0; i<movie_count; i++){
        if((i+1)>tobeSorted.size()){
            break;
        }
        string movid = tobeSorted[i].movie_id;
        int movscore = tobeSorted[i].movie_score;
        MovieAndRank mov(movid,movscore);
        reccs.push_back(mov);
    }
    return reccs;
    
    
}


//make a serpate unorderd set for watch history
//check if the movie is in watch history
//if not then do the point adding

