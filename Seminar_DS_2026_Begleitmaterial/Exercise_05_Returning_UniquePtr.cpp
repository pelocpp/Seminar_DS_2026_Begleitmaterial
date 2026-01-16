// =====================================================================================
// Exercise_05_Returning_UniquePtr.cpp
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

#include <iostream>
#include <memory>
#include <optional>
#include <span>
#include <utility>

namespace Exercise_Smart_Pointer_Returning_UniquePtr {

    // =========================================================
    // helper method 'countDigits'

    static std::size_t countDigits(std::size_t n)
    {
        std::size_t count{};

        // do-while ensures that 0 is counted as 1 digit
        do {
            n /= 10;
            ++count;
        } while (n != 0);

        return count;
    }

    // =========================================================
    // Variant 1: return std::unique_ptr directly
    // (move semantics and/or copy-move elision behind the scenes)

    static std::unique_ptr<std::size_t[]> splitToDigits(
        std::size_t   number,
        std::size_t& count,
        bool& success)
    {
        count = countDigits(number);

        std::unique_ptr<std::size_t[]> digits{ std::make_unique<std::size_t[]>(count) };

        if (digits == nullptr) {
            success = false;
            return digits;
        }
        else {
            std::size_t index{};
            do {
                std::size_t digit = number % 10;
                number /= 10;
                digits[count - index - 1] = digit;
                ++index;
            } while (number != 0);

            success = true;
            return digits;
        }
    }

    // =========================================================
    // Variant 2: return values by reference parameters

    static bool splitToDigitsByRef(
        std::size_t                     number,
        std::unique_ptr<std::size_t[]>& digits,
        std::size_t& count)
    {
        count = countDigits(number);

        digits = std::make_unique<std::size_t[]>(count);

        if (digits == nullptr) {
            return false;
        }
        else {
            std::size_t index{};
            do {
                std::size_t digit = number % 10;
                number /= 10;
                digits[count - index - 1] = digit;
                ++index;
            } while (number != 0);

            return true;
        }
    }

    // =========================================================
    // Variant 3: struct

    struct DigitsSplitting
    {
        std::size_t                    m_number;
        std::unique_ptr<std::size_t[]> m_digits;
        std::size_t                    m_count;
        bool                           m_success;
    };

    static DigitsSplitting splitToDigits(std::size_t number)
    {
        DigitsSplitting splitting{ number };

        auto count{ countDigits(number) };

        std::unique_ptr<std::size_t[]> digits{ std::make_unique<std::size_t[]>(count) };

        if (digits == nullptr) {
            splitting.m_success = false;
            return splitting;
        }
        else {
            std::size_t index{};

            do {
                std::size_t digit = number % 10;
                number /= 10;
                digits[count - index - 1] = digit;
                ++index;
            } while (number != 0);

            splitting.m_digits = std::move(digits);
            splitting.m_count = count;
            splitting.m_success = true;

            return splitting;
        }
    }

    // =========================================================
    // Variant 4: std::tuple

    using SplittedDigitsTuple =
        std::tuple<std::size_t, std::unique_ptr<std::size_t[]>, std::size_t, bool>;

    static SplittedDigitsTuple splitToDigitsTuple(std::size_t number)
    {
        SplittedDigitsTuple splitting{ number, nullptr, 0, false };

        auto count{ countDigits(number) };

        auto digits{ std::make_unique<std::size_t[]>(count) };

        if (digits == nullptr) {
            return splitting;
        }
        else {
            std::size_t index{};

            do {
                std::size_t digit = number % 10;
                number /= 10;
                digits[count - index - 1] = digit;
                ++index;
            } while (number != 0);

            std::get<1>(splitting) = std::move(digits);
            std::get<2>(splitting) = count;
            std::get<3>(splitting) = true;

            return splitting;
        }
    }

    // =========================================================
    // Variant 5: std::optional

    using SplittedDigitsPair =
        std::pair<std::unique_ptr<std::size_t[]>, std::size_t>;

