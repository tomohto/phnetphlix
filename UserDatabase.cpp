#include "UserDatabase.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

UserDatabase::UserDatabase()
{
    loadedBefore = false;
}

bool UserDatabase::load(const std::string& filename)
{
    if(loadedBefore){ //if it was already loaded then return false
        std::cout<<"This database was already loaded"<<std::endl;
        return false;
    }
    std::ifstream infile(filename);
    if(!infile){
        std::cout<<"Could not successfully load file: "<<filename<<std::endl;
        return false;
    }else{
        int loadCount = 0;
        std::string name;
        std::string email;
        int movieCount;
        
        for(;;){
            if(!getline(infile, name)){
                break;
            }
            getline(infile, email);
            infile >> movieCount;
            infile.ignore(10000,'\n');
            
            std::vector<std::string> watchHist;
            for(int i = 0; i<movieCount; i++){
                std::string currMovie;
                getline(infile,currMovie);
                watchHist.push_back(currMovie);
            }
            multmap.insert(email,User(name,email,watchHist));
            loadCount++;
            infile.ignore(10000,'\n');
        }
        infile.close();
        loadedBefore = true;
        return true;
    }
    
}

User* UserDatabase::get_user_from_email(const std::string& email) const
{
    TreeMultimap<std::string, User>::Iterator searcher = multmap.find(email);
    if(searcher.is_valid()) return &(searcher.get_value());
    else return nullptr;
}

