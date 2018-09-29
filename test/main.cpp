/**
 * @brief Test program main file
 * @author Wolfram Rösler
 * @date 2018-09-29
 */

#define BOOST_TEST_MODULE tester
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
