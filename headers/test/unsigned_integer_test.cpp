#include <cstdint>
#include <sstream>

#include <gtest/gtest.h>

#include "../unsigned_integer.hpp"

using namespace utility;

TEST(UnsignedIntegerTest, ConstructorDefault) {
    Unsigned_integer<32> i;
    auto binary = i.to_string(2);
    EXPECT_EQ(i.precision, 32);
    EXPECT_EQ(binary, "0");

    Unsigned_integer<0> iz;
    binary = iz.to_string(2);
    EXPECT_EQ(iz.precision, 0);
    EXPECT_EQ(binary, "0");

    Unsigned_integer<1> io;
    binary = io.to_string(2);
    EXPECT_EQ(io.precision, 1);
    EXPECT_EQ(binary, "0");
}

TEST(UnsignedIntegerTest, ConstructorUnsignedInt64) {
    Unsigned_integer<16> i1{128};
    EXPECT_EQ(i1.to_string(2), "10000000");

    // Largest unsigned int
    Unsigned_integer<64> i2{static_cast<std::uint64_t>(-1)};
    EXPECT_EQ(
        i2.to_string(2),
        "1111111111111111111111111111111111111111111111111111111111111111");

    // Zero value if overflown
    Unsigned_integer<8> i3{256};
    EXPECT_EQ(i3.to_string(2), "0");

    Unsigned_integer<6> i4{0b111101};
    EXPECT_EQ(i4.to_string(2), "111101");

    Unsigned_integer<16> i5{0};
    EXPECT_EQ("0", i5.to_string());
}

TEST(UnsignedIntegerTest, ConstructorStringBinary) {
    Unsigned_integer<12> i1{"0B111111111111"};
    EXPECT_EQ(i1.to_string(2), "111111111111");

    Unsigned_integer<8> i2{"0b1"};
    EXPECT_EQ(i2.to_string(2), "1");

    Unsigned_integer<8> i3{"0B"};
    EXPECT_EQ(i3.to_string(2), "0");

    Unsigned_integer<5> i4{"0b10101"};
    EXPECT_EQ(i4.to_string(2), "10101");
}

TEST(UnsignedIntegerTest, ConstructorStringDecimal) {
    Unsigned_integer<8> i1{"128"};
    EXPECT_EQ(i1.to_string(2), "10000000");

    Unsigned_integer<5> i2{"9"};
    EXPECT_EQ(i2.to_string(2), "1001");

    Unsigned_integer<4> i3{"0"};
    EXPECT_EQ(i3.to_string(2), "0");

    Unsigned_integer<17> i4{"101093"};
    EXPECT_EQ(i4.to_string(2), "11000101011100101");
}

TEST(UnsignedIntegerTest, ConstructorStringHex) {
    Unsigned_integer<8> i1{"0x80"};
    EXPECT_EQ(i1.to_string(2), "10000000");

    Unsigned_integer<12> i2{"0X0"};
    EXPECT_EQ(i2.to_string(2), "0");

    Unsigned_integer<12> i3{"0x"};
    EXPECT_EQ(i3.to_string(2), "0");

    Unsigned_integer<16> i4{"0X3039"};
    EXPECT_EQ(i4.to_string(2), "11000000111001");

    Unsigned_integer<16> i5{"0xAAAA"};
    EXPECT_EQ(i5.to_string(2), "1010101010101010");

    Unsigned_integer<20> i6{"0x5F02C"};
    EXPECT_EQ(i6.to_string(2), "1011111000000101100");
}

TEST(UnsignedIntegerTest, ConstructorStringOctal) {
    Unsigned_integer<8> i1{"0200"};
    EXPECT_EQ(i1.to_string(2), "10000000");

    Unsigned_integer<12> i2{"00"};
    EXPECT_EQ(i2.to_string(2), "0");

    Unsigned_integer<16> i4{"030071"};
    EXPECT_EQ(i4.to_string(2), "11000000111001");

    Unsigned_integer<16> i5{"0125252"};
    EXPECT_EQ(i5.to_string(2), "1010101010101010");

    Unsigned_integer<20> i6{"01370054"};
    EXPECT_EQ(i6.to_string(2), "1011111000000101100");
}

