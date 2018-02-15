#include "dnai/models/user.h"

namespace dnai {
    namespace models {

       User::User(): QObject(nullptr)
       {

       }

       User::~User()
       {

       }

       QString User::name() const
       {
           return m_name;
       }

       void User::setName(const QString &name)
       {
           m_name = name;
       }

       QString User::profile_url() const
       {
           return m_profile_url;
       }

       void User::setProfile_url(const QString &profile_url)
       {
           m_profile_url = profile_url;
       }
    }
}
