// Copyright (c) 2000-2001  David Muse
// See the file COPYING for more information

#ifndef MSQLCONNECTION_H
#define MSQLCONNECTION_H

#define NUM_CONNECT_STRING_VARS 2

#include <sqlrconnection.h>

#include <msql.h>

class msqlconnection;

class msqlcursor : public sqlrcursor_svr {
	friend class msqlconnection;
	private:
				msqlcursor(sqlrconnection_svr *conn);
				~msqlcursor();
		bool		executeQuery(const char *query,
						uint32_t length,
						bool execute);
		const char	*errorMessage(bool *liveconnection);
		bool		knowsRowCount();
		uint64_t	rowCount();
		bool		knowsAffectedRows();
		uint64_t	affectedRows();
		uint32_t	colCount();
		const char * const * columnNames();
		uint16_t	columnTypeFormat();
		void		returnColumnInfo();
		bool		noRowsToReturn();
		bool		skipRow();
		bool		fetchRow();
		void		returnRow();
		void		cleanUpData(bool freeresult, bool freebinds);

		m_result	*msqlresult;
		m_field		*msqlfield;
		char		**columnnames;
		m_row		msqlrow;
		int		ncols;
		int		nrows;

		msqlconnection	*msqlconn;
};

class msqlconnection : public sqlrconnection_svr {
	friend class msqlcursor;
	public:
			msqlconnection();
	private:
		uint16_t	getNumberOfConnectStringVars();
		bool		supportsNativeBinds();
		void	handleConnectString();
		bool	logIn();
		sqlrcursor_svr	*initCursor();
		void	deleteCursor(sqlrcursor_svr *curs);
		void	logOut();
		bool	isTransactional();
		bool	ping();
		const char	*identify();
		bool	autoCommitOn();
		bool	autoCommitOff();
		bool	commit();
		bool	rollback();

		int	msql;

		const char	*host;
		const char	*db;

		int	devnull;
};

#endif