TEST(UnsignedIntegerTest, StringOutputDecimal) {
    Unsigned_integer<8> i1{"127"};
    EXPECT_EQ("127", i1.to_string());

    Unsigned_integer<32> i2{"9999999"};
    EXPECT_EQ("9999999", i2.to_string());

    Unsigned_integer<128> i3{"0000000"};
    EXPECT_EQ("0", i3.to_string());

    Unsigned_integer<64> i4{"18446744073709551615"};
    EXPECT_EQ("18446744073709551615", i4.to_string());

    Unsigned_integer<256> i5{
        "1157920892373161954235709850086879078532699846656405640394575840079131"
        "29639935"};
    EXPECT_EQ(
        "1157920892373161954235709850086879078532699846656405640394575840079131"
        "29639935",
        i5.to_string());

    Unsigned_integer<1024> i6{
        "1797693134862315907729305190789024733617976978942306572734300811577326"
        "7580550096313270847732240753602112011387987139335765878976881441662249"
        "2847430639474124377767893424865485276302219601246094119453082952085005"
        "7688381506823424628814739131105408272371633505106845862982399472459384"
        "79716304835356329624224137215"};
    EXPECT_EQ(
        "1797693134862315907729305190789024733617976978942306572734300811577326"
        "7580550096313270847732240753602112011387987139335765878976881441662249"
        "2847430639474124377767893424865485276302219601246094119453082952085005"
        "7688381506823424628814739131105408272371633505106845862982399472459384"
        "79716304835356329624224137215",
        i6.to_string());

    // The below works, but takes around 2 seconds.
    // Unsigned_integer<8192> i7{
    //     "1090748135619415929462984244733782862448264161996232692431832786189721"
    //     "3318491192952162642345252019872239572917961570252731098708201771840636"
    //     "1097976507755479907890629884219298953860982522804820515969685161359163"
    //     "8196771886542609324560121290553901886301017900252535799917200010079600"
    //     "0265358368009052978058809523505016301954756539110053123645600148474260"
    //     "3529355124584392891875276869627934408805561751569434994540667782514081"
    //     "4900616105920256438504578013326493565836047242407382442812245131517757"
    //     "5191648992263657437224322773680750276278830452065017927617009456991684"
    //     "9725787968385173704999690096112051565505011556127149149251534210574896"
    //     "6629547032786321505730828430221664970324396138635251626409516168005427"
    //     "6234359963089216914461811874063953106654048857394348328774281674074953"
    //     "7099351186875635997039011702182361674945862096985700626361208270671540"
    //     "8157066575137281027022310927564910276759160520878304632411049364568754"
    //     "9209673229824591847634273837902724484380185269777649410727156115804346"
    //     "9082745933999196141424274141059911742606055648376375631452761136265862"
    //     "8383368621157993638020878537675545336789915694234433955666315070087213"
    //     "5354702556703120041307254958345083574396538289360770809785505789129679"
    //     "0735278005493562156109079584517295411597292747987752773856000820411855"
    //     "8930004777748727761853813510493840581861598652211605960308356405941821"
    //     "1897140378687262194814987276036536162988561748224130334854387853240247"
    //     "5141941718301228107820972930353737280457437209522870362277636394529086"
    //     "9806258422355148507571039619387449629866808188769662815778153079393179"
    //     "0931436483407617385818195630029944227907549550612888183084300796486932"
    //     "3217915876591803556521615711540299212027615560787310793747746684152836"
    //     "2987708699450152031231862594203085693838944657061346236704234026821102"
    //     "9589549511970870765461866227962945364516207565093510189060237738215395"
    //     "3277620867697858973196633030889330466516943618507835064156833694453005"
    //     "1437491311298834367265238595404904273455928723949525227184617404367854"
    //     "7546104743770197680255766058810380772707077179422219770903854385858440"
    //     "9549211609985253890397465570394397308609093059696336076752996493841459"
    //     "8185705963754561497355827813623833288906309004288017321424808663962671"
    //     "3335280092327583508730596141187237814221014601986157473868550968960891"
    //     "8918044133955852482286754111321263879367556765034036297003193002339782"
    //     "8465318547238244232028015189689660418822976000815437610652254270163595"
    //     "6508754338511471232142272666054035817814690908065764689505876619971865"
    //     "05665475715792894"};
    // EXPECT_EQ(
    //     "1090748135619415929462984244733782862448264161996232692431832786189721"
    //     "3318491192952162642345252019872239572917961570252731098708201771840636"
    //     "1097976507755479907890629884219298953860982522804820515969685161359163"
    //     "8196771886542609324560121290553901886301017900252535799917200010079600"
    //     "0265358368009052978058809523505016301954756539110053123645600148474260"
    //     "3529355124584392891875276869627934408805561751569434994540667782514081"
    //     "4900616105920256438504578013326493565836047242407382442812245131517757"
    //     "5191648992263657437224322773680750276278830452065017927617009456991684"
    //     "9725787968385173704999690096112051565505011556127149149251534210574896"
    //     "6629547032786321505730828430221664970324396138635251626409516168005427"
    //     "6234359963089216914461811874063953106654048857394348328774281674074953"
    //     "7099351186875635997039011702182361674945862096985700626361208270671540"
    //     "8157066575137281027022310927564910276759160520878304632411049364568754"
    //     "9209673229824591847634273837902724484380185269777649410727156115804346"
    //     "9082745933999196141424274141059911742606055648376375631452761136265862"
    //     "8383368621157993638020878537675545336789915694234433955666315070087213"
    //     "5354702556703120041307254958345083574396538289360770809785505789129679"
    //     "0735278005493562156109079584517295411597292747987752773856000820411855"
    //     "8930004777748727761853813510493840581861598652211605960308356405941821"
    //     "1897140378687262194814987276036536162988561748224130334854387853240247"
    //     "5141941718301228107820972930353737280457437209522870362277636394529086"
    //     "9806258422355148507571039619387449629866808188769662815778153079393179"
    //     "0931436483407617385818195630029944227907549550612888183084300796486932"
    //     "3217915876591803556521615711540299212027615560787310793747746684152836"
    //     "2987708699450152031231862594203085693838944657061346236704234026821102"
    //     "9589549511970870765461866227962945364516207565093510189060237738215395"
    //     "3277620867697858973196633030889330466516943618507835064156833694453005"
    //     "1437491311298834367265238595404904273455928723949525227184617404367854"
    //     "7546104743770197680255766058810380772707077179422219770903854385858440"
    //     "9549211609985253890397465570394397308609093059696336076752996493841459"
    //     "8185705963754561497355827813623833288906309004288017321424808663962671"
    //     "3335280092327583508730596141187237814221014601986157473868550968960891"
    //     "8918044133955852482286754111321263879367556765034036297003193002339782"
    //     "8465318547238244232028015189689660418822976000815437610652254270163595"
    //     "6508754338511471232142272666054035817814690908065764689505876619971865"
    //     "05665475715792894",
    //     i7.to_string());
}

