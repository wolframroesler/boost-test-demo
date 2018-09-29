/**
 * @brief Test program main file
 * @author Wolfram Rösler
 * @date 2018-09-29
 */

#include <fstream>
#include <iomanip>
#include "mytest.h"

// The following defines that this file will create the
// test program's main function.
#define BOOST_TEST_MODULE mytest

// Include the boost::test framework
#include <boost/test/unit_test.hpp>

/**
 * Global fixture
 */
namespace {
    class GFx {
    public:
        // The following is executed before running the first test suite.
        GFx() {}

        // The following is executed after completing the last test suite.
        ~GFx() {}
    };
    BOOST_GLOBAL_FIXTURE(GFx);
}

/**
 * Create a string that contains random binary data.
 *
 * @param size The number of random bytes to create.
 *
 * @returns The specified number of random bytes.
 *
 * @bug Windows people need to rewrite this function.
 */
std::string RandomData(size_t size) {
    std::string ret;
    auto ifs = std::ifstream("/dev/urandom",std::ios::binary);
    auto isi = std::istream_iterator<char>(ifs);
    std::copy_n(isi,size,std::insert_iterator<std::string>(ret,ret.begin()));
    return ret;
}
