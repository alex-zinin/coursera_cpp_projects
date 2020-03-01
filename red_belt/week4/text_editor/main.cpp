#include <string>
#include "test_runner.h"
#include<string_view>
#include"profile.h"
#include<list>
#include<deque>
#include<algorithm>
#include<iterator>

using namespace std;

class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor(): text(), buffer_size(0)
    {
        text.clear();
        pos = text.begin();
    }

    void Left()
    {
        if(pos != text.begin())
        {
            pos--;
        }
    }

    void Right()
    {
        if(pos != text.end())
        {
            pos++;
        }
    }

    void Insert(const char& token)
    {
        auto it = text.insert(pos, token);
        it++;
        pos = it;
    }

    void Cut(size_t tokens)
    {
        if(tokens == 0 || pos == text.end() || text.empty())
        {
            buffer_size = 0;
            return;
        }

        auto it = pos;
        int size = 0;
        for(int i = 0; i < tokens; i++)
        {
            it++;
            size++;
            if(it == text.end())
                break;
        }
        if(it != text.end())
        {
            move(pos, it, buffer.begin());
            buffer_size = tokens;
            pos = text.erase(pos, it);
        } else
        {
            move(pos, text.end(), buffer.begin());
            buffer_size = size;
            text.erase(pos, text.end());
            pos = text.end();
        }
    }

    void Copy(size_t tokens)
    {
        if(tokens == 0 || pos == text.end() || text.empty())
        {
            buffer_size = 0;
            return;
        }

        auto it = pos;
        int size = 0;
        for(int i = 0; i < tokens; i++)
        {
            it++;
            size++;
            if(it == text.end())
                break;
        }
        if(it != text.end())
        {
            move(pos, it, buffer.begin());
            buffer_size = tokens;
        }
        else
        {
            move(pos, text.end(), buffer.begin());
            buffer_size = size;
        }
    }

    void Paste()
    {
        if(buffer_size != 0)
            pos = text.insert(pos, buffer.begin(), buffer.begin() + buffer_size);
        for(int i = 0; i < buffer_size; i++)
            pos++;
    }

    string GetText() const
    {
        return string(text.begin(), text.end());
    }

public:
    list<char> text;
    list<char>::iterator pos;
    int buffer_size;
    deque<char> buffer;
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");//cout << editor.text << endl;
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }//cout << *editor.it << endl;
        editor.Cut(first_part_len);//cout << editor.buffer << "?" << endl;
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");//cout << editor.text << endl;
        editor.Paste();// cout << *editor.pos << endl;
        editor.Left();
        editor.Left();
        editor.Cut(3);//

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

void MyTest()
{
    Editor editor;
    TypeText(editor, "sfa");
    editor.Cut(10);
    editor.Paste();
    editor.Left();
    editor.Right();
    ASSERT_EQUAL(editor.GetText(), "sfa");

}

void Testing_Cut()
{
    Editor editor;
    //1
    editor.Cut(10);
    editor.Insert('a');
    editor.Left();
    //2
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    //3
    editor.Cut(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    TypeText(editor, "bcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //5
    editor.Cut(5);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    //6
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bcde");
    editor.Right();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bde");
    editor.Cut(1);
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "b");
}

void Testing_Copy()
{
    Editor editor;
    //1
    editor.Copy(10);
    editor.Insert('a');
    editor.Paste();
    editor.Left();
    ASSERT_EQUAL(editor.GetText(), "a");
    //2
    editor.Copy(1);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");//between a
    //3
    editor.Copy(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");
    TypeText(editor, "bcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcdea");
}


void RunTimeTest()
{

    Editor editor;
    LOG_DURATION("RUN_TIME_TEST:");
    for(int i = 0; i < 199000; i++)
    {
        editor.Insert('a');
        editor.Insert('q');
        editor.Insert('f');
        editor.Insert('u');
        editor.Insert('k');
    }
    for(int i = 0; i < 500000; i++)
    {
        //int a = (editor.text.end() - editor.text.begin())/2;
        //editor.pos = editor.text.begin() + a;(int) (editor.text.end() - editor.text.begin())/2;
        editor.Paste();
        editor.Copy(10);
        editor.Right();
        editor.Paste();
        editor.Cut(10);
    }

}
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    RUN_TEST(tr, MyTest);
    RUN_TEST(tr, Testing_Copy);
    RUN_TEST(tr, Testing_Cut);
    RUN_TEST(tr, RunTimeTest);
    return 0;
}