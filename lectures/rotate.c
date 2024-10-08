void rotate(void* start, void* middle, void* end) {
  int leftSize = (char*)middle - (char*)start;
  int rightSize = (char*)end - (char*)middle;
  void* tmp = malloc(rightSize);
  memcpy(tmp, middle, rightSize);
  memcpy(middle, start, (char*)end - leftSize);
  memcpy(start, tmp, rightSize);
}
