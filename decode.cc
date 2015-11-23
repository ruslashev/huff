#include <fstream>
#include <cstdarg>
#include <cstdlib>
#include <vector>
#include <deque>

void die(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  puts("");
  exit(1);
}

struct tree
{
  tree *left, *right;
  bool leaf;
  char val;
  unsigned int freq;
};

std::deque<char> bits;

void readfile()
{
  FILE *fd = fopen("in", "rb");
  if (!fd)
    die("failed to open file \"in\"");
  fseek(fd, 0, SEEK_END);
  size_t len = ftell(fd);
  rewind(fd);

  for (size_t i = 0; i < len; i++) {
    unsigned char byte;
    if (fread(&byte, 1, 1, fd) != 1)
      die("failed to read file \"in\"");
    std::deque<char> bitsrev;
    for (size_t j = 0; j < 8; j++) {
      bitsrev.push_front(byte % 2);
      byte /= 2;
    }
    for (char &c : bitsrev)
      bits.push_back(c);
  }

  fclose(fd);
}

int take(int n)
{
  int num = 0;
  for (int i = 0; i < n; i++) {
    num *= 2;
    num += bits.front();
    bits.pop_front();
  }
  return num;
}

int main()
{
  readfile();
  printf("%d %d\n", take(6), take(6));
  return 0;
}

// vim: et:ts=2:sw=2

