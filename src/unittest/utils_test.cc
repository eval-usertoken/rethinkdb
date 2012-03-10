#include "unittest/gtest.hpp"

#include "utils.hpp"
#include "arch/address.hpp"
#include "arch/runtime/runtime.hpp"
#include "unittest/unittest_utils.hpp"

namespace unittest {

TEST(UtilsTest, BeginsWithMinus) {
    char test1[] = "    -foo";
    char test2[] = "-bar";
    char test3[] = "    baz";
    char test4[] = "qux-";
    char test5[] = "";
    ASSERT_TRUE(begins_with_minus(test1));
    ASSERT_TRUE(begins_with_minus(test2));
    ASSERT_FALSE(begins_with_minus(test3));
    ASSERT_FALSE(begins_with_minus(test4));
    ASSERT_FALSE(begins_with_minus(test5));
}

TEST(UtilsTest, StrtofooStrict) {
    char test1[] = "-1024";
    char test2[] = "1024";
    char test3[] = "102834728273347433844";
    char test4[] = "123lskdjf";

    const char *end;

    ASSERT_EQ(0, strtoul_strict(test1, &end, 10));
    ASSERT_EQ(1024, strtoul_strict(test2, &end, 10));
    ASSERT_EQ(0, strtoul_strict(test3, &end, 10));
    ASSERT_EQ(123, strtoul_strict(test4, &end, 10));
    ASSERT_FALSE(strncmp("lskdjf", end, 6));

    ASSERT_EQ(0, strtoull_strict(test1, &end, 10));
    ASSERT_EQ(1024, strtoull_strict(test2, &end, 10));
    ASSERT_EQ(0, strtoull_strict(test3, &end, 10));
    ASSERT_EQ(123, strtoull_strict(test4, &end, 10));
    ASSERT_FALSE(strncmp("lskdjf", end, 6));
}

TEST(UtilsTest, PreciseTime) {
    precise_time_t precise_time;
    precise_time.tm_sec = 4;
    precise_time.tm_min = 4;
    precise_time.tm_mday = 4;
    precise_time.tm_hour = 4;
    precise_time.tm_mon = 4;
    precise_time.tm_year = 110;
    precise_time.tm_wday = 4;
    precise_time.tm_yday = 243;
    precise_time.tm_isdst = -1;
    precise_time.ns = 102948;

    char buf[100];
    format_precise_time(precise_time, buf, 100);

    EXPECT_EQ(std::string("2010-05-04T04:04:04.000102"), std::string(buf, buf + strnlen(buf, 100)));

    struct timespec zerotime;
    zerotime.tv_sec = 0;
    zerotime.tv_nsec = 0;
    set_precise_time_offset(zerotime, 0);

    struct timespec timespec;
    timespec.tv_sec = 1203731445;
    timespec.tv_nsec = 1203745;
    precise_time = get_absolute_time(timespec);

    format_precise_time(precise_time, buf, 100);

    EXPECT_EQ(std::string("2008-02-23T01:50:45.001203"), std::string(buf, buf + strnlen(buf, 100)));
    EXPECT_EQ(format_precise_time(precise_time), std::string(buf, buf + strnlen(buf, 100)));
    initialize_precise_time();
}

TEST(UtilsTest, SizedStrcmp)
{
    char test1[] = "foobarbazn\nqux";
    char test2[] = "foobarbazn\nquxr";
    char test3[] = "hello world";

    ASSERT_EQ(-1, sized_strcmp(test1, 14, test2, 15));
    ASSERT_EQ(1, sized_strcmp(test2, 15, test1, 14));
    ASSERT_EQ(0, sized_strcmp(test1, 10, test1, 10));
    ASSERT_EQ(0, sized_strcmp(test1, 14, test1, 14));
    ASSERT_EQ(0, sized_strcmp(test1, 0, test1, 0));
    ASSERT_NE(0, sized_strcmp(test3, 11, test1, 14));
}

/* This doesn't quite belong in `utils_test.cc`, but I don't want to create a
new file just for it. */

void run_ip_address_test() {
    ip_address_t test("111.112.113.114");
    EXPECT_EQ("111.112.113.114", test.as_dotted_decimal());
}

TEST(UtilsTest, IPAddress)
{
    // Since ip_address_t may block, it requires a thread_pool_t to exist
    run_in_thread_pool(&run_ip_address_test);
}

}  // namespace unittest