    static std::optional<SplittedDigitsPair> splitToDigitsOptional(std::size_t number)
    {
        std::optional<SplittedDigitsPair> result{};

        auto count{ countDigits(number) };

        auto digits{ std::make_unique<std::size_t[]>(count) };

        if (digits == nullptr) {
            return result;
        }
        else {
            std::size_t index{};

            do {
                std::size_t digit = number % 10;
                number /= 10;
                digits[count - index - 1] = digit;
                ++index;
            } while (number != 0);

            result = std::pair{ std::move(digits) , count };

            return result;
        }
    }

    // =========================================================

    static void test_returning_unique_ptr_variant_01()
    {
        // return std::unique_ptr directly
        // (Move Semantics or Copy-Move Elision)

        std::size_t number{ 12345 };
        std::size_t count{};
        bool success{};

        std::unique_ptr<std::size_t[]> buffer{ splitToDigits(number, count, success) };

        if (success) {

            std::span<size_t> digits{ buffer.get(), count };

          //  std::println("Splitting of {}:", number);
            std::cout << "Splitting of " << number << ':' << std::endl;
            for (std::size_t i{}; auto digit : digits) {

              //  std::println("{}: {}", i, digit);
                std::cout << i << ": " << digit << std::endl;
                ++i;
            }
        }
    }

    static void test_returning_unique_ptr_variant_02()
    {
        // pass all parameters by reference

        std::size_t number{ 54321 };
        std::size_t count{};
        std::unique_ptr<std::size_t[]> buffer{};

        bool success{ splitToDigitsByRef(number, buffer, count) };

        if (success) {

            std::span<size_t> digits{ buffer.get(), count };

            //std::println("Splitting of {}:", number);
            std::cout << "Splitting of " << number << ':' << std::endl;
            for (std::size_t i{}; auto digit : digits) {

                //std::println("{}: {}", i, digit);
                std::cout << i << ": " << digit << std::endl;
                ++i;
            }
        }
    }

    static void test_returning_unique_ptr_variant_03()
    {
        // returning a struct

        std::size_t number{ 13524 };

        DigitsSplitting splitting{ splitToDigits(number) };

        if (splitting.m_success) {

            std::span<size_t> digits{ splitting.m_digits.get(), splitting.m_count };

           // std::println("Splitting of {}:", number);
            std::cout << "Splitting of " << number << ':' << std::endl;
            for (std::size_t i{}; auto digit : digits) {

                //std::println("{}: {}", i, digit);
                std::cout << i << ": " << digit << std::endl;
                ++i;
            }
        }
    }

    static void test_returning_unique_ptr_variant_04()
    {
        // returning a tuple

        std::size_t number{ 53142 };

        const auto& [digit, buffer, count, success] { splitToDigitsTuple(number) };

        if (success) {

            std::span<size_t> digits{ buffer.get(), count };

         //   std::println("Splitting of {}:", number);
            std::cout << "Splitting of " << number << ':' << std::endl;
            for (std::size_t i{}; auto digit : digits) {

                // std::println("{}: {}", i, digit);
                std::cout << i << ": " << digit << std::endl;
                ++i;
            }
        }
    }

    static void test_returning_unique_ptr_variant_05()
    {
        // returning a std::optional

        std::size_t number{ 15243 };

        auto result{ splitToDigitsOptional(number) };

        if (result.has_value()) {

            const auto& [buffer, count] = result.value();

            std::span<size_t> digits{ buffer.get(), count };

            // std::println("Splitting of {}:", number);
            std::cout << "Splitting of " << number << ':' << std::endl;

            for (std::size_t i{}; auto digit : digits) {

                //   std::println("{}: {}", i, digit);
                std::cout << i << ": " << digit << std::endl;
                ++i;
            }
        }
        std::cout << std::endl;
    }

    // =========================================================

    static void testExercise()
    {
        test_returning_unique_ptr_variant_01();
        test_returning_unique_ptr_variant_02();
        test_returning_unique_ptr_variant_03();
        test_returning_unique_ptr_variant_04();
        test_returning_unique_ptr_variant_05();
    }
}

void test_exercises_smartpointer_returning_unique_ptr()
{
    using namespace Exercise_Smart_Pointer_Returning_UniquePtr;

    testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
