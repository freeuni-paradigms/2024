
# პროგრამირების პარადიგმები - Fx - სესია 2 - 2021/22

# ინსტრუქციები - აუცილებლად დაიცავით
## ნაშრომის დატოვება
დესკტოპზე უნდა დაგხვდეთ დირექტორია რომლის სახელიც თქვენი უნივერსიტეტის ელ-ფოსტის პრეფიქსია. ამ დირექტორიაში უნდა დააკოპიროთ თქვენი ნაშრომები საგამოცდოს დატოვებამდე.  
**გირჩევთ თავიდანვე მოცემულ დირექტორიაში დააკომპიროთ საკითხები და მანდ იმუშაოთ ამოხსნებზე, რომ ბოლოს კოპირება არ დაგავიწყდეთ.**

## ტერმინალის გამოყენება
კოდის დასაწერად გირჩევთ გამოიყენოთ VSCode რედაქტორი რომელიც შეგიძლიათ იპოვოთ დესკტოპზე. 
ამოცანაზე სამუშაოდ მისი ფაილების გასახსნელად გამოიყენეთ: **File > Open Folder** და აირჩიეთ დესკტოპზე გადმოწერილი საგამოცდო საკითხების დირექტორია. 
კოდის დასაკომპილირებლად და ტესტების გასაშვებად შეგიძლიათ გამოიყენოთ VSCode-ში ჩაშენებული ტერმინალი: **Terminal > New Terminal**

ასევე შეგიძლიათ გამოიყენოთ Windows-ის სტანდარტული ტერმინალი. გახსენით საკითხის დირექტორია, list_sum მაგალითად, და ცარიელ ადგილას ჯერ დააჭირეთ **Control + Shift + Mouse-Right-Click** და შემდეგ აირჩიეთ **Open Command Prompt**

**კოდის დაკომპილირებიდან მის გაშვებამდე კარგად დააკვირდით კომპილაცია წარმატებით დასრულდა თუ არა. კომპილაცია თუ ვერ შესრულდა, ძველი დაკომპილირებული პროგრამა (a.exe მაგალითად) უცვლელი ანუ ძველი რჩება. თუ გინდათ რომ დარწმუნდეთ ახალ დაკომპილირებულ პროგრამას ამოწმებთ გირჩევთ კომპილაციამდე ძველი კომპილაციის შედეგი წაშალოთ, მაგალითად ტერმინალში გაუშვით del a.exe**

<span style="color:red">**საკითხებთან ერთად მოცემული ტესტები არის მხოლოდ სამაგალითო, რათა გაგიადვილდეთ ნაშრომების შემოწმება. საბოლოო შეფასების დათვლისას ნაშრომები გასწორდება ტესტების სხვა სიმრავლეზე.**</span>

---

# List Sum - სქემა (60 ქულა)
თქვენი ამოცანაა იმპლემენტაცია გაუკეთოთ sum ფუნქციას რომელიც უნდა აჯამებდეს ერთი და იგივე ზომის დადებით რიცხვებს.  

რიცხვები გადმოგეცემათ მისი ციფრების სიად. მაგალითად:

