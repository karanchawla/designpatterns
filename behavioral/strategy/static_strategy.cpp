/**
 * @file dynamic_strategy.cpp
 * @author Karan Chawla (krnchwla@gmail.com)
 * @brief This example shows how the Strategy pattern can be used to statically
 * select the text processor (markdown or html) for list creation.
 * HTML: <ul>
 * <li> Foo
 * <li> Bar
 * <ul>
 * Markdown:
 * * Foo
 * * Bar
 * @date 2022-03-15
 */

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

enum class OutputFormat { Markdown, Html };

struct ListStrategy {
  virtual ~ListStrategy() = default;
  virtual void add_list_item(ostringstream &oss, const string &item) = 0;
  virtual void start(ostringstream &oss) = 0;
  virtual void end(ostringstream &oss) = 0;
};

struct MarkdownListStrategy : ListStrategy {
  // NOTE: Since there's no dynamic polymorphism, we are forced to implement the
  // start() and end() methods.

  void start(ostringstream &) override {}
  void end(ostringstream &) override {}
  void add_list_item(ostringstream &oss, const string &item) override {
    oss << " * " << item << endl;
  }
};

struct HtmlListStrategy : ListStrategy {
  void start(ostringstream &oss) override { oss << "<ul>" << endl; }
  void end(ostringstream &oss) override { oss << "</ul>" << endl; }
  void add_list_item(ostringstream &oss, const string &item) override {
    oss << "<li>" << item << "</li>" << endl;
  }
};

// Template parameter allows us to define the strategy statically.
// However, we cannot switch at runtime.
template <typename Strategy>
struct TextProcessor {
  void clear() {
    oss.str("");
    oss.clear();
  }

  void append_list(const vector<string> &items) {
    list_strategy.start(oss);
    for (auto &item : items) list_strategy.add_list_item(oss, item);
    list_strategy.end(oss);
  }

  string str() const { return oss.str(); }

 private:
  ostringstream oss;
  Strategy list_strategy;
};

void main() {
  // Markdown
  TextProcessor<MarkdownListStrategy> tpm;
  tpm.append_list({"foo", "bar", "baz"});
  cout << tpm.str() << endl;

  // HTML
  TextProcessor<HtmlListStrategy> tph;
  tph.append_list({"foo", "bar", "baz"});
  cout << tph.str() << endl;
}