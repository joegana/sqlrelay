// Copyright (c) 2000-2001  David Muse
// See the file COPYING for more information

#ifndef LAGOCONNECTION_H
#define LAGOCONNECTION_H

#define NUM_CONNECT_STRING_VARS 5

#include <sqlrconnection.h>

#include <lago.h>

class lagoconnection;

class lagocursor : public sqlrcursor {
	friend class lagoconnection;
	private:
			lagocursor(sqlrconnection *conn);
		bool	executeQuery(const char *query,
					long length,
					bool execute);
		char	*getErrorMessage(bool *liveconnection);
		void	returnRowCounts();
		void	returnColumnCount();
		void	returnColumnInfo();
		bool	noRowsToReturn();
		bool	skipRow();
		bool	fetchRow();
		void	returnRow();
		void	cleanUpData(bool freerows,
					bool freecols,
					bool freebinds);

		LRST	lagoresult;
		int	ncols;
		int	nrows;
		int	affectedrows;

		lagoconnection	*lagoconn;
};

class lagoconnection : public sqlrconnection {
	friend class lagocursor;
	private:
		int	getNumberOfConnectStringVars();
		void	handleConnectString();
		bool	logIn();
		sqlrcursor	*initCursor();
		void	deleteCursor(sqlrcursor *curs);
		void	logOut();
		bool	ping();
		char	*identify();
		bool	isTransactional();
		bool	autoCommitOn();
		bool	autoCommitOff();
		bool	commit();
		bool	rollback();

		LCTX	lagocontext;

		char	*host;
		char	*port;
		char	*db;
};

#endif
