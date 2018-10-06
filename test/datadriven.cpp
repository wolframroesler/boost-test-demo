/**
 * @brief Data-driven test example
 * @author Wolfram Rösler
 * @date 2018-10-06
 */

// Include the library we want to test
#include <base64.h>

// Include the test program's global functions
#include "mytest.h"

// Include the boost::test framework
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

// Enable the "s" postfix to create a std::string literal
using namespace std::literals;

// Define the name of this test suite
BOOST_AUTO_TEST_SUITE(datadriven)

// Plain text strings
const auto plain = {
    ""s,
    std::string("",1),
    "  "s,
    "Hello World"s,
    "\x01\x02\x02"s,
};

// The corresponding base 64-encoded strings
const auto encoded = {
    "",
    "AA==",
    "ICA=",
    "SGVsbG8gV29ybGQ=",
    "AQIC",
};

/*
* Test base-64 encoding with the sample data
*/
BOOST_DATA_TEST_CASE(enc,
    boost::unit_test::data::make(plain) ^ encoded ,
    p,e) {
    BOOST_TEST(base64::encode(p)==e);
}

/*
 * Test base-64 decoding with the sample data
 */
BOOST_DATA_TEST_CASE(dec,
    boost::unit_test::data::make(plain) ^ encoded ,
    p,e) {
    BOOST_TEST(base64::decode(e)==p);
}

// The following line must be at the end of the file
BOOST_AUTO_TEST_SUITE_END()
