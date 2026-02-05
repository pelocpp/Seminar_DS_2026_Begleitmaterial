// =====================================================================================
// Exercise_04_constexpr_maximum.cpp
// =====================================================================================

namespace Exercise_ConstExpr {

    // works for int arguments
    static constexpr auto maximum(int a, int b, int c) {

        if (a > b && a > c)
        {
            return a;
        }
        else if (b > a && b > c)
        {
            return b;
        }
        else
        {
            return c;
        }
    };

    template <typename T>
    static constexpr auto maximumGeneric(T a, T b, T c) {

        if (a > b && a > c)
        {
            return a;
        }
        else if (b > a && b > c)
        {
            return b;
        }
        else
        {
            return c;
        }
    };

    static constexpr auto maximumAuto(auto a, auto b, auto c) {

        if (a > b && a > c)
        {
            return a;
        }
        else if (b > a && b > c)
        {
            return b;
        }
        else
        {
            return c;
        }
    };

    // works for int arguments
    static auto maximumLambda = [](int a, int b, int c) constexpr {

        if (a > b && a > c)
        {
            return a;
        }
        else if (b > a && b > c)
        {
            return b;
        }
        else
        {
            return c;
        }
        };

    // works for arguments of different type (?!?)
    // type of the ternary ?: expression is
    // the common type of its second and third argument
    static auto maximumAutoLambda = [](auto a, auto b, auto c) constexpr {
        return (a > b && a > c) ? a : ((b > a && b > c) ? b : c);
        };

    // works for arguments of different type (?!?)
    // type of the ternary ?: expression is
    // the common type of its second and third argument
    static auto maximumMoreAutoLambda = [](auto a, auto b, auto c) constexpr {

        if (a > b && a > c)
        {
            return a;
        }
        else if (b > a && b > c)
        {
            return b;
        }
        else
        {
            return c;
        }
        };

    // works for arbitrary arguments of the same type (!)
    template <typename T>
    static auto maximumGenericLambda = [](T a, T b, T c) constexpr {
        return (a > b && a > c) ? a : ((b > a && b > c) ? b : c);
        };

    // works for arbitrary arguments of the same type (!)
    // different syntax
    static auto maximumMoreGenericLambda = []<typename T>(T a, T b, T c) constexpr {
        return (a > b && a > c) ? a : ((b > a && b > c) ? b : c);
    };

    static void testExercise()
    {
        constexpr auto result01 = maximum(1, 2, 3);
        static_assert(result01 == 3, "3 Expected");

        constexpr auto result02 = maximumGeneric(1.5, 2.5, 3.5);
        // constexpr auto result03 = maximumGeneric(1.5, 2.5f, 3.5);          // does NOT compile (!)
        constexpr auto result04 = maximumGeneric<double>(1.5, 2.5f, 3.5);

        constexpr auto result05 = maximumAuto(1.5, 2.5, 3.5);
        // constexpr auto result06 = maximumAuto(1.5, 2.5f, 3.5);             // does NOT compile (!)
        // constexpr auto result07 = maximumAuto<double>(1.5, 2.5f, 3.5);     // does NOT compile (!)

        constexpr auto result08 = maximumLambda(1, 2, 3);

        constexpr auto result09 = maximumAutoLambda(3, 1, 2);
        constexpr auto result10 = maximumAutoLambda(3, 2, 1);                 // Why does this compile, different argument types (?)

        constexpr auto result11 = maximumMoreAutoLambda(1.5, 3.5, 2.5);
        // constexpr auto result12 = maximumMoreAutoLambda(1.5, 3.5f, 2.5);   // does NOT compile (!)

        constexpr auto result13 = maximumAutoLambda(1.5, 3.5f, 2.5);          // Why does this compile (?)

        constexpr auto result14 = maximumGenericLambda<int>(5, 7, 6);
        constexpr auto result15 = maximumGenericLambda<double>(7.5, 8.5, 6.5f);  // Compiles, but different argument types (!)

        constexpr auto result16 = maximumMoreGenericLambda(5, 4, 3);
        // constexpr auto result17 = maximumMoreGenericLambda(5.5f, 4.5, 3.5);   // does NOT compile (!), compare with 'maximumGeneric' (?!?!)
    }
}

void test_exercises_constexpr_maximum()
{
    using namespace Exercise_ConstExpr;

    testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
