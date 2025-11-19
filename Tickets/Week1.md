# **ATLAS – Week 1 Sprint (Tech Lead Breakdown)**

**Sprint Goal:**
Set up the foundational repo structure and create the first “hello world” C++ engine capable of reading data and calculating basic statistics.

**Sprint Duration:** 7 days

**Team:** Solo (you, but structured like a real team sprint)

---

## **Ticket 3 – BASIC CSV DATA LOADER**

* **ID:** ATLAS-003
* **Priority:** High
* **Type:** Story
* **Description:**
  Implement a simple C++ CSV loader to read historical price data into a vector of structs.
* **Acceptance Criteria:**

  * Can read a sample CSV (Date, Open, High, Low, Close, Volume)
  * Data stored in `std::vector<struct Bar>`
  * Print first 5 rows to console for verification

---

## **Ticket 4 – STATISTICS UTILITIES**

* **ID:** ATLAS-004
* **Priority:** High
* **Type:** Story
* **Description:**
  Implement basic statistical functions: `mean()`, `stddev()`, `correlation()`. These will serve as building blocks for future factor calculations.
* **Acceptance Criteria:**

  * `Statistics.hpp` and `Statistics.cpp` exist in `cpp/include` and `cpp/src`
  * Unit tests using GoogleTest cover all functions
  * Functions return correct values on sample dataset

---

## **Ticket 5 – UNIT TESTS SETUP**

* **ID:** ATLAS-005
* **Priority:** High
* **Type:** Task
* **Description:**
  Integrate GoogleTest framework for C++ and create initial test suite.
* **Acceptance Criteria:**

  * `cpp/tests/CMakeLists.txt` configured
  * Test executable compiles
  * Tests for `mean`, `stddev`, and CSV loader pass

---

## **Ticket 6 – COMMITTING & DOCUMENTATION**

* **ID:** ATLAS-006
* **Priority:** Medium
* **Type:** Task
* **Description:**
  Commit all code, add clear README sections, and document how to build/run the engine.
* **Acceptance Criteria:**

  * README explains:

    * Folder structure
    * Build instructions (`cmake -B build && cmake --build build`)
    * Run instructions (`./build/atlas_engine`)
  * Git commits follow clean style (atomic, descriptive)

---

# **Daily Breakdown (Suggested)**

| Day   | Tasks                                                         |
| ----- | ------------------------------------------------------------- |
| Day 1 | ATLAS-001 → Repo structure, CMakeLists.txt, push initial repo |
| Day 2 | ATLAS-002 → “Hello World” executable, build success           |
| Day 3 | ATLAS-003 → CSV loader (read & print sample data)             |
| Day 4 | ATLAS-004 → Implement `mean()` & `stddev()`                   |
| Day 5 | ATLAS-004 → Implement `correlation()` and edge case handling  |
| Day 6 | ATLAS-005 → Add GoogleTest + unit tests for all utilities     |
| Day 7 | ATLAS-006 → Documentation, cleanup, commit & push             |

---

If you want, I can **also make Jira-style tickets for Week 2**, which covers the **first MVP backtester with Position/Portfolio structures and PnL calculation**, so you have a **2-week professional sprint plan** ready to go.

Do you want me to do that next?