TEST(UnsignedIntegerTest, StringOutputHex) {
    Unsigned_integer<64> i1{"736489"};
    EXPECT_EQ("B3CE9", i1.to_string(16));

    Unsigned_integer<64> i2{"0"};
    EXPECT_EQ("0", i2.to_string(16));

    Unsigned_integer<64> i3{"16"};
    EXPECT_EQ("10", i3.to_string(16));

    Unsigned_integer<64> i4{"11259375"};
    EXPECT_EQ("ABCDEF", i4.to_string(16));

    Unsigned_integer<64> i5{"99999999"};
    EXPECT_EQ("5F5E0FF", i5.to_string(16));

    Unsigned_integer<64> i6{"15"};
    EXPECT_EQ("F", i6.to_string(16));
}

TEST(UnsignedIntegerTest, StringOutputOctal) {
    Unsigned_integer<64> i1{"736489"};
    EXPECT_EQ("2636351", i1.to_string(8));

    Unsigned_integer<64> i2{"0"};
    EXPECT_EQ("0", i2.to_string(8));

    Unsigned_integer<64> i3{"8"};
    EXPECT_EQ("10", i3.to_string(8));

    Unsigned_integer<64> i4{"11259375"};
    EXPECT_EQ("52746757", i4.to_string(8));

    Unsigned_integer<64> i5{"99999999"};
    EXPECT_EQ("575360377", i5.to_string(8));

    Unsigned_integer<64> i6{"7"};
    EXPECT_EQ("7", i6.to_string(8));
}

