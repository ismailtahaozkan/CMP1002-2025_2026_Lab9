# Grading Rubric — Dynamic Memory Management & Static Classes

**Total: 100 points**

| # | Test Group | Points | What Is Tested |
|---|---|---|---|
| 1 | Basic Construction & Destruction | 20 | Constructor allocates memory, sets capacity/size, isEmpty works, multiple coexisting objects |
| 2 | Add & Get Operations | 20 | add() within capacity, get() returns correct values, add() fails when full, get() returns -1 for out-of-bounds and empty arrays |
| 3 | RemoveLast | 10 | removeLast() decreases size, returns false on empty, add-after-remove works correctly |
| 4 | Copy Constructor (Deep Copy) | 15 | Copied array has same elements, modifying copy doesn't affect original, copying empty array works |
| 5 | Copy Assignment Operator | 15 | Assignment copies correctly, self-assignment is safe, assignment creates independent copy |
| 6 | Tracker (Static Class) | 20 | Object creation/destruction tracked, multiple objects tracked, copy constructor increments count, assignment does NOT change count, resetCount works |

## Point Distribution Detail

### Group 1 — Construction & Destruction (20 pts)
- Correct capacity and zero size on construction: 8 pts
- Capacity-1 edge case: 4 pts
- Multiple coexisting objects: 8 pts

### Group 2 — Add & Get (20 pts)
- add() returns true when space available: 5 pts
- get() returns correct values: 5 pts
- add() returns false when full: 5 pts
- get() returns -1 for invalid indices: 5 pts

### Group 3 — RemoveLast (10 pts)
- removeLast() decreases size: 4 pts
- removeLast() on empty returns false: 3 pts
- Add after remove works: 3 pts

### Group 4 — Copy Constructor (15 pts)
- Elements copied correctly: 5 pts
- Deep copy independence: 5 pts
- Empty array copy: 5 pts

### Group 5 — Copy Assignment (15 pts)
- Elements assigned correctly: 5 pts
- Self-assignment safe: 5 pts
- Independent after assignment: 5 pts

### Group 6 — Tracker Static Class (20 pts)
- Creation/destruction count: 5 pts
- Multiple object tracking: 5 pts
- Copy constructor increments: 5 pts
- Assignment does NOT increment: 5 pts
