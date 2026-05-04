// ============================================================
// Test File: Dynamic Memory Management & Static Classes
// Uses Catch2 (single-header amalgamated)
// ============================================================

// Redirect student's main() to avoid conflict
#define main student_main
#include "MainProgram.cpp"
#undef main

#include "catch_amalgamated.hpp"

// ============================================================
// Helper: reset Tracker before each test
// ============================================================

struct TrackerReset {
    TrackerReset() { Tracker::resetCount(); }
    ~TrackerReset() { Tracker::resetCount(); }
};

// ============================================================
// TEST GROUP 1: Basic Construction & Destruction (20 pts)
// ============================================================

TEST_CASE("Constructor allocates and initializes correctly", "[construction]") {
    TrackerReset guard;

    SECTION("New IntArray has correct capacity and zero size") {
        IntArray arr(10);
        REQUIRE(arr.getCapacity() == 10);
        REQUIRE(arr.size() == 0);
        REQUIRE(arr.isEmpty() == true);
    }

    SECTION("Constructor with capacity 1") {
        IntArray arr(1);
        REQUIRE(arr.getCapacity() == 1);
        REQUIRE(arr.size() == 0);
    }

    SECTION("Multiple objects can coexist") {
        IntArray a(3);
        IntArray b(5);
        IntArray c(7);
        REQUIRE(a.getCapacity() == 3);
        REQUIRE(b.getCapacity() == 5);
        REQUIRE(c.getCapacity() == 7);
    }
}

// ============================================================
// TEST GROUP 2: Add & Get Operations (20 pts)
// ============================================================

TEST_CASE("Add and Get work correctly", "[add_get]") {
    TrackerReset guard;

    SECTION("Adding within capacity succeeds") {
        IntArray arr(5);
        REQUIRE(arr.add(10) == true);
        REQUIRE(arr.add(20) == true);
        REQUIRE(arr.add(30) == true);
        REQUIRE(arr.size() == 3);
    }

    SECTION("Get returns correct values") {
        IntArray arr(5);
        arr.add(100);
        arr.add(200);
        arr.add(300);
        REQUIRE(arr.get(0) == 100);
        REQUIRE(arr.get(1) == 200);
        REQUIRE(arr.get(2) == 300);
    }

    SECTION("Add fails when full") {
        IntArray arr(2);
        REQUIRE(arr.add(1) == true);
        REQUIRE(arr.add(2) == true);
        REQUIRE(arr.add(3) == false);
        REQUIRE(arr.size() == 2);
    }

    SECTION("Get returns -1 for out-of-bounds index") {
        IntArray arr(5);
        arr.add(42);
        REQUIRE(arr.get(-1) == -1);
        REQUIRE(arr.get(1) == -1);
        REQUIRE(arr.get(100) == -1);
    }

    SECTION("Get returns -1 on empty array") {
        IntArray arr(5);
        REQUIRE(arr.get(0) == -1);
    }
}

// ============================================================
// TEST GROUP 3: RemoveLast (10 pts)
// ============================================================

TEST_CASE("RemoveLast works correctly", "[remove]") {
    TrackerReset guard;

    SECTION("RemoveLast decreases size") {
        IntArray arr(5);
        arr.add(10);
        arr.add(20);
        REQUIRE(arr.removeLast() == true);
        REQUIRE(arr.size() == 1);
        REQUIRE(arr.get(0) == 10);
    }

    SECTION("RemoveLast on empty array returns false") {
        IntArray arr(5);
        REQUIRE(arr.removeLast() == false);
    }

    SECTION("RemoveLast then add overwrites correctly") {
        IntArray arr(3);
        arr.add(10);
        arr.add(20);
        arr.removeLast();
        arr.add(99);
        REQUIRE(arr.size() == 2);
        REQUIRE(arr.get(1) == 99);
    }
}

// ============================================================
// TEST GROUP 4: Copy Constructor (15 pts)
// ============================================================

