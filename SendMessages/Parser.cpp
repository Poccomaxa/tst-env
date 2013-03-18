#include "stdafx.h"
#include "Parser.h"
#include "Processor.h"
#include "utils.h"

using namespace std;
using namespace boost::algorithm;

Scenario *Parser::parse(std::istream &in) {
	string buf;
	curLine = 1;
	Scenario *sc = new Scenario;
	getline(in, buf);
	while (in) {		
		vector<string> parts;
		split(parts, buf, boost::is_any_of("|"));

		if (parts.size() != 3)
			return formErrorMessage("There must be three parts, separated with ':'");

		int i = 0;
		
		Trigger *tr = NULL;
		Command *cmd = NULL;
		lout << "Line: " << curLine << " ";
		for (vector<string>::iterator it = parts.begin(); it != parts.end(); ++it ,++i) {
		
			trim(*it);

			vector<string> args;
			split(args, *it, boost::is_any_of(","));
			for_each(args.begin(), args.end(), boost::bind(trim<std::string>, _1, std::locale()));
			for_each(args.begin(), args.end(), boost::bind(to_lower<std::string>, _1, std::locale()));

			switch(i) {
			case 0:
				tr = tf.createTrigger(args);
				break;
			case 1:
				cmd = cf.createCommand(args);
				break;				
			case 2:
				break;
			}
			
		}
		if (tr && cmd)
			lout << "SUCCESS" << endl;

		sc->addInstruction(Instruction(tr, cmd));

		++curLine;
		getline(in, buf);
	}

	return sc;
}

Scenario *Parser::formErrorMessage(const std::string &er) {
	stringstream ss;
	ss << "Line: " << curLine << L"Error: " << er << endl;
	Processor::get().ShowMessage(ss.str());
	lout << ss.str();
	return NULL;
}