#ifndef  _SOCIAL_NETWORK_H_
#define _SOCIAL_NETWORK_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

class User {
private:
    User() : _age(0), _height(0), _sex(false) {};
    std::string _id;
    std::string _name;
    std::vector<std::string> _friends;
    unsigned char _age;
    unsigned char _height;
    std::vector<std::string> _hobbies;
    bool _sex; // true: male, false: female
public:
    User(std::string name) : User() {
        _name = name;
        _id = name;
        auto end_pos = std::remove(_id.begin(), _id.end(), ' '); // remove spaces
        _id.erase(end_pos, _id.end());
    };

    User(std::string name, unsigned char age, unsigned char height,
        bool sex, std::vector<std::string>& friends,
        std::vector<std::string>& hobbies) : User(name) {
        _age = age;
        _height = height;
        _sex = sex;
        _friends = friends;
        _hobbies = hobbies;
    }

    std::string getName() const { return _name; };
    void setSex(bool sex) { _sex = sex; };
    bool getSex() const { return _sex; };
    void setId(std::string& id) { _id = id; };
    std::string getId() const { return _id; };
    void setAge(unsigned char age) { _age = age; };
    unsigned char getAge() const { return _age; };
    void setHeight(unsigned char height) { _height = height; };
    unsigned char getHeight() const { return _height; };
    void setHobbies(std::vector<std::string>& hobbies) { _hobbies = hobbies; };
    void addHobby(std::string& hobby) { _hobbies.push_back(hobby); };
    std::vector<std::string> getHobbies() const { return _hobbies; };    
    void addFriend(User& frd) {
        if (this == &frd) return;
        auto it = find(_friends.begin(), _friends.end(), frd.getId());
        if (it == _friends.end()) {
            _friends.push_back(frd._id);
            frd._friends.push_back(_id);
        }         
    };
    std::vector<std::string> getFriends() const { return _friends; };
};

typedef std::shared_ptr<User> UserPtr;

class SocialNetwork { 
public:
    void addUser(std::string name);
    void addUser(UserPtr user);
    void deleteUser(std::string id); 
    UserPtr getUser(const std::string& id) const;
    std::vector<UserPtr> searchUserByName(const std::string &name) const;
    std::vector<UserPtr> searchUserByAge(const unsigned char age) const;
    std::vector<UserPtr> searchUserByHobbies(const std::vector<std::string>& hobbies) const;
    std::vector<std::string> getFriendsOfUser(const std::string userId) const;
private:
    std::unordered_map<std::string, UserPtr> _idMapTbl;
    std::unordered_map<std::string, std::vector<UserPtr>> _nameMapTbl;
    std::unordered_map<unsigned char, std::vector<UserPtr>> _ageMapTbl;
};

#endif // _SOCIAL_NETWORK_H_
