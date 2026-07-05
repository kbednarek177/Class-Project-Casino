#pragma once
#include <cstdint>
#include <string>

namespace Security {
    inline std::string hashPassword(const std::string& password) {
        uint64_t hash = 5381;
        for (char c : password) {
            hash = ((hash << 5) + hash) + c;
        }
        return std::to_string(hash);
    }
}

class Person {
    protected:
        std::string name;
        std::string surname;
        int age;

    public:
        Person(const std::string& n, const std::string& s, int a) : name(n), surname(s), age(a) {}
        virtual ~Person() = default;

        std::string getName() const { return name; }
        std::string getSurname() const { return surname; }
        int getAge() const { return age; }
};

class Player : public Person {
    friend class ProfileManager;
    private:
        int id;
        int balance, bet;
        std::string password;

        std::string getPassword() const { return password; }

    public:
        Player(int i, const std::string& n, const std::string& s,
        int a, const std::string& p, int b = 1000, bool hash = false) : Person(n, s, a)
        {
            id = i;
            if(hash){
                password = p;
            }
            else{
                password = Security::hashPassword(p);
            }
            balance = b;
            bet = 0;
        }

        void addWinnings(int num);
        int getBalance() const { return balance; }

        int placeBet();
        int getBet() const { return bet; }
        void resetBet() { bet = 0; }

        bool doubleBet() {
            if (balance >= bet) {
                balance -= bet;
                bet *= 2;       
                return true;
            }
            return false;
        }

        int getId() const { return id; }
        bool isPasswordValid(const std::string& p) const { return Security::hashPassword(p) == password; }
};

class Dealer : public Person {
    private:
        int id;
        static int casino_id;

    public:
        Dealer(const std::string& n, const std::string& s, int a) : Person(n, s, a) 
        {
            casino_id++;
            id = casino_id;
        }

        int getId() const { return id; }
};