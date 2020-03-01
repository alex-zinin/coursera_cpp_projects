#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
    unique_ptr<Worker> next;

    Worker(): next() {}
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
      throw logic_error("Unimplemented");
  }

protected:
    void PassOn(unique_ptr<Email> email) const
  {
      if(next.get() != nullptr)
          next->Process(move(email));
  }

public:
  void SetNext(unique_ptr<Worker> nex)
  {
      next = move(nex);
  }
};


class Reader : public Worker {
public:

  explicit Reader(istream& input): emails()
  {
      string from, to, body;
      while(!input.eof())
      {
          getline(input, from);
          if(input.eof())
              break;
          getline(input, to);
          if(input.eof())
              break;
          getline(input, body);
          if(input.eof())
              break;
          emails.push_back(make_unique<Email>(Email{from, to, body}));
      }
  }

  void Process(unique_ptr<Email> email) override
  {
        PassOn(move(email));
  }

  void Run()
  {
    for(auto& x: emails)
        Process(move(x));
  }

public:
    vector<unique_ptr<Email>> emails;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;
    explicit Filter(Function func): funct(func) {}

    void Process(unique_ptr<Email> email)
    {
        if(funct(*email))
        {
            PassOn(move(email));
        }
    }
public:
    Function funct;

};


class Copier : public Worker {
public:
    explicit Copier(const string& adr): adress(adr) {}

  void Process(unique_ptr<Email> email)
  {
    if(adress != (*email).to)
    {
        Email em = *email;
        em.to = adress;
        PassOn(move(email));
        PassOn(make_unique<Email>(Email{em.from, em.to, em.body}));
    } else{
        PassOn(move(email));
    }
  }

public:
    string adress;
};


class Sender : public Worker {
public:
    explicit Sender(ostream& outpt): output(outpt) {}

    void Process(unique_ptr<Email> email)
    {
        output << (email->from) << endl << (email->to) << endl << (email->body) << endl;
        PassOn(move(email));
    }

private:
    ostream& output;
};


class PipelineBuilder {
public:

  explicit PipelineBuilder(istream& in): handlers()
  {
      first_handler = make_unique<Reader>(in);
      last_handler = first_handler.get();
  }


  PipelineBuilder& FilterBy(Filter::Function filter)
  {
      (last_handler)->SetNext(make_unique<Filter>(filter));
      last_handler = last_handler->next.get();

      return *this;
  }

  PipelineBuilder& CopyTo(const string& recipient)
  {
      (last_handler)->SetNext(make_unique<Copier>(recipient));
      last_handler = last_handler->next.get();

      return *this;
  }


  PipelineBuilder& Send(ostream& out)
  {
      (last_handler)->SetNext(make_unique<Sender>(out));
      last_handler = last_handler->next.get();

      return *this;
  }

  unique_ptr<Worker> Build()
  {
      return move(first_handler);
  }

private:
    vector<unique_ptr<Worker>> handlers;
    unique_ptr<Worker> first_handler;
    Worker* last_handler;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}