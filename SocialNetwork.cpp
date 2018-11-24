#include "SocialNetwork.h"

using namespace std;

void SocialNetwork::addUser(string name)
{
    UserPtr newUser = (UserPtr) new User(name);
    addUser(newUser);
}

void SocialNetwork::addUser(UserPtr user)
{
    if (user == nullptr) return;

    // create unique id
    unsigned long index = 0;
    for (;;) {
        char buff[256] = { 0 };
        string id = user->getId();
        if (index) {
            sprintf_s(buff, "%lu", index);
            id.append(buff);
        }
        if (_idMapTbl.find(id) == _idMapTbl.end()) {
            user->setId(id);
            break;
        }
        index++;
    }

    // update _idMapTbl
    _idMapTbl[user->getId()] = user;

    // update _nameMapTbl
    if (_nameMapTbl.find(user->getName()) != _nameMapTbl.end()) {
        _nameMapTbl[user->getName()].push_back(user);
    }
    else {
        vector<UserPtr> v;
        v.push_back(user);
        _nameMapTbl[user->getName()] = v;
    }

    // update _ageMapTbl
    if (_ageMapTbl.find(user->getAge()) != _ageMapTbl.end()) {
        _ageMapTbl[user->getAge()].push_back(user);
    }
    else {
        vector<UserPtr> v;
        v.push_back(user);
        _ageMapTbl[user->getAge()] = v;
    }
}

void SocialNetwork::deleteUser(string id)
{
    UserPtr delUser = getUser(id);
    if (delUser == nullptr) return;

    // delete in _idMapTbl
    auto idMapit = _idMapTbl.find(id);
    if (idMapit != _idMapTbl.end())
        _idMapTbl.erase(idMapit);

    // delete in _nameMapTbl
    auto nameMapit = _nameMapTbl.find(delUser->getName());
    if (nameMapit != _nameMapTbl.end() && nameMapit->second.size() > 0) {
        auto it = nameMapit->second.begin();
        for (; it != nameMapit->second.end(); it++) {
            if ((*it)->getId() == id) {
                nameMapit->second.erase(it);
                break;
            }
        }
    }

    // delete in _ageMapTbl
    auto ageMapit = _ageMapTbl.find(delUser->getAge());
    if (ageMapit != _ageMapTbl.end() && ageMapit->second.size() > 0) {
        auto it = ageMapit->second.begin();
        for (; it != ageMapit->second.end(); it++) {
            if ((*it)->getId() == id) {
                ageMapit->second.erase(it);
                break;
            }
        }
    }
}

UserPtr SocialNetwork::getUser(const string& id) const
{
    auto it = _idMapTbl.find(id);
    if (it != _idMapTbl.end())
        return it->second;
    else
        return nullptr;
}

vector<UserPtr> SocialNetwork::searchUserByName(const string &name) const
{
    auto it = _nameMapTbl.find(name);
    if (it != _nameMapTbl.end())
        return it->second;
    else
        return vector<UserPtr>();
}

vector<UserPtr> SocialNetwork::searchUserByAge(const unsigned char age) const
{
    auto it = _ageMapTbl.find(age);
    if (it != _ageMapTbl.end())
        return it->second;
    else
        return vector<UserPtr>();
}

vector<UserPtr> SocialNetwork::searchUserByHobbies(const vector<string>& hobbies) const
{
    vector<UserPtr> ret;
    vector<string> searchHobbies = hobbies;
    sort(searchHobbies.begin(), searchHobbies.end());
    for (auto it = _idMapTbl.begin(); it != _idMapTbl.end(); ++it) {
        vector<string> userHobbies = it->second->getHobbies();        
        sort(userHobbies.begin(), userHobbies.end());
        if (includes(userHobbies.begin(), userHobbies.end(), searchHobbies.begin(), searchHobbies.end()))
            ret.push_back(it->second);
    }
    return ret;
}

vector<string> SocialNetwork::getFriendsOfUser(const string userId) const
{
    vector<string> ret;
    UserPtr user = getUser(userId);
    if (user != nullptr) ret = user->getFriends();
    return ret;
}