TEST_CASE("Copy constructor creates deep copy", "[copy_ctor]") {
    TrackerReset guard;

    SECTION("Copied array has same elements") {
        IntArray original(5);
        original.add(1);
        original.add(2);
        original.add(3);

        IntArray copy(original);
        REQUIRE(copy.size() == 3);
        REQUIRE(copy.getCapacity() == 5);
        REQUIRE(copy.get(0) == 1);
        REQUIRE(copy.get(1) == 2);
        REQUIRE(copy.get(2) == 3);
    }

    SECTION("Modifying copy does not affect original") {
        IntArray original(5);
        original.add(10);
        original.add(20);

        IntArray copy(original);
        copy.add(30);
        copy.removeLast();
        copy.removeLast();

        // Original unchanged
        REQUIRE(original.size() == 2);
        REQUIRE(original.get(0) == 10);
        REQUIRE(original.get(1) == 20);
    }

    SECTION("Copy of empty array works") {
        IntArray original(3);
        IntArray copy(original);
        REQUIRE(copy.size() == 0);
        REQUIRE(copy.getCapacity() == 3);
        REQUIRE(copy.isEmpty() == true);
    }
}

// ============================================================
// TEST GROUP 5: Copy Assignment Operator (15 pts)
// ============================================================

TEST_CASE("Copy assignment operator works correctly", "[copy_assign]") {
    TrackerReset guard;

    SECTION("Assignment copies elements correctly") {
        IntArray a(5);
        a.add(10);
        a.add(20);

        IntArray b(3);
        b.add(99);

        b = a;
        REQUIRE(b.size() == 2);
        REQUIRE(b.getCapacity() == 5);
        REQUIRE(b.get(0) == 10);
        REQUIRE(b.get(1) == 20);
    }

    SECTION("Self-assignment is safe") {
        IntArray a(5);
        a.add(42);
        a = a;
        REQUIRE(a.size() == 1);
        REQUIRE(a.get(0) == 42);
    }

    SECTION("Assignment creates independent copy") {
        IntArray a(4);
        a.add(1);
        a.add(2);

        IntArray b(2);
        b = a;
        b.add(3);

        // a is unchanged
        REQUIRE(a.size() == 2);
        REQUIRE(b.size() == 3);
    }
}

// ============================================================
// TEST GROUP 6: Tracker (Static Class) (20 pts)
// ============================================================

TEST_CASE("Tracker counts objects correctly", "[tracker]") {
    TrackerReset guard;

    SECTION("Single object creation and destruction") {
        REQUIRE(Tracker::getActiveCount() == 0);
        {
            IntArray arr(5);
            REQUIRE(Tracker::getActiveCount() == 1);
        }
        REQUIRE(Tracker::getActiveCount() == 0);
    }

    SECTION("Multiple objects tracked") {
        REQUIRE(Tracker::getActiveCount() == 0);
        IntArray a(3);
        REQUIRE(Tracker::getActiveCount() == 1);
        IntArray b(3);
        REQUIRE(Tracker::getActiveCount() == 2);
        {
            IntArray c(3);
            REQUIRE(Tracker::getActiveCount() == 3);
        }
        REQUIRE(Tracker::getActiveCount() == 2);
    }

    SECTION("Copy constructor increments count") {
        IntArray a(5);
        a.add(1);
        REQUIRE(Tracker::getActiveCount() == 1);
        {
            IntArray b(a);
            REQUIRE(Tracker::getActiveCount() == 2);
        }
        REQUIRE(Tracker::getActiveCount() == 1);
    }

    SECTION("Copy assignment does NOT change count") {
        IntArray a(3);
        IntArray b(3);
        REQUIRE(Tracker::getActiveCount() == 2);
        b = a;
        REQUIRE(Tracker::getActiveCount() == 2);
    }

    SECTION("resetCount works") {
        IntArray a(3);
        Tracker::resetCount();
        REQUIRE(Tracker::getActiveCount() == 0);
    }
}
