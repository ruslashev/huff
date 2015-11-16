#include <fstream>
#include <cstdarg>

void die(const char *format, ...);

struct tree
{
  tree *left, *right;
  int val, freq;
};

unsigned char *file;

void readfile()
{
  FILE *fd = fopen("in", "rb");
  if (!fd)
    die("failed to open file \"in\"");
  fseek(fd, 0, SEEK_END);
  size_t len = ftell(fd);
  rewind(fd);
  file = new unsigned char [len+1];
  if (fread(file, 1, len, fd) != len)
    die("failed to read file \"in\"");
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

void die(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  puts("");
  exit(1);
}

// vim: et:ts=2:sw=2

