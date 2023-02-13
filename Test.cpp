//
// Created by Alex Shockley on 9/15/2020.
//

#include "catch.hpp"
#include "SString.h"
TEST_CASE("SString test file") {
    SString a = SString("Yes");
    SString b = SString();
    SString c = SString("Multi Words");

    SECTION("Testting get data function...") {
        CHECK(a.getData() == "Yes");
        CHECK(b.getData() == "\0");
        CHECK(c.getData() == "Multi Words");
    }
    SECTION("Testing .contains function") {
        CHECK(a.contains("yes"));
        CHECK(c.contains("Words"));
        CHECK(c.contains("Word"));

    }
    SECTION("Testing wordAt function") {
        CHECK(a.wordAt(0).getData() == "Yes");
        CHECK(c.wordAt(1).getData() == "Words");
        CHECK(c.wordAt(0).getData() == "Multi");

    }
    SECTION("Testing set string function") {
        b.setString("New String");
        c.setString("Single Word");
        CHECK(b.getData() == "New String");
        CHECK(c.getData() == "Single Word");
    }
    SECTION("Testing = operator") {
        b = c;
        CHECK(b.getData() == " Multi Words");
        b = a;
        CHECK(b.getData() == "Yes");
        CHECK(c.getData() == "Multi Words");

    }
    SECTION("Testing GetNumWords function") {
        b.setString("This string has 5 words");
        CHECK(b.getNumWords() == 5);
        CHECK(a.getNumWords() == 1);
        CHECK(c.getNumWords() == 2);
    }
}