TEST(UnsignedIntegerTest, StringOutputBinary) {
    Unsigned_integer<64> i1{"736489"};
    EXPECT_EQ("10110011110011101001", i1.to_string(2));

    Unsigned_integer<64> i2{"0"};
    EXPECT_EQ("0", i2.to_string(2));

    Unsigned_integer<64> i3{"2"};
    EXPECT_EQ("10", i3.to_string(2));

    Unsigned_integer<64> i4{"11259375"};
    EXPECT_EQ("101010111100110111101111", i4.to_string(2));

    Unsigned_integer<64> i5{"99999999"};
    EXPECT_EQ("101111101011110000011111111", i5.to_string(2));

    Unsigned_integer<64> i6{"1"};
    EXPECT_EQ("1", i6.to_string(2));
}

TEST(UnsignedIntegerTest, ImplicitCasting) {
    Unsigned_integer<64> i1{999};
    Unsigned_integer<128> i2{i1};
    EXPECT_EQ("999", i2.to_string());

    Unsigned_integer<128> i3{1234};
    Unsigned_integer<64> i4{i3};
    EXPECT_EQ("1234", i4.to_string());

    Unsigned_integer<128> result1{i1 + i3};
    EXPECT_EQ("2233", result1.to_string());

    Unsigned_integer<12> result2{i1 + i3};
    EXPECT_EQ("2233", result2.to_string());

    Unsigned_integer<1> i5{0};
    Unsigned_integer<12> result3{i1 + i3 + i5};
    EXPECT_EQ("2233", result3.to_string());

    Unsigned_integer<64> i6{i1};
    EXPECT_EQ("999", i6.to_string());
}

