typedef struct {
  char student_id;     // 0 1
  short late_by_hours; // 1 2
  int score;  // 3 4
} Submission; // 7

int ClassScore(Submission *s, int n) {
  int total_class_score = 0;
  for (int i = 0; i < n; i++) {
    if (s[i].late_by_hours < 5) {
      total_class_score += s[i].score;
    } else {
      // 50% penalty on very late HW
      total_class_score += (s[i].score + 1) / 2;
    }
  }
  return total_class_score;
}