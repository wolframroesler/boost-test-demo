/**
 * @brief Sample test suite
 * @author Wolfram Rösler
 * @date 2018-09-29
 */

#include <fstream>
#include <iomanip>
#include <base64.h>

// Include the boost::test framework
#include <boost/test/unit_test.hpp>

namespace {
    /**
     * Create random binary data.
     *
     * @param size The number of random bytes to create.
     * @param base64 If true, base64s the result. If false, returns binary data.
     *
     * @returns This number of random bytes (before base64).
     */
    std::string RandomData(size_t size) {
        std::string ret;
        std::ifstream ifs("/dev/urandom",std::ios::binary);
        std::istream_iterator<char> isi(ifs);
        std::copy_n(isi,size,std::insert_iterator<std::string>(ret,ret.begin()));
        return ret;
    }
}

// Define the name of this test suite
BOOST_AUTO_TEST_SUITE(base64)

// To verify the explicit examples, use the base64 command, for example:
//
//      $ echo -n "Hello World" | base64
//      SGVsbG8gV29ybGQ=
//
//      $ echo -n "SGVsbG8gV29ybGQ=" | base64 -d
//      Hello World

/*
 * Test base-64 encoding using explicit examples.
 */
BOOST_AUTO_TEST_CASE(enc) {
    BOOST_TEST(base64::encode("")                   =="");
    BOOST_TEST(base64::encode(std::string("",1))    =="AA==");
    BOOST_TEST(base64::encode("  ")                 =="ICA=");
    BOOST_TEST(base64::encode("Hello World")        =="SGVsbG8gV29ybGQ=");
    BOOST_TEST(base64::encode("\x01\x02\x03")       =="AQID");
}

/*
 * Test base-64 decoding using explicit examples.
 */
BOOST_AUTO_TEST_CASE(dec) {
    BOOST_TEST(base64::decode("")                   =="");
    BOOST_TEST(base64::decode("AA==")               ==std::string("",1));
    BOOST_TEST(base64::decode("ICA=")               =="  ");
    BOOST_TEST(base64::decode("SGVsbG8gV29ybGQ=")   =="Hello World");
    BOOST_TEST(base64::decode("AQID")               =="\x01\x02\x03");

    // Space is not a legal character for base-64 encoded strings.
    BOOST_CHECK_THROW(base64::decode(" "),std::exception);
}

/*
 * Test base-64 encoding and decoding with random strings.
 */
BOOST_AUTO_TEST_CASE(both) {
    for(auto size : { 1, 100, 1000, 10'000 }) {
        for(auto _=0;_<10;++_) {
            // Make a random binary string of this size
            const auto str = RandomData(size);

            // Encode it, then decode it
            const auto enc = base64::encode(str);
            const auto dec = base64::decode(enc);

            // Compare
            BOOST_TEST(dec==str,"String size: " + std::to_string(str.size()));
        }
    }
}

// The following line must be at the end of the file
BOOST_AUTO_TEST_SUITE_END()
