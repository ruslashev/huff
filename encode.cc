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

void printree(tree *node, int indent=0)
{
  const char *indstr = "|";
  if (node->leaf) {
    for (int i = 0; i < indent; i++)
      printf("%s", indstr);
    printf("%d:'%c'\n", node->freq, node->val);
  } else {
    for (int i = 0; i < indent; i++)
      printf("%s", indstr);
    printf("^ %d\n", node->freq);
    if (node->left)
      printree(node->left, indent+1);
    if (node->right)
      printree(node->right, indent+1);
    for (int i = 0; i < indent; i++)
      printf("%s", indstr);
    printf("v\n");
  }
}

void findtree(tree *node, char val, std::string &code, bool &success)
{
  // h: 0100
  if (node->leaf) {
    if (node->val == val)
      success = 1;
  } else {
    code += '0';
    findtree(node->left, val, code, success);
    if (success)
      return;
    code.pop_back();
    code += '1';
    findtree(node->right, val, code, success);
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
  printree(root);

  for (size_t i = 0; i < text.length(); i++) {
    std::string code = "";
    bool success = false;
    findtree(root, text[i], code, success);
    printf("'%c' = %s\n", text[i], code.c_str());
  }

  // FILE *f = fopen("in", "wb");
  // tree root = 

  return 0;
}

// vim: et:ts=2:sw=2

