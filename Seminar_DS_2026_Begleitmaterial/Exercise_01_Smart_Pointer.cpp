// =====================================================================================
// Exercise_01_Smart_Pointer.cpp
// =====================================================================================

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <cstddef>
#include <iostream>
#include <memory>

namespace Exercise_Smart_Pointer {

    // =============================================================
    // MyString implementation using std::shared_ptr

    // Note:
    //     This is a theoretical implementation of the task.
    //     In practice, there is exactly one owner of the string within the class.
    //     Therefore, the class `std: :unique_ptr` would be the appropriate implementation method.

    // Note the side effects of both implementations:
    // 
    //     The Rule of Zero could be applied to the `MyStringSP` class.
    //     However, the resulting behavior of the `MyStringSP` class is incorrect,
    //     because copies of `MyStringSP` objects are not real copies (shallow-copy behavior)!
    // 
    //     The Rule of Zero is not applicable to the `MyStringUP` class,
    //     because attempting to copy or assign `MyStringUP` objects results in error messages.
    //     The copy constructor and the assignment operator must be explicitly implemented
    //     (with deep-copy behavior).
    // 
    //     In both implementations, a destructor can be omitted.
    //     The destructor of a `std::shared_ptr` or a `std::unique_ptr` object
    //     is automatically called as being a child object of a parent object in both cases.

    class MyStringSP
    {
    private:
        std::shared_ptr<char[]> m_string;
        std::size_t             m_length;

    public:
        // default c'tor
        MyStringSP() : m_length{} {}

        // user defined c'tor
        MyStringSP(const char* string)
        {
            m_length = std::strlen(string);
            m_string = std::make_shared<char[]>(m_length + 1);
            std::memcpy(m_string.get(), string, m_length + 1);  // incl. copying '\0'
        }

        // no destructor necessary

        // public interface
        void print()
        {
            if (m_string.get() == nullptr) {
                std::cout << "<null>" << std::endl;
            }
            else {
                std::cout << m_string.get() << std::endl;
            }
        }

        // getter
        std::size_t length() const { return m_length; }

        // subscript operator
        char& operator[] (int index) {

            if (index >= m_length) {
                throw std::out_of_range("Wrong index!");
            }

            return m_string.get()[index];
        }

        // copy c'tor
        MyStringSP(const MyStringSP& other) {

            // shallow (flat) copy
            // m_string = other.m_string;
            // m_length = other.m_length;

            // or deep copy
            m_length = other.m_length;
            m_string = std::make_shared<char[]>(m_length + 1);
            std::memcpy(m_string.get(), other.m_string.get(), m_length + 1); // copying '\0'
        }

        MyStringSP& operator=(const MyStringSP& other) {

            if (this == &other) {
                return *this;
            }

            // shallow (flat) copy
            // m_string = other.m_string;
            // m_length = other.m_length;

            // or deep copy
            m_length = other.m_length;
            m_string = std::make_shared<char[]>(m_length + 1);
            std::memcpy(m_string.get(), other.m_string.get(), m_length + 1);  // copying '\0'

            return *this;
        }

        // move c'tor
        MyStringSP(MyStringSP&& other) noexcept {

            m_string = std::move(other.m_string);
            m_length = other.m_length;
            other.m_length = 0;
        }

        // move assignment
        MyStringSP& operator=(MyStringSP&& other) noexcept {

            if (this == &other) {
                return *this;
            }

            m_string = std::move(other.m_string);
            m_length = other.m_length;
            other.m_length = 0;

            return *this;
        }
    };

    // =============================================================
    // MyString implementation using std::unique_ptr

    class MyStringUP
    {
    private:
        std::unique_ptr<char[]> m_string;
        std::size_t             m_length;

    public:
        // default c'tor
        MyStringUP() : m_length{} {}

        // user defined c'tor
        MyStringUP(const char* string)
        {
            m_length = std::strlen(string);
            m_string = std::make_unique<char[]>(m_length + 1);
            std::memcpy(m_string.get(), string, m_length + 1);  // copying '\0'
        }

        // no destructor necessary

        // public interface
        void print()
        {
            if (m_string.get() == nullptr) {
                std::cout << "<null>" << std::endl;
            }
            else {
                std::cout << m_string.get() << std::endl;
            }
        }

