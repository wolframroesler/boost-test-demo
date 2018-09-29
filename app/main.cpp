/**
 * @brief Base-64 encoder/decoder application
 * @author Wolfram Rösler
 * @date 2018-09-29
 */

#include <iostream>
#include <base64.h>

int main(int argc,char** argv) {

    try {
        if (argc==2) {

            // Encode
            std::cout << base64::encode(argv[1]) << std::endl;
            return EXIT_SUCCESS;

        } else if (argc==3 && !strcmp(argv[1],"-d")) {

            // Decode
            std::cout << base64::decode(argv[2]) << std::endl;
            return EXIT_SUCCESS;

        } else {

            // Error
            std::cerr << "Usage: " << argv[0] << " [ -d ] String" << std::endl;
            return EXIT_FAILURE;
        }

    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