TEST(UnsignedIntegerTest, Addition) {
    Unsigned_integer<64> i1{0};
    Unsigned_integer<64> i2{1};
    Unsigned_integer<64> i3{9'999'999'999};
    Unsigned_integer<64> i4{46'372'891};
    Unsigned_integer<64> i5{7};

    Unsigned_integer<64> result1{i1 + i1};
    EXPECT_EQ("0", result1.to_string());

    Unsigned_integer<64> result2{i1 + i2};
    EXPECT_EQ("1", result2.to_string());

    Unsigned_integer<64> result3{i2 + i2};
    EXPECT_EQ("2", result3.to_string());

    Unsigned_integer<64> result4{i3 + i2};
    EXPECT_EQ("10000000000", result4.to_string());

    Unsigned_integer<64> result5{i3 + i1};
    EXPECT_EQ("9999999999", result5.to_string());

    Unsigned_integer<64> result6{i4 + i2};
    EXPECT_EQ("46372892", result6.to_string());

    Unsigned_integer<64> result7{i5 + i5};
    EXPECT_EQ("14", result7.to_string());

    Unsigned_integer<64> result8{i5 + i5 + i5};
    EXPECT_EQ("21", result8.to_string());

    Unsigned_integer<64> result9{i1 + i2 + i3 + i4};
    EXPECT_EQ("10046372891", result9.to_string());

    EXPECT_EQ("5", (i2 + 4).to_string());
    EXPECT_EQ("5", (4 + i2).to_string());
    EXPECT_EQ("1", (0 + i2).to_string());
    EXPECT_EQ("5", ("4" + i2).to_string());
    EXPECT_EQ("5", ("0b100" + i2).to_string());
    EXPECT_EQ("5", (i2 + "4").to_string());
    EXPECT_EQ("5", (i2 + "0b100").to_string());
}

TEST(UnsignedIntegerTest, Subtraction) {
    Unsigned_integer<64> i1{0};
    Unsigned_integer<64> i2{1};
    Unsigned_integer<64> i3{9'999'999'999};
    Unsigned_integer<64> i4{46'372'891};
    Unsigned_integer<64> i5{7};

    Unsigned_integer<64> result1{i1 - i1};
    EXPECT_EQ("0", result1.to_string());

    Unsigned_integer<64> result2{i2 - i1};
    EXPECT_EQ("1", result2.to_string());

    Unsigned_integer<64> result3{i2 - i2};
    EXPECT_EQ("0", result3.to_string());

    Unsigned_integer<64> result4{i3 - i2};
    EXPECT_EQ("9999999998", result4.to_string());

    Unsigned_integer<64> result5{i3 - i1};
    EXPECT_EQ("9999999999", result5.to_string());

    Unsigned_integer<64> result6{i4 - i2};
    EXPECT_EQ("46372890", result6.to_string());

    Unsigned_integer<64> result7{i5 - i5};
    EXPECT_EQ("0", result7.to_string());

    Unsigned_integer<64> result8{i4 - i5 - i5};
    EXPECT_EQ("46372877", result8.to_string());

    Unsigned_integer<64> result9{i3 - i4 - i2 - i1};
    EXPECT_EQ("9953627107", result9.to_string());

    EXPECT_EQ("3", (i5 - 4).to_string());
    EXPECT_EQ("3", (4 - i2).to_string());
    EXPECT_EQ("3", ("4" - i2).to_string());
    EXPECT_EQ("3", ("0b100" - i2).to_string());

    short s{5};
    EXPECT_EQ("4", (s - i2).to_string());
    EXPECT_EQ("4", (5ll - i2).to_string());
    EXPECT_EQ("3", (4.0 - i2).to_string());

    // Junk result, but does not hang or crash
    Unsigned_integer<64> result10{i2 - i4};
    EXPECT_NE("", result10.to_string());
}

TEST(UnsignedIntegerTest, PreIncrementOperator) {
    Unsigned_integer<64> i1{0};
    EXPECT_EQ("1", (++i1).to_string());
    ++i1;
    ++i1;
    ++i1;
    ++i1;
    EXPECT_EQ("5", i1.to_string());
}

TEST(UnsignedIntegerTest, PostIncrementOperator) {
    Unsigned_integer<64> i1{0};
    EXPECT_EQ("0", (i1++).to_string());
    EXPECT_EQ("1", i1.to_string());
    i1++;
    i1++;
    i1++;
    i1++;
    EXPECT_EQ("5", i1.to_string());
}

TEST(UnsignedIntegerTest, PreDecrementOperator) {
    Unsigned_integer<64> i1{10};
    EXPECT_EQ("9", (--i1).to_string());
    --i1;
    --i1;
    --i1;
    --i1;
    EXPECT_EQ("5", i1.to_string());
}

TEST(UnsignedIntegerTest, PostDecrementOperator) {
    Unsigned_integer<64> i1{10};
    EXPECT_EQ("10", (i1--).to_string());
    EXPECT_EQ("9", i1.to_string());
    i1--;
    i1--;
    i1--;
    i1--;
    EXPECT_EQ("5", i1.to_string());
}

TEST(UnsignedIntegerTest, AdditionCompoundAssignment) {
    Unsigned_integer<16> i1{10};
    Unsigned_integer<32> i2{15};
    i1 += i2;
    EXPECT_EQ("25", i1.to_string());
    --(i1 += i1);
    EXPECT_EQ("49", i1.to_string());
    EXPECT_EQ("51", (i1 += 2).to_string());
    EXPECT_EQ("53", (i1 += "2").to_string());
}

TEST(UnsignedIntegerTest, SubtractionCompoundAssignment) {
    Unsigned_integer<16> i1{10};
    Unsigned_integer<32> i2{15};
    i2 -= i1;
    EXPECT_EQ("5", i2.to_string());
    (i2 -= i2)++;
    EXPECT_EQ("1", i2.to_string());
    EXPECT_EQ("8", (i1 -= 2).to_string());
    EXPECT_EQ("6", (i1 -= "2").to_string());
}

TEST(UnsignedIntegerTest, DivisionCompoundAssignment) {
    Unsigned_integer<16> i1{100};
    Unsigned_integer<32> i2{10};
    i1 /= i2;
    EXPECT_EQ("10", i1.to_string());
    (i2 /= i2)++;
    EXPECT_EQ("2", i2.to_string());
    EXPECT_EQ("5", (i1 /= 2).to_string());
    EXPECT_EQ("2", (i1 /= "2").to_string());
}

TEST(UnsignedIntegerTest, ModuloCompoundAssignment) {
    Unsigned_integer<16> i1{10};
    Unsigned_integer<32> i2{15};
    i1 %= i2;
    EXPECT_EQ("10", i1.to_string());
    (i2 %= i2)++;
    EXPECT_EQ("1", i2.to_string());
    EXPECT_EQ("0", (i1 %= 2).to_string());
    EXPECT_EQ("0", (i1 %= "2").to_string());
}

TEST(UnsignedIntegerTest, MultiplicationCompoundAssignment) {
    Unsigned_integer<16> i1{10};
    Unsigned_integer<32> i2{15};
    i2 *= i1;
    EXPECT_EQ("150", i2.to_string());
    (i2 *= i2)++;
    EXPECT_EQ("22501", i2.to_string());
    EXPECT_EQ("20", (i1 *= 2).to_string());
    EXPECT_EQ("40", (i1 *= "2").to_string());
}

TEST(UnsignedIntegerTest, ComparisonOperators) {
    Unsigned_integer<16> i1{10};
    Unsigned_integer<32> i2{15};
    Unsigned_integer<128> i3{15};

    EXPECT_TRUE(i1 == i1);
    EXPECT_TRUE(i2 == i3);
    EXPECT_TRUE(i1 != i3);
    EXPECT_FALSE(i2 != i3);

    EXPECT_TRUE(i1 < i2);
    EXPECT_FALSE(i2 < i1);
    EXPECT_FALSE(i1 < i1);

    EXPECT_TRUE(i1 <= i2);
    EXPECT_FALSE(i2 <= i1);
    EXPECT_TRUE(i1 <= i1);

    EXPECT_TRUE(i3 > i1);
    EXPECT_FALSE(i1 > i2);
    EXPECT_FALSE(i2 > i3);

    EXPECT_TRUE(i3 >= i1);
    EXPECT_FALSE(i1 >= i2);
    EXPECT_TRUE(i2 >= i3);

    EXPECT_TRUE(i3 >= 10);
    EXPECT_TRUE(i3 >= "10");
    EXPECT_TRUE(10 <= i3);
    EXPECT_TRUE("10" <= i3);

    EXPECT_TRUE(i3 > 10);
    EXPECT_TRUE(i3 > "10");
    EXPECT_TRUE(10 < i3);
    EXPECT_TRUE("10" < i3);

    EXPECT_TRUE(15 == i3);
    EXPECT_TRUE("15" == i3);
    EXPECT_TRUE(10 != i3);
    EXPECT_TRUE("10" != i3);
}

TEST(UnsignedIntegerTest, Division) {
    Unsigned_integer<64> i1{0};
    Unsigned_integer<16> i2{1};
    Unsigned_integer<64> i3{9'999'999'999};
    Unsigned_integer<256> i4{46'372'891};
    Unsigned_integer<1024> i5{7};
    Unsigned_integer<64> i6{2};

    EXPECT_EQ("3", (i5 / i6).to_string());
    EXPECT_EQ("0", (i2 / i1).to_string());
    EXPECT_EQ("0", (i2 / i3).to_string());
    EXPECT_EQ("0", (i2 / i4).to_string());
    EXPECT_EQ("0", (i4 / i3).to_string());
    EXPECT_EQ("215", (i3 / i4).to_string());

    EXPECT_EQ("6624698", (i4 / i5).to_string());
    EXPECT_EQ("1428571428", (i3 / i5).to_string());

    EXPECT_EQ("9999999999", (i3 / i2).to_string());
    EXPECT_EQ("46372891", (i4 / i2).to_string());
    EXPECT_EQ("7", (i5 / i2).to_string());

    EXPECT_EQ("0", (i5 / i1).to_string());

    EXPECT_EQ("3", (i5 / 2).to_string());
    EXPECT_EQ("4", (4 / i2).to_string());
    EXPECT_EQ("4", ("4" / i2).to_string());
    EXPECT_EQ("4", ("0b100" / i2).to_string());

    short s{5};
    EXPECT_EQ("5", (s / i2).to_string());
    EXPECT_EQ("5", (5ll / i2).to_string());
    EXPECT_EQ("2", (4.0 / i6).to_string());
}

TEST(UnsignedIntegerTest, Modulo) {
    Unsigned_integer<64> i1{0};
    Unsigned_integer<16> i2{1};
    Unsigned_integer<64> i3{9'999'999'999};
    Unsigned_integer<256> i4{46'372'891};
    Unsigned_integer<1024> i5{7};
    Unsigned_integer<64> i6{2};

    EXPECT_EQ("1", (i5 % i6).to_string());
    EXPECT_EQ("0", (i2 % i1).to_string());
    EXPECT_EQ("1", (i2 % i3).to_string());
    EXPECT_EQ("1", (i2 % i4).to_string());
    EXPECT_EQ("46372891", (i4 % i3).to_string());
    EXPECT_EQ("29828434", (i3 % i4).to_string());

    EXPECT_EQ("5", (i4 % i5).to_string());
    EXPECT_EQ("3", (i3 % i5).to_string());

    EXPECT_EQ("0", (i3 % i2).to_string());
    EXPECT_EQ("0", (i4 % i2).to_string());
    EXPECT_EQ("0", (i5 % i2).to_string());

    EXPECT_EQ("3", (i5 % 4).to_string());
    EXPECT_EQ("4", (4 % i5).to_string());
    EXPECT_EQ("0", ("4" % i2).to_string());
    EXPECT_EQ("0", ("0b100" % i2).to_string());

    short s{5};
    EXPECT_EQ("0", (s % i2).to_string());
    EXPECT_EQ("0", (5ll % i2).to_string());
    EXPECT_EQ("0", (4.0 % i6).to_string());
}

TEST(UnsignedIntegerTest, Multiplication) {
    Unsigned_integer<64> i1{0};
    Unsigned_integer<16> i2{1};
    Unsigned_integer<64> i3{9'999'999'999};
    Unsigned_integer<256> i4{46'372'891};
    Unsigned_integer<1024> i5{7};
    Unsigned_integer<64> i6{2};

    EXPECT_EQ("14", (i5 * i6).to_string());
    EXPECT_EQ("0", (i2 * i1).to_string());
    EXPECT_EQ("69999999993", (i5 * i2 * i3).to_string());
    EXPECT_EQ("46372891", (i4 * i2).to_string());
    EXPECT_EQ("463728909953627109", (i4 * i3).to_string());
    EXPECT_EQ("463728909953627109", (i3 * i4).to_string());

    EXPECT_EQ("324610237", (i4 * i5).to_string());
    EXPECT_EQ("69999999993", (i3 * i5).to_string());

    EXPECT_EQ("9999999999", (i3 * i2).to_string());
    EXPECT_EQ("46372891", (i4 * i2).to_string());
    EXPECT_EQ("7", (i5 * i2).to_string());

    EXPECT_EQ("0", (i5 * i1).to_string());

    EXPECT_EQ("21", (i5 * 3).to_string());
    EXPECT_EQ("21", (3 * i5).to_string());
    EXPECT_EQ("21", ("3" * i5).to_string());
    EXPECT_EQ("21", (i5 * "3").to_string());

    EXPECT_EQ("28", (i5 * 4).to_string());
    EXPECT_EQ("4", (4 * i2).to_string());
    EXPECT_EQ("4", ("4" * i2).to_string());
    EXPECT_EQ("4", ("0b100" * i2).to_string());

    short s{5};
    EXPECT_EQ("5", (s * i2).to_string());
    EXPECT_EQ("5", (5ll * i2).to_string());
    EXPECT_EQ("8", (4.0 * i6).to_string());
}

TEST(UnsignedIntegerTest, BitOperators) {
    Unsigned_integer<64> i1{6};
    Unsigned_integer<16> i2{3};
    Unsigned_integer<4> i3{3};
    EXPECT_EQ(2, i1 & i2);
    EXPECT_EQ(7, i1 | i2);
    EXPECT_EQ(5, i1 ^ i2);
    EXPECT_EQ(12, ~i3);

    EXPECT_EQ(7, i1 | 3);
    EXPECT_EQ(2, i1 & 3);
    EXPECT_EQ(5, i1 ^ 3);
    EXPECT_EQ(7, i1 | "3");
    EXPECT_EQ(2, i1 & "3");
    EXPECT_EQ(5, i1 ^ "3");
    EXPECT_EQ(7, 6 | i2);
    EXPECT_EQ(2, 6 & i2);
    EXPECT_EQ(5, 6 ^ i2);
    EXPECT_EQ(7, "6" | i2);
    EXPECT_EQ(2, "6" & i2);
    EXPECT_EQ(5, "6" ^ i2);

    EXPECT_EQ(48, i1 << 3);
    EXPECT_EQ(1, i1 >> 2);
    EXPECT_EQ(0, i1 >> 3);
    EXPECT_EQ(0, i1 >> 4);
}

TEST(UnsignedIntegerTest, CompoundBitOperators) {
    Unsigned_integer<64> i1{6};
    Unsigned_integer<16> i2{3};

    i1 &= i2;
    EXPECT_EQ(2, i1);
    i1 = 6;
    i1 &= 3;
    EXPECT_EQ(2, i1);
    i1 = 6;
    (i1 &= "3")++;
    EXPECT_EQ(3, i1);
    i1 = 6;

    i1 |= i2;
    EXPECT_EQ(7, i1);
    i1 = 6;
    i1 |= 3;
    EXPECT_EQ(7, i1);
    i1 = 6;
    (i1 |= "3")++;
    EXPECT_EQ(8, i1);
    i1 = 6;

    i1 ^= i2;
    EXPECT_EQ(5, i1);
    i1 = 6;
    i1 ^= 3;
    EXPECT_EQ(5, i1);
    i1 = 6;
    (i1 ^= "3")++;
    EXPECT_EQ(6, i1);
    i1 = 6;

    i1 <<= 3;
    EXPECT_EQ(48, i1);
    i1 = 6;
    i1 >>= 2;
    EXPECT_EQ(1, i1);
    i1 = 6;
    (i1 >>= 3)++;
    EXPECT_EQ(1, i1);
    i1 = 6;
}

TEST(UnsignedIntegerTest, OStreamOutput) {
    std::stringstream ss;
    Unsigned_integer<64> i{9999999};
    ss << i;
    EXPECT_EQ("9999999", ss.str());
    ss.str("");

    ss << std::hex << i;
    EXPECT_EQ("98967F", ss.str());
    ss.str("");

    ss << std::oct << i;
    EXPECT_EQ("46113177", ss.str());
    ss.str("");
}

TEST(UnsignedIntegerTest, IStreamInput) {
    std::stringstream ss;
    Unsigned_integer<64> i1{9999999};
    Unsigned_integer<64> i2{0};
    ss << i1;
    ss >> i2;
    EXPECT_EQ(9999999, i2);
    ss.clear();

    ss << "0x98967F";
    ss >> i2;
    EXPECT_EQ(9999999, i2);
    ss.clear();

    ss << "046113177";
    ss >> i2;
    EXPECT_EQ(9999999, i2);
    ss.clear();

    ss << "0xF";
    ss >> i2;
    EXPECT_EQ(15, i2);
    ss.clear();
}

TEST(UnsignedIntegerTest, Exponentiation) {
    Unsigned_integer<64> i1{1};
    Unsigned_integer<64> i2{0};
    Unsigned_integer<64> i3{4};
    Unsigned_integer<1024> i4{9999};
    EXPECT_EQ(1, i1.exp(i2));
    EXPECT_EQ(1, i1.exp(1));
    EXPECT_EQ(16, i3.exp(2));
    EXPECT_EQ(
        "9950122304230088282807169262820931544009761744243462256953938140772606"
        "6148386743841546236419103479078394269912554383014712195070531219955897"
        "146209915828840276319986866171890488126302980400122499500001",
        i4.exp(50).to_string());
    EXPECT_EQ(999700029999, i4.exp(3));
    EXPECT_EQ(1, i2.exp(i2));
}

TEST(UnsignedIntegerTest, Root) {
    Unsigned_integer<128> i1{16};
    Unsigned_integer<64> i2{7776};
    Unsigned_integer<54> i3{78126};
    Unsigned_integer<128> i4{"93795878551873643905024"};
    Unsigned_integer<128> i5{3404825447};
    Unsigned_integer<34> i6{15};
    Unsigned_integer<24> i7{23};
    Unsigned_integer<14> i8{1};
    Unsigned_integer<14> i9{0};
    Unsigned_integer<14> i10{143};

    EXPECT_EQ(4, i1.root(2));
    EXPECT_EQ(6, i2.root("5"));
    EXPECT_EQ(0, i9.root(10));
    EXPECT_EQ(1, i8.root(15));
    EXPECT_EQ(34, i4.root(i6));
    EXPECT_EQ(23, i5.root(7));
    EXPECT_EQ(23, i7.root(1));
    EXPECT_EQ(5, i3.root(7));
    EXPECT_EQ(11, i10.root(2));
    EXPECT_EQ(0, i10.root(0));
}
