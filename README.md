# Boost.Test Demonstration

This project demonstrates how to make unit test programs with the Boost.Test framework. It contains three things:

* A library that contains base-64 encoding and decoding functions (in directory `lib`)
* A simple application that invokes these functions (in directory `app`)
* A unit test program to test the base-64 functions (in directory `test`)

## How to build

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## How to run

### Run the sample program

```
$ cd build

$ ./myapp
Usage: ./myapp [ -d ] String

$ ./myapp "Hello World"
SGVsbG8gV29ybGQ=

$ ./myapp -d SGVsbG8gV29ybGQ=
Hello World
```

### Run the test program

```
$ ./mytest
Running 3 test cases...

*** No errors detected
```

With a progress bar:

```
$ ./mytest -p
Running 3 test cases...

0%   10   20   30   40   50   60   70   80   90   100%
|----|----|----|----|----|----|----|----|----|----|
***************************************************

*** No errors detected
```

Just a single test suite:

```
$ ./mytest -t base64
Running 3 test cases...

*** No errors detected
```

Just a single test case:

```
$ ./mytest -t base64/enc
Running 1 test case...

*** No errors detected
```

With detailed output:

```
$ ./mytest -t base64/enc -l all
Running 1 test case...
Entering test module "mytest"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:33: Entering test suite "base64"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:46: Entering test case "enc"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:47: info: check base64::encode("") =="" has passed
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:48: info: check base64::encode(std::string("",1)) =="AA==" has passed
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:49: info: check base64::encode("  ") =="ICA=" has passed
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:50: info: check base64::encode("Hello World") =="SGVsbG8gV29ybGQ=" has passed
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:51: info: check base64::encode("\x01\x02\x03") =="AQID" has passed
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:46: Leaving test case "enc"; testing time: 236us
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:33: Leaving test suite "base64"; testing time: 274us
Leaving test module "mytest"; testing time: 312us

*** No errors detected
```

... and of course you can combine these.

More command line options:

* ./mytest --help
* http://www.boost.org/doc/libs/1_68_0/libs/test/doc/html/boost_test/runtime_config/summary.html

### Make integration

```
$ cd build
$ make test
Running tests...
Test project /Users/wolfram/Nextcloud/src/boost-test-demo/build
    Start 1: mytest
1/1 Test #1: mytest ...........................   Passed    0.35 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.36 sec
```

To show the details (e. g. when a test failed):

```
$ cat Testing/Temporary/LastTest.log
Start testing: Sep 29 19:25 CEST
----------------------------------------------------------
1/1 Testing: mytest
1/1 Test: mytest
Command: "/Users/wolfram/Nextcloud/src/boost-test-demo/build/mytest" "--random" "--log_level=test_suite"
Directory: /Users/wolfram/Nextcloud/src/boost-test-demo/build
"mytest" start time: Sep 29 19:25 CEST
Output:
----------------------------------------------------------
Running 3 test cases...
Test cases order is shuffled using seed: 1538257954
Entering test module "mytest"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:33: Entering test suite "base64"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:71: Entering test case "both"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:71: Leaving test case "both"; testing time: 335651us
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:57: Entering test case "dec"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:57: Leaving test case "dec"; testing time: 148us
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:46: Entering test case "enc"
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:46: Leaving test case "enc"; testing time: 50us
/Users/wolfram/Nextcloud/src/boost-test-demo/test/base64.cpp:33: Leaving test suite "base64"; testing time: 335937us
Leaving test module "mytest"; testing time: 335956us

*** No errors detected

<end of output>
Test time =   0.35 sec
----------------------------------------------------------
Test Passed.
"mytest" end time: Sep 29 19:25 CEST
"mytest" time elapsed: 00:00:00
----------------------------------------------------------

End testing: Sep 29 19:25 CEST
```

## How to extend

To add additional test cases to a test suite, add additional `BOOST_FIXTURE_TEST_CASE` blocks like the one in `base64.cpp`.

To add additional test suites, copy sample.cpp. Set `BOOST_AUTO_TEST_SUITE` to the name of the test suite (usually identical to the file name). Don't forget to add the new file to `add_executable` in the cmake file.

To define code to run before/after all test suites, modify the ctor/dtor of the `GFx` class in main.cpp.
