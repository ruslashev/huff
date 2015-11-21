#include <fstream>
#include <cstdarg>
#include <string>
#include <map>
#include <deque>
#include <algorithm>

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

unsigned char po2(int n)
{
  unsigned char result = 1;
  for (int i = 0; i < n; i++)
    result *= 2;
  return result;
}

void ntobinary(int bits, int n, std::vector<char> *stream)
{
  if (n > pow(2, bits+1)-1)
    die("%d bits is not enough", bits);
  std::vector<char> buf;
  int i = 0;
  while (n) {
    i++;
    buf.push_back(n % 2);
    n /= 2;
  }
  for (int j = i; j <= bits; j++)
    buf.push_back(0);
  for (i = 0; i < bits; i++) {
    stream->push_back(buf[bits-i-1]);
  }
}

void outputtree(int bitsf, int bitsv, tree *node, std::vector<char> *stream)
{
  if (node->leaf) {
    stream->push_back(1);
    ntobinary(bitsf, node->freq, stream);
    ntobinary(bitsv, node->val, stream);
  } else {
    stream->push_back(0);
    outputtree(bitsf, bitsv, node->left, stream);
    outputtree(bitsf, bitsv, node->right, stream);
  }
}

void findtree(tree *node, char val, std::string &code, bool &success)
{
  if (node->leaf) {
    if (node->val == val)
      success = 1;
  } else {
    findtree(node->left, val, code, success);
    if (success)
      code = "0" + code;
    else {
      findtree(node->right, val, code, success);
      if (success)
        code = "1" + code;
    }
  }
}

int main()
{
  const std::string text = "hello, world! this is an example asdfghjkl";

  std::map<char,unsigned int> freqs;
  for (size_t i = 0; i < text.length(); i++)
    if (freqs.find(text[i]) == freqs.end())
      freqs[text[i]] = 1;
    else
      freqs[text[i]]++;

  struct elem {
    bool leaf;
    unsigned int freq;
    char val;
    tree *node;
  };
  std::deque<elem> list;
  for (const auto &n : freqs)
    list.push_back({1, n.second, n.first});

  std::sort(list.begin(), list.end(),
      [](auto i, auto j) { return i.freq < j.freq; });

  while (list.size() > 1) {
    tree *node = new tree;
    auto a = list.front();
    list.pop_front();
    auto b = list.front();
    list.pop_front();

    node->freq = a.freq + b.freq;

    if (a.leaf) {
      node->left = new tree;
      node->left->left = nullptr;
      node->left->right = nullptr;
      node->left->leaf = 1;
      node->left->val = a.val;
      node->left->freq = a.freq;
    } else
      node->left = a.node;

    if (b.leaf) {
      node->right = new tree;
      node->right->left = nullptr;
      node->right->right = nullptr;
      node->right->leaf = 1;
      node->right->val = b.val;
      node->right->freq = b.freq;
    } else
      node->right = b.node;

    list.push_front({0, node->freq, 0, node});

    std::sort(list.begin(), list.end(),
        [](auto i, auto j) { return i.freq < j.freq; });
  }
  tree *root = list[0].node;

  std::vector<char> stream = {
    0, 0, 0, 1, 0, 1, // 6 bits saying 5 bits for frequency
    0, 0, 0, 1, 1, 1}; // 6 bits saying 7 bits for value

  outputtree(5, 7, root, &stream);

  for (size_t i = 0; i < text.length(); i++) {
    std::string code = "";
    bool success = false;
    findtree(root, text[i], code, success);
    for (char &c : code)
      stream.push_back(c-'0');
  }

  while (stream.size() % 8)
    stream.push_back(0);

  printf("original message size: %zu B\ncompressed incl. tree: %zu B\n",
      text.size(), stream.size()/8);

  std::vector<unsigned char> file;
  unsigned char current = 0, i = 1;
  for (char &c : stream) {
    current += c * po2(8-i);
    i++;
    if (i > 8) {
      file.push_back(current);
      current = 0;
      i = 1;
    }
  }

  FILE *fd = fopen("in", "wb");
  if (!fd)
    die("failed to open file to read \"in\"");
  fwrite(file.data(), sizeof(unsigned char),
      file.size()*sizeof(unsigned char), fd);
  fclose(fd);

  return 0;
}

// vim: et:ts=2:sw=2

