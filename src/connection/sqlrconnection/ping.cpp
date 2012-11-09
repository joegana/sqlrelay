// Copyright (c) 1999-2001  David Muse
// See the file COPYING for more information

#include <sqlrconnection.h>

void sqlrconnection_svr::pingCommand() {
	dbgfile.debugPrint("connection",1,"ping");
	bool	pingresult=ping();
	clientsock->write(pingresult);
	flushWriteBuffer();
	if (!pingresult) {
		reLogIn();
	}
}

bool sqlrconnection_svr::ping() {
	sqlrcursor_svr	*pingcur=initCursorInternal();
	const char	*pingquery=pingQuery();
	int		pingquerylen=charstring::length(pingquery);
	// since we're creating a new cursor for this, make sure it can't
	// have an ID that might already exist
	if (pingcur->openCursorInternal(cursorcount+1) &&
		pingcur->prepareQuery(pingquery,pingquerylen) &&
		executeQueryInternal(pingcur,pingquery,pingquerylen)) {
		pingcur->cleanUpData(true,true);
		pingcur->closeCursor();
		deleteCursorInternal(pingcur);
		return true;
	}
	pingcur->closeCursor();
	deleteCursorInternal(pingcur);
	return false;
}

const char *sqlrconnection_svr::pingQuery() {
	return "select 1";
}
