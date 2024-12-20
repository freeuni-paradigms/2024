# Vector (40 ქულა)

თქვენი ამოცანაა იმპლემენტაცია გაუკეთოთ Vector ჯენერიკ სტრუქტურას შემდეგი ინტერფეისით:

* void VectorInit(Vector\* v, int elem_size, FreeFn free_fn) - ინიციალიზაცია უნდა გაუკეთოს გადმოცემულ ვექტორს. გადმოგეცემათ შესანახი ელემენტების ზომა ბაიტებში და მეხსიერების გამათავისუფლებელი ფუნქცია (თუ ასეთი საჭიროა)
* void VectorDestroy(Vector\* v) - უნდა გაათავისუფლოს ვექტორის და მასში შენახული ელემენტების მიერ გამოყენებული მეხსიერება
* void VectorAppend(Vector\* v, void\* elem) - ვექტორში ბოლო ელემენტად უნდა დაამატოს მოცემულ მისამართზე არსებული მნიშვნელობა
* void VectorInsert(Vector\* v, int index, void\* elem) - ვექტორში მოცემულ ინდექსზე უნდა ჩაამატოს გადმოცემულ მისამართზე არსებული მნიშვნელობა
* void VectorOverwrite(Vector\* v, int index, void\* elem) - ვექტორში მოცემულ ინდექსზე არსებულ ელემენტს უნდა გადააწერს გადმოცემულ მისამართზე არსებული მნიშვნელობა
* void\* VectorGet(Vector\* v, int index) - უნდა დააბრუნოს მოცემული ინდექსის ელემენტის მისამართი
* void VectorRemove(Vector\* v, int index, void\* elem) - ვექტორიდან უნდა ამოაგდოს მოცემული ინდექსის მქონე ელემენტი. თუ გადმოცემული **elem** მისამართი არანულოვანია, ელემენტის ამოგდებამდე მისი მნიშვნელობა უნდა დააკოპიროს ამ მისამართზე
* int VectorSize(Vector\* v) - უნდა დააბრუნოს ვექტორში შენახული ელემენტების რაოდენობა

ვექტორის იმპლემენტაციის შემდეგ, მისი გამოყენებით იმპლემენტაცია უნდა გაუკეთოთ StudentVector სტრუქტურას რომლის ინტერფეისიც მორგებულია Student ობიექტების დამუშავებაზე. ფუნქციების უმრავლესობა უკვე იმპლემენტირებულია, თქვენ დაგჭირდებათ მხოლოდ ორი ახალი ფუნქციის შევსება:

* void StudentFree(void\* elem) - უნდა გაათავისუფლოს სტუდენტის ობიექტის მიერ გამოყენებული დინამიურად გამოყოფილი მეხსიერება
* StudentVector StudentVectorCloneRange(StudentVector\* v, int start, int end) - უკვე არსებული ვექტორის ელემენტები [start, end] დიაპაზონში (start-ის და end-ის ჩათვლით) უნდა დაკლონოს ახალ ვექტორში. ამ ფუნქციას ევალება ახალი StudentVector ობიექტის შექმნა, მისი ინიციალიზაცია და ძველი ვექტორიდან მოცემულ დიაპაზონში არსებული ელემენტების კლონირება და ახალ ვექტორში დამატება.

## შეფასება

* VectorInit, VectorDestroy, VectorAppend, VectorGet ფუნქციების იმპლემენტაცია შეფასდება საკითხის შეფასების 40%-ით
* VectorInsert, VectorOverwrite, VectorRemove 40%-ით
* StudentVector -ის იმპლემენტაციაში 20%

**ტესტზე თქვენი ნამუშევარი შეიძლება სწორ პასუხს აბრუნებდეს, მაგრამ მიუხედავად ამისა თუ თქვენი იმპლემენტაცია მეხსიერებას არასწორად იყენებს (მაგალითად free დაგავიწყდათ, ან უკვე დაბრუნებულ მეხსიერებას იყენებთ თავიდან) დაგაკლდებათ ტესტის შეფასების 15%.**

## ტესტირება

ნაშრომის დასაკომპილირებლად ტერმინალში გაუშვით: `gcc *.c` ხოლო ტესტებზე შესამოწმებლად: `a.exe`

