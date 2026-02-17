// =====================================================================================
// Exercise_06_constexpr_rgb.cpp
// =====================================================================================

#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <optional>
#include <string_view>

//#pragma warning (push)
//#pragma warning (disable : 4244)
//#pragma warning (disable : 4302)
//#pragma warning (disable : 4305)
//#pragma warning (disable : 4309)

// windef.h -- Basic Windows Type Definitions
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

// wingdi.h
typedef DWORD               COLORREF;

// wingdi.h
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

namespace MacrosDiscouragedUsage
{
    static void test_macro_rgb_01()
    {
        // Color constants - examples from Microsoft
        const COLORREF rgbRed = 0x000000FF;
        const COLORREF rgbGreen = 0x0000FF00;
        const COLORREF rgbBlue = 0x00FF0000;
        const COLORREF rgbBlack = 0x00000000;
        const COLORREF rgbWhite = 0x00FFFFFF;

        COLORREF red = RGB(255, 0, 0);
        COLORREF lightBlue = RGB(25, 55, 200);
        COLORREF aqua = RGB(128, 255, 255);

        // wrong use cases
        COLORREF unknown1 = RGB(55.55, 66, 70);     // no warning, no error
        COLORREF unknown2 = RGB(55, 66.66f, 70);    // no warning, no error
        COLORREF unknown3 = RGB(-1, -2, -3);        // no warning, no error
        COLORREF unknown4 = RGB(-1, -2, "ABC");     // 'type cast' : truncation from 'const char *' to 'BYTE'
    }
}

// =====================================================================================

namespace ConstexprRecommendedUsage
{
    static constexpr std::uint32_t Rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b)
    {
        return
            static_cast<std::uint32_t>(r) |
            static_cast<std::uint32_t>(g) << 8 |
            static_cast<std::uint32_t>(b) << 16;
    }

    class Color
    {
    private:
        std::uint8_t m_r;
        std::uint8_t m_g;
        std::uint8_t m_b;

    public:
        constexpr explicit Color(std::uint8_t r, std::uint8_t g, std::uint8_t b)
            : m_r(r), m_g(g), m_b(b)
        {
        }

        constexpr explicit Color(const std::string_view s)
            : Color(parse(s))
        {
        }

        constexpr Color(const Color& rhs) = default;
        constexpr Color& operator= (const Color& rhs) = default;

    private:
        static constexpr Color parse(std::string_view str)
        {
            if (str.size() != 7) {
                return Color{ 0, 0, 0 };
            }
            else if (str[0] != '#') {
                return Color{ 0, 0, 0 };
            }
            else {

            }

            std::string_view svR{ str.substr(1, 2) };
            std::string_view svG{ str.substr(3, 2) };
            std::string_view svB{ str.substr(5, 2) };

            auto r{ byte(svR) };
            auto g{ byte(svG) };
            auto b{ byte(svB) };

            if (r.has_value() && g.has_value() && b.has_value()) {
                return Color{ r.value() , g.value() , b.value() };
            }
            else {
                return Color{ 0, 0, 0 };
            }
        }

        // decode a nibble
        static constexpr std::optional<std::uint8_t> nibble(char n) {
            if (n >= '0' && n <= '9') {
                return n - '0';
            }
            else if (n >= 'a' && n <= 'f') {
                return n - 'a' + 10;
            }
            else if (n >= 'A' && n <= 'F') {
                return n - 'A' + 10;
            }
            else {
                return std::nullopt;
            }
        }

        // decode a byte
        static constexpr std::optional<std::uint8_t> byte(std::string_view sv)
        {
            auto upperNibble = nibble(sv[0]);
            auto lowerNibble = nibble(sv[1]);

            if (lowerNibble.has_value() && upperNibble.has_value()) {
                return upperNibble.value() << 4 | lowerNibble.value();
            }
            else {
                return std::nullopt;
            }
        }

    public:
        // getter
        constexpr std::uint8_t GetRValue() const { return m_r; };
        constexpr std::uint8_t GetGValue() const { return m_g; };
        constexpr std::uint8_t GetBValue() const { return m_b; };

        constexpr std::uint32_t value() const
        {
            return
                static_cast<std::uint32_t> (m_r) |
                static_cast<std::uint32_t> (m_g) << 8 |
                static_cast<std::uint32_t> (m_b) << 16;
        }
    };
}

// ===============================================================================================

// function Rgb
static void test_constexpr_color_01()
{
    COLORREF red = RGB(255, 0, 0);
    COLORREF lightBlue = RGB(173, 216, 230);
    COLORREF aqua = RGB(0, 255, 255);
    COLORREF darkGreen = RGB(1, 50, 32);

    std::cout << std::format("{:#010X}", red) << std::endl;
    std::cout << std::format("{:#010X}", lightBlue) << std::endl;
    std::cout << std::format("{:#010X}", aqua) << std::endl;
    std::cout << std::format("{:#010X}", darkGreen) << std::endl;
    std::cout << std::endl;
}

