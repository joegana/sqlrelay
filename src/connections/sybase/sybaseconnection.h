// Copyright (c) 2000-2001  David Muse
// See the file COPYING for more information

#ifndef SYBASECONNECTION_H
#define SYBASECONNECTION_H

#define FETCH_AT_ONCE		10
#define MAX_SELECT_LIST_SIZE	256
#define MAX_ITEM_BUFFER_SIZE	4096
#define MAX_BIND_VARS		512

#define NUM_CONNECT_STRING_VARS 11

#include <rudiments/environment.h>
#include <sqlrconnection.h>

extern "C" {
	#include <ctpublic.h>
}

class sybaseconnection;

class sybasecursor : public sqlrcursor {
	friend class sybaseconnection;
	private:
			sybasecursor(sqlrconnection *conn);
			~sybasecursor();
		bool	openCursor(int id);
		bool	closeCursor();
		bool	prepareQuery(const char *query, long length);
		bool	inputBindString(const char *variable,
						unsigned short variablesize,
						const char *value,
						unsigned short valuesize,
						short *isnull);
		bool	inputBindLong(const char *variable,
						unsigned short variablesize,
						unsigned long *value);
		bool	inputBindDouble(const char *variable,
						unsigned short variablesize,
						double *value,
						unsigned short precision,
						unsigned short scale);
		bool	outputBindString(const char *variable, 
						unsigned short variablesize,
						char *value, 
						unsigned short valuesize, 
						short *isnull);
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
		void	cleanUpData(bool freeresult, bool freebinds);
		void	discardResults();
		void	discardCursor();

		char	*cursorname;

		void	checkRePrepare();

		CS_COMMAND	*languagecmd;
		CS_COMMAND	*cursorcmd;
		CS_COMMAND	*cmd;
		CS_INT		results;
		CS_INT		resultstype;
		CS_INT		ncols;
		CS_INT		affectedrows;

		CS_INT		rowsread;
		int		row;
		int		maxrow;
		int		totalrows;

		CS_DATAFMT	parameter[MAX_BIND_VARS];
		int		paramindex;
		char		*outbindvalues[MAX_BIND_VARS];
		unsigned short	outbindvaluelengths[MAX_BIND_VARS];
		int		outbindindex;

		CS_DATAFMT	column[MAX_SELECT_LIST_SIZE];
		char		data[MAX_SELECT_LIST_SIZE]
					[FETCH_AT_ONCE]
					[MAX_ITEM_BUFFER_SIZE];
		CS_INT		datalength[MAX_SELECT_LIST_SIZE]
					[FETCH_AT_ONCE];
		CS_SMALLINT	nullindicator[MAX_SELECT_LIST_SIZE]
					[FETCH_AT_ONCE];

		char		*query;
		int		length;
		bool		prepared;
		bool		clean;

		regularexpression	cursorquery;
		regularexpression	rpcquery;

		bool			isrpcquery;

		sybaseconnection	*sybaseconn;
};


class sybaseconnection : public sqlrconnection {
	friend class sybasecursor;
	public:
			sybaseconnection();
			~sybaseconnection();
	private:
		int	getNumberOfConnectStringVars();
		void	handleConnectString();
		bool	logIn();
		void	logInError(const char *error, int stage);
		sqlrcursor	*initCursor();
		void	deleteCursor(sqlrcursor *curs);
		void	logOut();
		char	*identify();
		char	bindVariablePrefix();
		void	dropTempTable(sqlrcursor *cursor,
					const char *tablename);

		CS_CONTEXT	*context;
		CS_LOCALE	*locale;
		CS_CONNECTION	*dbconn;

		char		*sybase;
		char		*lang;
		char		*server;
		char		*db;
		char		*charset;
		char		*language;
		char		*encryption;
		int		enc;
		char		*hostname;
		char		*packetsize;

		environment	*env;

		static	stringbuffer	*errorstring;
		static	bool		deadconnection;

		static	CS_RETCODE	csMessageCallback(CS_CONTEXT *ctxt,
						CS_CLIENTMSG *msgp);
		static	CS_RETCODE	clientMessageCallback(CS_CONTEXT *ctxt,
						CS_CONNECTION *cnn,
						CS_CLIENTMSG *msgp);
		static	CS_RETCODE	serverMessageCallback(CS_CONTEXT *ctxt,
						CS_CONNECTION *cnn,
						CS_SERVERMSG *msgp);
};

#endif
