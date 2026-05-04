CXX = g++
CXXFLAGS = -Wall --std=c++17
TEST_BIN = test_runner
SOURCES_TEST = test.cpp catch_amalgamated.cpp

# ================================================================
# Default: build the student program
# ================================================================
all: main

main: MainProgram.cpp
	$(CXX) $(CXXFLAGS) -o main MainProgram.cpp

# ================================================================
# Build the test binary (shared by all test targets)
# ================================================================
$(TEST_BIN): test.cpp MainProgram.cpp catch_amalgamated.cpp catch_amalgamated.hpp
	$(CXX) $(CXXFLAGS) -o $(TEST_BIN) $(SOURCES_TEST)

# ================================================================
# Run ALL tests at once
# ================================================================
test: $(TEST_BIN)
	@echo "============================================"
	@echo "  RUNNING ALL TESTS"
	@echo "============================================"
	./$(TEST_BIN)

# ================================================================
# GROUP 1: Basic Construction & Destruction (20 pts)
# ================================================================
test_group1: $(TEST_BIN)
	@echo "============================================"
	@echo "  GROUP 1: Construction & Destruction [20 pts]"
	@echo "============================================"
	./$(TEST_BIN) "[construction]" --colour-mode ansi

# ================================================================
# GROUP 2: Add & Get Operations (20 pts)
# ================================================================
test_group2: $(TEST_BIN)
	@echo "============================================"
	@echo "  GROUP 2: Add & Get Operations [20 pts]"
	@echo "============================================"
	./$(TEST_BIN) "[add_get]" --colour-mode ansi

# ================================================================
# GROUP 3: RemoveLast (10 pts)
# ================================================================
test_group3: $(TEST_BIN)
	@echo "============================================"
	@echo "  GROUP 3: RemoveLast [10 pts]"
	@echo "============================================"
	./$(TEST_BIN) "[remove]" --colour-mode ansi

# ================================================================
# GROUP 4: Copy Constructor — Deep Copy (15 pts)
# ================================================================
test_group4: $(TEST_BIN)
	@echo "============================================"
	@echo "  GROUP 4: Copy Constructor [15 pts]"
	@echo "============================================"
	./$(TEST_BIN) "[copy_ctor]" --colour-mode ansi

# ================================================================
# GROUP 5: Copy Assignment Operator (15 pts)
# ================================================================
test_group5: $(TEST_BIN)
	@echo "============================================"
	@echo "  GROUP 5: Copy Assignment Operator [15 pts]"
	@echo "============================================"
	./$(TEST_BIN) "[copy_assign]" --colour-mode ansi

# ================================================================
# GROUP 6: Tracker — Static Class (20 pts)
# ================================================================
test_group6: $(TEST_BIN)
	@echo "============================================"
	@echo "  GROUP 6: Tracker (Static Class) [20 pts]"
	@echo "============================================"
	./$(TEST_BIN) "[tracker]" --colour-mode ansi

