(load "num_occurrences.scm")

;; Sample tests from problem statement
(display (if (equal? (num-occurrences '(1 2 3 1 2) equal?) '(2 2 1 2 2)) "TEST 1: SUCCESS" "TEST 1: FAILURE"))(newline)
(display (if (equal? (num-occurrences '("foo" "bar" "dev" "bar") string=?) '(1 2 1 2)) "TEST 2: SUCCESS" "TEST 2: FAILURE"))(newline)

;; More tests
(display (if (equal? (num-occurrences '(7 2 6 3 10 3 6 1 10 2 7 9 4 8 9 9 10 10 4 10 4 1 8 10 3 7 1 9 9 5) equal?) '(3 2 2 3 6 3 2 3 6 2 3 5 3 2 5 5 6 6 3 6 3 3 2 6 3 3 3 5 5 1)) "TEST 3: SUCCESS" "TEST 3: FAILURE"))(newline)
(display (if (equal? (num-occurrences '(2 10 8 5 8 6 7 7 9 1 1 6 7 7 9 5 3 3 2 10 4 4 5 9 4 2 2 7 5 5 6 2 9 8 9 4 9 1 8 5) equal?) '(5 2 4 6 4 3 5 5 6 3 3 3 5 5 6 6 2 2 5 2 4 4 6 6 4 5 5 5 6 6 3 5 6 4 6 4 6 3 4 6)) "TEST 4: SUCCESS" "TEST 4: FAILURE"))(newline)
(display (if (equal? (num-occurrences '(4 1 2 1 5 2 5 5 4 2 5 3 2 3 3 3 4 3 5 4) equal?) '(4 2 4 2 5 4 5 5 4 4 5 5 4 5 5 5 4 5 5 4)) "TEST 5: SUCCESS" "TEST 5: FAILURE"))(newline)
(display (if (equal? (num-occurrences '(2 31 84 32 30 68 64 16 15 51 24 66 56 91 31 100 2 98 28 37 15 38 47 84 41 23 12 83 31 27 45 74 65 5 28 56 64 91 63 62 8 22 2 64 85 76 66 20 98 79) equal?) '(3 3 2 1 1 1 3 1 2 1 1 2 2 2 3 1 3 2 2 1 2 1 1 2 1 1 1 1 3 1 1 1 1 1 2 2 3 2 1 1 1 1 3 3 1 1 2 1 2 1)) "TEST 6: SUCCESS" "TEST 6: FAILURE"))(newline)
(display (if (equal? (num-occurrences '(10 4 8 10 10 5 5 6 6 9 4 9 2 1 8 3 10 7 4 9 8 10 5 5 7 10 9 10 5 1 8 3 4 6 2 3 8 8 8 2 4 5 9 4 4 2 4 2 8 5) equal?) '(7 8 8 7 7 7 7 3 3 5 8 5 5 2 8 3 7 2 8 5 8 7 7 7 2 7 5 7 7 2 8 3 8 3 5 3 8 8 8
 5 8 7 5 8 8 5 8 5 8 7)) "TEST 7: SUCCESS" "TEST 7: FAILURE"))(newline)
(display (if (equal? (num-occurrences '(4 16 14 2 15 6 2 1 13 5 5 10 1 20 11 4 12 15 3 10 17 11 15 17 9 14 5 3 13 12 20 9 14 17 13 14 1 12 14 13 6 15 7 20 3 4 15 4 17 7 20 4 18 2 15 6 10 2 9 11 16 15 4 4 2 12 1 2 18 15 3 3 17 17 1 20 8 3 17 12 20 18 13 7 18 14 13 15 5 16 16 10 2 9 4 14 15 8 2 7) equal?) '(8 4 7 8 10 3 8 5 6 4 4 4 5 6 3 8 5 10 6 4 7 3 10 7 4 7 4 6 6 5 6 4 7 7 6 7 5 5 7 6 3 10 4 6 6 8 10 8 7 4 6 8 4 8 10 3 4 8 4 3 4 10 8 8 8 5 5 8 4 10 6 6 7 7 5 6 2 6 7 5 6 4 6 4 4 7 6 10 4 4 4 4 8 4 8 7 10 2 8 4)) "TEST 8: SUCCESS" "TEST 8: FAILURE"))(newline)
(display (if (equal? (num-occurrences '(5 16 19 20 15 17 16 4 5 15 7 2 17 1 13 14 15 13 12 12 4 11 18 4 11 4 19 6 17 4 8 3 14 17 10 20 7 15 7 17 17 8 19 6 14 10 20 5 11 11 3 9 16 15 13 7 8 3 20 2 7 15 1 20 4 17 8 4 17 20 1 17 16 1 3 17 16 18 13 6 11 3 11 13 20 6 1 17 7 14 12 10 6 5 15 14 14 6 8 14) equal?) '(4 5 3 7 7 11 5 7 4 7 6 2 11 5 5 7 7 5 3 3 7 6 2 7 6 7 3 6 11 7 5 5 7 11 3 7 6
 7 6 11 11 5 3 6 7 3 7 4 6 6 5 1 5 7 5 6 5 5 7 2 6 7 5 7 7 11 5 7 11 7 5 11 5 5
 5 11 5 2 5 6 6 5 6 5 7 6 5 11 6 7 3 3 6 4 7 7 7 6 5 7)) "TEST 9: SUCCESS" "TEST 9: FAILURE"))(newline)
