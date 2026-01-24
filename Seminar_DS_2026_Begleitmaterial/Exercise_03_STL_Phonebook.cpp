// =====================================================================================
// Exercise_03_STL_Phonebook.cpp
// =====================================================================================

#include <algorithm> 
#include <cstddef>
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

        Entry entry{ first, last, number };
        m_entries.push_back(entry);
        return true;
    }

    bool PhoneBookVector::update(const std::string& first, const std::string& last, std::size_t number)
    {
        auto pos = std::find_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const auto& entry) {
                const auto& [entryFirst, entrylast, entryNumber] = entry;
                return entryFirst == first && entrylast == last;
            }
        );

        if (pos == m_entries.end()) {
            return false;
        }
        else {
            auto& entry = *pos;
            std::get<2>(entry) = number;
            return true;
        }

        return true;
    }

    std::optional<std::size_t> PhoneBookVector::search(const std::string& first, const std::string& last) const
    {
        auto pos = std::find_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const auto& entry) {
                const auto& [entryFirst, entrylast, entryNumber] = entry;
                return entryFirst == first && entrylast == last;
            }
        );

        if (pos == m_entries.end()) {
            return std::nullopt;
        }
        else {
            const Entry& entry = *pos;
            std::optional<std::size_t> result{ std::get<2>(entry) };
            return result;
        }
    }

    bool PhoneBookVector::contains(const std::string& first, const std::string& last) const
    {
        auto pos = std::find_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const auto& entry) {
                const auto& [entryFirst, entrylast, entryNumber] = entry;
                return entryFirst == first && entrylast == last;
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
                const auto& [entryFirst, entrylast, entryNumber] = entry;
                return entryFirst == first && entrylast == last;
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
                const auto& [entryFirst, entryLast, entryNumber] = entry;
                std::cout << entryFirst << " " << entryLast << ": " << entryNumber << std::endl;
            }
        );
    }
}

namespace Exercise_Phonebook_Using_StdUnordererMap {

    //class PhoneBookMap : public IPhoneBook
    //{
    //private:
    //    std::unordered_map<std::string, std::size_t> m_map;

    //public:
    //    // public interface
    //    std::size_t size() override;
    //    bool insert(const std::string& first, const std::string& last, std::size_t number) override;
    //    bool update(const std::string& first, const std::string& last, std::size_t number) override;
    //    bool search(const std::string& first, const std::string& last, std::size_t& number) override;
    //    bool remove(const std::string& first, const std::string& last) override;
    //    bool contains(const std::string& first, const std::string& last) override;
    //    std::forward_list<std::string> getNames() override;
    //    std::string toString() override;
    //    void print() override;

    //private:
    //    // helper methods
    //    static std::pair<std::string, std::string> getNameFromKey(const std::string&);
    //    static std::string getKeyFromName(const std::string&, const std::string&);

    //    static void printEntry(const std::pair<std::string, std::size_t>&);
    //    static std::string pairToString(const std::pair<std::string, std::size_t>&);
    //    static std::string append(const std::string&, const std::pair<std::string, std::size_t>&);
    //};

    class PhoneBookMap
    {
    private:
        // member type
      //  using Entry = std::pair<std::string, std::size_t>;

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

    std::size_t PhoneBookMap::size() const
    {
        return m_entries.size();
    }

    bool PhoneBookMap::insert(const std::string& first, const std::string& last, std::size_t number)
    {
        const auto& key{ getKeyFromName(first, last) };

        std::pair<std::string, std::size_t> entry{ key, number };

        // std::pair<std::unordered_map<std::string, std::size_t>::iterator, bool> result = m_entries.insert(entry);
        auto [pos, succeeded] { m_entries.insert(entry) };

        // returns a bool value set to true if and only if the insertion took place
        // bool insertionSucceeded = result.second;

        return succeeded;
    }

    bool PhoneBookMap::update(const std::string& first, const std::string& last, std::size_t number)
    {
        const auto& key{ getKeyFromName(first, last) };

        auto pos = m_entries.find(key);

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

        std::unordered_map<std::string, std::size_t>::const_iterator pos = m_entries.find(key);

        if (pos == m_entries.end()) {

            std::cout << first << " " << last << " not found!" << std::endl;
            return std::nullopt;
        }
        else {
            std::pair<std::string, std::size_t> result = *pos;
           // number = result.second;
            return result.second;
        }
    }

    bool PhoneBookMap::contains(const std::string& first, const std::string& last) const
    {
        const auto& key{ getKeyFromName(first, last) };

        auto pos = m_entries.find(key);

        return pos != m_entries.end();
    }

    bool PhoneBookMap::remove(const std::string& first, const std::string& last)
    {
        const auto& key{ getKeyFromName(first, last) };

        auto numErased = m_entries.erase(key);

        return numErased == 1;
    }


    // ---------------------------------------------------------------------------

    //void PhoneBookMap::printEntry(const std::pair<std::string, std::size_t>& entry)
    //{
    //    std::string key = entry.first;
    //    std::pair<std::string, std::string> fullName = getNameFromKey(key);
    //    std::size_t number = entry.second;
    //    std::cout << fullName.first << " " << fullName.second << ": " << number << std::endl;
    //}

    void PhoneBookMap::print() const
    {
        std::for_each(
            m_entries.begin(),
            m_entries.end(),
            [] (const auto& entry) {

                const auto& [key, name] = entry;

                // auto !!!
                std::pair<std::string, std::string> fullName = getNameFromKey(key);

                std::cout << fullName.first << " " << fullName.second << ": " << key << std::endl;
            }
        );
    }

    // ---------------------------------------------------------------------------

    std::pair<std::string, std::string> PhoneBookMap::getNameFromKey(const std::string& key)
    {
        std::size_t pos = key.find("_");

        std::string first = key.substr(0, pos);
        std::string last = key.substr(pos + 1);

        return std::pair<std::string, std::string>(first, last);
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