# ================================================================
# Run all groups one by one with scoring summary
# ================================================================
grade: $(TEST_BIN)
	@echo ""
	@echo "╔════════════════════════════════════════════╗"
	@echo "║        GRADING — ALL 6 TEST GROUPS        ║"
	@echo "╠════════════════════════════════════════════╣"
	@echo "║  Group 1: Construction & Destruction  20p  ║"
	@echo "║  Group 2: Add & Get Operations        20p  ║"
	@echo "║  Group 3: RemoveLast                  10p  ║"
	@echo "║  Group 4: Copy Constructor            15p  ║"
	@echo "║  Group 5: Copy Assignment Operator    15p  ║"
	@echo "║  Group 6: Tracker (Static Class)      20p  ║"
	@echo "║                                TOTAL 100p  ║"
	@echo "╚════════════════════════════════════════════╝"
	@echo ""
	@G1=0; G2=0; G3=0; G4=0; G5=0; G6=0; \
	echo "============================================"; \
	echo "  GROUP 1: Construction & Destruction [20 pts]"; \
	echo "============================================"; \
	./$(TEST_BIN) "[construction]" --colour-mode ansi 2>&1; \
	if [ $$? -eq 0 ]; then G1=20; echo ">>> GROUP 1: PASS  [20/20]"; \
	else echo ">>> GROUP 1: FAIL  [0/20]"; fi; \
	echo ""; \
	echo "============================================"; \
	echo "  GROUP 2: Add & Get Operations [20 pts]"; \
	echo "============================================"; \
	./$(TEST_BIN) "[add_get]" --colour-mode ansi 2>&1; \
	if [ $$? -eq 0 ]; then G2=20; echo ">>> GROUP 2: PASS  [20/20]"; \
	else echo ">>> GROUP 2: FAIL  [0/20]"; fi; \
	echo ""; \
	echo "============================================"; \
	echo "  GROUP 3: RemoveLast [10 pts]"; \
	echo "============================================"; \
	./$(TEST_BIN) "[remove]" --colour-mode ansi 2>&1; \
	if [ $$? -eq 0 ]; then G3=10; echo ">>> GROUP 3: PASS  [10/10]"; \
	else echo ">>> GROUP 3: FAIL  [0/10]"; fi; \
	echo ""; \
	echo "============================================"; \
	echo "  GROUP 4: Copy Constructor [15 pts]"; \
	echo "============================================"; \
	./$(TEST_BIN) "[copy_ctor]" --colour-mode ansi 2>&1; \
	if [ $$? -eq 0 ]; then G4=15; echo ">>> GROUP 4: PASS  [15/15]"; \
	else echo ">>> GROUP 4: FAIL  [0/15]"; fi; \
	echo ""; \
	echo "============================================"; \
	echo "  GROUP 5: Copy Assignment Operator [15 pts]"; \
	echo "============================================"; \
	./$(TEST_BIN) "[copy_assign]" --colour-mode ansi 2>&1; \
	if [ $$? -eq 0 ]; then G5=15; echo ">>> GROUP 5: PASS  [15/15]"; \
	else echo ">>> GROUP 5: FAIL  [0/15]"; fi; \
	echo ""; \
	echo "============================================"; \
	echo "  GROUP 6: Tracker (Static Class) [20 pts]"; \
	echo "============================================"; \
	./$(TEST_BIN) "[tracker]" --colour-mode ansi 2>&1; \
	if [ $$? -eq 0 ]; then G6=20; echo ">>> GROUP 6: PASS  [20/20]"; \
	else echo ">>> GROUP 6: FAIL  [0/20]"; fi; \
	echo ""; \
	TOTAL=$$((G1 + G2 + G3 + G4 + G5 + G6)); \
	echo "╔════════════════════════════════════════════╗"; \
	echo "║             SCORE SUMMARY                  ║"; \
	echo "╠════════════════════════════════════════════╣"; \
	printf "║  Group 1: Construction        %3d / 20    ║\n" $$G1; \
	printf "║  Group 2: Add & Get           %3d / 20    ║\n" $$G2; \
	printf "║  Group 3: RemoveLast          %3d / 10    ║\n" $$G3; \
	printf "║  Group 4: Copy Constructor    %3d / 15    ║\n" $$G4; \
	printf "║  Group 5: Copy Assignment     %3d / 15    ║\n" $$G5; \
	printf "║  Group 6: Tracker             %3d / 20    ║\n" $$G6; \
	echo "╠════════════════════════════════════════════╣"; \
	printf "║  TOTAL                        %3d / 100   ║\n" $$TOTAL; \
	echo "╚════════════════════════════════════════════╝"

# ================================================================
# Clean
# ================================================================
clean:
	rm -f main $(TEST_BIN) *.o

.PHONY: all test test_group1 test_group2 test_group3 test_group4 test_group5 test_group6 grade clean