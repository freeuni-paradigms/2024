# მატრიცა

თქვენი ამოცანაა იმპლემენტაცია გაუკეთოთ ორ განზომილებიან მატრიცას ზომებით N x N. მატრიცას უნდა ქონდეს შემდეგი ინტერფეისი:

* void MatrixInit(Matrix* m, int n, size_t elem_size, Free free_fn); -- ინიციალიზაცია უნდა გაუკეთოს მატრიცას n ხაზით და n სვეტით, სადაც თითოეული ელემენტის ზომაა elem_size ბაიტებში და free_fn ფუნქცია (თუ გადმოგეცათ) უნდა გამოიძახოთ მატრიცის გასუფთავებისას.
* void MatrixDestroy(Matrix* m); -- ათავისფლებს მატრიცის მიერ გამოყენებულ მეხსიერებას.
* void MatrixSet(Matrix* m, int row, int col, void* elem); -- row ხაზში და col სვეტში უნდა ჩაწეროს გადმოცემული ელემენტი.
* void* MatrixGet(Matrix* m, int row, int col); -- უნდა დააბრუნოს ელემენტი row ხაზში და col სვეტში.
* void MatrixRotate(Matrix* m); -- უნდა მოაბრუნოს მატრიცა 90 გრადუსით საათის ისრის მოძრაობის მიმართულებით. დეტალები იხილეთ ქვემოთ.
* void MatrixAccumulate(Matrix* m, int row, int col, Accumulate accumulate_fn, void* aux_data); -- მატრიცის იმ დიაგონალების, რომლებიც გადიან (row, col) ელემენტზე, ყოველი ელემენტისთვის უნდა გამოიძახოს გადმოცემული accumulate ფუნქცია და ელემენტის მნიშვნელობასთან ერთად გადასცას aux_data. დეტალები იხილეთ ქვემოთ.

## მობრუნება
3x3-ზე მატრიცის 90 გრადუსით მობრუნებისას ელემენტები უნდა გადანაცვლდნენ შემდეგნაირად:
(0, 0) => (0, 2)
(0, 2) => (2, 2)
(2, 2) => (2, 0)
(2, 0) => (0, 0)
(0, 1) => (1, 2)
(1, 2) => (2, 1)
(2, 1) => (1, 0)
(1, 0) => (0, 1)
(1, 1) რჩება ადგილის უცვლელად.

## დიაგონალები
3x3-ზე მატრიცაში ინდექსით (1, 1) ელემენტზე გამავალი დიაგონალებია (0, 0) - (1, 1) - (2, 2) და (0, 2) - (1, 1) - (2, 0)
ხოლო ინდექსით (1, 2) ელემენტზე გამავალი დიაგონალები: (0, 1) - (1, 2) და (1, 2) - (2, 1)

ზემოთ იმპლემენტირებული მატრიცის გამოყენებით იმპლემენტაცია გაუკეთეთ IntMatrix სტრუქტურას შემდეგი ინტერფეისით:

* void IntMatrixInit(IntMatrix* m, int n); -- ინიციალიზაციას უნდა გაუკეთოს ინტეჯერების ორ განზომილებიან მატრიცას.
* void IntMatrixDestroy(IntMatrix* m); -- ათავისუფლებს ინტეჯერების მატრიცის მიერ გამოყენებულ მეხსიერებას.
* void IntMatrixSet(IntMatrix* m, int row, int col, int elem); -- (row, col) ინდექსზე უნდა ჩაწეროს გადმოცემული ინტეჯერი.
* int IntMatrixGet(IntMatrix* m, int row, int col); -- უნდა დააბრუნოს (row, col) ინდექსზე მყოფნი ინტეჯერი.
* int IntMatrixSum(Matrix* m, int row, int col); -- უნდა დააბრუნოს ჯამი მატრიცის იმ დიაგონალების ელემენტების რომლებიც გადიან (row, col) ინდექსზე.

**გაითვალისწინეთ რომ IntMatrix-ის იმპლემენტაციისას არ უნდა გამოიყენოთ Matrix სტრუქტურის შიგთავსი (member variables). თქვენ წვდომა გაქვთ მხოლოდ მის ინტერფეისზე (ზემოთ ჩამოთვლილ ფუნქციებზე).

### ტესტირება
ფაილების კომპილაციისთვის გაუშვით **gcc matrix.c tests.c**
ხოლო დაკომპილირებული ფაილის გასაშვებად: **a.exe**
მეხსიერებაზე შესამოწმებლად კოდი დააკომპილირეთ შემდეგი ბრძანებით: **gcc -fsanitize=address -g matrix.c tests.c** (ვინდოუსზე იმედია მუშაობს.)
*მეხსიერების არასწორად გამოყენების შემთხვევაში დაკარგავთ ტესტისთვის განკუთვნილი ქულის 15%-ს.*


### შეიძლება დაგჭირდეთ შემდეგი ფუნქციები სტანდარტული ბიბლიოთეკიდან:

#### <stdlib.h>
* void* malloc( size_t size ); -- Allocates size bytes of uninitialized storage.
* void *realloc( void *ptr, size_t new_size ); -- Reallocates the given area of memory. It must be previously allocated by malloc(), calloc() or realloc() and not yet freed with a call to free or realloc. Otherwise, the results are undefined.
* void free( void* ptr ); -- Deallocates the space previously allocated by malloc(), calloc(), aligned_alloc, (since C11) or realloc().

#### <string.h>
* void* memcpy( void *dest, const void *src, size_t count ); -- Copies count characters from the object pointed to by src to the object pointed to by dest. Both objects are interpreted as arrays of unsigned char.
* void* memmove( void* dest, const void* src, size_t count ); -- Copies count characters from the object pointed to by src to the object pointed to by dest. Both objects are interpreted as arrays of unsigned char. The objects may overlap: copying takes place as if the characters were copied to a temporary character array and then the characters were copied from the array to dest.
 The behavior is undefined if access occurs beyond the end of the dest array. The behavior is undefined if either dest or src is a null pointer.
* char * strdup(const char *str1); -- Returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by str1. The returned pointer must be passed to free to avoid a memory leak.
* char *strndup(const char *str, size_t size); -- Returns a pointer to a null-terminated byte string, which contains copies of at most size bytes from the string pointed to by str. If the null terminator is not encountered in the first size bytes, it is added to the duplicated string.