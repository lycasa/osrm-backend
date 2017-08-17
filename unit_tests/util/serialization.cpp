#include "storage/serialization.hpp"

using namespace osrm::util;

#include <boost/functional/hash.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <vector>

BOOST_AUTO_TEST_SUITE(serialization_test)

using namespace osrm;
using namespace osrm::util;

BOOST_AUTO_TEST_CASE(pack_test)
{
    std::vector<bool> v = {0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1};

    BOOST_CHECK_EQUAL(osrm::storage::serialization::packBits(v, 0, 8), 0x2e);
    BOOST_CHECK_EQUAL(osrm::storage::serialization::packBits(v, 5, 7), 0x65);
    BOOST_CHECK_EQUAL(osrm::storage::serialization::packBits(v, 6, 8), 0x95);
    BOOST_CHECK_EQUAL(osrm::storage::serialization::packBits(v, 11, 1), 0x01);
}

BOOST_AUTO_TEST_CASE(unpack_test)
{
    std::vector<bool> v(14), expected = {0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1};

    osrm::storage::serialization::unpackBits(v, 0, 8, 0x2e);
    osrm::storage::serialization::unpackBits(v, 5, 7, 0x65);
    osrm::storage::serialization::unpackBits(v, 6, 8, 0x95);
    osrm::storage::serialization::unpackBits(v, 11, 1, 0x01);
    BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
