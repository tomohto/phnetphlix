#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

MovieDatabase::MovieDatabase()
{
}

bool MovieDatabase::load(const std::string& filename)
{
    if(loadedBefore){
        return false;
    }else{
        std::ifstream infile(filename);
        if(!infile){
            std::cout<<"couldnt load file"<<std::endl;
            return false;
        }else{
            for(;;){
                std::string ID;
                std::string name;
                std::string year;
                std::vector<std::string> directors;
                std::vector<std::string> actors;
                std::vector<std::string> genres;
                float rating;
                getline(infile,ID);
                getline(infile,name);
                getline(infile,year);
                
                std::string currLine;
                
                getline(infile,currLine);//push the directors
                std::istringstream dirList(currLine);
                std::string currItem;
                while(getline(dirList,currItem,',')){
                    directors.push_back(currItem);
                }
                
                getline(infile,currLine);//push the actors
                std::istringstream actList(currLine);
                while(getline(actList,currItem,',')){
                    actors.push_back(currItem);
                }
                
                
                getline(infile,currLine);//push the genres
                std::istringstream genList(currLine);
                while(getline(genList,currItem,',')){
                    genres.push_back(currItem);
                }
                
                infile >> rating;//get the rating
                infile.ignore(10000,'\n');
                
                byID.insert(ID,Movie(ID,name,year,directors,actors,genres,rating));
                
                for(int i = 0; i<directors.size();i++){
                    byDir.insert(directors[i], Movie(ID,name,year,directors,actors,genres,rating));
                }
                for(int i = 0; i<actors.size();i++){
                    byAct.insert(actors[i], Movie(ID,name,year,directors,actors,genres,rating));
                }
                for(int i = 0; i<genres.size();i++){
                    byGen.insert(genres[i], Movie(ID,name,year,directors,actors,genres,rating));
                }
                if(!getline(infile, ID)){
                    break;
                }
            }
        }
        loadedBefore = true;
        return true;
    }
}

Movie* MovieDatabase::get_movie_from_id(const std::string& id) const
{
    TreeMultimap<std::string,Movie>::Iterator searcher = byID.find(id);
    if(searcher.is_valid()) return &(searcher.get_value());
    else return nullptr;
    
}

std::vector<Movie*> MovieDatabase::get_movies_with_director(const std::string& director) const
{
    std::vector<Movie*> dirMovies;
    TreeMultimap<std::string,Movie>::Iterator searcher = byDir.find(director);
    while(searcher.is_valid()){
        dirMovies.push_back(&(searcher.get_value()));
        searcher.advance();
    }
    return dirMovies; // Replace this line with correct code.
}

std::vector<Movie*> MovieDatabase::get_movies_with_actor(const std::string& actor) const
{
    std::vector<Movie*> actMovies;
    TreeMultimap<std::string,Movie>::Iterator searcher = byAct.find(actor);
    while(searcher.is_valid()){
        actMovies.push_back(&(searcher.get_value()));
        searcher.advance();
    }
    return actMovies;
}

std::vector<Movie*> MovieDatabase::get_movies_with_genre(const std::string& genre) const
{
    std::vector<Movie*> genMovies;
    TreeMultimap<std::string,Movie>::Iterator searcher = byGen.find(genre);
    while(searcher.is_valid()){
        genMovies.push_back(&(searcher.get_value()));
        searcher.advance();
    }
    return genMovies;
}
