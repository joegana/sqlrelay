// Copyright (c) 1999-2001  David Muse
// See the file COPYING for more information

#include <mdbtoolsconnection.h>

extern "C" {
        #include <mdbsql.h>
}

#include <config.h>

#include <datatypes.h>

#if defined(HAVE_MDB_RUN_QUERY)
	// it's called mdb_sql_run_query in the .h file,
	// but mdb_run_query in the library
	extern "C" int mdb_run_query(MdbSQL *sql, char *query);
#elif !defined(HAVE_MDB_SQL_RUN_QUERY)
	extern "C" MdbSQL * _mdb_sql(MdbSQL *sql);
	extern "C" int yyparse();
#endif

mdbtoolsconnection::mdbtoolsconnection() : sqlrconnection_svr() {
}

uint16_t mdbtoolsconnection::getNumberOfConnectStringVars() {
	return NUM_CONNECT_STRING_VARS;
}

void mdbtoolsconnection::handleConnectString() {
	db=connectStringValue("db");
}

bool mdbtoolsconnection::logIn(bool printerrors) {
	return true;
}

sqlrcursor_svr *mdbtoolsconnection::initCursor() {
	return (sqlrcursor_svr *)new mdbtoolscursor((sqlrconnection_svr *)this);
}

void mdbtoolsconnection::deleteCursor(sqlrcursor_svr *curs) {
	delete (mdbtoolscursor *)curs;
}

void mdbtoolsconnection::logOut() {
}

bool mdbtoolsconnection::ping() {
	return true;
}

const char *mdbtoolsconnection::identify() {
	return "mdbtools";
}

const char *mdbtoolsconnection::dbVersion() {
#ifdef MDB_VERSION_NO
	return MDB_VERSION_NO;
#else
	return "unknown";
#endif
}

bool mdbtoolsconnection::getDatabaseList(sqlrcursor_svr *cursor,
					const char *wild,
					char ***cols,
					uint32_t *colcount,
					char ****rows,
					uint64_t *rowcount) {
	// FIXME: I'm not sure there's any way to get this, or even if 
	// a "database list" exists in an mdb file.  Send back something 
	// though.
	return false;
}

bool mdbtoolsconnection::getTableList(sqlrcursor_svr *cursor,
					const char *wild,
					char ***cols,
					uint32_t *colcount,
					char ****rows,
					uint64_t *rowcount) {
	// FIXME: I'm not sure what to call to get this but mdb-tables
	// does it somehow.
	return false;
}

bool mdbtoolsconnection::getColumnList(sqlrcursor_svr *cursor,
					const char *table,
					const char *wild,
					char ***cols,
					uint32_t *colcount,
					char ****rows,
					uint64_t *rowcount) {
	// FIXME: I'm not sure what to call to get this.
	return false;
}

bool mdbtoolsconnection::isTransactional() {
	return false;
}

bool mdbtoolsconnection::setIsolationLevel(const char *isolevel) {
	// do nothing
	return true;
}

bool mdbtoolsconnection::autoCommitOn() {
	// do nothing
	return true;
}

bool mdbtoolsconnection::autoCommitOff() {
	// do nothing
	return true;
}

bool mdbtoolsconnection::commit() {
	// do nothing
	return true;
}

bool mdbtoolsconnection::rollback() {
	// do nothing
	return true;
}

mdbtoolscursor::mdbtoolscursor(sqlrconnection_svr *conn) :
					sqlrcursor_svr(conn) {
	mdbtoolsconn=(mdbtoolsconnection *)conn;
	columnnames=NULL;
	mdbsql=(void *)new MdbSQL;
}

mdbtoolscursor::~mdbtoolscursor() {
	delete[] columnnames;
	delete (MdbSQL *)mdbsql;
}

bool mdbtoolscursor::openCursor(uint16_t id) {

	// handle db
	const char	*dbval;
	if (mdbtoolsconn->db && mdbtoolsconn->db[0]) {
		dbval=mdbtoolsconn->db;
	} else {
		dbval="";
	}

	return mdb_sql_open((MdbSQL *)mdbsql,const_cast<char *>(dbval));
}

bool mdbtoolscursor::closeCursor() {

	if (!sqlrcursor_svr::closeCursor()) {
		return false;
	}

	mdb_sql_exit((MdbSQL *)mdbsql);
	return true;
}

bool mdbtoolscursor::supportsNativeBinds() {
	return false;
}

