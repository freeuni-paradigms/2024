typedef struct {
    char *name; // 4, off 0
    short freeCredits; // 2, off 4
    short *grades; // 4, off 6
    short (*addScores)(void *scores, int n); // 4, off 10
} Student; // 14 bytes

typedef struct {
    char *name;    // 4, off 0
    short credits; // 2, off 4
    short studentsNumber; // 2, off 6
    Student **students; // 4, off 8 
} Course; // 12 bytes

short studentScore(Course *course, int studentIndex, int defaultScore) {
    int result = 0;
    short scores[4];

    if (((Student *)(course->students[studentIndex]->name))->addScores((void *)scores, 4) >= 40) {
        result += scores[0] * course->credits;
    } else {
        result = defaultScore;
    }

    return result;
}


///