/**
 * @file profilemanager.hpp
 * @brief Klasa zarządzająca profilami graczy (zapis/odczyt). Wzorzec Singleton.
 */
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "person.hpp" 

/**
 * @brief Singleton zarządzający bazą graczy w kasynie.
 * Odpowiada za logowanie, rejestrację, usuwanie profili oraz zapisywanie i odczytywanie danych do/z pliku JSON.
 */
class ProfileManager {
    private:
        /** @brief Nazwa pliku z danymi graczy. */
        std::string file;
        /** @brief Wektor przechowujący wszystkich zarejestrowanych graczy w pamięci. */
        std::vector<std::shared_ptr<Player>> activePlayers;

        /**
         * @brief Prywatny konstruktor zapobiegający tworzeniu wielu instancji (Singleton).
         * @param name Nazwa pliku do zapisu/odczytu. Domyślnie "players.json".
         */
        ProfileManager(const std::string& name = "players.json");

    public:
        ProfileManager(const ProfileManager&) = delete;
        ProfileManager& operator=(const ProfileManager&) = delete;  

        /**
         * @brief Pobiera jedyną instancję ProfileManager.
         * @return Referencja do obiektu zarządzającego profilami.
         */
        static ProfileManager& getInstance() {
            static ProfileManager instance; 
            return instance;
        }

        /** @brief Zapisuje listę aktywnych graczy do pliku JSON. */
        void savePlayers();
        
        /** @brief Wczytuje listę graczy z pliku JSON. */
        void loadPlayers(); 
        
        /** @brief Rozpoczyna proces interaktywnego tworzenia nowego profilu gracza. */
        void createProfile();
        
        /**
         * @brief Przeprowadza proces logowania gracza o podanym ID.
         * @param id Identyfikator gracza.
         * @return Wskaźnik na obiekt gracza, jeśli logowanie się powiodło. W przeciwnym razie nullptr.
         */
        std::shared_ptr<Player> loginPlayer(int id);
        
        /**
         * @brief Usuwa profil o podanym ID po potwierdzeniu hasłem.
         * @param id Identyfikator gracza.
         * @param currentPlayer Referencja do wskaźnika obecnie zalogowanego gracza.
         * @return Zwraca true jeśli pomyślnie usunięto, w przeciwnym razie false.
         */
        bool deleteProfile(int id, std::shared_ptr<Player>& currentPlayer);
        
        /** @brief Wyświetla w konsoli listę zarejestrowanych graczy. */
        void showPlayers() const;

        /**
         * @brief Sprawdza, czy podany ciąg znaków składa się wyłącznie z liter.
         * @param n Ciąg znaków do sprawdzenia.
         * @return True jeśli same litery, w przeciwnym razie false.
         */
        bool isAlpha(const std::string& n){
            if (n.empty()) { return false; }
                for (char c : n) {
                    if (!std::isalpha(static_cast<unsigned char>(c))) {
                        return false; 
                    }
            }
            return true;
        }
};