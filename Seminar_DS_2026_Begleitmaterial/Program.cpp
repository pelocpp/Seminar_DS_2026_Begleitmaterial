// =====================================================================================
// Program.cpp
// =====================================================================================

extern void test_exercises_smartpointer();         // std::unique_ptr or std::shared_ptr as class member
extern void test_exercises_stl_erase_remove();     // erasing and removinv in STL Containers
extern void test_exercises_phonebook();            // STL basics (container, algorithms, lambdas)
extern void test_exercises_constexpr_maximum();    // maximum of three values at compile time
extern void test_exercises_returning_unique_ptr(); // returning an std::unique_ptr object
extern void test_exercises_constexpr_rgb();        // RGB colors at compile time

int main()
{
    //test_exercises_smartpointer();
    //test_exercises_stl_erase_remove();
    //test_exercises_phonebook();
    //test_exercises_constexpr_maximum();
    //test_exercises_returning_unique_ptr();
    test_exercises_constexpr_rgb();
}

// =====================================================================================
// End-of-File
// =====================================================================================