bool mdbtoolscursor::executeQuery(const char *query, uint32_t length,
							bool execute) {

	// execute the query
	mdb_sql_reset((MdbSQL *)mdbsql);
#if defined(HAVE_MDB_RUN_QUERY)
	if (!mdb_run_query((MdbSQL *)mdbsql,(char *)query)) {
		return false;
	}
#elif defined(HAVE_MDB_SQL_RUN_QUERY)
	if (!mdb_sql_run_query((MdbSQL *)mdbsql,(char *)query)) {
		return false;
	}
#else
	g_input_ptr=(char *)query;
	_mdb_sql((MdbSQL *)mdbsql);
	if (yyparse()) {
		return false;
	}
#endif

	return true;
}

void mdbtoolscursor::errorMessage(const char **errorstring,
					int64_t *errorcode,
					bool *liveconnection) {
	*errorstring="error";
	*errorcode=0;
	*liveconnection=true;
}

bool mdbtoolscursor::knowsRowCount() {
	return false;
}

uint64_t mdbtoolscursor::rowCount() {
	return 0;
}

bool mdbtoolscursor::knowsAffectedRows() {
	return false;
}

uint64_t mdbtoolscursor::affectedRows() {
	return 0;
}

uint32_t mdbtoolscursor::colCount() {
	return ((MdbSQL *)mdbsql)->num_columns;
}

const char * const *mdbtoolscursor::columnNames() {
	columnnames=new char *[((MdbSQL *)mdbsql)->num_columns];
	for (unsigned int i=0; i<((MdbSQL *)mdbsql)->num_columns; i++) {
		MdbSQLColumn	*col=(MdbSQLColumn *)
			g_ptr_array_index(((MdbSQL *)mdbsql)->columns,i);
		columnnames[i]=col->name;
	}
	return columnnames;
}

uint16_t mdbtoolscursor::columnTypeFormat() {
	return (uint16_t)COLUMN_TYPE_IDS;
}

void mdbtoolscursor::returnColumnInfo() {

	// for each column...
	for (unsigned int i=0; i<((MdbSQL *)mdbsql)->num_columns; i++) {

		// get the column
		MdbSQLColumn	*col=(MdbSQLColumn *)
			g_ptr_array_index(((MdbSQL *)mdbsql)->columns,i);

		// send the column definition
		conn->sendColumnDefinition(col->name,
					charstring::length(col->name),
					UNKNOWN_DATATYPE,0,0,0,0,0,0,0,0,0,0,0);
	}
}

bool mdbtoolscursor::noRowsToReturn() {
	// if there were no columns then there can be no rows
	return (((MdbSQL *)mdbsql)->num_columns==0);
}

bool mdbtoolscursor::skipRow() {
	return fetchRow();
}

bool mdbtoolscursor::fetchRow() {
#ifdef HAVE_MDB_SQL_FETCH_ROW
	return mdb_sql_fetch_row((MdbSQL *)mdbsql,
				((MdbSQL *)mdbsql)->cur_table);
#else
	return mdb_fetch_row(((MdbSQL *)mdbsql)->cur_table);
#endif
}

void mdbtoolscursor::getField(uint32_t col,
				const char **field, uint64_t *fieldlength,
				bool *blob, bool *null) {

	// find the corresponding column in the current table
	MdbTableDef	*table=((MdbSQL *)mdbsql)->cur_table;
	MdbSQLColumn	*column=(MdbSQLColumn *)
			g_ptr_array_index(((MdbSQL *)mdbsql)->columns,col);

	for (unsigned int tcol=0; tcol<table->num_cols; tcol++) {
		MdbColumn	*tablecolumn=(MdbColumn *)
				g_ptr_array_index(table->columns,tcol);

			if (!charstring::compare(tablecolumn->name,
							column->name)) {
#ifdef HAVE_MDB_COL_TO_STRING_5_PARAM
			char	*data=mdb_col_to_string(
					((MdbSQL *)mdbsql)->mdb,
					((MdbSQL *)mdbsql)->mdb->pg_buf,
					tablecolumn->cur_value_start,
					tablecolumn->col_type,
					tablecolumn->cur_value_len);
#else
			char	*data=mdb_col_to_string(
					((MdbSQL *)mdbsql)->mdb,
					tablecolumn->cur_value_start,
					tablecolumn->col_type,
					tablecolumn->cur_value_len);
#endif
			if (data) {
				*field=data;
				*fieldlength=charstring::length(data);
			} else {
				*null=true;
			}
		}
	}
}

void mdbtoolscursor::cleanUpData(bool freeresult, bool freebinds) {
	delete[] columnnames;
	columnnames=NULL;
}
