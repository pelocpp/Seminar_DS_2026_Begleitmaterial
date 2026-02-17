// =====================================================================================
// Exercise_02_STL_Erase_Remove.cpp
// =====================================================================================

#include "ScopedTimer.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

namespace Exercise_STL_Erase_Remove {

    template <typename T>
    static void print(const std::vector<T>& v)
    {
        //  std::println("Size: {}, Capacity: {}", v.size(), v.capacity());
        std::cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << std::endl;

        for (auto elem : v) {
            //std::print("{} ", elem);
            std::cout << elem << std::endl;
        }
        //std::println();
        //std::println();
        std::cout << std::endl;
        std::cout << std::endl;

    }

    static void testExercise_01()
    {
        // "wrong" implementation (usage of invalid iterator)

        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        print(vec);

        // erase all even numbers
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            if (*it % 2 == 0) {
                vec.erase(it);
            }
        }

        print(vec);
    }

    static void testExercise_02()
    {
        // correct implementation, but inefficient runtime behaviour

        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        print(vec);

        // erase all even numbers
        for (auto it = vec.begin(); it != vec.end(); )
        {
            if (*it % 2 == 0) {
                it = vec.erase(it);
            }
            else {
                ++it;
            }
        }

        print(vec);
    }

    static void testExercise_03()
    {
        // again correct implementation, but efficient (good) runtime behaviour

        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        print(vec);

        auto pos = std::remove_if(
            vec.begin(),
            vec.end(),
            [](auto elem) { return elem % 2 == 0; }
        );

        vec.erase(pos, vec.end());

        print(vec);
    }

    static void testExercise_04()
    {
        // again correct implementation, but efficient (good) runtime behaviour

        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        print(vec);

        // SOLLTE: Remove / Erase Idiom sein
        auto pos = std::erase_if(
            vec,
            [](auto elem) { return elem % 2 == 0; }
        );

        print(vec);
    }

    // =======================================
    // 2 benchmarks:
    // constexpr std::size_t Max = 20;
    // constexpr std::size_t NumIterations = 1;

    constexpr std::size_t Max = 5000;
    constexpr std::size_t NumIterations = 1000;

    static void testExercise_benchmark_01()
    {
        std::vector<int> original(Max);

        std::iota(original.begin(), original.end(), 1);

        ScopedTimer watch{};

        for (std::size_t i{}; i != NumIterations; ++i) {

            // demonstration of inefficient implementation

            std::vector<int> vec{ original };

            // print(vec);

            for (std::vector<int>::iterator it = vec.begin(); it != vec.end();)
            {
                if (*it % 2 == 0)
                    it = vec.erase(it);
                else
                    ++it;
            }

            // print(vec);
        }
    }

    static void testExercise_benchmark_02()
    {
        std::vector<int> original(Max);

        std::iota(original.begin(), original.end(), 1);

        ScopedTimer watch{};

        for (std::size_t i{}; i != NumIterations; ++i) {

            // demonstration of a better, (hopefully) efficient implementation

            std::vector<int> vec{ original };

            // print(vec);

            std::vector<int>::iterator pos = std::remove_if(
                vec.begin(),
                vec.end(),
                [](auto elem) { return elem % 2 == 0; }
            );

            vec.erase(pos, vec.end());

            // print(vec);
        }
    }

    static void testExercise_benchmark_03()
    {
        std::vector<int> original(Max);

        std::iota(original.begin(), original.end(), 1);

        ScopedTimer watch{};

        for (std::size_t i{}; i != NumIterations; ++i) {

            // demonstration of a better, (hopefully) efficient implementation

            std::vector<int> vec{ original };

            // print(vec);

            std::erase_if(
                vec,
                [](auto elem) { return elem % 2 == 0; }
            );

            // print(vec);
        }
    }

    static void testExercise() {

        // testExercise_01();  // crashes - by design
        //testExercise_02();
        //testExercise_03();

        testExercise_benchmark_01();
        testExercise_benchmark_02();
        testExercise_benchmark_03();
    }
}

void test_exercises_stl_erase_remove()
{
    using namespace Exercise_STL_Erase_Remove;

    testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
