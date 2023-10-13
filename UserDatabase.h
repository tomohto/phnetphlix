#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED
#include "treemm.h"
#include <string>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User> multmap;
    bool loadedBefore;
};

#endif // USERDATABASE_INCLUDED
