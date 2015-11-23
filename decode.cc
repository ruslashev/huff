#include <fstream>
#include <cstdarg>
#include <cstdlib>
#include <vector>
#include <deque>

std::deque<char> bits;
int bitsf, bitsv;

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

tree* readnode()
{
  tree *node = new tree;
  int type = take(1);
  if (type == 1) {
    node->leaf = 1;
    node->freq = take(bitsf);
    node->val = take(bitsv);
  } else if (type == 0) {
    node->leaf = 0;
    node->left = readnode();
    node->right = readnode();
  }
}

int main()
{
  readfile();
  bitsf = take(6);
  bitsv = take(6);
  tree *root = readnode();
  return 0;
}

// vim: et:ts=2:sw=2

