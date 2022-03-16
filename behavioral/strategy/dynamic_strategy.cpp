/**
 * @file dynamic_strategy.cpp
 * @author Karan Chawla (krnchwla@gmail.com)
 * @brief This example shows how the Strategy pattern can be used to dynamically
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

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

enum class OutputFormat { Markdown, Html };

struct ListStrategy {
  virtual ~ListStrategy() = default;

  // Common Behavior
  virtual void add_list_item(std::ostringstream &, const std::string &){};
  virtual void start(std::ostringstream &){};
  virtual void end(std::ostringstream &){};
};

struct MarkdownListStrategy : ListStrategy {
  // specific behavior
  void add_list_item(std::ostringstream &oss,
                     const std::string &item) override {
    oss << " * " << item << std::endl;
  }

  // NOTE: dynamic polymorphism allows us to not implement the start() and end()
  // methods.
};

struct HtmlListStrategy : ListStrategy {
  // specific behavior
  void start(std::ostringstream &oss) override { oss << "<ul>" << std::endl; }
  void end(std::ostringstream &oss) override { oss << "</ul>" << std::endl; }
  void add_list_item(std::ostringstream &oss,
                     const std::string &item) override {
    oss << "<li>" << item << "</li>" << std::endl;
  }
};

struct TextProcessor {
  void clear() {
    oss.str("");
    oss.clear();
  }

  void append_list(const std::vector<std::string> &items) {
    // User calls the general interface, independent of the actual
    // implementation.
    list_strategy->start(oss);
    for (const std::string &item : items)
      list_strategy->add_list_item(oss, item);
    list_strategy->end(oss);
  }

  void set_output_format(const OutputFormat format) {
    switch (format) {
      case OutputFormat::Markdown:
        list_strategy = std::make_unique<MarkdownListStrategy>();
        break;
      case OutputFormat::Html:
        list_strategy = std::make_unique<HtmlListStrategy>();
        break;
      default:
        throw std::runtime_error("Unsupported strategy.");
    }
  }
  std::string str() const { return oss.str(); }

 private:
  std::ostringstream oss;

  // Pointer or reference to allow dynamic polymorphism
  std::unique_ptr<ListStrategy> list_strategy;
};

int main() {
  // markdown
  TextProcessor processor;
  processor.set_output_format(OutputFormat::Markdown);
  processor.append_list({"foo", "bar", "baz"});
  std::cout << processor.str() << std::endl;

  // html
  processor.clear();
  processor.set_output_format(OutputFormat::Html);
  processor.append_list({"foo", "bar", "baz"});
  std::cout << processor.str() << std::endl;

  return 0;
}