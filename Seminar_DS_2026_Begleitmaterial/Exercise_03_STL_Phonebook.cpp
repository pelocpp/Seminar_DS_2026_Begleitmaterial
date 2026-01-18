// =====================================================================================
// Exercise_03_STL_Phonebook.cpp
// =====================================================================================

// TBD

// =====================================================================================
// End-of-File
// =====================================================================================

#include <cstddef>
#include <forward_list>
#include <optional>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm> 
#include <iostream>

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
        std::size_t size();
        bool insert(const std::string& first, const std::string& last, std::size_t number);
        bool update(const std::string& first, const std::string& last, std::size_t number);
        std::optional<std::size_t> search(const std::string& first, const std::string& last);
        bool remove(const std::string& first, const std::string& last);
        bool contains(const std::string& first, const std::string& last);
        void print();
    };

    // getter
    std::size_t PhoneBookVector::size()
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

    std::optional<std::size_t> PhoneBookVector::search(const std::string& first, const std::string& last)
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

    bool PhoneBookVector::contains(const std::string& first, const std::string& last)
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

    void PhoneBookVector::print()
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

    static void test_phonebook_with_vector()
    {
        using namespace Exercise_Phonebook_Using_StdVector;

        PhoneBookVector book{};

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
}

namespace Exercise_Phonebook_Using_StdUnorderedMap {

    static void test_phonebook_with_unordered_map()
    {
    }
}

void test_exercises_phonebook()
{
    Exercise_Phonebook_Using_StdVector::test_phonebook_with_vector();
    Exercise_Phonebook_Using_StdUnorderedMap::test_phonebook_with_unordered_map();
}

// =====================================================================================
// End-of-File
// =====================================================================================
