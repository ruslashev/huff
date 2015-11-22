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
  unsigned char *file = new unsigned char [len+1];
  if (fread(file, 1, len, fd) != len)
    die("failed to read file \"in\"");
  fclose(fd);

  for (size_t i = 0; i < len; i++) {
    unsigned char byte = file[i];
    std::deque<char> bitsrev;
    printf("current byte: %d\n", byte);
    for (size_t j = 0; j < 8; j++) {
      bitsrev.push_front(byte % 2);
      byte /= 2;
    }
    for (char &c : bitsrev) {
      printf("%d\n", c);
      bits.push_back(c);
    }
  }
}

void readtree()
{

}

int main()
{
  readfile();
  readtree();
  return 0;
}

// vim: et:ts=2:sw=2

