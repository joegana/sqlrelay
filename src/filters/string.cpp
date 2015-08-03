// Copyright (c) 2015  David Muse
// See the file COPYING for more information

#include <sqlrelay/sqlrserver.h>
#include <rudiments/character.h>
#include <debugprint.h>

class SQLRSERVER_DLLSPEC string : public sqlrfilter {
	public:
			string(sqlrfilters *sqlrfs,
					xmldomnode *parameters,
					bool debug);
			~string();
		bool	run(sqlrserverconnection *sqlrcon,
					sqlrservercursor *sqlrcur,
					const char *query);
	private:
		const char		*pattern;
		char			*lowerpattern;
		bool			ignorecase;

		bool	enabled;
};

string::string(sqlrfilters *sqlrfs,
				xmldomnode *parameters,
				bool debug) :
				sqlrfilter(sqlrfs,parameters,debug) {
	debugFunction();

	enabled=charstring::compareIgnoringCase(
			parameters->getAttributeValue("enabled"),"no");
	if (!enabled) {
		return;
	}

	pattern=parameters->getAttributeValue("pattern");

	ignorecase=!charstring::compareIgnoringCase(
			parameters->getAttributeValue("ignorecase"),"yes");

	lowerpattern=NULL;
	if (ignorecase) {
		lowerpattern=charstring::duplicate(pattern);
		for (char *c=lowerpattern; *c; c++) {
			*c=character::toLowerCase(*c);
		}
		pattern=lowerpattern;
	}
}

string::~string() {
	delete[] lowerpattern;
}

bool string::run(sqlrserverconnection *sqlrcon,
				sqlrservercursor *sqlrcur,
				const char *query) {
	debugFunction();

	if (!enabled) {
		return true;
	}

	char	*lowered=NULL;
	if (ignorecase) {
		lowered=charstring::duplicate(query);
		for (char *c=lowered; *c; c++) {
			*c=character::toLowerCase(*c);
		}
		query=lowered;
	}

	bool	result=!charstring::contains(query,pattern);

	if (result && debug) {
		stdoutput.printf("string: matches pattern \"%s\"\n\n",pattern);
	}

	delete[] lowered;
	return result;
}

extern "C" {
	SQLRSERVER_DLLSPEC sqlrfilter
			*new_sqlrfilter_string(sqlrfilters *sqlrfs,
							xmldomnode *parameters,
							bool debug) {
		return new string(sqlrfs,parameters,debug);
	}
}