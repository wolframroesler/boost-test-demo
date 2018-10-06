/**
 * @brief Test suite for the Base-64 library
 * @author Wolfram Rösler
 * @date 2018-09-29
 */

// Include the library we want to test
#include <base64.h>

// Include the test program's global functions
#include "mytest.h"

// Include the boost::test framework
#include <boost/test/unit_test.hpp>

// Define the name of this test suite
BOOST_AUTO_TEST_SUITE(base64)

// Test fixture
struct Fx {

    // Set-up procedure (invoked before every test case)
    Fx() {
    }

    // Tear-down procedure (invoked after every test case)
    ~Fx() {
    }
};

/*
 * Test base-64 encoding using explicit examples.
 */
BOOST_FIXTURE_TEST_CASE(enc,Fx) {
    BOOST_TEST(base64::encode("")                   =="");
    BOOST_TEST(base64::encode(std::string("",1))    =="AA==");
    BOOST_TEST(base64::encode("  ")                 =="ICA=");
    BOOST_TEST(base64::encode("Hello World")        =="SGVsbG8gV29ybGQ=");
    BOOST_TEST(base64::encode("\x01\x02\x03")       =="AQID");
}

/*
 * Test base-64 decoding using explicit examples.
 */
BOOST_FIXTURE_TEST_CASE(dec,Fx) {
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
BOOST_FIXTURE_TEST_CASE(both,Fx) {
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