* 12 წარმოდგება როგორც '(1 2)
* 53 როგორც '(5 3)
* ხოლო (sum '((1 2) (5 3))) უნდა აბრუნებდეს '(6 5)

გაითვალისწინეთ რომ sum ფუნქცია იღებს რიცხვების სიას, ანუ სიების სიას.

**ტესტების 85%-ში ერთი და იგივე პოზიციაზე მყოფი ციფრების ჯამი 9-ზე მეტი არასდროს არ იქნება, ანუ ნაშთის გადატანის გათვალისწინება არ დაგჭირდებათ.**

**ტესტირება**
ტერმინალში გაუშვით შემდეგი ბრძანება: `kawa list_sum.scm`

---

# Cooking - ნაკადები (50 ქულა)
გევალებათ სიმულაცია გაუკეთოთ კულინარიულ შეჯიბრს N რაოდენობის მონაწილით და სამი ჟიურის წევრით. შეჯიბრება შემდეგი წესების მიხედვით იმართება:
* მონაწილეები ჯერ ინდივიდუალურად ამზადებენ კერძს
* კერძის დამზადების შემდეგ ისინი დგებიან ჟიურთან რიგში
* ჟიური მონაწილეებს რიგის მიმდევრობით იძახებს
* მონაწილე ელოდება სამივე ჟიურის წევრისგან მიიღოს პასუხი (გამოიტანეთ ეკრანი true/false)
* სამივე ჟიური დამოუკიდებლად აძლევს ხმას მიმდინარე მონაწილე გადავიდეს თუ არა შემდეგ ეტაპზე

სიმულაცია უნდა გააკეთოთ N + 3 ნაკადის რაოდენობით რომელიც სიმულაციის დაწყებისთანავე უნდა გაუშვათ. CookingShow ფუნქცია თითოეული მონაწილის და ჟიურის წევრის საქმეების შესრულებას უნდა უშვებდეს ცალ-ცალკე განსხვავებულ ნაკადში. CookingShow ფუნქცია არ უნდა ასრულებდეს მუშაობას მანამ სანამ ყველა მონაწილე არ შეფასდება.


---

## <stdlib.h>
* void\* malloc( size_t size ); -- Allocates size bytes of uninitialized storage.
* void \*realloc( void \*ptr, size_t new_size ); -- Reallocates the given area of memory. It must be previously allocated by malloc(), calloc() or realloc() and not yet freed with a call to free or realloc. Otherwise, the results are undefined.
* void free( void\* ptr ); -- Deallocates the space previously allocated by malloc(), calloc(), aligned_alloc, (since C11) or realloc().
* void qsort (void\* base, size_t num, size_t size, int (\*compar)(const void\*,const void\*)); -- Sorts the num elements of the array pointed to by base, each element size bytes long, using the compar function to determine the order. The sorting algorithm used by this function compares pairs of elements by calling the specified compar function with pointers to them as argument. The function does not return any value, but modifies the content of the array pointed to by base reordering its elements as defined by compar. The order of equivalent elements is undefined.

## <string.h>
* void\* memcpy( void \*dest, const void \*src, size_t count ); -- Copies count characters from the object pointed to by src to the object pointed to by dest. Both objects are interpreted as arrays of unsigned char.
* void\* memmove( void\* dest, const void\* src, size_t count ); -- Copies count characters from the object pointed to by src to the object pointed to by dest. Both objects are interpreted as arrays of unsigned char. The objects may overlap: copying takes place as if the characters were copied to a temporary character array and then the characters were copied from the array to dest.
 The behavior is undefined if access occurs beyond the end of the dest array. The behavior is undefined if either dest or src is a null pointer.
* char \* strdup(const char \*str1); -- Returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by str1. The returned pointer must be passed to free to avoid a memory leak.
* char \*strndup(const char \*str, size_t size); -- Returns a pointer to a null-terminated byte string, which contains copies of at most size bytes from the string pointed to by str. If the null terminator is not encountered in the first size bytes, it is added to the duplicated string.
* int strcmp ( const char \* str1, const char \* str2 ); -- Compares the C string str1 to the C string str2. This function starts comparing the first character of each string. If they are equal to each other, it continues with the following pairs until the characters differ or until a terminating null-character is reached. This function performs a binary comparison of the characters. For a function that takes into account locale-specific rules, see strcoll.
* int strncmp ( const char \* str1, const char \* str2, size_t num ); -- Compares up to num characters of the C string str1 to those of the C string str2. This function starts comparing the first character of each string. If they are equal to each other, it continues with the following pairs until the characters differ, until a terminating null-character is reached, or until num characters match in both strings, whichever happens first.

## <semaphore.h>

* sem_t: სემაფორის ტიპის სტრუქტურა
* int sem_init(sem_t \*sem, int pshared, unsigned int value); -- initializes the unnamed semaphore at the address pointed to by sem. The value argument specifies the initial value for the semaphore.
* int sem_destroy(sem_t \*sem); -- destroys the unnamed semaphore at the address pointed to by sem.
* int sem_post(sem_t \*sem); -- increments (unlocks) the semaphore pointed to by sem.  If the semaphore's value consequently becomes greater than zero, then another process or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
* int sem_wait(sem_t \*sem); -- decrements (locks) the semaphore pointed to by sem.  If the semaphore's value is greater than zero, then the decrement proceeds, and the function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the decrement (i.e., the semaphore value rises above zero), or a signal handler interrupts the call.
* int sem_getvalue(sem_t \*restrict sem, int \*restrict sval); -- places the current value of the semaphore pointed to sem into the integer pointed to by sval.

## <pthread.h>
* pthread_t: ნაკატის ტიპის სტრუქტურა
* int pthread_create(pthread_t \*thread, const pthread_attr_t \*attr, void \*(\*start_routine) (void \*), void \*arg); -- The pthread_create() function starts a new thread in the calling process.  The new thread starts execution by invoking start_routine(); arg is passed as the sole argument of start_routine().
* int pthread_join(pthread_t thread, void \*\*retval); -- The pthread_join() function waits for the thread specified by thread to terminate.  If that thread has already terminated, then pthread_join() returns immediately.  The thread specified by thread must be joinable.
* void pthread_exit(void \*retval); -- The pthread_exit() function terminates the calling thread and returns a value via retval that (if the thread is joinable) is available to another thread in the same process that calls pthread_join(3).
* pthread_mutex_t: მუტექსის ტიპის სტრუქტურა
* int pthread_mutex_init(pthread_mutex_t \*mutex, const pthread_mutexattr_t \*attr); -- The pthread_mutex_init() function initialises the mutex referenced by mutex with attributes specified by attr. If attr is NULL, the default mutex attributes are used; the effect is the same as passing the address of a default mutex attributes object. Upon successful initialisation, the state of the mutex becomes initialised and unlocked.
* int pthread_mutex_destroy(pthread_mutex_t \*mutex); -- The pthread_mutex_destroy() function destroys the mutex object referenced by mutex; the mutex object becomes, in effect, uninitialised. An implementation may cause pthread_mutex_destroy() to set the object referenced by mutex to an invalid value. A destroyed mutex object can be re-initialised using pthread_mutex_init(); the results of otherwise referencing the object after it has been destroyed are undefined.
* int pthread_mutex_lock(pthread_mutex_t \*mutex); -- The mutex object referenced by mutex shall be locked by calling pthread_mutex_lock(). If the mutex is already locked, the calling thread shall block until the mutex becomes available. This operation shall return with the mutex object referenced by mutex in the locked state with the calling thread as its owner.
* int pthread_mutex_unlock(pthread_mutex_t \*mutex); -- he pthread_mutex_unlock() function shall release the mutex object referenced by mutex. The manner in which a mutex is released is dependent upon the mutex's type attribute. If there are threads blocked on the mutex object referenced by mutex when pthread_mutex_unlock() is called, resulting in the mutex becoming available, the scheduling policy shall determine which thread shall acquire the mutex.
* int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex); -- The pthread_cond_wait() and pthread_cond_timedwait() functions are used to block on a condition variable. They are called with mutex locked by the calling thread or undefined behaviour will result. These functions atomically release mutex and cause the calling thread to block on the condition variable cond; atomically here means "atomically with respect to access by another thread to the mutex and then the condition variable". That is, if another thread is able to acquire the mutex after the about-to-block thread has released it, then a subsequent call to pthread_cond_signal() or pthread_cond_broadcast() in that thread behaves as if it were issued after the about-to-block thread has blocked. Upon successful return, the mutex has been locked and is owned by the calling thread.