        // subscript operator
        char& operator[] (int index) {

            if (index >= m_length) {
                throw std::out_of_range("Wrong index!");
            }

            return m_string.get()[index];
        }

        // copy c'tor
        MyStringUP(const MyStringUP& other) {

            m_length = std::strlen(other.m_string.get());
            m_string = std::make_unique<char[]>(m_length + 1);
            std::memcpy(m_string.get(), other.m_string.get(), m_length + 1);  // copying '\0'
        }

        // copy assignment
        MyStringUP& operator=(const MyStringUP& other) {

            if (this == &other) {
                return *this;
            }

            m_length = std::strlen(other.m_string.get());
            m_string = std::make_unique<char[]>(m_length + 1);
            std::memcpy(m_string.get(), other.m_string.get(), m_length + 1);  // copying '\0'

            return *this;
        }

        // move c'tor
        MyStringUP(MyStringUP&& other) noexcept {

            m_string = std::move(other.m_string);
            m_length = other.m_length;
            other.m_length = 0;
        }

        // move assignment
        MyStringUP& operator=(MyStringUP&& other) noexcept {

            if (this == &other) {
                return *this;
            }

            m_string = std::move(other.m_string);
            m_length = other.m_length;
            other.m_length = 0;

            return *this;
        }
    };

    // =============================================================
    // test routines

    static void testExercise_00()
    {
        MyStringSP ms1{ };
        ms1.print();
        MyStringUP ms2{ };
        ms2.print();
    }

    static void testExercise_01()
    {
        MyStringSP ms1{ "123" };
        ms1.print();

        MyStringSP ms2{ "ABCDE" };
        ms2.print();

        ms1 = ms2;   // assignment 
        ms1.print();

        ms2[0] = '?';

        ms1.print();
        ms2.print();
    }

    static void testExercise_02()
    {
        MyStringSP ms1{ "ABCDE" };
        ms1.print();

        MyStringSP ms2{ ms1 };  // copy construction
        ms2.print();

        ms2[0] = '?';

        ms1.print();
        ms2.print();
    }

    static void testExercise_10()
    {
        MyStringUP ms1{ "123" };
        ms1.print();

        MyStringUP ms2{ "ABCDE" };
        ms2.print();

        ms1 = ms2;    // assignment 

        ms1.print();

        ms2[0] = '?';

        ms1.print();
        ms2.print();
    }

    static void testExercise_11()
    {
        MyStringUP ms1{ "ABCDE" };
        ms1.print();

        MyStringUP ms2{ ms1 };  // copy construction
        ms2.print();

        ms2[0] = '?';

        ms1.print();
        ms2.print();
    }

    static void testExercise_20()
    {
        MyStringSP ms1{ "ABCDE" };
        ms1.print();

        MyStringSP ms2{ ms1 };  // copy construction
        ms2.print();

        ms1 = ms2;              // copy assignment
        ms1.print();
    }

    static void testExercise_21()
    {
        MyStringSP ms1{ "ABCDE" };
        ms1.print();

        MyStringSP ms2{ std::move(ms1) };  // move construction
        ms1.print();
        ms2.print();

        ms1 = std::move(ms2);              // move assignment
        ms1.print();
        ms2.print();
    }

    static void testExercise_22()
    {
        MyStringUP ms1{ "ABCDE" };
        ms1.print();

        MyStringUP ms2{ ms1 };             // copy construction
        ms2.print();

        ms1 = ms2;                         // copy assignment
        ms1.print();
    }

    static void testExercise_23()
    {
        MyStringUP ms1{ "ABCDE" };
        ms1.print();

        MyStringUP ms2{ std::move(ms1) };  // move construction
        ms1.print();
        ms2.print();

        ms1 = std::move(ms2);              // move assignment
        ms1.print();
        ms2.print();
    }

    static void testExercise() {

        // default c'tors
        testExercise_00();

        // MyStringSP
        testExercise_01();  // testing assignment
        testExercise_02();  // testing copy construction

        // MyStringUP
        testExercise_10();  // testing assignment
        testExercise_11();  // testing copy construction

        // MyStringSP
        testExercise_20();  // testing copy semantics
        testExercise_21();  // testing move semantics

        // MyStringUP
        testExercise_22();  // testing copy semantics
        testExercise_23();  // testing move semantics
    }
}

void test_exercises_smartpointer()
{
    using namespace Exercise_Smart_Pointer;

    testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