static void test_constexpr_color_02()
{
    COLORREF unknown1 = RGB(255.0, 0.0, 0.0);             // No warning, no error
    COLORREF unknown2 = RGB('173', '216', '230');         // No warning, no error
    COLORREF unknown3 = RGB("0", "255", "255");           // Warning: 'type cast' : truncation from 'const char *' to 'BYTE'
    COLORREF unknown4 = RGB(1000, 5000, 32000);           // No warning, no error

    std::cout << std::format("{:#010X}", unknown1) << std::endl;
    std::cout << std::format("{:#010X}", unknown2) << std::endl;
    std::cout << std::format("{:#010X}", unknown3) << std::endl;
    std::cout << std::format("{:#010X}", unknown4) << std::endl;
    std::cout << std::endl;
}

static void test_constexpr_color_03()
{
    using namespace ConstexprRecommendedUsage;

    constexpr std::uint32_t red{ Rgb(255, 0, 0) };
    constexpr std::uint32_t lightBlue{ Rgb(173, 216, 230) };
    constexpr std::uint32_t aqua{ Rgb(0, 255, 255) };
    constexpr std::uint32_t darkGreen{ Rgb(1, 50, 32) };

    std::cout << std::format("{:#010X}", red) << std::endl;
    std::cout << std::format("{:#010X}", lightBlue) << std::endl;
    std::cout << std::format("{:#010X}", aqua) << std::endl;
    std::cout << std::format("{:#010X}", darkGreen) << std::endl;
    std::cout << std::endl;
}

static void test_constexpr_color_04()
{
    using namespace ConstexprRecommendedUsage;

    constexpr std::uint32_t red = Rgb(255.0, 0.0, 0.0);             // Warning: 'argument': conversion from 'double' to 'const uint8_t', possible loss of data
    constexpr std::uint32_t lightBlue = Rgb('173', '216', '230');   // Warning: 'argument': truncation from 'int' to 'const uint8_t'
   // constexpr std::uint32_t aqua = Rgb("0", "255", "255");        // Error: cannot convert argument 1 from 'const char [2]' to 'const uint8_t'
    constexpr std::uint32_t darkGreen = Rgb(1000, 5000, 32000);     // Warning:  'argument': truncation from 'int' to 'const uint8_t'

    std::cout << std::format("{:#010X}", red) << std::endl;
    std::cout << std::format("{:#010X}", lightBlue) << std::endl;
    //std::cout << std::format("{:#010X}", aqua) << std::endl;
    std::cout << std::format("{:#010X}", darkGreen) << std::endl;
    std::cout << std::endl;
}

// ===============================================================================================
// class Color

static void test_constexpr_color_10()
{
    using namespace ConstexprRecommendedUsage;

    constexpr Color cyan{ 0, 255, 255 };

    static_assert(cyan.GetRValue() == 0,   "0 Expected");
    static_assert(cyan.GetGValue() == 255, "255 Expected");
    static_assert(cyan.GetBValue() == 255, "255 Expected");
}

static void test_constexpr_color_11()
{
    using namespace ConstexprRecommendedUsage;

    constexpr Color cyan{ 0, 255, 255 };
    auto value{ cyan.value() };
    std::cout << std::format("{:#010X}", value) << std::endl;
}

static void test_constexpr_color_12()
{
    using namespace ConstexprRecommendedUsage;

    constexpr Color cyan{ "#00FFFF" };

    constexpr auto r{ cyan.GetRValue() };
    constexpr auto g{ cyan.GetGValue() };
    constexpr auto b{ cyan.GetBValue() };
    std::cout << std::format("{:#04X}:{:#04X}:{:#04X}", r, g, b) << std::endl;

    constexpr auto value{ cyan.value() };
    std::cout << std::format("{:#010X}", value) << std::endl;
}

static void test_constexpr_color_13()
{
    using namespace ConstexprRecommendedUsage;

    constexpr Color red{ 255, 0, 0 };
    constexpr Color lightBlue{ 173, 216, 230 };
    constexpr Color aqua{ 0, 255, 255 };
    constexpr Color darkGreen{ 1, 50, 32 };

    std::cout << std::format("{:#010X}", red.value()) << std::endl;
    std::cout << std::format("{:#010X}", lightBlue.value()) << std::endl;
    std::cout << std::format("{:#010X}", aqua.value()) << std::endl;
    std::cout << std::format("{:#010X}", darkGreen.value()) << std::endl;
}

// #pragma warning(pop)

// =====================================================================================

void test_exercises_constexpr_rgb()
{
    test_constexpr_color_01();
    test_constexpr_color_02();
    test_constexpr_color_03();
    test_constexpr_color_04();

    test_constexpr_color_10();
    test_constexpr_color_11();
    test_constexpr_color_12();
    test_constexpr_color_13();
}

// =====================================================================================
// End-of-File
// =====================================================================================
