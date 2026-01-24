// =====================================================================================
// Exercise_03_STL_Phonebook.cpp
// =====================================================================================

#include <algorithm> 
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Exercise_Phonebook_Using_StdVector {

    class PhoneBookVector
    {
    private:
        // member type
        using Entry = std::tuple<std::string, std::string, std::size_t>;

        // member data
        std::vector<Entry> m_entries;

    public:
        // public interface
        std::size_t size() const;
        bool insert(const std::string& first, const std::string& last, std::size_t number);
        bool update(const std::string& first, const std::string& last, std::size_t number);
        std::optional<std::size_t> search(const std::string& first, const std::string& last) const;
        bool remove(const std::string& first, const std::string& last);
        bool contains(const std::string& first, const std::string& last) const;
        void print() const;
    };

    // getter
    std::size_t PhoneBookVector::size() const
    {
        return m_entries.size();
    }

    // public interface
    bool PhoneBookVector::insert(const std::string& first, const std::string& last, std::size_t number)
    {
        if (contains(first, last)) {
            return false;
        }

        auto entry = Entry{ first, last, number };
        m_entries.push_back(entry);
        return true;
    }

    bool PhoneBookVector::update(const std::string& first, const std::string& last, std::size_t number)
    {
        auto pos = std::find_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const auto& entry) {
                const auto& [_first, _last, _number] = entry;
                return _first == first && _last == last;
            }
        );

        if (pos == m_entries.end()) {
            return false;
        }
        else {
            auto& entry{ *pos };
            std::get<2>(entry) = number;
            return true;
        }
    }

    std::optional<std::size_t> PhoneBookVector::search(const std::string& first, const std::string& last) const
    {
        auto pos = std::find_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const auto& entry) {
                const auto& [_first, _last, _number] = entry;
                return _first == first && _last == last;
            }
        );

        if (pos == m_entries.end()) {
            return std::nullopt;
        }
        else {
            const auto& entry{ *pos };
            auto number{ std::get<2>(entry) };
            return number;
        }
    }

    bool PhoneBookVector::contains(const std::string& first, const std::string& last) const
    {
        auto pos = std::find_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const auto& entry) {
                const auto& [_first, _last, _number] = entry;
                return _first == first && _last == last;
            }
        );

        return pos != m_entries.end();
    }

    bool PhoneBookVector::remove(const std::string& first, const std::string& last)
    {
        auto pos = std::find_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const auto& entry) {
                const auto& [_first, _last, _number] = entry;
                return _first == first && _last == last;
            }
        );

        if (pos == m_entries.end()) {
            return false;
        }
        else {
            m_entries.erase(pos);
            return true;
        }
    }

    void PhoneBookVector::print() const
    {
        std::for_each(
            m_entries.begin(),
            m_entries.end(),
            [](auto const& entry) {
                const auto& [first, last, number] = entry;
                std::cout << first << " " << last << ": " << number << std::endl;
            }
        );
    }
}

namespace Exercise_Phonebook_Using_StdUnordererMap {

    class PhoneBookMap
    {
    private:
        // member data
        std::unordered_map<std::string, std::size_t> m_entries;

    public:
        // public interface
        std::size_t size() const;
        bool insert(const std::string& first, const std::string& last, std::size_t number);
        bool update(const std::string& first, const std::string& last, std::size_t number);
        std::optional<std::size_t> search(const std::string& first, const std::string& last) const;
        bool remove(const std::string& first, const std::string& last);
        bool contains(const std::string& first, const std::string& last) const;
        void print() const;

    private:
        // helper methods
        static std::pair<std::string, std::string> getNameFromKey(const std::string&);
        static std::string getKeyFromName(const std::string&, const std::string&);
    };

    // getter
    std::size_t PhoneBookMap::size() const
    {
        return m_entries.size();
    }

