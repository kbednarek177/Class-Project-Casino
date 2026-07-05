/**
 * @file person.hpp
 * @brief Definicje klas bazowych i dziedziczących dla uczestników gry (Gracz, Krupier) oraz narzędzia bezpieczeństwa.
 */
#pragma once
#include <cstdint>
#include <string>

/**
 * @brief Przestrzeń nazw przechowująca narzędzia bezpieczeństwa.
 */
namespace Security {
    /**
     * @brief Haszuje hasło prostym algorytmem djb2.
     * @param password Hasło jawne w formie tekstu.
     * @return Zhaszowana postać hasła w formie łańcucha znaków.
     */
    inline std::string hashPassword(const std::string& password) {
        uint64_t hash = 5381;
        for (char c : password) {
            hash = ((hash << 5) + hash) + c;
        }
        return std::to_string(hash);
    }
}

/**
 * @brief Podstawowa klasa reprezentująca osobę uczestniczącą w kasynie.
 */
class Person {
    protected:
        std::string name;     /**< @brief Imię osoby. */
        std::string surname;  /**< @brief Nazwisko osoby. */
        int age;              /**< @brief Wiek osoby. */

    public:
        /**
         * @brief Konstruktor dla klasy Person.
         * @param n Imię.
         * @param s Nazwisko.
         * @param a Wiek.
         */
        Person(const std::string& n, const std::string& s, int a) : name(n), surname(s), age(a) {}
        
        virtual ~Person() = default;

        std::string getName() const { return name; }
        std::string getSurname() const { return surname; }
        int getAge() const { return age; }
};

/**
 * @brief Klasa reprezentująca zarejestrowanego gracza w kasynie.
 * Dziedziczy po Person. Przechowuje informacje o stanie konta i zabezpieczeniach.
 */
class Player : public Person {
    friend class ProfileManager;
    private:
        int id;             /**< @brief Unikalny identyfikator gracza. */
        int balance;        /**< @brief Stan konta gracza (żetony). */
        int bet;            /**< @brief Aktualnie postawiony zakład przez gracza. */
        std::string password; /**< @brief Hasło gracza (zazwyczaj zahaszowane). */

        /** @brief Zwraca hasło gracza. Używane wyłącznie przez zaprzyjaźniony ProfileManager. */
        std::string getPassword() const { return password; }

    public:
        /**
         * @brief Konstruktor gracza.
         * @param i ID.
         * @param n Imię.
         * @param s Nazwisko.
         * @param a Wiek.
         * @param p Hasło (jawne lub hash).
         * @param b Początkowy stan konta (domyślnie 1000).
         * @param hash Jeśli true, oznacza, że podane hasło p jest już zhaszowane.
         */
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

        /**
         * @brief Dodaje wygraną do salda gracza (nie może przekroczyć 10 000 000).
         * @param num Wartość wygranej.
         */
        void addWinnings(int num);
        
        int getBalance() const { return balance; }

        /**
         * @brief Pobiera od gracza decyzję o kwocie zakładu z konsoli.
         * @return Kwota postawionego zakładu.
         */
        int placeBet();
        
        int getBet() const { return bet; }
        
        /** @brief Zeruje aktualny zakład. */
        void resetBet() { bet = 0; }

        /**
         * @brief Podwaja aktualny zakład, o ile gracz ma wystarczające środki.
         * @return True jeśli podwojenie się udało, w przeciwnym razie false.
         */
        bool doubleBet() {
            if (balance >= bet) {
                balance -= bet;
                bet *= 2;       
                return true;
            }
            return false;
        }

        int getId() const { return id; }
        
        /**
         * @brief Sprawdza poprawność hasła podanego przez użytkownika z haszem.
         * @param p Hasło jawne wprowadzone przez użytkownika.
         * @return True jeśli hasło jest prawidłowe.
         */
        bool isPasswordValid(const std::string& p) const { return Security::hashPassword(p) == password; }
};

/**
 * @brief Klasa reprezentująca krupiera prowadzącego gry.
 * Dziedziczy po Person.
 */
class Dealer : public Person {
    private:
        int id;                     /**< @brief ID krupiera. */
        static int casino_id;       /**< @brief Licznik krupierów do automatycznego generowania ID. */

    public:
        /**
         * @brief Konstruktor krupiera.
         * @param n Imię.
         * @param s Nazwisko.
         * @param a Wiek.
         */
        Dealer(const std::string& n, const std::string& s, int a) : Person(n, s, a) 
        {
            casino_id++;
            id = casino_id;
        }

        int getId() const { return id; }
};