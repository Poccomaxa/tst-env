#include "stdafx.h"
#include "Parser.h"
#include "utils.h"

using namespace std;
using namespace boost::algorithm;

void Parser::parse(std::istream &in) {
	string buf;
	while (in) {
		getline(in, buf);
		vector<string> parts;
		split(parts, buf, boost::is_any_of(":"));
		
		for_each(parts.begin(), parts.end(), boost::bind(&trim<string>, _1, std::locale() ));
		for_each(parts.begin(), parts.end(), [](string &st) { lout << st << endl; });
	}
}