    // public interface
    bool PhoneBookMap::insert(const std::string& first, const std::string& last, std::size_t number)
    {
        const auto& key{ getKeyFromName(first, last) };

        auto entry{ std::pair<std::string, std::size_t>{ key, number } };

        auto [pos, succeeded] { m_entries.insert(entry) };

        // returns a bool value set to true if and only if the insertion took place
        return succeeded;
    }

    bool PhoneBookMap::update(const std::string& first, const std::string& last, std::size_t number)
    {
        const auto& key{ getKeyFromName(first, last) };

        auto pos{ m_entries.find(key) };

        if (pos == m_entries.end()) {
            return false;
        }
        else {
            (*pos).second = number;
            return true;
        }
    }

    std::optional<std::size_t> PhoneBookMap::search(const std::string& first, const std::string& last) const
    {
        const auto& key{ getKeyFromName(first, last) };

        auto pos{ m_entries.find(key) };

        if (pos == m_entries.end()) {

            std::cout << first << " " << last << " not found!" << std::endl;
            return std::nullopt;
        }
        else {
            const auto& [key, number] {*pos};
            return number;
        }
    }

    bool PhoneBookMap::contains(const std::string& first, const std::string& last) const
    {
        const auto& key{ getKeyFromName(first, last) };

        auto pos{ m_entries.find(key) };

        return pos != m_entries.end();
    }

    bool PhoneBookMap::remove(const std::string& first, const std::string& last)
    {
        const auto& key{ getKeyFromName(first, last) };

        auto numErased{ m_entries.erase(key) };

        return numErased == 1;
    }

    void PhoneBookMap::print() const
    {
        std::for_each(
            m_entries.begin(),
            m_entries.end(),
            [] (const auto& entry) {
                const auto& [key, number] = entry;
                const auto& [first, last] { getNameFromKey(key) };
                std::cout << first << " " << last << ": " << number << std::endl;
            }
        );
    }

    // helper methods
    std::pair<std::string, std::string> PhoneBookMap::getNameFromKey(const std::string& key)
    {
        auto pos{ key.find("_") };
        const auto& first{ key.substr(0, pos) };
        const auto& last{ key.substr(pos + 1) };

        return { first, last };
    }

    std::string PhoneBookMap::getKeyFromName(const std::string& first, const std::string& last)
    {
        return first + "_" + last;   // "Hubert", "Mueller" ==> "Hubert_Mueller"
    }
}

static void test_phonebook()
{
    using namespace Exercise_Phonebook_Using_StdVector;
    using namespace Exercise_Phonebook_Using_StdUnordererMap;

    //using PhoneBook = PhoneBookVector;
    using PhoneBook = PhoneBookMap;

    PhoneBook book{};

    // testing insert
    book.insert("Franz", "Schneider", 8483);
    book.insert("Hans", "Mueller", 5326);
    book.insert("Sepp", "Meier", 7561);
    book.insert("Anton", "Huber", 4899);
    book.print();

    // testing invalid insertion
    bool succeeded{ book.insert("Franz", "Schneider", 4321) };
    if (!succeeded) {
        std::cout << "Franz Schneider already in Phonebook!" << std::endl;
    }

    // testing 'update'
    std::cout << "Updating phone number of Franz Schneider:" << std::endl;
    succeeded = book.update("Franz", "Schneider", 1234);
    book.print();

    // testing 'remove'
    std::cout << "Removing Anton Huber:" << std::endl;
    succeeded = book.remove("Anton", "Huber");
    book.print();

    // testing 'contains'
    bool found{ book.contains("Sepp", "Meier") };
    std::cout << "Found Sepp Meier: " << std::boolalpha << found << std::endl;
    found = book.contains("Otto", "Meier");
    std::cout << "Found Otto Meier: " << found << std::endl;

    // testing 'search'
    std::optional<std::size_t> numberMeier{ book.search("Sepp", "Meier") };
    if (numberMeier.has_value()) {
        std::cout << "Hans Meier: " << numberMeier.value() << std::endl;
    }

    std::cout << std::endl;
}

void test_exercises_phonebook()
{
    test_phonebook();
}

// =====================================================================================
// End-of-File
// =====================================================================================
