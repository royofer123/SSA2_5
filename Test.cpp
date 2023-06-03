#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("Initialization of MagicalContainer") {
    // Test case to verify the initialization of MagicalContainer
    MagicalContainer mc;
    CHECK(mc.size() == 0);
}

TEST_CASE("Adding and removing elements from MagicalContainer (+removing an existing element doesn't throw)") {
    // Test case to add and remove elements from MagicalContainer
    MagicalContainer mc;
    mc.addElement(10);
    CHECK(mc.size() == 1);

    mc.addElement(20);
    CHECK(mc.size() == 2);

    mc.addElement(30);
    CHECK(mc.size() == 3);

    CHECK_NOTHROW(mc.removeElement(10));
    CHECK(mc.size() == 2);

    CHECK_NOTHROW(mc.removeElement(30));
    CHECK(mc.size() == 1);

    mc.addElement(40);
    CHECK(mc.size() == 2);

    CHECK_NOTHROW(mc.removeElement(20));
    CHECK(mc.size() == 1);

    CHECK_NOTHROW(mc.removeElement(40));
    CHECK(mc.size() == 0);
}

TEST_CASE("Erasing a non-existing member throws an exception") {
    // Test case to verify that removing a non-existing element throws an exception
    MagicalContainer mc;
    mc.addElement(15);
    mc.addElement(25);
    mc.addElement(35);
    CHECK_THROWS(mc.removeElement(45));
    CHECK_THROWS(mc.removeElement(55));
}

TEST_CASE("Adding duplicate elements ignores the duplicates") {
    // Test case to verify that adding duplicate elements ignores the duplicates
    MagicalContainer mc;
    mc.addElement(10);
    CHECK(mc.size() == 1);

    mc.addElement(20);
    CHECK(mc.size() == 2);

    mc.addElement(30);
    CHECK(mc.size() == 3);

    mc.addElement(20);
    CHECK(mc.size() == 3);

    mc.addElement(50);
    CHECK(mc.size() == 4);
}

TEST_CASE("Test each iterator individually") {
    // Test case to individually test each iterator
    MagicalContainer mc;

    mc.addElement(3);
    mc.addElement(6);
    mc.addElement(9);
    mc.addElement(12);
    mc.addElement(15);
    mc.addElement(18);

    SUBCASE("PrimeIterator") {
        // Subcase for testing PrimeIterator
        MagicalContainer::PrimeIterator it = MagicalContainer::PrimeIterator(mc).begin();
        SUBCASE("Testing increment operator and dereference operator") {
            // Subcase to test the functionality of PrimeIterator's increment operator (++) and dereference operator (*)
            CHECK(*it == 3);
            ++it;
            CHECK(*it == 5);
            ++it;
            CHECK(*it == 7);
            ++it;
            CHECK(*it == 11);
            ++it;
            CHECK(*it == 13);
            ++it;
            CHECK(*it == 17);
        }
        SUBCASE("Testing iterator comparison") {
            // Subcase to test the comparison of two PrimeIterators
            MagicalContainer::PrimeIterator it2 = MagicalContainer::PrimeIterator(mc).begin();
            ++it2;
            ++it2;
            ++it2;
            ++it2;

            CHECK_FALSE(it2 > it);
            CHECK(it > it2);

            ++it2;

            CHECK(it == it2);
        }
    }

    SUBCASE("SideCrossIterator") {
        // Subcase for testing SideCrossIterator
        MagicalContainer::SideCrossIterator it = MagicalContainer::SideCrossIterator(mc).begin();
        SUBCASE("Testing increment operator and dereference operator") {
            // Subcase to test the functionality of SideCrossIterator's increment operator (++) and dereference operator (*)
            CHECK(*it == 3);
            ++it;
            CHECK(*it == 18);
            ++it;
            CHECK(*it == 6);
            ++it;
            CHECK(*it == 15);
            ++it;
            CHECK(*it == 9);
            ++it;
            CHECK(*it == 12);
        }
        SUBCASE("Testing iterator comparison") {
            // Subcase to test the comparison of two SideCrossIterators
            MagicalContainer::SideCrossIterator it2 = MagicalContainer::SideCrossIterator(mc).begin();
            ++it2;
            ++it2;
            ++it2;
            ++it2;

            CHECK_FALSE(it2 > it);
            CHECK(it > it2);

            ++it2;

            CHECK(it == it2);
        }
    }

    SUBCASE("AscendingIterator") {
        // Subcase for testing AscendingIterator
        MagicalContainer::AscendingIterator it = MagicalContainer::AscendingIterator(mc).begin();
        SUBCASE("Testing increment operator and dereference operator") {
            // Subcase to test the functionality of AscendingIterator's increment operator (++) and dereference operator (*)
            CHECK(*it == 3);
            ++it;
            CHECK(*it == 6);
            ++it;
            CHECK(*it == 9);
            ++it;
            CHECK(*it == 12);
            ++it;
            CHECK(*it == 15);
            ++it;
            CHECK(*it == 18);
        }
        SUBCASE("Testing iterator comparison") {
            // Subcase to test the comparison of two AscendingIterators
            MagicalContainer::AscendingIterator it2 = MagicalContainer::AscendingIterator(mc).begin();
            ++it2;
            ++it2;
            ++it2;
            ++it2;

            CHECK_FALSE(it2 > it);
            CHECK(it > it2);

            ++it2;

            CHECK(it == it2);
        }
    }
}

