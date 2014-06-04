// Copyright (c) 2014  David Muse
// See the file COPYING for more information

#include <sqlrelay/sqlrcontroller.h>
#include <sqlrelay/sqlrconnection.h>
#include <sqlrelay/sqlrcursor.h>
#include <sqlrelay/sqlparser.h>
#include <sqlrelay/sqlrresultsettranslation.h>
#include <debugprint.h>

class reformatdatetime : public sqlrresultsettranslation {
	public:
			reformatdatetime(sqlrresultsettranslations *sqlrrsts,
							xmldomnode *parameters);
			~reformatdatetime();
		bool	run(sqlrconnection_svr *sqlrcon,
					sqlrcursor_svr *sqlrcur,
					uint16_t fieldindex,
					const char *field,
					uint32_t fieldlength,
					const char **newfield,
					uint32_t *newfieldlength);
	private:
		char		*reformattedfield;
		uint32_t	reformattedfieldlength;

		bool		ddmm;
		bool		yyyyddmm;
		const char	*datetimeformat;
		const char	*dateformat;
		const char	*timeformat;
};

reformatdatetime::reformatdatetime(sqlrresultsettranslations *sqlrrsts,
						xmldomnode *parameters) :
				sqlrresultsettranslation(sqlrrsts,parameters) {

	reformattedfield=NULL;
	reformattedfieldlength=0;

	// get the parameters
	const char	*dateddmm=
			parameters->getAttributeValue("dateddmm");
	const char	*dateyyyyddmm=
			parameters->getAttributeValue("dateyyyyddmm");
	if (charstring::length(dateddmm) &&
		!charstring::length(dateyyyyddmm)) {
		dateyyyyddmm=dateddmm;
	}
	ddmm=!charstring::compareIgnoringCase(dateddmm,"yes");
	yyyyddmm=!charstring::compareIgnoringCase(dateyyyyddmm,"yes");

	datetimeformat=parameters->getAttributeValue("datetimeformat");
	dateformat=parameters->getAttributeValue("dateformat");
	timeformat=parameters->getAttributeValue("timeformat");

}

reformatdatetime::~reformatdatetime() {
	delete[] reformattedfield;
}

bool reformatdatetime::run(sqlrconnection_svr *sqlrcon,
					sqlrcursor_svr *sqlrcur,
					uint16_t fieldindex,
					const char *field,
					uint32_t fieldlength,
					const char **newfield,
					uint32_t *newfieldlength) {
	debugFunction();

	// For now, call the sqlrcontroller method.
	// Eventually that code should be moved here.
	sqlrcon->cont->reformatDateTimes(sqlrcur,fieldindex,
					field,fieldlength,
					newfield,newfieldlength,
					ddmm,yyyyddmm,
					datetimeformat,
					dateformat,
					timeformat);

	return true;
}

extern "C" {
	sqlrresultsettranslation *new_reformatdatetime(
					sqlrresultsettranslations *sqlrrsts,
					xmldomnode *parameters) {
		return new reformatdatetime(sqlrrsts,parameters);
	}
}