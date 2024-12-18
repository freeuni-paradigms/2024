(load "lunar.scm")

; 1. len == 1
(display (if (equal? (lunar_addition 4 
                                     2)
                                     4) "1 SUCCESS" "1 FAILURE"))(newline)
; 2. len1 == len2
(display (if (equal? (lunar_addition 193526 
                                     560739)
                                     593739) "2 SUCCESS" "2 FAILURE"))(newline)
; 3. len1 > len2
(display (if (equal? (lunar_addition 40817
                                        36) 
                                     40837) "3 SUCCESS" "3 FAILURE"))(newline)
; 4. len1 < len2
(display (if (equal? (lunar_addition 620
                                  120589) 
                                  120689) "4 SUCCESS" "4 FAILURE"))(newline)
; 5. big nums 
(display (if (equal? (lunar_addition     78206499421
                                     956934636642646) 
                                     956978636699646) "5 SUCCESS" "5 FAILURE"))(newline)

; 6. mostly same nums
(display (if (equal? (lunar_addition 284798187
                                      34798487) 
                                     284798487) "6 SUCCESS" "6 FAILURE"))(newline)

; 7. ans is num1
(display (if (equal? (lunar_addition 869658516537
                                        358303414) 
                                     869658516537) "7 SUCCESS" "7 FAILURE"))(newline)

; 8. zeros
(display (if (equal? (lunar_addition 54321
                                   9000004) 
                                   9054324) "8 SUCCESS" "8 FAILURE"))(newline)
