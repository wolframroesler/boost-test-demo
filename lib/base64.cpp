/*
 * @brief base64 encoder/decoder
 * @author Wolfram Rösler
 * @date 2018-09-29
 */

#include <base64.h>

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>

using it_binary_t = boost::archive::iterators::transform_width<
    boost::archive::iterators::binary_from_base64<
        boost::archive::iterators::remove_whitespace<
            std::string::const_iterator
        >
    >,8,6
>;

using it_base64_t = boost::archive::iterators::insert_linebreaks<
    boost::archive::iterators::base64_from_binary<
        boost::archive::iterators::transform_width<
            std::string::const_iterator,6,8
        >
    >,72
>;

namespace base64 {
    /**
     * Base-64 encoder.
     *
     * @param val The data to encode (may be binary).
     *
     * @returns the parameter string in Base-64 encoding.
     *
     * @see base64::decode
     * @see base64::encodeSHA256
     */
    std::string encode(const std::string& val) {
        const auto writePaddChars = (3 - val.length() % 3) % 3;
        std::string ret(it_base64_t(val.begin()),it_base64_t(val.end()));
        ret.append(writePaddChars,'=');
        return ret;
    }

    /**
     * Base-64 decoder.
     *
     * @param val The Base-64 string to decode.
     *
     * @returns the decoded parameter string.
     *
     * @throws std::exception if val contains illegal characters.
     *
     * @see base64::encode
     */
    std::string decode(const std::string& val) {
        std::string base64 = val;
        const auto paddChars = count(base64.begin(), base64.end(), '=');
        std::replace(base64.begin(),base64.end(),'=','A');
        std::string ret(it_binary_t(base64.begin()), it_binary_t(base64.end()));
        ret.erase(ret.end()-paddChars,ret.end());
        return ret;
    }
}

// Boost magic based on http://stackoverflow.com/a/10973348