TEST_CASE("Test comparing iterators pointing to different containers throws") {
    // Test case to verify that comparing iterators pointing to different containers throws an exception
    MagicalContainer mc1, mc2;

    // Fill containers with some data
    for(int i = 1; i <= 100; i++) {
        mc1.addElement(i);
        mc2.addElement(i * 2);
    }

    SUBCASE("AscendingIterator") {
        // Subcase for testing AscendingIterator
        MagicalContainer::AscendingIterator it1 = MagicalContainer::AscendingIterator(mc1).begin();
        MagicalContainer::AscendingIterator endit1 = MagicalContainer::AscendingIterator(mc1).begin();
        MagicalContainer::AscendingIterator it2 = MagicalContainer::AscendingIterator(mc2).begin();
        MagicalContainer::AscendingIterator endit2 = MagicalContainer::AscendingIterator(mc2).begin();

        while(it1 != endit1 && it2 != endit2) {
            CHECK_THROWS((void)(it1 == it2));
            CHECK_THROWS((void)(it1 > it2));
            CHECK_THROWS((void)(it1 < it2));
            CHECK_THROWS((void)(it1 != it2));
            ++it1;
            ++it2;
        }
    }

    SUBCASE("SideCrossIterator") {
        // Subcase for testing SideCrossIterator
        MagicalContainer::SideCrossIterator it1 = MagicalContainer::SideCrossIterator(mc1).begin();
        MagicalContainer::SideCrossIterator endit1 = MagicalContainer::SideCrossIterator(mc1).begin();
        MagicalContainer::SideCrossIterator it2 = MagicalContainer::SideCrossIterator(mc2).begin();
        MagicalContainer::SideCrossIterator endit2 = MagicalContainer::SideCrossIterator(mc2).begin();

        while(it1 != endit1 && it2 != endit2) {
            CHECK_THROWS((void)(it1 == it2));
            CHECK_THROWS((void)(it1 > it2));
            CHECK_THROWS((void)(it1 < it2));
            CHECK_THROWS((void)(it1 != it2));
            ++it1;
            ++it2;
        }
    }

    SUBCASE("PrimeIterator") {
        // Subcase for testing PrimeIterator
        MagicalContainer::PrimeIterator it1 = MagicalContainer::PrimeIterator(mc1).begin();
        MagicalContainer::PrimeIterator endit1 = MagicalContainer::PrimeIterator(mc1).begin();
        MagicalContainer::PrimeIterator it2 = MagicalContainer::PrimeIterator(mc2).begin();
        MagicalContainer::PrimeIterator endit2 = MagicalContainer::PrimeIterator(mc2).begin();

        while(it1 != endit1 && it2 != endit2) {
            CHECK_THROWS((void)(it1 == it2));
            CHECK_THROWS((void)(it1 > it2));
            CHECK_THROWS((void)(it1 < it2));
            CHECK_THROWS((void)(it1 != it2));
            ++it1;
            ++it2;
        }
    }
}
