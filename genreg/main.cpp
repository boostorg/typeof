#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

template<class T, class Tokenizer>
    T getTokenAt(const Tokenizer& tokens, size_t pos)
{
    typename Tokenizer::iterator it = tokens.begin();

    for (size_t i = 0; i < pos; ++i)
    {
        if (++it == tokens.end())
            break;
    }

    if (it == tokens.end())
        throw runtime_error("line parsing error -- not enough tokens");

    return lexical_cast<T>(*it);
}

string name2path(const string& name, const string& ext)
{
    return string("../../../boost/typeof/std/") + name + "." + ext;
}

string copyright(const string& master)
{
    return
        "// Copyright (C) 2005 " + master + ".\n"
        "// Use, modification and distribution is subject to the Boost Software\n"
        "// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)\n\n"
        "// This is a generated file -- please do not modify by hand."
        ;
}

class ofile
{
public:
    ofile(const string& name, const string& ext)
        : m_out(name2path(name, ext).c_str())
        , m_isnew(true)
    {
        if (!m_out.is_open())
            throw runtime_error(name2path(name, ext) + " -- can't create");

        m_guard = "BOOST_TYPEOF_STD_" + name + "_" + ext + "_INCLUDED";
        
        m_out << copyright("Arkadiy Vertleyb, Peder Holt") << endl;
        m_out << endl;
        m_out << "#ifndef " << m_guard << endl;
        m_out << "#define " << m_guard << endl;
        m_out << endl;
    }

    ~ofile()
    {
        m_out << endl;
        m_out << "#endif//" << m_guard << endl;
    }

    void operator()(const string& text)
    {
        if (m_isnew)
        {
            m_isnew = false;
            m_out << endl << "#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()" << endl << endl;
        }

        if (text[0] == '#')
        {
            m_out << text << endl;
            return;
        }

        tokenizer<escaped_list_separator<char> > tokens(text, escaped_list_separator<char>('\\', ',', '\"'));

        string what = getTokenAt<string>(tokens, 0);
        string name = getTokenAt<string>(tokens, 1);

        if (what == "TEMPLATE")
        {
            int nMin = getTokenAt<int>(tokens, 2);
            int nMax = nMin;

            try
            {
                nMax = getTokenAt<int>(tokens, 3);
            }
            catch(const runtime_error&)
            {}

            for (int i = nMin; i <= nMax; ++i)
            {
                if (i == nMin && i != nMax)
                    m_out << "#ifdef BOOST_TYPEOF_COMPLIANT" << endl;

                if (i == nMax && i != nMin)
                    m_out << "#endif//BOOST_TYPEOF_COMPLIANT" << endl;

                m_out << "BOOST_TYPEOF_REGISTER_TEMPLATE(" << name << ", " << i << ")" << endl;
            }
        }
        else if (what == "TYPE")
        {
            m_out << "BOOST_TYPEOF_REGISTER_TYPE(" << name << ")" << endl;
        }
        else if (what == "TEMPLATE_X")
        {
            string params = getTokenAt<string>(tokens, 2);
            m_out << "BOOST_TYPEOF_REGISTER_TEMPLATE(" << name << ", " << params << ")" << endl; 
        }
        else
        {
            throw runtime_error(string("Can't register ") + what);
        }
    }
    void include(const string& path)
    {
        m_out << "#include <" << path << ">" << endl;
    }
private:
    ofstream m_out;
    string m_guard;
    bool m_isnew;
};

int main() 
{
    try
    {
        string text;
        boost::shared_ptr<ofile> file_ptr;
        
        ifstream in("input.txt");

        while(getline(in, text))
        {
            if (text.empty())
            {
                continue;
            }
            else if (text[0] == '~')
            {
                string name = text.substr(1);
                file_ptr.reset(new ofile(name, "hpp"));
                file_ptr->include(name);
                file_ptr->include("boost/typeof/typeof.hpp");
            }
            else if (text[0] == '@')
            {
                string name = text.substr(1);
                file_ptr->include(string("boost/typeof/std/") + name + ".hpp");
            }
            else
            {
                (*file_ptr)(text);
            }
        }
        return 0;
    }
    catch(const runtime_error& err)
    {
        cout << err.what() << endl;
        return 1;
    }
    catch(const bad_lexical_cast& err)
    {
        cout << err.what() << endl;
        return 1;
    }
}
