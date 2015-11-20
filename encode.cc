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

void ntobinary(int bits, int n, std::vector<char> *stream)
{
  std::vector<char> buf;
  int i = 0;
  while (n) {
    i++;
    buf.push_back(n % 2);
    n /= 2;
  }
  if (buf.size() > pow(2, (size_t)bits+1)-1)
    die("%d bits is not enough", bits);
  for (int j = i; j <= bits; j++)
    buf.push_back(0);
  for (i = 0; i < bits; i++)
    stream->push_back(buf[bits-i-1]);
}

void outputtree(int bits, tree *node, std::vector<char> *stream)
{
  if (node->leaf) {
    stream->push_back(1);
    ntobinary(bits, (int)node->freq, stream);
    ntobinary(bits, (int)node->val, stream);
  } else {
    stream->push_back(0);
    outputtree(bits, node->left, stream);
    outputtree(bits, node->right, stream);
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

  for (size_t i = 0; i < text.length(); i++) {
    std::string code = "";
    bool success = false;
    findtree(root, text[i], code, success);
    printf("'%c' = %s\n", text[i], code.c_str());
  }

  std::vector<char> stream;
  stream.push_back(0);
  stream.push_back(0);
  stream.push_back(0);
  stream.push_back(1);
  stream.push_back(0);
  stream.push_back(1); // 6 bits saying 5 bits
  outputtree(5, root, &stream);

  for (char c : stream)
    printf("%c", '0'+c);
  puts("");

  // FILE *f = fopen("in", "wb");
  // tree root =

  return 0;
}

// vim: et:ts=2:sw=2

