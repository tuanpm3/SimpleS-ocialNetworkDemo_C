// BMW-SocialNetwork.cpp : Defines the entry point for the console application.
//

#include "SocialNetwork.h"
#include <assert.h>

using namespace std;

template<typename T>
bool compareVector(vector<T> v1, vector<T> v2)
{
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

// UT : void addUser(UserPtr user);
void TEST1()
{
    SocialNetwork sn;    

    // 
    UserPtr user1 = (UserPtr) new User("minh tuan");
    user1->setSex(true);
    user1->setAge(32);
    vector<string> hb1 = { "hb1", "hb2"};
    user1->setHobbies(hb1);

    UserPtr user2 = (UserPtr) new User("minh tuan");
    user2->setSex(true);
    user2->setAge(20);
    vector<string> hb2 = { "hb2", "hb3" };
    user2->setHobbies(hb2);

    UserPtr user3 = (UserPtr)new User("ngoc trinh");
    user3->setSex(false);
    user3->setAge(25);
    vector<string> hb3 = { "hb4", "hb5s" };
    user3->setHobbies(hb3);

    sn.addUser(user1);
    sn.addUser(user2);
    sn.addUser(user3);

    assert(sn.getUser("minhtuan") == user1);
    assert(sn.getUser("minhtuan1") == user2);
    assert(sn.getUser("ngoctrinh") == user3);
    assert(sn.getUser("notfound") == nullptr);
}

// UT : void addUser(std::string& name);
void TEST2()
{
    SocialNetwork sn;

    sn.addUser("nguyen van a");
    sn.addUser("nguyen van b");
    sn.addUser("pham minh tuan");
    assert(sn.getUser("nguyenvana")->getName() == "nguyen van a");
    assert(sn.getUser("nguyenvanb")->getName() == "nguyen van b");
    assert(sn.getUser("phamminhtuan")->getName() == "pham minh tuan");
    assert(sn.getUser("notfound") == nullptr);
}

// UT : deleteUser()
void TEST3()
{
    SocialNetwork sn;

    sn.addUser("nguyen van a");
    sn.addUser("nguyen van b");
    sn.addUser("pham minh tuan");    
    assert(sn.getUser("nguyenvana")->getName() == "nguyen van a");
    assert(sn.getUser("nguyenvanb")->getName() == "nguyen van b");
    assert(sn.getUser("phamminhtuan")->getName() == "pham minh tuan");
    sn.deleteUser("phamminhtuan");
    assert(sn.getUser("phamminhtuan") == nullptr);
}

// UT : searchUserByName()
void TEST4()
{
    SocialNetwork sn;

    sn.addUser("nguyen van a");
    sn.addUser("nguyen van b");
    sn.addUser("nguyen van b");
    sn.addUser("pham minh tuan");
    sn.addUser("pham minh tuan");
    sn.addUser("pham minh tuan");

    assert(sn.searchUserByName("nguyen van a").size() == 1);
    assert(sn.searchUserByName("nguyen van b").size() == 2);
    assert(sn.searchUserByName("pham minh tuan").size() == 3);
    assert(sn.searchUserByName("not exist name").size() == 0);
}

// UT : searchUserByAge()
void TEST5()
{
    SocialNetwork sn;

    // 
    UserPtr user1 = (UserPtr) new User("user1");
    user1->setAge(32);
    UserPtr user2 = (UserPtr) new User("user2");
    user2->setAge(20);
    UserPtr user3 = (UserPtr) new User("user3");
    user3->setAge(20);
    UserPtr user4 = (UserPtr) new User("user4");
    user4->setAge(25);
    UserPtr user5 = (UserPtr) new User("user5");
    user5->setAge(25);
    UserPtr user6 = (UserPtr) new User("user6");
    user6->setAge(25);
    sn.addUser(user1);
    sn.addUser(user2);
    sn.addUser(user3);
    sn.addUser(user4);
    sn.addUser(user5);
    sn.addUser(user6);
    assert(sn.searchUserByAge(32).size() == 1);
    assert(sn.searchUserByAge(20).size() == 2);
    assert(sn.searchUserByAge(25).size() == 3);
    assert(sn.searchUserByAge(27).size() == 0);
}

// UT : searchUserByHobbies()
void TEST6()
{
    SocialNetwork sn;

    // 
    UserPtr user1 = (UserPtr) new User("user1");
    user1->setAge(32);
    user1->setHobbies(vector<string>({ "hb1", "hb2" }));

    UserPtr user2 = (UserPtr) new User("user2");
    user2->setAge(20);
    user2->setHobbies(vector<string>({ "hb1", "hb2", "hb3" }));

    UserPtr user3 = (UserPtr) new User("user3");
    user3->setAge(20);
    user3->setHobbies(vector<string>({ "hb1", "hb3" }));

    UserPtr user4 = (UserPtr) new User("user4");
    user4->setAge(25);
    user4->setHobbies(vector<string>({ "hb4"}));

    UserPtr user5 = (UserPtr) new User("user5");
    user5->setAge(25);
    user5->setHobbies(vector<string>({ "hb1", "hb2", "hb3" }));
        
    sn.addUser(user1);
    sn.addUser(user2);
    sn.addUser(user3);
    sn.addUser(user4);
    sn.addUser(user5);

    assert(sn.searchUserByHobbies(vector<string>({ "hb1", "hb2"})).size() == 3);
    assert(sn.searchUserByHobbies(vector<string>({ "hb1", "hb3" })).size() == 3);
    assert(sn.searchUserByHobbies(vector<string>({ "hb4"})).size() == 1);
    assert((sn.searchUserByHobbies(vector<string>({ "hb4" })))[0]->getName() == "user4");
    assert(sn.searchUserByHobbies(vector<string>({ "hb1", "hb2", "hb3" })).size() == 2);
}

// UT : getFriendsOfUser()
void TEST7()
{
    SocialNetwork sn;

    sn.addUser("nguyen van a");
    sn.addUser("nguyen van b");
    sn.addUser("nguyen van c");
    sn.addUser("nguyen van d");
    sn.addUser("nguyen van d");

    sn.getUser("nguyenvana")->addFriend(*(sn.getUser("nguyenvanb")));
    sn.getUser("nguyenvana")->addFriend(*(sn.getUser("nguyenvanc")));
    sn.getUser("nguyenvana")->addFriend(*(sn.getUser("nguyenvand1")));
    sn.getUser("nguyenvand1")->addFriend(*(sn.getUser("nguyenvand")));

    vector<string> expectFriends1 = {"nguyenvanb", "nguyenvanc", "nguyenvand1"};
    assert(compareVector(sn.getFriendsOfUser("nguyenvana"), expectFriends1));

    vector<string> expectFriends2 = { "nguyenvana", "nguyenvand"};
    assert(compareVector(sn.getFriendsOfUser("nguyenvand1"), expectFriends2));
}

int main()
{
    cout << "START UT" << endl;
    TEST1();
    TEST2();
    TEST3();
    TEST4();
    TEST5();
    TEST6();
    TEST7();
    cout << "OK" << endl;
    return 0;
}

